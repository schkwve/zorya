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
#include "../log/logging.h"

/**
 * @brief Stores the info about an attribute
*/

typedef struct attribute {
  char *name;
  char *content;
  struct attribute *next;
} attribute_t;

/**
 * @brief Stores the info about a element.
*/

typedef struct element {
  char *tag;
  attribute_t *attributes;
  char *content_until_new_tag;
  struct element *next;
  int id;
  enum ElementType {
    REGULAR_ELEMENT, 
    CLOSING_ELEMENT, 
    DTD_ELEMENT
  } type;
  bool hasClosingTag;
} element_t;


/**
 * @brief Function to actually parse the HTML into a list of elements
*/
element_t* parse_html(char* rawData, size_t size);

#endif // __PARSE_H__