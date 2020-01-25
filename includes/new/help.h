#ifndef HELP_H
# define HELP_H

#include "wolf3d.h"

typedef struct  s_new_vector3
{
    double      x;
    double      y;
    double      z;
    double      w;
}               t_new_vector3;
typedef struct	s_tmp_trio //sectorno, sx1, sx2;
{
    int	sec_nb;
    int	sx1;
    int	sx2;
}				t_tmp_trio;
typedef struct	s_new_xy
{
    float	x;
    float	y;
}				t_new_xy;

typedef struct	s_new_xyz
{
    float	x;
    float	y;
    float	z;
}				t_new_xyz;

typedef struct	s_new_rect
{
    t_new_xy	size;
    t_new_xy	crd;
}				t_new_rect;

#endif
