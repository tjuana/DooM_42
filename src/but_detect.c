/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   but_detect.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: drafe <drafe@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/14 18:46:09 by drafe             #+#    #+#             */
/*   Updated: 2020/01/22 20:03:31 by drafe            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

/*
** **************************************************************************
**	static int but_bool(int dist, float degree)
**	Function to check angle between view vec and button center
** **************************************************************************
*/

static int		but_bool(int dist, float degree, float yaw)
{
	if ((degree >= 0) && (degree < 125) && (dist == 0))
		return (dist);
	else if ((degree >= 0) && (degree < 15) && (dist == 1) && \
	((to_degrees(yaw) < 100) && (to_degrees(yaw) > 0)))
		return (dist);
	else if ((degree >= 0) && (degree < 125) && (dist == 0))
		return (dist);
	else if ((degree >= 0) && (degree < 15) && (dist == 1) && \
	((to_degrees(yaw) > -100) && (to_degrees(yaw) <= 0)))
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
**	static int but_dist(t_vector3 vec1, t_vector3 vec2)
**	Function to define distance to door
** **************************************************************************
*/

static int		but_dist(t_player *pl, int s_nb)
{
	t_vector3	vec;
	t_vector3	vec2;
	int			tmp_dist;

	tmp_dist = 3;
	vec.x = (pl->sectors[s_nb].vertex[1].x + pl->sectors[s_nb].vertex[0].x) / 2;
	vec.y = (pl->sectors[s_nb].vertex[1].y + pl->sectors[s_nb].vertex[0].y) / 2;
	vec.x = vec.x - pl->where.x;
	vec.y = vec.y - pl->where.y;
	tmp_dist = (int)sqrt(pow(vec.x, 2) + pow(vec.y, 2));
	vec2.x = pl->anglecos;
	vec2.y = pl->anglesin;
	vec = ft_vec3_normalize(vec);
	vec2 = ft_vec3_normalize(vec2);
	//printf("dist==%d  deg==%f yaw==%f\n", tmp_dist, to_degrees(acos(vec2_cos(vec, vec2))), to_degrees(pl->yaw));
	if (but_bool(tmp_dist, to_degrees(acos(vec2_cos(vec, vec2))), pl->yaw) == -1)
		return (3);
	return (tmp_dist);
}

/*
** **************************************************************************
**	static int but_exist(t_player *pl)
**	Function to return button sector nb in front of player
** **************************************************************************
*/

int				but_detect(t_player *pl)
{
	int		i;
	int		s_nb;
	int		dist;
	int		tmp_dist;
	int		but_sec_nb;

	i = -1;
	s_nb = -1;
	dist = 3;
	tmp_dist = 0;
	but_sec_nb = -1;
	while (++i < pl->sectors[pl->sector].npoints)
	{
		s_nb = pl->sectors[pl->sector].neighbors[i];
		if ((pl->sectors[pl->sector].neighbors[i] >= 0) && \
		pl->sectors[s_nb].npoints == 2)
		{
			tmp_dist = but_dist(pl, s_nb);
			if (tmp_dist < dist)
			{
				dist = tmp_dist;
				but_sec_nb = s_nb;
			}
		}
	}
	printf("%d, %d\n", dist, but_sec_nb);
	return (but_sec_nb);
}
