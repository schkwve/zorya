/**
 * @file parse.c
 * @brief Implementation of HTML (2.0) parser functions.
 * @author Kevin Alavik <kevin@alavik.se>
 * @date 1/03/2024
 */

#include "parse.h"

char**
_split_lines(char* data);

node_t*
parse_html(const char* data, size_t size)
{
    node_t* root = malloc(sizeof(node_t));
    root->num_children = 0;
    root->children = NULL;
    root->element = NULL;
    log_debug("%u", size);
    char* ptr = (char*)data;
    node_t* node = root;

    // TODO: Fix this stupid shit... aka add loop protection orwhatever.
    while (1) {
        
        if (ptr > data + size) {
            break;
        }
        ptr = strchr(ptr, '<');

        if (ptr == NULL) {
            break;
        }
        struct node_t* newnode = malloc(sizeof(node_t));
        newnode->num_children = 0;
        newnode->children = NULL;
        newnode->element = malloc(sizeof(element_t));

        if (*(ptr + 1) == '/') {
            ptr++;
            newnode->element->closing = true;
        }else {
            newnode->element->closing = false;
        }

        char* closing = strchr(ptr, '>');
        char* space = strchr(ptr, ' ');
        log_debug("space %u closing %u", space, closing);
        if (closing < space || space == NULL) {
            newnode->element->name = malloc(closing - ptr);
            memcpy(newnode->element->name, ptr + 1, closing - ptr - 1);
            newnode->element->name[closing - ptr - 1] = '\0';
            ptr = closing + 1;
        } else {
            newnode->element->name = malloc(space - ptr);
            memcpy(newnode->element->name, ptr + 1, space - ptr - 1);
            newnode->element->name[space - ptr - 1] = '\0';
            ptr = space + 1;
        }
        log_debug("Found %s tag \"%s\" at idx %u",newnode->element->closing ? "closing" : "opening" , newnode->element->name, ptr - data);
        
        newnode->parent = node;
        if (node->num_children == 0) {
            node->children = malloc(sizeof(node_t*));
            node->num_children++;
            node->children[0] = newnode;
        } else {
            node->num_children++;
            node->children = realloc(node->children, sizeof(node_t*) * node->num_children);
            node->children[node->num_children - 1] = newnode;
        }
        if (newnode->element->closing) {
            //TODO: check if we are at the right closing tag
            node = node->parent;
        } else {

            node = newnode;
        }
        log_debug("added");
    }
    return root;
}

void free_html_tree(node_t* node)
{
    for (int i = 0; i < node->num_children && node->children != NULL; i++) {
        free_html_tree(node->children[i]);
    }
    free(node->children);
    if (node->element){
        free(node->element->name);
        free(node->element);
    }
    free(node);
}
