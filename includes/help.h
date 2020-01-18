#ifndef HELP_H
# define HELP_H

typedef struct  s_vector3
{
    double      x;
    double      y;
    double      z;
    double      w;
}               t_vector3;
typedef struct	s_tmp_trio //sectorno, sx1, sx2;
{
    int	sec_nb;
    int	sx1;
    int	sx2;
}				t_tmp_trio;
typedef struct	s_xy
{
    float	x;
    float	y;
}				t_xy;

typedef struct	s_xyz
{
    float	x;
    float	y;
    float	z;
}				t_xyz;

typedef struct	s_rect
{
    t_xy	size;
    t_xy	crd;
}				t_rect;

#endif
