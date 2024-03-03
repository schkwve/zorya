/**
 * @file parse.c
 * @brief Implementation of HTML (2.0) parser functions.
 * @author Kevin Alavik <kevin@alavik.se>
 * @date 1/03/2024
 */

#include "parse.h"
#include <stdio.h>
char**
_split_lines(char* data);

node_t*
parse_html(const char* data, size_t size)
{
    node_t* root = malloc(sizeof(node_t));
    root->num_children = 0;
    root->children = NULL;
    root->element = NULL;
    char* ptr = (char*)data;
    node_t* node = root;
    bool selfClosing = false;

    // TODO: Fix this stupid shit... aka add loop protection orwhatever.
    while (1) {
        //reset
        selfClosing = false;
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
        newnode->element->name = NULL;
        newnode->element->content = NULL;
        newnode->element->attribute_count = 0;
        newnode->element->attributes = NULL;

        if (*(ptr + 1) == '/') {
            free(newnode->element);
            free(newnode);

            char* closing = strchr(ptr, '>');
            char* space = strchr(ptr, ' ');
            if (closing < space || space == NULL) {
                ptr = closing + 1;
            } else {
                ptr = space + 1;
            }
            node = node->parent;
            continue;
        } else {
            char* closing = strchr(ptr, '>');
            char* space = strchr(ptr, ' ');

            if (*(closing-1) == '/') {
                selfClosing = true;
            }

            if (closing < space || space == NULL) {
                newnode->element->name = malloc(closing - ptr);
                memcpy(newnode->element->name, ptr + 1, closing - ptr - 1);
                newnode->element->name[closing - ptr - 1] = '\0';
                ptr = closing + 1;
            } else {
                newnode->element->name = malloc(space - ptr);
                memcpy(newnode->element->name, ptr + 1, space - ptr - 1);
                newnode->element->name[space - ptr - 1] = '\0';
                ptr = space;
                while (*(ptr) == ' ') {
                        ptr++;
                        char* equal = strchr(ptr, '=');
                        char* closing2 = strchr(ptr, '>');
                        char* space2 = strchr(ptr, ' ');
                        char* tmp = NULL;
                        if (closing2 < space2 || space == NULL) {
                            if (selfClosing) {
                                break; // ignor self closing slash
                            }

                            tmp = closing2;
                        } else {
                            tmp = space2;
                        }
                        if (equal > tmp || equal == NULL) {
                            //attribute has no value, add a null
                            struct attribute_t attr = {};
                            attr.name = malloc(tmp - ptr + 1);
                            memcpy(attr.name, ptr, tmp - ptr);
                            attr.value = NULL;
                            attr.name[tmp - ptr] = '\0';
                            newnode->element->attributes = realloc(newnode->element->attributes, sizeof(attribute_t) * (newnode->element->attribute_count + 1));
                            newnode->element->attributes[newnode->element->attribute_count] = attr;
                            newnode->element->attribute_count++;
                            ptr = tmp;
                            continue;
                        }
                        struct attribute_t attr = {};
                        attr.name = malloc(equal - ptr + 1);
                        char* openqoute = strchr(ptr, '"');
                        char* closeqoute = strchr(openqoute+1, '"');
                        attr.value = malloc(closeqoute - openqoute);
                        memcpy(attr.name, ptr, equal - ptr);
                        memcpy(attr.value, openqoute + 1, closeqoute - openqoute - 1);
                        attr.name[equal - ptr] = '\0';
                        attr.value[closeqoute - openqoute - 1] = '\0';
                        newnode->element->attributes = realloc(newnode->element->attributes, sizeof(attribute_t) * (newnode->element->attribute_count + 1));
                        newnode->element->attributes[newnode->element->attribute_count] = attr;
                        newnode->element->attribute_count++;
                        ptr = closeqoute+1;
                }
                ptr = strchr(ptr, '>')+1;
                
            }


            char* opening = strchr(ptr, '<');
            if(*(opening + 1) == '/' && !selfClosing) {
                newnode->element->content = malloc(opening - ptr + 1);
                memcpy(newnode->element->content, ptr, opening - ptr);
                newnode->element->content[opening - ptr] = '\0';
            }

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
        }
        if (!selfClosing) {
            node = newnode;
        }
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
        for (int i = 0; i < node->element->attribute_count; i++) {
            free(node->element->attributes[i].name);
            free(node->element->attributes[i].value);
        }
        if (node->element->attributes != NULL)
            free(node->element->attributes);
        free(node->element->name);
        if (node->element->content != NULL)
            free(node->element->content);
        free(node->element);
    }
    free(node);
}

void print_html_tree(node_t* node,int lvl){
    if (node->element != NULL) {
        if(node->element->name != NULL) {
            for (int i = 0; i < lvl; i++) {
                printf(" ");
            }
            printf("%s", node->element->name);
            for (int i = 0; i < node->element->attribute_count; i++) {
                printf(" %s=\"%s\"", node->element->attributes[i].name, node->element->attributes[i].value);
            }
            if (node->element->content != NULL) {
                printf(" __CONTENT__= \"%s\"", node->element->content, node->element->name);
            }
            printf("\n");
        }
    }
    for (int i = 0; i < node->num_children && node->children != NULL; i++) {
        print_html_tree(node->children[i],lvl+1);
    }
}
