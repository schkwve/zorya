/**
 * @file html/tree_utils.h
 * @author Kevin Alavik <kevin@alavik.se>
 * @date 1/03/2024
 * @brief A util lib for the HTML parser, see .h
 */

#include "tree_utils.h"

node_t*
_tree_pop(node_t* node)
{
    if (node == NULL) {
        return NULL;
    }

    node_t* parent = node->parent;
    if (parent != NULL) {
        if (parent->child == node) {
            parent->child = node->child;
        } else {
            node_t* sibling = parent->child;
            while (sibling->child != node) {
                sibling = sibling->child;
            }
            sibling->child = node->child;
        }
        if (node->child != NULL) {
            node->child->parent = parent;
        }
    }

    node->parent = NULL;
    node->child = NULL;

    return node;
}

void
_tree_push(node_t* parent, node_t* node)
{
    if (parent == NULL || node == NULL) {
        return;
    }

    node->parent = parent;
    node->child = parent->child;
    if (parent->child != NULL) {
        parent->child->parent = node;
    }
    parent->child = node;
}

node_t*
_tree_pop_at_index(node_t* parent, int index)
{
    if (parent == NULL || index < 0) {
        return NULL;
    }

    int count = 0;
    node_t* current = parent->child;
    node_t* prev = NULL;

    while (current != NULL) {
        if (count == index) {
            if (prev == NULL) {
                parent->child = current->child;
            } else {
                prev->child = current->child;
            }
            current->parent = NULL;
            current->child = NULL;
            return current;
        }
        prev = current;
        current = current->child;
        count++;
    }

    return NULL;
}
