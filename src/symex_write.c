/*
 * File      : symex_write.c
 * Author    : Hariprasad Govardhanam [harigov AT gmail.com]
 * Purpose   : Implements functions used to write data stored
 *						 in lists to file in s-expression form.
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

#include "symex_write.h"

void
symex_print_to_file (symex_list_node_t*node, FILE* fp)
{
	while (node != NULL)
	{
		if (node->type == SYMEX_BYTES)
		{
			fprintf (fp, " %d:", node->length);
			fwrite (node->data, 1, node->length, fp);
			fprintf (fp, " ");
		}
		else if (node->type == SYMEX_LIST)
		{
			fprintf (fp, "(");
			symex_print_to_file (node->data, fp);
			fprintf (fp, ")");
		}
		node = node->next;
	}
}

int
symex_write_to_file (symex_list_t *list, const char* filename)
{
	FILE* fp;

	fp = fopen (filename, "w");
	if (fp == NULL)
		return -1;

	symex_print_to_file (list->fnode, fp);

	return 0;
}

