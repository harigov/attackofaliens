/*
 * File      : game.h
 * Author    : Hariprasad Govardhanam [harigov AT gmail.com]
 * Purpose   : Defines functions and types that are used
 *             everywhere else in the game.
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

#ifndef __GAME_H__
#define __GAME_H__

#include "symex.h"
#include "dlist.h"

#define XRESOLUTION 640
#define YRESOLUTION 480

typedef enum {LEFT_DIR, RIGHT_DIR, UP_DIR, DOWN_DIR} DIRECTION;
typedef enum {ALIVE, DEAD} STATE;
typedef int BOOL;
static const int True = 1, False = 0;

int frame_rate, min_gap_between_aliens;

/* checks for a condition, and if satisfied it 
 * prints an error message */
void check_error (int condition, const char* errmsg);

#ifdef __DLIST_H__
	DLIST	*aliens, *planes, *bullets;
#endif

#endif /* __GAME_H__ */
