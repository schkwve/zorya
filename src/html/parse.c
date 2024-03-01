/**
 * @file parse.c
 * @brief Implementation of HTML (2.0) parser functions.
 * @author Kevin Alavik <kevin@alavik.se>
 * @date 29/02/2024
 */

#include "parse.h"

char **_split_lines(char *data);
element_t *_parse_element_from_line(char *line);
node_t *_construct_node_tree(element_t *elements, int element_count);

element_t *_parse_element_from_line(char *line)
{
	char ch;
	element_t *element = malloc(sizeof(element_t));
	if (element == NULL)
	{
		log_fatal("Memory allocation failed!");
		return NULL;
	}

	int i;
	for (i = 0; (ch = line[i]) != '\0'; i++)
	{
		if (ch == '<')
		{
			int start = i + 1;
			int end = start;
			while (line[end] != ' ' && line[end] != '>' && line[end] != '\0')
			{
				end++;
			}
			element->tag = malloc((end - start + 1) * sizeof(char));
			if (element->tag == NULL)
			{
				log_fatal("Memory allocation failed!");
				free(element);
				return NULL;
			}
			strncpy(element->tag, line + start, end - start);
			element->tag[end - start] = '\0';

			if (element->tag[0] == '/')
			{
				element->closing = true;
				memmove(element->tag, element->tag + 1, strlen(element->tag));
			}
			else
			{
				element->closing = false;
			}

			log_debug("Found tag: %s", element->tag);

			element->attributes = NULL;
			attribute_t *last_attribute = NULL;

			int attr_start = end;
			while (line[attr_start] != '>' && line[attr_start] != '\0')
			{
				if (line[attr_start] == ' ' || line[attr_start] == '=')
				{
					attr_start++;
					int attr_end = attr_start;
					while (line[attr_end] != ' ' && line[attr_end] != '=' && line[attr_end] != '>' && line[attr_end] != '\0')
					{
						attr_end++;
					}
					char *attribute_name_temp = malloc((attr_end - attr_start + 1) * sizeof(char));
					if (attribute_name_temp == NULL)
					{
						log_fatal("Memory allocation failed!");
						free(element->tag);
						free(element);
						return NULL;
					}
					strncpy(attribute_name_temp, line + attr_start, attr_end - attr_start);
					attribute_name_temp[attr_end - attr_start] = '\0';

					log_debug("Found attribute: %s", attribute_name_temp);

					attribute_t *new_attribute = malloc(sizeof(attribute_t));
					if (new_attribute == NULL)
					{
						log_fatal("Memory allocation failed!");
						free(attribute_name_temp);
						free(element->tag);
						free(element);
						return NULL;
					}

					new_attribute->name = attribute_name_temp;
					new_attribute->value = NULL;
					new_attribute->next = NULL;

					if (last_attribute != NULL)
					{
						last_attribute->next = new_attribute;
					}
					else
					{
						element->attributes = new_attribute;
					}
					last_attribute = new_attribute;

					attr_start = attr_end;
					if (line[attr_start] == '=')
					{
						attr_start++;
						while (line[attr_start] == ' ' && line[attr_start] != '\0')
						{
							attr_start++;
						}
						if (line[attr_start] == '"')
						{
							attr_start++;
							int attr_value_start = attr_start;
							while (line[attr_start] != '"' && line[attr_start] != '\0')
							{
								attr_start++;
							}
							char *attribute_value_temp = malloc((attr_start - attr_value_start + 1) * sizeof(char));
							if (attribute_value_temp == NULL)
							{
								log_fatal("Memory allocation failed!");
								free(attribute_name_temp);
								free(element->tag);
								free(element);
								return NULL;
							}
							strncpy(attribute_value_temp, line + attr_value_start, attr_start - attr_value_start);
							attribute_value_temp[attr_start - attr_value_start] = '\0';

							log_debug("Found attribute value: %s", attribute_value_temp);

							new_attribute->value = attribute_value_temp;
						}
					}
					attr_start = attr_end;
				}
				else
				{
					attr_start++;
				}
			}

			i = end;
		}
	}
	return element;
}

/**
 * @brief Parse HTML data and construct a parse tree.
 *
 * This function parses the input HTML data and constructs a parse tree.
 * The parse tree represents the structure of the HTML document.
 *
 * @param data The input string containing HTML data.
 * @return A pointer to the root node of the parse tree.
 *         If parsing fails or the input is empty, NULL is returned.
 */
node_t *parse_html(char *data)
{
	char **lines = _split_lines(data);
	element_t **elements = NULL;
	int element_count = 0;

	for (int i = 0; lines[i] != NULL; i++)
	{
		element_t *element = _parse_element_from_line(lines[i]);
		if (element != NULL)
		{
			elements = realloc(elements, sizeof(element_t *) * (element_count + 1));
			if (elements == NULL)
			{
				log_fatal("Memory allocation failed");
				exit(EXIT_FAILURE);
			}
			elements[element_count++] = element;
		}
	}

	for (int i = 0; lines[i] != NULL; i++)
	{
		free(lines[i]);
	}
	free(lines);

	node_t *root = NULL;
	if (element_count > 0)
	{
		// root = _construct_node_tree(*elements, element_count);
		for (int i = 0; i < element_count; i++)
		{
			element_t curElement = *elements[i];
			log_info("Found element! Tag: %s", curElement.tag);
			log_info("Attributes:");
			attribute_t *curAttr = curElement.attributes;
			while (curAttr != NULL)
			{
				log_info(" - %s: %s", curAttr->name, curAttr->value);
				curAttr = curAttr->next;
			}
		}
	}

	for (int i = 0; i < element_count; i++)
	{
		free(elements[i]);
	}
	free(elements);

	return root;
}

char **_split_lines(char *data)
{
	char **lines = NULL;
	int num_lines = 0;
	char *line = strtok(data, "\n");
	while (line != NULL)
	{
		lines = realloc(lines, (num_lines + 1) * sizeof(char *));
		if (lines == NULL)
		{
			log_fatal("Memory allocation failed");
			exit(EXIT_FAILURE);
		}

		char *non_space_ptr = line;
		while (*non_space_ptr == ' ')
		{
			non_space_ptr++;
		}

		lines[num_lines] = strdup(non_space_ptr);
		if (lines[num_lines] == NULL)
		{
			log_fatal("Memory allocation failed");
			exit(EXIT_FAILURE);
		}

		num_lines++;
		line = strtok(NULL, "\n");
	}

	lines = realloc(lines, (num_lines + 1) * sizeof(char *));
	if (lines == NULL)
	{
		log_fatal("Memory allocation failed");
		exit(EXIT_FAILURE);
	}
	lines[num_lines] = NULL;
	return lines;
}

// TODO: Make this actually construct the node tree :)
node_t *_construct_node_tree(element_t *elements, int element_count)
{
	for (int i = 0; i < element_count; i++)
	{
		element_t curElement = elements[i];
		log_info("Found element! Tag: %s", curElement.tag);
		log_info("Attributes:");
		attribute_t *curAttr = curElement.attributes;
		while (curAttr != NULL)
		{

			if (!curElement.closing)
			{

				log_info(" - %s: %s", curAttr->name, curAttr->value);
			}

			curAttr = curAttr->next;
		}
	}
	node_t *tree = NULL;
	return tree;
}
