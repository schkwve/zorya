/**
 * @file handler.h
 * @author Kevin Alavik <kevin@alavik.se>
 * @date 02/03/2024
 * @brief Impelementation of the HTML hander
 */

#ifndef HANDLER_H
#define HANDLER_H

#include "parse.h"
#include <utils/logging.h>

struct parse_element
*find_in_html_tree(struct parse_node *node, char *name);
void
handle_html(struct parse_node *tree, char *fall_back_title);

#endif /* HANDLER_H */
