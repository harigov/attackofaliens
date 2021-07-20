/*
 * File      : symex_parse.h
 * Author    : Hariprasad Govardhanam [harigov AT gmail.com]
 * Purpose   : Header file for defining functions for parsing
 *						 s-expressions.
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

#ifndef __SYMEX_PARSE_H__
#define __SYMEX_PARSE_H__

#include "symex_list.h"

/* main functions */
symex_list_t*	symex_parse_from_file 	(FILE*);
symex_list_t*	symex_parse_file_string (char*);

/* char reading functions */
int (*symex_get_char) (void);
void symex_unget_char (void);

int symex_get_char_from_file 	(void);
int symex_get_char_from_string 	(void);

/* parsing functions */
symex_list_node_t*	symex_parse_symex			(void);
symex_list_node_t*	symex_parse_list			(void);
symex_list_node_t*	symex_parse_string			(void);
symex_list_node_t*	symex_parse_bytes			(int length);

#endif /* __SYMEX_PARSE_H__ */
