#ifndef DOOR_H
# define DOOR_H

typedef struct	s_door
{
	int		nb;//door sector nb
	float	dir;//speed of lift door up or down
	int		max_d;//lift up while max_d
	int		min_d;//lift down while min_d
}				t_door;


#endif
