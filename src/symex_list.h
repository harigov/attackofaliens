/*
 * File      : symex_list.h
 * Author    : Hariprasad Govardhanam [harigov AT gmail.com]
 * Purpose   : Header file for list structure used to store
 *						 parsed s-expressions.
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

#ifndef __SYMEX_LIST_H__
#define __SYMEX_LIST_H__

typedef enum { SYMEX_NONE, SYMEX_LIST, SYMEX_BYTES } SYMEX_DATA_TYPE;

struct symex_list_node_t
{
	SYMEX_DATA_TYPE type;
	void *data;
	int length;
	struct symex_list_node_t *prev, *next;
};
typedef struct symex_list_node_t symex_list_node_t;

struct symex_list_t
{
	symex_list_node_t *fnode, *cnode;
};
typedef struct symex_list_t symex_list_t;

/* functions operating on symex_list_t */
symex_list_t*	symex_list_create 	(void);
void			symex_list_destroy 	(symex_list_t*);

/* functions operating on symex_list_node_t */
symex_list_node_t*	symex_list_node_create 	(
								SYMEX_DATA_TYPE type, 
								void *data,
								int length
								);
void				symex_list_node_destroy (symex_list_node_t*);

#endif /* __SYMEX_LIST_H__ */

