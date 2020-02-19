#ifndef ENGINE_H
#define ENGINE_H
# include "wolf3d.h"

#define hfov (0.73f*WIN_H)
#define vfov (0.2f*WIN_H)

typedef struct	s_new_cycle//item
{
	t_new_tmp_trio	queue[MAX_QUEUE];//sectors queue for draw sector by sector
	t_new_tmp_trio	*head;
	t_new_tmp_trio	*current;
	t_new_tmp_trio	*tail;
	int			*rend_sec;
}				t_new_cycle;

typedef struct	s_new_sector//have to be static
{
    float		floor;//floor height
	float		ceil;//ceil height
    t_vector3	*vertex; //here stored all sector vertexes.
    int		*neighbors;// Each edge may have a corresponding neighboring sector
    int			npoints;// How many vertexes there are
}				t_new_sector;//*sectors = NULL;

/*typedef struct s_new_sect_ops
{
	const t_new_sector	*sect;
    const t_new_xy		*vert;
    t_new_xy 			p;
    t_new_xy			d;
    float			px;
    float			dx;
    float			py;
    float			dy;
    float			eye_h;
    float			hole_low;
    float			hole_high;
	t_new_xy		dir_vec;
    //float			xd;
    //float			yd;
}					t_new_sect_ops;*/

typedef struct	s_new_others
{
    float	move_vec[2];//when player moves
    int		moving;
}			t_new_others;

typedef struct	s_new_ceil //y - height of ceil, n - neighbor, a - top, b - bottom
{
	float	yceil;//ceiling heights, relative to where the player's view is
	float	nyceil;//boundary between two neighbor sectors
	
	int		y1a;//ceil projection
	int		y2a;//ceil projection
	int		ny1a;//projection neighbor
	int		ny2a;//projection neighbor

	int		cya;//Y coordinates for our ceil in this X coordinate (top)
	int		cyb;//Y coordinates for our ceil in this X coordinate (bottom)
	int		cnya;//Y coordinates for neighbor ceil in this X coordinate
	int		cnyb;//Y coordinates for neighbor ceil in this X coordinate
}				t_new_ceil;

typedef struct	s_new_floor//y - height of floor, n - neighbor, a - top, b - bottom
{
	float	yfloor;//floor heights, relative to where the player's view is
	float	nyfloor;//boundary between two neighbor sectors

	int		y1b;//floor projection 
	int		y2b;//floor projection
	int		ny1b;//floor projection neighbor
	int		ny2b;//floor projection neighbor
	
	int		ya;//Y coordinates for our floor in this X coordinate
	int		yb;//Y coordinates for our floor in this X coordinate
	int		nya;//Y coordinates for neighbor floor in this X coordinate
	int		nyb;//Y coordinates for neighbor floor in this X coordinate
}				t_new_floor;

#endif
