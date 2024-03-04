/*
 * @file handler.c
 * @author Kevin Alavik <kevin@alavik.se>
 * @date 02/03/2024
 * @brief Source file for handler.h, dumb fuck :^)
 */

#include "handler.h"
#include <suzTK/window.h>

/**
 * @brief Finds a tag in an HTML tree.
 *
 * @param node
 *        ???
 *
 * @param name
 *        Tag to be searched for
 *
 * @return Parsed element if it was found;
 *         NULL otherwise.
 */
static struct parse_element *find_in_html_tree(struct parse_node *node,
                                               char *name)
{
    if (node->element != NULL) {
        if (strcasecmp(node->element->name, name) == 0) {
            return node->element;
        }
    }

    for (int i = 0; i < node->num_children && node->children != NULL; i++) {
        struct parse_element *e = find_in_html_tree(node->children[i], name);
        if (e != NULL) {
            return e;
        }
    }

    return NULL;
}

/**
 * @brief Handles HTML tags.
 *
 * @param tree
 *        ???
 *
 * @param fall_back_title
 *        ???
 */
void handle_html(struct parse_node *tree, char *fall_back_title)
{
    char *t = "Untitled Page";

    if (tree == NULL) {
        log_error("HTML tree is NULL");
        return;
    }

    struct parse_element *title = find_in_html_tree(tree, "title");

    if (title != NULL && title->content != NULL) {
        t = title->content;
    } else {
        log_error("Title element not found, using url as title.");
        t = fall_back_title;
    }

    log_debug("Setting title to '%s'", t);

    // suzwin_set_title(full_title);
}
