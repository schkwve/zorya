/**
 * @file html/html_handler.h
 * @author Kevin Alavik <kevin@alavik.se>
 * @date 1/03/2024
 * @brief A library to handle the HTML thats been parsed from the parser.
 */

#ifndef __HTML_HANDLER_H__
#define __HTML_HANDLER_H__

#include "parse.h"

int
render_html(node_t* element_tree);

#endif // __HTML_HANDLER_H__
