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
#include <stdlib.h>
#include "../log/logging.h"

/**
* @breif This contains all possible element types
*/

enum ElementType { 
  REGULAR_ELEMENT, 
  CLOSING_ELEMENT, 
  DTD_ELEMENT
};

/**
 * @brief This contains all information about a element attribute.
 */

typedef struct {
  char *name;
  char *content;
  attribute_t *next;
} attribute_t

/**
 * @brief This contains all information about a element.
 */

typedef struct {
  char *tag;
  attribute_t *attributes;
  char *content_until_new_tag;
  element_t *next;
  int id;
  enum ElementType type;
  bool hasClosingTag;
} element_t

element_t* parse_html(char* rawData, size_t size);

#endif // __PARSE_H__
