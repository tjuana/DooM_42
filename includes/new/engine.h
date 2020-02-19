#ifndef ENGINE_H
#define ENGINE_H
# include "wolf3d.h"

#define hfov (0.73f*WIN_H)
#define vfov (0.2f*WIN_H)

/*
** **************************************************************************
**	t_new_tmp_trio
**
**	Structure for game sector.
**
**	Arguments:
**	int sec_nb						|
**	int sx1							|
**	int sx2							|
** **************************************************************************
*/
typedef struct		s_new_tmp_trio
{
	int				sec_nb;
	int				sx1;
	int				sx2;
}					t_new_tmp_trio;

/*
** **************************************************************************
**	t_new_cycle
**
**	Structure for game sector.
**
**	Arguments:
**	t_new_tmp_trio queue[MAX_QUEUE]	| sectors queue for draw sector by sector
**	t_new_tmp_trio *head			|
**	t_new_tmp_trio *current			|
**	t_new_tmp_trio *tail			|
**	int *rend_sec					|
** **************************************************************************
*/
typedef struct		s_new_cycle
{
	t_new_tmp_trio	queue[MAX_QUEUE];
	t_new_tmp_trio	*head;
	t_new_tmp_trio	*current;
	t_new_tmp_trio	*tail;
	int				*rend_sec;
}					t_new_cycle;

/*
** **************************************************************************
**	t_new_sector
**
**	Structure for game sector.
**
**	Arguments:
**	float floor				| floor height
**	floa ceil				| ceil height
**	t_vector3 *vertex		| here stored all sector vertexes.
**	signed char *neighbors	|  Each edge may have a corresponding neighboring sector
**	int npoints				|  How many vertexes there are
** **************************************************************************
*/
typedef struct		s_new_sector
{
	float			floor;
	float			ceil;
    t_vector3		*vertex;
    signed char		*neighbors;
    int				npoints;
}					t_new_sector;

/*
** **************************************************************************
**	t_new_others
**
**	Structure for others values.
**
**	Arguments:
**	float					| when player moves
**	int						|
** **************************************************************************
*/
typedef struct		s_new_others
{
    float			move_vec[2];
    int				moving;
}					t_new_others;

/*
** **************************************************************************
**	t_new_ceil
**
**	Structure for ceil.
**
**	y - height of ceil, n - neighbor, a - top, b - bottom
**
**	Arguments:
**	int y1a					| ceil projection
**	int y2a					| ceil projection
**	int ny1a				| projection neighbor
**	int ny2a				| projection neighbor
**	int cya					| Y coordinates for our ceil in this X coordinate (top)
**	int cyb					| Y coordinates for our ceil in this X coordinate (bottom)
**	int cnya				| Y coordinates for neighbor ceil in this X coordinate
**	int cnyb				| Y coordinates for neighbor ceil in this X coordinate
** **************************************************************************
*/
typedef struct		s_new_ceil
{
	float			yceil;
	float			nyceil;
	int				y1a;
	int				y2a;
	int				ny1a;
	int				ny2a;
	int				cya;
	int				cyb;
	int				cnya;
	int				cnyb;
}					t_new_ceil;


/*
** **************************************************************************
**	t_new_floor
**
**	Structure for floor.
**
**	y - height of floor, n - neighbor, a - top, b - bottom
**
**	Arguments:
**	float yfloor			| floor heights, relative to where the player's view is
**	float nyfloor			| boundary between two neighbor sectors
**	int y1b					| floor projection 
**	int y2b					| floor projection
**	int ny1b				| floor projection neighbor
**	int ny2b				| floor projection neighbor
**	int ya					| Y coordinates for our floor in this X coordinate
**	int yb					| Y coordinates for our floor in this X coordinate
**	int nya					| Y coordinates for neighbor floor in this X coordinate
**	int nyb					| Y coordinates for neighbor floor in this X coordinate
** **************************************************************************
*/
typedef struct		s_new_floor
{
	float			yfloor;
	float			nyfloor;
	int				y1b;
	int				y2b;
	int				ny1b;
	int				ny2b;
	int				ya;
	int				yb;
	int				nya;
	int				nyb;
}					t_new_floor;

#endif
