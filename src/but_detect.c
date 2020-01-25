/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   but_detect.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: drafe <drafe@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/25 21:13:51 by drafe             #+#    #+#             */
/*   Updated: 2020/01/25 21:37:41 by drafe            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

/*
** **************************************************************************
**	static int but_bool(int dist, float degree, float yaw)
**	Function to check angle between view vec and button center
** **************************************************************************
*/

static int	but_bool(int dist, float degree, float yaw)
{
	if ((degree >= 0) && (degree < 125) && (dist == 0))
		return (dist);
	else if ((degree >= 0) && (degree < 15) && (dist == 1) && \
	((to_deg(yaw) < 100) && (to_deg(yaw) > 0)))
		return (dist);
	else if ((degree >= 0) && (degree < 125) && (dist == 0))
		return (dist);
	else if ((degree >= 0) && (degree < 15) && (dist == 1) && \
	((to_deg(yaw) > -100) && (to_deg(yaw) <= 0)))
		return (dist);
	return (-1);
}

/*
** **************************************************************************
**	static int but_dist(t_player *pl, int s_nb)
**	Function to define distance to button
** **************************************************************************
*/

static int	but_dist(t_player *pl, int s_nb)
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
	if (but_bool(tmp_dist, to_deg(acos(vec2_cos(vec, vec2))), pl->yaw) == -1)
		return (3);
	return (tmp_dist);
}

/*
** **************************************************************************
**	int but_detect(t_player *pl)
**	Function to return button sector nb in front of player
** **************************************************************************
*/

int			but_detect(t_player *pl)
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
		(pl->sectors[s_nb].npoints == 2))
		{
			tmp_dist = but_dist(pl, s_nb);
			if ((tmp_dist < dist) && (but_sec_nb = s_nb))
				dist = tmp_dist;
		}
	}
	return (but_sec_nb);
}
