/**
 * @file html/parse.h
 * @author Kevin Alavik <kevin@alavik.se>
 * @date 29/02/2024
 * @brief A parser for standard HTML 2.0
 */

#ifndef __PARSE_H__
#define __PARSE_H__

#include <stddef.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "../utils/logging.h"

/**
 * @brief Attribute struct for storing attribute info
 */

typedef struct Attribute
{
  char *name;                 // Name for attribute (in class="test") class is the name.
  char *value;                // Vale for attribute (in class="test") test is the value.
  struct Attribute *next;   // Pointer to the next attribute
} attribute_t;

/**
 * @brief Element struct for storing HTML element info
 */

typedef struct Element
{
  char *tag;                          // Tag is something like: h1.
  bool closing;                       // If true, it means that the tag is a closing one. </h1> is a closing one.
  char *content;                      // Content between two tags (in <h1>Hello</h1) Hello is the content. NULL if its something like a <meta>, <link>. Most of these ones have a closing tag in they self. Example: '<meta name="description" content="" />'.
  struct element_t *closing_element;  // Pointer to the closing element (in <h1></h1>) </h1> is the closing element. NULL if the element is self closing. <meta /> is one self closing element.
  attribute_t *attributes;     // Attributes. NULL If there is no attributes.
} element_t;

/**
 * @brief Node struct for element tree
 */

typedef struct
{
  element_t *element;    // Pointer to the element in the node
  struct node_t *parent; // The parent node
  struct node_t *child;  // The child node
} node_t;

/**
 * @brief
 *
 * @param data
 *        The raw HTML data (ASCII)
 *
 * @return An array of nodes
 */

node_t *parse_html(char *data);

#endif // __PARSE_H__
