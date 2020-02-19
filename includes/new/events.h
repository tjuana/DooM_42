#ifndef EVENTS_H
#define EVENTS_H
# include "wolf3d.h"

/*
** **************************************************************************
**	t_file_read
**
**	Structure for file read.
**
**	Arguments:
**	SDL_Event ev	|
**	int wsad[40]	|
**	int ground		|
**	int falling		|
**	int ducking		|
**	int quit		|
** **************************************************************************
*/
typedef struct	s_new_sub_ev
{
	SDL_Event	ev;
	int			wsad[40];
	int			ground;
	int			falling;
	int			ducking;
	int			quit;
}				t_new_sub_ev;

/*
** **************************************************************************
**	t_file_read
**
**	Structure for file read.
**
**	Arguments:
**	int x			|
**	int y			|
**	float yaw		|
** **************************************************************************
*/
typedef struct	s_new_mouse
{
	int			x;
	int			y;
	float		yaw;
}				t_new_mouse;

#endif
