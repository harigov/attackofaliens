/*
 * File      : bullet.h
 * Author    : Hariprasad Govardhanam [harigov AT gmail.com]
 * Purpose   : Defines functions that create and control
 *             a bullet.
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


#ifndef __BULLET_H__
#define __BULLET_H__

#include <SDL.h>
#include "game.h"

enum { JETPLANE_GUN, ALIEN_GUN };

struct tagBullet
{
	int firedby;
	int xpos, ypos;
	/* destructive power of this bullet
	 * used to calculate the effect of
	 * this bullet on the life of an
	 * alien or plane */
	int power;
	DIRECTION dir;
};

typedef struct tagBullet BULLET;

BULLET*		create_bullet (int xpos, int ypos, DIRECTION dir, int firedby);
void		destroy_bullet (BULLET*);

void		move_bullet (BULLET*);
void		draw_bullet (BULLET*, SDL_Surface*);
void		check_bullet (BULLET*);

#endif /* __BULLET_H__ */
