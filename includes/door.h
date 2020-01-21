#ifndef DOOR_H
# define DOOR_H

typedef struct	s_door
{
	int		s_nb;//door sector nb
	float	dir;//speed of lift door up or down
	int		max_d;//lift up while max_d
	int		min_d;//lift down while min_d
	int		opened;// door close or not?
}				t_door;


#endif
