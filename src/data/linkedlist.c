/**
 * @file data/linkedlist.c
 * @author Jozef Nagy <schkwve@gmail.com>
 * @date 09/03/2024
 * @brief Linked List implementation
 */

#include <stdlib.h>

#include "linkedlist.h"

/**
 * @brief Creates a new node in a singly linked list.
 *
 * @param data
 *        Data pointer which will be inserted to the new node
 *
 * @return Pointer to the new node.
 */
static struct ll_node *create_node(void *data)
{
    struct ll_node *new = malloc(sizeof(struct ll_node));
    if (!new) {
        return NULL;
    }

    new->data = data;
    new->next = NULL;
    return new;
}

/**
 * @brief Creates a new singly linked list.
 *
 * @return Newly created list.
 */
struct linkedlist *ll_create_list(void)
{
    struct linkedlist *new = malloc(sizeof(struct linkedlist));
    if (new == NULL) {
        return NULL;
    }

    new->head = NULL;
    return new;
}

/**
 * @brief Appends data to the end of a linked list.
 *
 * @param list
 *        Pointer to a list which will be modified
 *
 * @param data
 *        Pointer to data which will be appended to the list
 */
void ll_append_entry(struct linkedlist *list, void *data)
{
    if (list->head == NULL) {
        list->head = create_node(data);
        return;
    }

    struct ll_node *cur = list->head;
    while (cur->next != NULL) {
        cur = cur->next;
    }

    cur->next = create_node(data);
}

/**
 * @brief Removes data from a linked list.
 *
 * @param list
 *        Pointer to a list which will be modified
 *
 * @param data
 *        Pointer to data which will be removed from the list
 */
void ll_remove_entry(struct linkedlist *list, void *data)
{
    struct ll_node *cur = list->head;
    struct ll_node *prev = cur;

    while (cur != NULL) {
        if (cur->data == data) {
            prev->next = cur->next;
            if (cur == list->head) {
                list->head = cur->next;
            }
            free(cur);
            return;
        }
        prev = cur;
        cur = cur->next;
    }
}

/**
 * @brief Destroys a singly linked list.
 *
 * @param list
 *        Linked list which should be freed.
 */
void ll_destroy(struct linkedlist *list)
{
    struct ll_node *cur = list->head;
    struct ll_node *next = cur;

    while (cur != NULL) {
        next = cur->next;
        free(cur);
        cur = next;
    }

    free(list);
}
