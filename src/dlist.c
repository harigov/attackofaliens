/*
 * File      : dlist.c
 * Author    : Hariprasad Govardhanam [harigov AT gmail.com]
 * Purpose   : Implements the code for doubly linked list.
 * Comments  :
 * License   : 
 * 
 * Attack of Aliens
 * Copyright (C) 2007 Hariprasad Govardhanam [harigov AT gmail.com]
 *
 * This program is free software; you can redistribute it 
 * and/or modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 2
 * of the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.
 */

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#include "game.h"
#include "dlist.h"

DLIST*
create_dlist (void)
{
	DLIST* list = malloc (sizeof (DLIST));
	check_error (list == NULL, "Memory allocation failed");

	list->fnode = NULL;
	list->cnode = NULL;
	list->snode = NULL;
	list->count = 0;

	return list;
}

void
destroy_dlist (DLIST* list)
{
	DLISTNODE* temp, *node;

	assert (list != NULL);

	node = list->fnode;
	while (node != NULL)
	{
		temp = node->next;
		free (node);
		node = temp;
	}

	free (list);
}

void
insert_item_dlist (DLIST* list, void *item)
{
	DLISTNODE* node;

	assert (list != NULL);

	node = malloc (sizeof (DLISTNODE));
	check_error (node == NULL, "Memory allocation failed");

	node->data = item;
	node->prev = NULL;
	node->next = list->fnode;

	if (list->fnode != NULL)
		list->fnode->prev = node;

	list->fnode = node;
	list->count++;
}

void*
remove_item_dlist (DLIST* list, void *item)
{
	DLISTNODE* node;

	assert (list != NULL);
	assert (item != NULL);

	node = list->fnode;
	while (node != NULL)
	{
		if (node->data == item)
		{
      if (node == list->cnode)
      {
        list->cnode = node->next;
      }

			if (node->prev != NULL)
				node->prev->next = node->next;
			else /* node is fnode */
				list->fnode = node->next;

			if (node->next != NULL)
				node->next->prev = node->prev;

			free (node);
			list->count--;
			return item;
		}
		node = node->next;
	}

	return NULL;
}

void*
first_item_dlist (DLIST* list)
{
	assert (list != NULL);

	list->cnode = list->fnode;

	if (list->fnode != NULL)
		return list->fnode->data;
	else
		return NULL;
}

void*
next_item_dlist (DLIST* list)
{
	assert (list != NULL);

	/* don't mix these two if conditions */
	if (list->cnode != NULL)
		list->cnode = list->cnode->next;

	if (list->cnode != NULL)
		return list->cnode->data;
	else
		return NULL;
}

void*
prev_item_dlist (DLIST* list)
{
	assert (list != NULL);

	/* don't mix these two if conditions */
	if (list->cnode != NULL)	
		list->cnode = list->cnode->prev;

	if (list->cnode != NULL)
		return list->cnode->data;
	else
		return NULL;
}

void
save_item_position_dlist (DLIST* list)
{
	list->snode = list->cnode;
}

void
restore_item_position_dlist (DLIST* list)
{
	list->cnode = list->snode;
}

