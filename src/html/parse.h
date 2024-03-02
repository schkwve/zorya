/**
 * @file html/parse.h
 * @author Kevin Alavik <kevin@alavik.se>
 * @date 01/03/2024
 * @brief A parser for standard HTML 2.0
 */

#ifndef __PARSE_H__
#define __PARSE_H__

#include "../utils/logging.h"
#include <stdbool.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>

struct attribute_t;
struct element_t;

typedef struct attribute_t
{
    char* name;
    char* value;
} attribute_t;

typedef struct element_t
{
    char* name;          // Opening tag name
    bool closing;        // True if its a closing tag
    int attribute_count; // The ammount of attributes
    attribute_t*
        attributes; // The list of attributes, Ex: { name: class, value: title }
} element_t;

typedef struct node_t {
    element_t* element;
    struct node_t* parent;
    size_t num_children;
    struct node_t** children;
} node_t;

node_t*
parse_html(const char* data, size_t size);

void 
free_html_tree(node_t* root);

#endif // __PARSE_H__
