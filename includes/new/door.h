#ifndef DOOR_H
# define DOOR_H

#include "wolf3d.h"

typedef struct	s_new_door
{
	int		nb;//door sector nb
	float	dir;//speed of lift door up or down
	int		max_d;//lift up while max_d
	int		min_d;//lift down while min_d
}				t_new_door;


#endif
