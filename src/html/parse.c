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
        printf("Memory allocation failed!\n");
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
                log_fatal("Memory allocation failed!\n");
                free(element);
                return NULL;
            }
            strncpy(element->tag, line + start, end - start);
            element->tag[end - start] = '\0';

            log_debug("Found tag: %s", element->tag);

            if (element->tag[0] == '/')
            {
                element->closing = true;
            }
            else
            {
                element->closing = false;
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
                perror("Memory allocation failed");
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
        root = _construct_node_tree(*elements, element_count);
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
    (void)elements;
    (void)element_count;

    node_t *tree;
    return tree;
}