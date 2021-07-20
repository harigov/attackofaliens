/*
 * File      : symex_list.c
 * Author    : Hariprasad Govardhanam [harigov AT gmail.com]
 * Purpose   : Implements functions declared in symex_list.h
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

/* Standard unclude files */
#include <stdio.h>
#include <stdlib.h>

/* User-Defined include files */
#include "symex_list.h"

/* functions related symex_list_t begin */

symex_list_t*
symex_list_create (void)
{
	symex_list_t* list;

	list = malloc (sizeof (symex_list_t));
	if (list == NULL)
		return NULL;

	list->fnode = NULL;
	list->cnode = NULL;

	return list;
}

void
symex_list_destroy (symex_list_t *list)
{
	if (list != NULL)
		free (list);
}

/* functions related to symex_list_t end */

/* functions related to symex_list_node_t begin */

symex_list_node_t*
symex_list_node_create (SYMEX_DATA_TYPE type, void *data, int length)
{
	symex_list_node_t* node;

	node = malloc (sizeof (symex_list_node_t));
	if (node == NULL)
		return NULL;

	node->type = type;
	node->data = data;
	node->length = length;
	node->next = NULL;
	node->prev = NULL;

	return node;
}

void
symex_list_node_destroy (symex_list_node_t* node)
{
	if (node != NULL)
	{
		free (node);
	}
}

/* functions related to symex_list_node_t end */

