/**
 * @file data/linkedlist.h
 * @author Jozef Nagy <schkwve@gmail.com>
 * @date 09/03/2024
 * @brief Linked List implementation
 */

#ifndef DATA_LINKEDLIST_H
#define DATA_LINKEDLIST_H

/**
 * @brief Singly linked list node
 */
struct ll_node
{
    void *data;
    struct ll_node *next;
};

/**
 * @brief Singly linked list
 */
struct linkedlist
{
    struct ll_node *head;
};

struct linkedlist *ll_create_list(void);

void ll_append(struct linkedlist *list, void *data);
void ll_remove(struct linkedlist *list, void *data);

void ll_destroy(struct linkedlist *list);

#endif /* DATA_LINKEDLIST_H  */
