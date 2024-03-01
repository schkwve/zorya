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
void _add_attribute(element_t *element, char *name, char *value);

element_t *_parse_element_from_line(char *line)
{
	char ch;
	element_t *element = malloc(sizeof(element_t));
	if (element == NULL)
	{
		log_fatal("Memory allocation failed!");
		return NULL;
	}

	int i = 0;
	while ((ch = line[i]) != '\0')
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

			element->attributes = NULL;

			while (line[end] != '>' && line[end] != '\0')
			{
				while (line[end] == ' ')
				{
					end++;
				}

				int attr_start = end;
				while (line[end] != '=' && line[end] != ' ' && line[end] != '>' && line[end] != '\0')
				{
					end++;
				}
				char *attribute_name = malloc((end - attr_start + 1) * sizeof(char));
				if (attribute_name == NULL)
				{
					log_fatal("Memory allocation failed!");
					free(element->tag);
					free(element);
					return NULL;
				}
				strncpy(attribute_name, line + attr_start, end - attr_start);
				attribute_name[end - attr_start] = '\0';

				if (line[end] == '=')
				{
					end++;
					while (line[end] == ' ')
					{
						end++;
					}
					char quote = line[end];
					if (quote == '\'' || quote == '\"')
					{
						end++;
						int attr_value_start = end;
						while (line[end] != quote && line[end] != '\0')
						{
							end++;
						}
						char *attribute_value = malloc((end - attr_value_start + 1) * sizeof(char));
						if (attribute_value == NULL)
						{
							log_fatal("Memory allocation failed!");
							free(attribute_name);
							free(element->tag);
							free(element);
							return NULL;
						}
						strncpy(attribute_value, line + attr_value_start, end - attr_value_start);
						attribute_value[end - attr_value_start] = '\0';
						end++;
						_add_attribute(element, attribute_name, attribute_value);
						free(attribute_value);
					}
					else
					{
						int attr_value_start = end;
						while (line[end] != ' ' && line[end] != '>' && line[end] != '\0')
						{
							end++;
						}
						char *attribute_value = malloc((end - attr_value_start + 1) * sizeof(char));
						if (attribute_value == NULL)
						{
							log_fatal("Memory allocation failed!");
							free(attribute_name);
							free(element->tag);
							free(element);
							return NULL;
						}
						strncpy(attribute_value, line + attr_value_start, end - attr_value_start);
						attribute_value[end - attr_value_start] = '\0';
						_add_attribute(element, attribute_name, attribute_value);
						free(attribute_value);
					}
				}
				else
				{
					_add_attribute(element, attribute_name, NULL);
				}
				free(attribute_name);
			}

			i = end;
		}
		else
		{
			i++;
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

void _add_attribute(element_t *element, char *name, char *value)
{
	attribute_t *new_attribute = malloc(sizeof(attribute_t));
	if (new_attribute == NULL)
	{
		log_fatal("Memory allocation failed!");
		exit(EXIT_FAILURE);
	}
	new_attribute->name = strdup(name);
	if (new_attribute->name == NULL)
	{
		log_fatal("Memory allocation failed!");
		free(new_attribute);
		exit(EXIT_FAILURE);
	}
	if (value != NULL)
	{
		new_attribute->value = strdup(value);
		if (new_attribute->value == NULL)
		{
			log_fatal("Memory allocation failed!");
			free(new_attribute->name);
			free(new_attribute);
			exit(EXIT_FAILURE);
		}
	}
	else
	{
		new_attribute->value = NULL;
	}
	new_attribute->next = NULL;

	if (element->attributes == NULL)
	{
		element->attributes = new_attribute;
	}
	else
	{
		attribute_t *current = element->attributes;
		while (current->next != NULL)
		{
			current = current->next;
		}
		current->next = new_attribute;
	}
}
