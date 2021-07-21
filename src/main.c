/*
 * File      : main.c
 * Author    : Hariprasad Govardhanam [harigov AT gmail.com]
 * Purpose   : Main program.
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
#include <assert.h>
#include <string.h>
#include <SDL.h>

#include "debug.h"
#include "game.h"
#include "jetplane.h"
#include "alien.h"
#include "bullet.h"

/* global variables */
const char*   game_name   = "Space Invaders";
DLIST*        levels      = NULL;

/* These will be initialized by game_init function */
SDL_Surface*  screen    = NULL;
SDL_Surface*  plane_sur  = NULL;
SDL_Surface*  aliens_sur[ALIEN_COUNT];

/* function prototypes */
void game_init (void);
void game_exit (void);
void game_draw (void);
void level_init (const char *fname);
void level_exit (void);
void level_cycle (void);

/* utility functions */
void  check_error (int condition, const char*);
char* strip_string (const char* str);

int main (int argc, char*argv[])
{
  SDL_Event event;
  Uint32 prev_time = 0, cur_time, frame_rate;
  char* level_file_name;
  int level_changed = 1, level_loaded = 0;

  game_init ();
  printf ("%d levels have been found",levels->count);

  level_file_name = first_item_dlist (levels);
  puts(level_file_name);
  while (level_file_name != NULL)
  {
    if (level_changed)
    {
      level_init (level_file_name);
      printf ("%s level initialized", level_file_name);
      level_changed = 0;
      level_loaded = 1;
    }

    cur_time = SDL_GetTicks ();
    if (prev_time != 0)
    {
      frame_rate = 1000/(cur_time - prev_time);
    }

    if (SDL_PollEvent (&event))
    {
      Uint8* keystate = SDL_GetKeyState (NULL);

      if (keystate[SDLK_q])
        exit (0);
      else if (keystate[SDLK_LEFT])
        move_jetplane (first_item_dlist (planes), LEFT_DIR);
      else if (keystate[SDLK_RIGHT])
        move_jetplane (first_item_dlist (planes), RIGHT_DIR);
      else if (keystate[SDLK_f])
      {
        if (1 != SDL_WM_ToggleFullScreen (screen))
        {
          fprintf (stderr, "Unable to toggle to fullscreen");
        }
      }

      if (keystate [SDLK_LCTRL])
        fire_jetplane (first_item_dlist (planes), UP_DIR);
    }

    /* check if there are any aliens
     * left in this level */
    if (aliens->count)
    {  
      level_cycle ();
    }
    else
    {
      level_exit ();
      level_file_name = next_item_dlist (levels);
      level_changed = 1;
      level_loaded = 0;
    }

    if (level_loaded)
      game_draw ();
    SDL_Flip (screen);  
    prev_time = cur_time;
  }

  return EXIT_SUCCESS;
}

void
game_init (void)
{
  FILE* fp = NULL;
#define MAXBUFSIZE 1024
  char buf[MAXBUFSIZE];
  SDL_Surface* temp;

  TRACE ("game_init entered");

  check_error (SDL_Init (SDL_INIT_VIDEO) != 0, 
	       "SDL initialization failed");

  planes = bullets = aliens = levels = NULL;

  atexit (game_exit);

  /* global variable screen */
  screen = SDL_SetVideoMode (XRESOLUTION, YRESOLUTION, 16, 
			     SDL_DOUBLEBUF|SDL_HWSURFACE);
  check_error (screen == NULL, "Set video mode failed");

  SDL_WM_SetCaption (game_name, NULL);

  SDL_EnableKeyRepeat (SDL_DEFAULT_REPEAT_DELAY, 
		       SDL_DEFAULT_REPEAT_INTERVAL);

  /* load plane image */
  temp = SDL_LoadBMP ("../data/plane.bmp");
  check_error (temp == NULL, "Loading plane image failed");
  plane_sur = SDL_DisplayFormat (temp);
  if (plane_sur == NULL) 
    plane_sur = temp;
  else
    SDL_FreeSurface (temp);

  /* load alien image */
  temp = SDL_LoadBMP ("../data/alien.bmp");
  check_error ( temp == NULL, "Loading alien image failed");
  aliens_sur[ALIEN_NORMAL] = SDL_DisplayFormat (temp);
  if (aliens_sur[ALIEN_NORMAL] == NULL) 
    aliens_sur[ALIEN_NORMAL] = temp;
  else
    SDL_FreeSurface (temp);

  /* load alien image */  
  /*  temp = SDL_LoadBMP ("../data/alien_evil.bmp");
      check_error (temp == NULL, "Loading alien image failed");
      aliens_sur[ALIEN_EVIL] = SDL_DisplayFormat (temp);
      if (aliens_sur[ALIEN_EVIL] == NULL)
      aliens_sur[ALIEN_EVIL] = temp;
      else
      SDL_FreeSurface (temp);*/

  SDL_SetColorKey (screen, SDL_SRCCOLORKEY, 
		   SDL_MapRGB (screen->format, 255, 0, 0));
  SDL_SetColorKey (plane_sur, SDL_SRCCOLORKEY, 
		   SDL_MapRGB (plane_sur->format, 255, 0, 0));
  SDL_SetColorKey (aliens_sur[ALIEN_NORMAL], SDL_SRCCOLORKEY, 
		   SDL_MapRGB (aliens_sur[ALIEN_NORMAL]->format, 255, 0, 0));
  /*  SDL_SetColorKey (aliens_sur[ALIEN_EVIL], SDL_SRCCOLORKEY, 
      SDL_MapRGB (aliens_sur[ALIEN_EVIL]->format, 255, 0, 0));*/

  /* prepare a list of levels */
  fp = fopen ("levels.conf", "r+");
  check_error (fp == NULL, "File levels.conf open failed");
  levels = create_dlist ();
  check_error (levels == NULL, "Levels creation failed");
  while (fgets (buf, MAXBUFSIZE, fp) != NULL)
    {
      char* str = strip_string (buf);
      insert_item_dlist (levels, str);
    }

  fclose (fp);

  frame_rate = 30;

  TRACE ("game_init leaving");
}

void 
game_exit (void)
{
  int i;

  TRACE ("game_exit entered");

  level_exit ();
  SDL_FreeSurface (plane_sur);
  for (i = 0;i < ALIEN_COUNT; i++)
    SDL_FreeSurface (aliens_sur[i]);
  SDL_Quit ();
  destroy_dlist (levels);

  TRACE ("game_exit leaving"); 
}

void
game_draw (void)
{
  ALIEN* alien;
  JETPLANE* plane;
  BULLET* bullet;

  TRACE ("game_draw entered");

  SDL_FillRect (screen, NULL, 0);

  

  plane = first_item_dlist (planes);
  while (plane != NULL)
    {
      draw_jetplane (plane, screen);
      plane = next_item_dlist (planes);
    }

  alien = first_item_dlist (aliens);
  while (alien != NULL)
    {
      draw_alien (alien, screen);
      alien = next_item_dlist (aliens);
    }

  bullet = first_item_dlist (bullets);
  while (bullet != NULL)
    {
      draw_bullet (bullet, screen);
      bullet = next_item_dlist (bullets);
    }

  TRACE ("game_draw leaving");
}

void
level_init (const char *fname)
{
  int i;
  FILE *fp;
  ALIEN* alien;
  symex_list_t *list;
  symex_list_node_t *node, *temp;

  TRACE ("level_init entered");

  fp = fopen (fname, "r");
  check_error (fp == NULL, "File open failed");

  fprintf (stderr, "Level %s loaded from file\n", fname);

  list = symex_parse_from_file (fp);
  if (list == NULL)
  {
    fclose (fp);
    exit (EXIT_FAILURE);
  }

  planes = create_dlist ();
  aliens = create_dlist ();
  bullets = create_dlist ();

  i = 0;
  node = list->fnode;
  while (node != NULL)
  {
    if (node->type == SYMEX_LIST)
    {
      node = node->data;
    }
    else if (node->type == SYMEX_BYTES)
    {
      if (strcmp (node->data, "alien") == 0)
      {
        temp = node->next;

        if (create_alien_from_symex (aliens_sur[ALIEN_NORMAL], ALIEN_NORMAL, temp) == NULL)
        {
          fprintf (stderr, "Alien creation failed\n");
          exit (EXIT_FAILURE);
        }

        node = node->next->next;
      }
      else if (strcmp (node->data, "alien_evil") == 0)
      {
        temp = node->next;

        if (create_alien_from_symex (aliens_sur[ALIEN_EVIL], ALIEN_EVIL, temp) == NULL)
        {
          fprintf (stderr, "Alien creation failed\n");
          exit (EXIT_FAILURE);
        }
      }
    }
  }

  symex_list_destroy (list);

  create_jetplane (plane_sur, DEFAULT_PLANE_POS, 30);

  /*  for (i = 0; i < 4; i++)
      {
      for (j = 0; j < 6; j++)
      {
      create_alien (aliens_sur[ALIEN_NORMAL], 
      115 + j*70, 35 + i*75, 12, 40, ALIEN_NORMAL);
      }
      }*/

  min_gap_between_aliens = 10;

  alien = first_item_dlist (aliens);
  while (alien != NULL)
  {
    save_item_position_dlist (aliens);
    find_neighbour_aliens (alien);
    restore_item_position_dlist (aliens);
    alien = next_item_dlist (aliens);
  }

  TRACE ("level_init leaving");
}

void
level_exit (void)
{
  TRACE ("level_exit entered");

  /*  destroy_jetplane (plane); */
  if (aliens)
    destroy_dlist (aliens);
  if (planes)
    destroy_dlist (planes);
  if (bullets)
    destroy_dlist (bullets);
  aliens = planes = bullets = NULL;

  TRACE ("level_exit leaving");
}

void
level_cycle (void)
{
  BULLET* bullet;

  ALIEN* alien = first_item_dlist (aliens), *temp;

  TRACE ("level_cycle entered");

  while (alien != NULL)
  {
    temp = next_item_dlist (aliens);

    alien_cycle (alien);

    alien = temp;
  }

  /* move bullet */
  bullet = first_item_dlist (bullets);
  while (bullet != NULL)
  {
    move_bullet (bullet);
    /* check if bullet hits any alien or plane */
    check_bullet (bullet);
    bullet = next_item_dlist (bullets);
  }

  TRACE ("level_cycle leaving");
}

void
check_error (int condition, const char* errmsg)
{
  if (condition)
    {
      fprintf (stderr, "%s\n", errmsg);
      exit (1);
    }
}

char*
strip_string (const char* str)
{
  /*assert (str && *str );*/

  const char *p1 = str, *p2 = str + strlen (str) - 1;
  char* retstr;

  TRACE ("strip_string entered");

  while (*p1 && (*p1 == ' ' || *p1 == '\n' || *p1 == '\t')) ++p1;
  while (*p2 && (*p2 == ' ' || *p2 == '\n' || *p2 == '\t')) --p2;

  retstr = malloc (p2 - p1 + 2);
  check_error (retstr == NULL, "Memory allocation failed");
  strncpy (retstr, p1, p2-p1+1);
  retstr[p2-p1+1] = 0;

  TRACE ("strip_string leaving");

  return retstr;
}

