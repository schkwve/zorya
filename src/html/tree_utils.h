/**
 * @file html/tree_utils.h
 * @author Kevin Alavik <kevin@alavik.se>, KapPetrov
 * <xicreationsofficial@gmail.com>
 * @date 1/03/2024
 * @brief A util lib for the HTML tree structure
 */

#ifndef __TREE_UTILS_H__
#define __TREE_UTILS_H__

#include "parse.h"

node_t*
_tree_pop(node_t* node);
void
_tree_push(node_t* parent, node_t* node);
node_t*
_tree_pop_at_index(node_t* parent, int index);

#endif // __TREE_UTILS_H__
