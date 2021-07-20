/*
 * File      : dlist.h
 * Author    : Hariprasad Govardhanam [harigov AT gmail.com]
 * Purpose   : Defines functions for doubly linked list.
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

#ifndef __DLIST_H__
#define __DLIST_H__

struct tagDListNode
{
	void *data;
	struct tagDListNode* next;
	struct tagDListNode* prev;
};

typedef struct tagDListNode DLISTNODE;

struct tagDList
{
	int count;
	DLISTNODE* fnode, *cnode, *snode;
};

typedef struct tagDList DLIST;

DLIST*	create_dlist (void);
void	destroy_dlist (DLIST*);

void	insert_item_dlist (DLIST* list, void *item);
void*	remove_item_dlist (DLIST* list, void *item);

void*	first_item_dlist (DLIST* list);
void*	next_item_dlist (DLIST* list);
void*	prev_item_dlist (DLIST* list);

void	save_item_position_dlist (DLIST* list);
void	restore_item_position_dlist (DLIST* list);

#endif /* __DLIST_H__ */

