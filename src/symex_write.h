/*
 * File      : symex_write.h
 * Author    : Hariprasad Govardhanam [harigov AT gmail.com]
 * Purpose   : Declares functions which write s-expressions stored
 *						 in a list structure to disk.
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

#ifndef __SYMEX_WRITE_H__
#define __SYMEX_WRITE_H__

#include <stdio.h>

#include "symex_list.h"

void	symex_print_to_file (symex_list_node_t*, FILE*fp);
int		symex_write_to_file (symex_list_t*, const char* filename);

#endif /* __SYMEX_WRITE_H__ */
