/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   door_detect.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: drafe <drafe@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/14 18:46:09 by drafe             #+#    #+#             */
/*   Updated: 2020/01/21 21:45:53 by drafe            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

/*
** **************************************************************************
**	static int vec2_cos(t_vector3 vec1, t_vector3 vec2)
**	Function to define door
** **************************************************************************
*/

static int		door_bool(int dist, float degree)
{
	if ((degree >= 0) && (degree < 125) && (dist == 0))
		return (dist);
	else if ((degree >= 0) && (degree < 67) && (dist == 1))
		return (dist);
	else if ((degree >= 0) && (degree < 50) && (dist == 2))
		return (dist);
	else if ((degree >= 0) && (degree < 38) && (dist == 3))
		return (dist);
	else if ((degree >= 0) && (degree < 31) && (dist == 4))
		return (dist);
	return (-1);
}

/*
** **************************************************************************
**	static int vec2_cos(t_vector3 vec1, t_vector3 vec2)
**	Function to define cos of two vec
** **************************************************************************
*/

static float	vec2_cos(t_vector3 vec1, t_vector3 vec2)
{
	float	res;
	float	tmp1;
	float	tmp2;

	tmp1 = sqrt(pow(vec1.x, 2) + pow(vec1.y, 2));
	tmp2 = sqrt(pow(vec2.x, 2) + pow(vec2.y, 2));
	res = (vec1.x * vec2.x + vec1.y * vec2.y);
	res = res / (tmp1 * tmp2);
	return (res);
}

/*
** **************************************************************************
**	static void door_v_find(t_player *pl)
**	Function to chooze nearest door vertexes
** **************************************************************************
*/

static int		door_vert_find(t_player *pl, t_vector3 *vec, int s_nb)
{
	int			dist;
	int			tmp_dist;
	int			i;
	int			j;

	i = -1;
	j = -1;
	dist = 6;
	tmp_dist = 0;
	while (++i < pl->sectors[s_nb].npoints)
	{
		j = -1;
		while(++j < pl->sectors[s_nb].npoints)
		{
			//printf("LFGK i==%d j==%d  x==%f y==%f \n", i, j, pl->sectors[s_nb].vertex[i].x, pl->sectors[s_nb].vertex[j].y);
			vec->x = (pl->sectors[s_nb].vertex[i].x + pl->sectors[s_nb].vertex[j].x) / 2;
			vec->y = (pl->sectors[s_nb].vertex[i].y + pl->sectors[s_nb].vertex[j].y) / 2;
			vec->x = vec->x - pl->where.x;
			vec->y = vec->y - pl->where.y;
			tmp_dist = (int)sqrt(pow(vec->x, 2) + pow(vec->y, 2));
			tmp_dist <= dist ? dist = tmp_dist : 0;
		}
	}
	return (dist);
}

/*
** **************************************************************************
**	static int door_dist(t_vector3 vec1, t_vector3 vec2)
**	Function to define distance to door
** **************************************************************************
*/

static int		door_dist(t_player *pl, int s_nb)
{
	t_vector3	vec;
	t_vector3	vec2;
	int			tmp_dist;

	tmp_dist = 6;
	tmp_dist = door_vert_find(pl, &vec, s_nb);
	vec2.x = pl->anglecos;
	vec2.y = pl->anglesin;
	vec = ft_vec3_normalize(vec);
	vec2 = ft_vec3_normalize(vec2);
	if (door_bool(tmp_dist, to_degrees(acos(vec2_cos(vec, vec2)))) == -1)
		return (6);
	return (tmp_dist);
}

/*
** **************************************************************************
**	static int door_exist(t_player *pl)
**	Function to return door sector nb in front of player
** **************************************************************************
*/

int				door_exist(t_player *pl)
{
	int		i;
	int		s_nb;
	int		dist;
	int		tmp_dist;
	int		door_sec_nb;

	i = -1;
	s_nb = -1;
	dist = 5;
	tmp_dist = 0;
	door_sec_nb = -1;
	while (++i < pl->sectors[pl->sector].npoints)
	{
		s_nb = pl->sectors[pl->sector].neighbors[i];
		if ((pl->sectors[pl->sector].neighbors[i] >= 0) && \
		(pl->sectors[s_nb].floor == 0 && pl->sectors[s_nb].ceil == 0))
		{
			tmp_dist = door_dist(pl, s_nb);
			if (tmp_dist <= dist)
			{
				dist = tmp_dist;
				door_sec_nb = s_nb;
			}
		}
	}
	return (door_sec_nb);
}
