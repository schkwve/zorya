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
    log_debug("%u", size);
    char* ptr = (char*)data;

    // TODO: Fix this stupid shit... aka add loop protection orwhatever.
    while (1) {
        
        if (ptr > data + size) {
            break;
        }
        ptr = strchr(ptr, '<');

        if (ptr == NULL) {
            break;
        }

        node_t* node = malloc(sizeof(node_t));
        node->element = malloc(sizeof(element_t));

        if (*(ptr + 1) == '/') {
            ptr++;
            element->closing = true;
        }else {
            element->closing = false;
        }

        char* closing = strchr(ptr, '>');
        char* space = strchr(ptr, ' ');
        if (closing < space) {
            element->name = malloc(closing - ptr);
            memcpy(element->name, ptr + 1, closing - ptr - 1);
            element->name[closing - ptr - 1] = '\0';
            ptr = closing + 1;
        } else {
            element->name = malloc(space - ptr);
            memcpy(element->name, ptr + 1, space - ptr - 1);
            element->name[space - ptr - 1] = '\0';
            ptr = space + 1;
        }


        log_debug("Found %s tag \"%s\" at idx %u",element->closing ? "closing" : "opening" , element->name, ptr - data);
        
    }

    return NULL;
}
