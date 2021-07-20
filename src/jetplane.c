/*
 * File      : jetplane.c
 * Author    : Hariprasad Govardhanam [harigov AT gmail.com]
 * Purpose   : Implements functions for creating and controlling
 *             jet planes.
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

#include "jetplane.h"
#include "bullet.h"
#include "assert.h"

JETPLANE*
create_jetplane (SDL_Surface* plane_sur, int xpos, int bullets)
{
	JETPLANE* plane = malloc (sizeof (JETPLANE));
	check_error (plane == NULL, "Memory allocation failed");

	plane->bullet_count = bullets;
	plane->xpos = xpos;
  plane->life_count = 100;
	plane->state = ALIVE;
	plane->surface = plane_sur;

	insert_item_dlist (planes, plane);

	return plane;
}

void
destroy_jetplane (JETPLANE* plane)
{
	if (plane != NULL)
	{
		plane = remove_item_dlist (planes, plane);
		if (plane != NULL)
			free (plane);
		else
			printf ("plane already freed\n");
	}
}

void
draw_jetplane (JETPLANE* plane, SDL_Surface* screen)
{
	SDL_Rect src, dest;

	src.x = src.y = 0;
	dest.w = src.w = plane->surface->w;
	dest.h = src.h = plane->surface->h;

	dest.x = plane->xpos;
	dest.y = YRESOLUTION - 80;

	SDL_BlitSurface (plane->surface, &src, screen, &dest);
}

void
move_jetplane (JETPLANE* plane, DIRECTION dir)
{
	if (plane->state == ALIVE)
	{
		switch (dir)
		{
			case LEFT_DIR:
				if (plane->xpos > 10)
					plane->xpos -= 10;
				break;
			case RIGHT_DIR:
				if (plane->xpos < (XRESOLUTION-70))
					plane->xpos += 10;
				break;
			case UP_DIR:
				break;
			case DOWN_DIR:
				break;
		}
	}
}

int
inside_jetplane (JETPLANE* plane, int xpos, int ypos)
{
	if (xpos >= plane->xpos && xpos <= plane->xpos+60 && 
			ypos >= plane->ypos && ypos <= plane->ypos+60)
		return 1;

	return 0;
}

void
fire_jetplane (JETPLANE* plane, DIRECTION dir)
{
	BULLET* bullet;

	/* bullet_count!=0  allows us to fire infinite bullets, if
	 * we initialize plane with a bullet_count of -1*/
	if (plane->state == ALIVE && plane->bullet_count != 0)
	{
		bullet = create_bullet (plane->xpos + 30, YRESOLUTION - 80, dir, JETPLANE_GUN);
		check_error (bullet == NULL, "Bullet creation failed");

		plane->bullet_count--;
	}
}

void
hit_jetplane_with_bullet (JETPLANE* plane, BULLET* bullet)
{
  assert (plane != NULL && bullet != NULL);
  plane->life_count -= bullet->power;
  if (plane->life_count <= 0)
    kill_jetplane (plane);
}

void
kill_jetplane (JETPLANE* plane)
{
	plane->state = DEAD;
}

