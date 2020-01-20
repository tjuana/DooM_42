/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   door.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: drafe <drafe@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/14 18:46:09 by drafe             #+#    #+#             */
/*   Updated: 2020/01/20 22:06:43 by drafe            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

/*
** **************************************************************************
**	static int door_total(t_player *pl)
**	Function to init array of doors
** **************************************************************************
*/

static void	door_init(t_player *pl, int	*sec_arr)
{
	int	i;

	i = -1;
	while(++i < pl->door_all)
	{
		printf("i==%d sec_arr[i]==%d\n", i, sec_arr[i]);
		pl->doors[i].nb = sec_arr[i];
		pl->doors[i].dir = 0.1;
		pl->doors[i].max_d = 20;
		pl->doors[i].min_d = 0;
	}
}

/*
** **************************************************************************
**	static void door_total(t_player *pl)
**	Function to countdown doors and malloc them
**	pl->sectors[pl->door.nb].ceil = pl->sectors[pl->door.nb].ceil
** **************************************************************************
*/

static void	door_total(t_player *pl)
{	
	int	i;
	int	sec_arr[MAX_DOORS];
	int	*ptr;

	pl->door_all = 0;
	i = -1;
	while(++i < pl->sectors_nb)
	{
		printf("i==%d sec_arr[i]==%d\n", i, sec_arr[i]);
		if ((pl->sectors[i].ceil == 0) && (pl->sectors[i].floor == 0))
		{
			sec_arr[pl->door_all] = i;
			if (pl->door_all++ >= MAX_DOORS)
			{
				ft_putstr_fd("Too much doors", 2);
				exit(EXIT_FAILURE);
			}
		}
	}
	ptr = sec_arr;
	if (pl->door_all > 0)
		if (!(pl->doors = (t_door *)malloc(sizeof(t_door) * pl->door_all)))
			exit(EXIT_FAILURE);
	door_init(pl, ptr);
}


/*
** **************************************************************************
**	static int door_exist(t_player *pl)
**	Function to define doors in front of player
** **************************************************************************
*/

static int	door_exist(t_player *pl)
{
	t_vector3	vec;
	t_vector3	vec2;
	t_vector3	vec3;
	t_vector3	vec4;
	int		sec_nb;
	float	c;
	int		dist;
	
	dist = -1;
	sec_nb = 2;
	c = 0;

	vec2.x = pl->sectors[sec_nb].vertex[1].x - pl->where.x;
	vec2.y = pl->sectors[sec_nb].vertex[1].y - pl->where.y;
	vec3.x = pl->sectors[sec_nb].vertex[3].x - pl->where.x;
	vec3.y = pl->sectors[sec_nb].vertex[3].y - pl->where.y;
	
	vec = ft_vec3_add(vec2, vec3);// find diagonal between pl and door edges
	dist = sqrt(pow(vec.x, 2) + pow(vec.y, 2));

	vec4.x = pl->anglecos;
	vec4.y = pl->anglesin;
	vec = ft_vec3_normalize(vec);
	
	c = acos(ft_vec3_cosinus(vec4, vec));
	c = to_degrees(c);
	//printf("\nacos c==%f \n", c);
	//printf("\ndist==%d \n", dist);
	if ((c >= 0) && (c < 48) && (dist < 8))
		printf("\nITS A DOOOOR dist==%d deg==%f \n", dist, c);
	else
		printf("\nITS JUST WALL \n");
	return (1);
}

/*
** **************************************************************************
**	void door_button(t_player *pl, t_subevents *se)
**	Function to start lift door when button pressed
** **************************************************************************
*/

void		door_button(t_player *pl, t_subevents *se)
{
	int		d_nb;
	int		d_sec_nb;

	if (pl->door_all == -1)
		door_total(pl);
	else if (pl->door_all < 1)
		return ;
	d_nb = door_exist(pl);
	d_nb = 0;//always first
	pl->door_nb = d_nb;
	d_sec_nb = pl->doors[d_nb].nb;
	if ((pl->sectors[d_sec_nb].ceil) <= pl->doors[d_nb].max_d)
		se->wsad[4] = 1;
	else
		se->wsad[4] = 0;
	
	
}

/*
** **************************************************************************
**	void door(t_player *pl)
**	Function to door open process
** **************************************************************************
*/

void		door(t_player *pl, t_subevents *se)
{
	int		d_nb;
	int		d_sec_nb;

	
	d_nb = pl->door_nb;
	d_sec_nb = 0;
	if ((pl->door_all < 1) || (d_nb > pl->door_all))
		return ;
	door_exist(pl);
	d_sec_nb = pl->doors[d_nb].nb;
	/*if (((pl->sectors[d_sec_nb].ceil + pl->doors[d_nb].dir) \
	<= pl->doors[d_nb].max_d) && (se->wsad[4] == 1))
		pl->sectors[d_sec_nb].ceil += pl->doors[d_nb].dir;
	*/d_sec_nb = se->wsad[4] == 1;
}
