/*
 * File      : bullet.c
 * Author    : Hariprasad Govardhanam [harigov AT gmail.com]
 * Purpose   : Implements the code for creating and controlling
 *             bullets.
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

#include <stdio.h>
#include <stdlib.h>

#include "alien.h"
#include "jetplane.h"
#include "bullet.h"

BULLET*
create_bullet (int xpos, int ypos, DIRECTION dir, int firedby)
{
	BULLET* bullet;
	bullet = malloc (sizeof *bullet);
	check_error (bullet == NULL, "Memory allocation failed");

	bullet->xpos = xpos;
	bullet->ypos = ypos;
	bullet->dir = dir;
	bullet->firedby = firedby;
  switch (firedby)
  {
    case ALIEN_GUN:
      bullet->power = 25;
      break;
    case JETPLANE_GUN:
      bullet->power = 50;
      break;
  }

	insert_item_dlist (bullets, bullet);

	return bullet;
}

void
destroy_bullet (BULLET* bullet)
{
	if (bullet != NULL)
	{
		remove_item_dlist (bullets, bullet);
		free (bullet);
	}
}

void
draw_bullet (BULLET* bullet, SDL_Surface* screen)
{
	SDL_Rect rect;

	rect.x = bullet->xpos;
	rect.y = bullet->ypos;
	rect.w = 4;
	rect.h = 6;
	SDL_FillRect (screen, &rect, SDL_MapRGB (screen->format, 255, 255, 255));
}

void
move_bullet (BULLET* bullet)
{
	int bullet_speed = 15;
	switch (bullet->dir)
	{
		case LEFT_DIR:
			if (bullet->xpos > 0)
				bullet->xpos -= bullet_speed;
			else
				destroy_bullet (bullet);
			break;
		case RIGHT_DIR:
			if (bullet->xpos < XRESOLUTION)
				bullet->xpos += bullet_speed;
			else
				destroy_bullet (bullet);
			break;
		case UP_DIR:
			if (bullet->ypos > 0)
				bullet->ypos -= bullet_speed;
			else
				destroy_bullet (bullet);
			break;
		case DOWN_DIR:
			if (bullet->ypos < YRESOLUTION)
				bullet->ypos += bullet_speed;
			else
				destroy_bullet (bullet);
			break;
	}
}

void
check_bullet (BULLET* bullet)
{
	ALIEN* alien;
	JETPLANE* plane;

	/* if bullet is firedby jetplane, it
	 * will only hurt aliens */
	if (bullet->firedby == JETPLANE_GUN)
	{
		alien = first_item_dlist (aliens);
		while (alien != NULL)
		{
			if (inside_alien (alien, bullet->xpos, bullet->ypos))
			{
        hit_alien_with_bullet (alien, bullet);
				/*kill_alien (alien);*/
				/*destroy_bullet (bullet);*/
				return;
			}
			alien = next_item_dlist (aliens);
		}
	}
	/* if bullet is firedby alien, it will
	 * only hurt jetplane */
	else if (bullet->firedby == ALIEN_GUN)
	{
		plane = first_item_dlist (planes);
		while (plane != NULL)
		{
			if (inside_jetplane (plane, bullet->xpos, bullet->ypos))
			{
        hit_jetplane_with_bullet (plane, bullet);
				/*kill_jetplane (plane);*/
				/*destroy_bullet (bullet);*/
        return;
			}
			plane = next_item_dlist (planes);
		}
	}	
}

