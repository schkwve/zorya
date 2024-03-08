/**
 * @file html/htmltree.h
 * @author Kevin Alavik <kevin@alavik.se>
 * @date 01/03/2024
 * @brief A parser for standard HTML 2.0
 */

#ifndef PARSE_H
#define PARSE_H

#include <stdbool.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>

#include <utils/logging.h>

struct parse_attribute
{
    char *name;
    char *value;
};

struct parse_element
{
    char *name;          // Opening tag name
    char *content;       // The content of the tag
    int attribute_count; // The ammount of attributes
    struct parse_attribute *
        attributes; // The list of attributes, Ex: { name: class, value: title }
};

struct parse_node
{
    struct parse_element *element;
    struct parse_node *parent;
    size_t num_children;
    struct parse_node **children;
};

struct parse_node *parse_html(const char *data, size_t size);

void free_html_tree(struct parse_node *root);

void print_html_tree(struct parse_node *root, int depth);

struct parse_element *find_in_html_tree(struct parse_node *node, char *name);

#endif /* PARSE_H */
