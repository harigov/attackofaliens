/*
 * File      : debug.h
 * Author    : Hariprasad Govardhanam [harigov AT gmail.com]
 * Purpose   : Defines functions and macros that are used
 *             for printing debug messages and other debugging
 *             purposes.
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

#ifndef __DEBUG_H__
#define __DEBUG_H__

#include <stdio.h>

#define NDEBUG

#ifdef NDEBUG
# define  TRACE(msg) 
#else
# define  TRACE(msg) fprintf (stderr, "%s\n", msg);
#endif

#endif /* __DEBUG_H__ */

