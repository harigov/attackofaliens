/*
 * File      : jetplane.h
 * Author    : Hariprasad Govardhanam [harigov AT gmail.com]
 * Purpose   : Defines functions for creating and controlling
 *             jetplanes.
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

#ifndef __JETPLANE_H__
#define __JETPLANE_H__

#include <SDL.h>
#include "game.h"
#include "bullet.h"

#define DEFAULT_PLANE_POS 10

struct tagJetplane
{
	int bullet_count;
	int xpos, ypos;
  int life_count;
	/* DEAD or ALIVE */
	STATE state; 
	SDL_Surface* surface;
};

typedef struct tagJetplane JETPLANE;

JETPLANE*	create_jetplane (SDL_Surface* sur, int xpos, int bullets);
void		destroy_jetplane (JETPLANE*);

void		draw_jetplane (JETPLANE*, SDL_Surface*);
void		move_jetplane (JETPLANE*, DIRECTION);

int			inside_jetplane (JETPLANE*, int xpos, int ypos);

void		fire_jetplane (JETPLANE*, DIRECTION);
void    hit_plane_with_bullet (JETPLANE*, BULLET*);
void		kill_jetplane (JETPLANE*);

#endif /* __JETPLANE_H__ */
