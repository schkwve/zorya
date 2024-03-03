/*
 * @file handler.c
 * @brief Source file for handler.h, dumb fuck :^)
 * @author Kevin Alavik <kevin@alavik.se>
 * @date 2/03/2024
 */

#include "handler.h"
#include "../main.h"
#include "../suzTK/window.h"

element_t* _find_in_html_tree(node_t* node, char* name);

void handle_html(node_t* tree, char* fall_back_title) {
    char* t = "Untitled Page";

    if (tree == NULL) {
        log_error("HTML tree is NULL");
        return;
    }

    element_t* title = _find_in_html_tree(tree, "title");

    if (title != NULL && title->content != NULL) {
        t = title->content;
    } else {
        log_error("Title element not found, using url as title.");
        t = fall_back_title;
    }

    log_debug("Setting title to '%s'", t);

    suzwin_set_title(t);
}

element_t* _find_in_html_tree(node_t* node, char* name) {
  if (node->element != NULL) {
    if (strcasecmp(node->element->name, name) == 0) {
      return node->element;
    }
  }

  for (int i = 0; i < node->num_children && node->children != NULL; i++) {
    element_t* e = _find_in_html_tree(node->children[i], name);
    if (e != NULL) {
      return e;
    }
  }

  return NULL;
}

