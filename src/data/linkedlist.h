/**
 * Copyright (c) 2024 Zorya Browser
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
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
