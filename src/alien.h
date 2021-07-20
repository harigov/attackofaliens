/*
 * File      : alien.h
 * Author    : Hariprasad Govardhanam [harigov AT gmail.com]
 * Purpose   : Defines the functions that create and control
 *             an alien.
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

#ifndef __ALIEN_H__
#define __ALIEN_H__

#include <SDL.h>
#include "bullet.h"
#include "game.h"

#define ALIEN_WIDTH   60
#define ALIEN_HEIGHT   60

typedef enum { ALIEN_NORMAL = 0, ALIEN_EVIL, ALIEN_COUNT} ALIEN_TYPE;

struct tagAlien
{
	ALIEN_TYPE type;
	/* position of the alien */
	int xpos, ypos;
	/* number of bullets that this alien have */
	int bullet_count;
	/* life of this alien from 0 to 100 */
	int life_count;
	/* speed of the alien */
	int speed;
	/* direction in which alien is moving */
	DIRECTION dir;
	/* dead or alive */
	STATE state;
	/* image of the alien */
	SDL_Surface* surface; 

  /* position at which alien has previously fired 
   * a bullet */
  int prev_xpos, prev_ypos;

	/* image number count to display images in 
	 * left-right-left fashion */
	int img_num;

	/* These ptrs start with an initial value
	 * of NULL, but if even after scanning for
	 * neighbours their value is NULL, it means
	 * that there is no left or right alien */
	struct tagAlien *left_alien, *right_alien;
};

typedef struct tagAlien ALIEN;

ALIEN*  create_alien (SDL_Surface *surface, int xpos, int ypos, 
          int bullets, int speed, ALIEN_TYPE type);
ALIEN*  create_alien_from_symex (SDL_Surface *surface, ALIEN_TYPE,
         symex_list_node_t *list);
void  destroy_alien (ALIEN*);

void  draw_alien (ALIEN*, SDL_Surface*);
void  move_alien (ALIEN*);
void  alien_cycle (ALIEN*);

BOOL  can_fire_bullet (ALIEN* alien);
void  fire_alien (ALIEN *alien);

int   inside_alien (ALIEN*, int xpos, int ypos);

void  hit_alien_with_bullet (ALIEN*, BULLET*);
void  kill_alien (ALIEN*);
void  find_neighbour_aliens (ALIEN*);

#endif /* __ALIEN_H__ */
