/**
 * @file parse.c
 * @author Kevin Alavik <kevin@alavik.se>
 * @date 01/03/2024
 * @brief Implementation of HTML (2.0) parser functions.
 */

#include <stdio.h>

#include "htmltree.h"

/**
 * @brief Parses an HTML file.
 *
 * @param data
 *        HTML file's contents.
 *
 * @param size
 *        Size of the HTML file.
 *
 * @return ???
 */
struct parse_node *parse_html(const char *data, size_t size)
{
    struct parse_node *root = malloc(sizeof(struct parse_node));
    root->num_children = 0;
    root->children = NULL;
    root->element = NULL;
    char *ptr = (char *)data;
    struct parse_node *node = root;
    bool selfClosing = false;

    // TODO: Fix this stupid shit... aka add loop protection orwhatever.
    while (1) {
        // reset
        selfClosing = false;
        if (ptr > data + size) {
            break;
        }
        ptr = strchr(ptr, '<');

        if (ptr == NULL) {
            break;
        }
        struct parse_node *newnode = malloc(sizeof(struct parse_node));
        newnode->num_children = 0;
        newnode->children = NULL;
        newnode->element = malloc(sizeof(struct parse_element));
        newnode->element->name = NULL;
        newnode->element->content = NULL;
        newnode->element->attribute_count = 0;
        newnode->element->attributes = NULL;

        if (*(ptr + 1) == '/') {
            free(newnode->element);
            free(newnode);

            char *closing = strchr(ptr, '>');
            char *space = strchr(ptr, ' ');
            if (closing < space || space == NULL) {
                ptr = closing + 1;
            } else {
                ptr = space + 1;
            }
            node = node->parent;
            continue;
        } else {
            char *closing = strchr(ptr, '>');
            char *space = strchr(ptr, ' ');

            if (*(closing - 1) == '/') {
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
                    char *equal = strchr(ptr, '=');
                    char *closing2 = strchr(ptr, '>');
                    char *space2 = strchr(ptr, ' ');
                    char *tmp = NULL;
                    if (closing2 < space2 || space == NULL) {
                        if (selfClosing) {
                            break; // ignor self closing slash
                        }

                        tmp = closing2;
                    } else {
                        tmp = space2;
                    }
                    if (equal > tmp || equal == NULL) {
                        if (ptr > tmp || tmp == NULL) {
                            continue;
                        }
                        // attribute has no value, add a null
                        struct parse_attribute attr = {};
                        attr.name = malloc(tmp - ptr + 1);
                        memcpy(attr.name, ptr, tmp - ptr);
                        attr.value = NULL;
                        attr.name[tmp - ptr] = '\0';
                        newnode->element->attributes = realloc(
                            newnode->element->attributes,
                            sizeof(struct parse_attribute) *
                                (newnode->element->attribute_count + 1));
                        newnode->element
                            ->attributes[newnode->element->attribute_count] =
                            attr;
                        newnode->element->attribute_count++;
                        ptr = tmp;
                        continue;
                    }
                    struct parse_attribute attr = {};
                    attr.name = malloc(equal - ptr + 1);
                    char *openqoute = strchr(ptr, '"');
                    char *closeqoute = strchr(openqoute + 1, '"');
                    attr.value = malloc(closeqoute - openqoute);
                    memcpy(attr.name, ptr, equal - ptr);
                    memcpy(
                        attr.value, openqoute + 1, closeqoute - openqoute - 1);
                    attr.name[equal - ptr] = '\0';
                    attr.value[closeqoute - openqoute - 1] = '\0';
                    newnode->element->attributes =
                        realloc(newnode->element->attributes,
                                sizeof(struct parse_attribute) *
                                    (newnode->element->attribute_count + 1));
                    newnode->element
                        ->attributes[newnode->element->attribute_count] = attr;
                    newnode->element->attribute_count++;
                    ptr = closeqoute + 1;
                }
                ptr = strchr(ptr, '>') + 1;
            }

            char *opening = strchr(ptr, '<');
            if (*(opening + 1) == '/' && !selfClosing) {
                newnode->element->content = malloc(opening - ptr + 1);
                memcpy(newnode->element->content, ptr, opening - ptr);
                newnode->element->content[opening - ptr] = '\0';
            }

            newnode->parent = node;
            if (node->num_children == 0) {
                node->children = malloc(sizeof(struct parse_node *));
                node->num_children++;
                node->children[0] = newnode;
            } else {
                node->num_children++;
                node->children =
                    realloc(node->children,
                            sizeof(struct parse_node *) * node->num_children);
                node->children[node->num_children - 1] = newnode;
            }
        }
        if (!selfClosing) {
            node = newnode;
        }
    }
    return root;
}

/**
 * @brief Destroys an HTML tree.
 *
 * @param node
 *        ???
 */
void free_html_tree(struct parse_node *node)
{
    for (int i = 0; i < node->num_children && node->children != NULL; i++) {
        free_html_tree(node->children[i]);
    }
    free(node->children);
    if (node->element) {
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

/**
 * @brief Prints an HTML tree.
 *
 * @param node
 *        ???
 *
 * @param lvl
 *        ???
 */
void print_html_tree(struct parse_node *node, int lvl)
{
    if (node->element != NULL) {
        if (node->element->name != NULL) {
            for (int i = 0; i < lvl; i++) {
                printf(" ");
            }
            printf("%s", node->element->name);
            for (int i = 0; i < node->element->attribute_count; i++) {
                printf(" %s=\"%s\"",
                       node->element->attributes[i].name,
                       node->element->attributes[i].value);
            }
            if (node->element->content != NULL) {
                printf(" __CONTENT__= \"%s\"", node->element->content);
            }
            printf("\n");
        }
    }
    for (int i = 0; i < node->num_children && node->children != NULL; i++) {
        print_html_tree(node->children[i], lvl + 1);
    }
}

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
struct parse_node *find_in_html_tree(struct parse_node *node, char *name)
{
    if (node->element != NULL) {
        if (strcasecmp(node->element->name, name) == 0) {
            return node;
        }
    }

    for (int i = 0; i < node->num_children && node->children != NULL; i++) {
        struct parse_node *n = find_in_html_tree(node->children[i], name);
        if (n != NULL) {
            return n;
        }
    }

    return NULL;
}