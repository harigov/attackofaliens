/*
 * File      : alien.c 
 * Author    : Hariprasad Govardhanam [harigov AT gmail.com]
 * Purpose   : Implements the code for creating and controlling
 *             aliens.
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
#include <string.h>
#include <assert.h>
#include <math.h>

#include "alien.h"
#include "jetplane.h"
#include "bullet.h"

ALIEN *
create_alien (SDL_Surface * surface, int xpos, int ypos,
	      int bullets, int speed, ALIEN_TYPE type)
{
  ALIEN *alien = malloc (sizeof (ALIEN));
  check_error (alien == NULL, "Memory allocation failed");

  alien->type = type;
  alien->xpos = xpos;
  alien->ypos = ypos;
  alien->bullet_count = bullets;
  alien->life_count = 50;
  alien->speed = speed;
  alien->dir = LEFT_DIR;
  alien->state = ALIVE;
  alien->surface = surface;
  alien->img_num = 0;
  alien->left_alien = NULL;
  alien->right_alien = NULL;

  insert_item_dlist (aliens, alien);

  return alien;
}

ALIEN *
create_alien_from_symex (SDL_Surface * surface, ALIEN_TYPE type, symex_list_node_t * node)
{
	ALIEN *alien;

	assert (node != NULL);

	if (node->type != SYMEX_LIST)
		return NULL;

	alien = create_alien (surface, 0, 0, 0, 0, type);
	if (alien == NULL)
		return NULL;

	node = node->data;

	if (node == NULL)
		return NULL;

	sscanf (node->data, "%i", &(alien->xpos));

	if (node->next == NULL)
		return NULL;

	node = node->next;
	sscanf (node->data, "%i", &(alien->ypos));

	if (node->next == NULL)
		return NULL;

	node = node->next;
	sscanf (node->data, "%i", &(alien->bullet_count));

	if (node->next == NULL)
		return NULL;

	node = node->next;
	sscanf (node->data, "%i", &(alien->speed));

	if (node->next == NULL)
		return NULL;

  switch (type)
  {
    case ALIEN_NORMAL:
      alien->life_count = 50;
      break;
    case ALIEN_EVIL:
      alien->life_count = 100;
      break;
  }

	node = node->next;
	if (strcmp (node->data, "left") == 0)
		alien->dir = LEFT_DIR;
	else if (strcmp (node->data, "right") == 0)
		alien->dir = RIGHT_DIR;
	else if (strcmp (node->data, "up") == 0)
		alien->dir = UP_DIR;
	else if (strcmp (node->data, "down") == 0)
		alien->dir = DOWN_DIR;

	return alien;
}

void
destroy_alien (ALIEN * alien)
{
	if (alien != NULL) {
		alien = remove_item_dlist (aliens, alien);
		if (alien != NULL)
			free (alien);
		else
			printf ("alien already freed\n");
	}
}

void
draw_alien (ALIEN * alien, SDL_Surface * screen)
{
	SDL_Rect src, dest;

	assert (alien != NULL);
	assert (screen != NULL);

	if (alien->dir == LEFT_DIR)
		src.x = (alien->img_num / 5) * 60;
	else                    /* even if dir is up, down or right */
		src.x = (alien->img_num / 5 + 3) * 60;

	src.y = 0;
	src.w = 60;
	src.h = alien->surface->h;

	dest.x = alien->xpos;
	dest.y = alien->ypos;
	dest.w = 60;
	dest.h = alien->surface->h;

	SDL_BlitSurface (alien->surface, &src, screen, &dest);

	if (++alien->img_num > 14)
		alien->img_num = 0;
}

void
move_alien (ALIEN * alien)
{
	int alien_speed = alien->speed / frame_rate;
	if (alien_speed < 2)
		alien_speed = 2;
	if (alien_speed > min_gap_between_aliens)
		alien_speed = min_gap_between_aliens;

	assert (alien != NULL);

	switch (alien->dir) {
		case LEFT_DIR:
			if (alien->left_alien == NULL) {
				if (alien->xpos > min_gap_between_aliens)
					alien->xpos -= alien_speed;
				else
					alien->dir = RIGHT_DIR;
			} else  { 
        /* if (alien->left_alien->dir == LEFT_DIR) { */
				if ((alien->xpos - alien->left_alien->xpos - ALIEN_WIDTH) >
						min_gap_between_aliens) {
					alien->xpos -= alien_speed;
				}
        else
				  alien->dir = RIGHT_DIR;
			} 
			break;
		case RIGHT_DIR:
			if (alien->right_alien == NULL) {
				if (alien->xpos < (XRESOLUTION - ALIEN_WIDTH - min_gap_between_aliens))
					alien->xpos += alien_speed;
				else
					alien->dir = LEFT_DIR;
			} else  {
        /* if (alien->right_alien->dir == RIGHT_DIR) { */
				if ((alien->right_alien->xpos - alien->xpos - ALIEN_WIDTH) >
						min_gap_between_aliens) {
					alien->xpos += alien_speed;
				}
        else
				  alien->dir = LEFT_DIR;
			} 
			break;
		case UP_DIR:
			/*
			 * if (alien->ypos > 10) alien->ypos -= alien_speed;
			 * alien->dir = LEFT_DIR;
			 */
			break;
		case DOWN_DIR:
			/*
			 * if (alien->ypos < (YRESOLUTION-140)) alien->ypos +=
			 * alien_speed; alien->dir = dir;
			 */
			break;
	}
}

void
alien_cycle (ALIEN * alien)
{
  JETPLANE* plane = NULL;
  if (alien->state == DEAD)
    destroy_alien (alien);

  move_alien (alien);
  plane = first_item_dlist (planes);
  while (plane != NULL && plane->state == ALIVE)
  {
    if (abs (alien->xpos - plane->xpos) <= 10 && can_fire_bullet (alien) == True)
    {
      fire_alien (alien);
    }
    plane = next_item_dlist (planes);
  }
}

BOOL
can_fire_bullet (ALIEN* alien)
{
  return (abs (alien->xpos - alien->prev_xpos) >= 2*alien->speed ||
          abs (alien->ypos - alien->prev_ypos) >= 2*alien->speed);
}

void
fire_alien (ALIEN* alien)
{
  BULLET* bullet;

  /* bullet_count!=0  allows us to fire infinite bullets, if
   * we initialize alien with a bullet_count of -1*/
  if (alien->state == ALIVE && alien->bullet_count != 0)
  {
    bullet = create_bullet (alien->xpos + 30, alien->ypos + 30, DOWN_DIR, ALIEN_GUN);
    check_error (bullet == NULL, "Bullet creation failed");

    alien->prev_xpos = alien->xpos;
    alien->prev_ypos = alien->ypos;
    alien->bullet_count--;
  }
}

int
inside_alien (ALIEN * alien, int xpos, int ypos)
{
	assert (alien != NULL);

	if (xpos >= alien->xpos && xpos <= alien->xpos + 60 &&
			ypos >= alien->ypos && ypos <= alien->ypos + 60)
		return 1;
	return 0;
}


void
hit_alien_with_bullet (ALIEN* alien, BULLET* bullet)
{
	assert (alien != NULL && bullet != NULL);
	alien->life_count -= bullet->power;
	if (alien->life_count < 0)
		kill_alien (alien);
}

void
kill_alien (ALIEN * alien)
{
	assert (alien != NULL);

	if (alien->left_alien != NULL)
		alien->left_alien->right_alien = alien->right_alien;
	if (alien->right_alien != NULL)
		alien->right_alien->left_alien = alien->left_alien;

	alien->state = DEAD;
}

void
find_neighbour_aliens (ALIEN * alien)
{
  ALIEN *nearest_left_alien = NULL, *nearest_right_alien = NULL,
    *a;

  assert (alien != NULL);

  /*
   * if (alien->left_alien == NULL) {
	 */
	/* loop through list of aliens */
	a = first_item_dlist (aliens);
	while (a != NULL) {
		/*
		 * if the alien a is in the same row then check if it is the
		 * nearest left or right alien
		 */
		if (a->ypos == alien->ypos) {
			if (a->xpos < alien->xpos) {
				if (nearest_left_alien == NULL || nearest_left_alien->xpos < a->xpos)
					nearest_left_alien = a;
			} else if (a->xpos > alien->xpos) {
				if (nearest_right_alien == NULL || nearest_right_alien->xpos > a->xpos)
					nearest_right_alien = a;
			}
		}
		a = next_item_dlist (aliens);
	}

	/*
	 * change the left_alien and right_alien fields of the alien
	 * structure
	 */
	alien->left_alien = nearest_left_alien;
	alien->right_alien = nearest_right_alien;
	/* } */
}
