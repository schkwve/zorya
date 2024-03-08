/*
 * @file handler.c
 * @author Kevin Alavik <kevin@alavik.se>
 * @date 02/03/2024
 * @brief Source file for handler.h, dumb fuck :^)
 */

#include "handler.h"
#include <core/browser.h>
#include <suzTK/window.h>

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
    char *t = fall_back_title;

    if (tree == NULL) {
        log_error("HTML tree is NULL");
        return;
    }

    struct parse_element *title = find_in_html_tree(tree, "title");

    if (title != NULL && title->content != NULL) {
        t = title->content;
    }

    log_debug("Setting title to '%s'", t);

    suzwin_set_title(window, t);
}
