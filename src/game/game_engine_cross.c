/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_ft_game_engine_cross.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjuana <tjuana@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/15 17:32:04 by nshelly           #+#    #+#             */
/*   Updated: 2020/02/17 18:04:34 by tjuana           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

void			ft_game_xy_vertex_of_sectors(t_vector3 *v_start, t_vector3 *v_end,\
	t_new_player *pl)
{
	v_start->x = pl->sectors[pl->cycle.current->sec_nb].vertex[pl->s].x  \
	- pl->pos.x;
	v_start->y = pl->sectors[pl->cycle.current->sec_nb].vertex[pl->s + 0].y - \
	pl->pos.y;
	v_end->x = pl->sectors[pl->cycle.current->sec_nb].vertex[pl->s + 1].x - \
	pl->pos.x;
	v_end->y = pl->sectors[pl->cycle.current->sec_nb].vertex[pl->s + 1].y - \
	pl->pos.y;

	pl->t1.x = v_start->x * pl->anglesin - v_start->y * pl->anglecos;
	pl->t1.y = v_start->x * pl->anglecos + v_start->y * pl->anglesin;
	pl->t2.x = v_end->x * pl->anglesin - v_end->y * pl->anglecos;
	pl->t2.y = v_end->x * pl->anglecos + v_end->y * pl->anglesin;
}

static void			ft_game_xy_vertex_of_sectors_sprite(t_vector3 *v_start, t_vector3 *v_end,\
	t_new_player *pl)
{
    v_start->x = 10 - pl->pos.x;
    v_start->y = 5 - pl->pos.y;
    v_end->x = 10 - pl->pos.x;
    v_end->y = 10 - pl->pos.y;

    pl->t1.x = v_start->x * pl->anglesin - v_start->y * pl->anglecos;
    pl->t1.y = v_start->x * pl->anglecos + v_start->y * pl->anglesin;
    pl->t2.x = v_end->x * pl->anglesin - v_end->y * pl->anglecos;
    pl->t2.y = v_end->x * pl->anglecos + v_end->y * pl->anglesin;
}

/*
** Acquire the x,y coordinates of the two endpoints
** (vertices) of this edge of the sector
** also rotate them around the player's view
*/

static void		ft_game_engine_cross2(t_new_player *pl, t_vector3 i1, t_vector3 i2)
{
	pl->org1.x = pl->t1.x;
	pl->org1.y = pl->t1.y;
	pl->org2.x = pl->t2.x;
	pl->org2.y = pl->t2.y;
	(pl->t1.y < pl->near_point.y && i1.y > 0) ? pl->t1 = i1 : pl->t1;
	(pl->t1.y < pl->near_point.y  && i1.y < 0) ? pl->t1 = i2 : pl->t1;
	(pl->t2.y < pl->near_point.y  && i1.y > 0) ? pl->t2 = i1 : pl->t2;
	(pl->t2.y < pl->near_point.y  && i1.y < 0) ? pl->t2 = i2 : pl->t2;
	if (fabs(pl->t2.x - pl->t1.x) > fabs(pl->t2.y - pl->t1.y))
	{
		pl->u0 = ((pl->t1.x - pl->org1.x) * 900 / (pl->org2.x - pl->org1.x));
		pl->u1 = ((pl->t2.x - pl->org1.x) * 900 / (pl->org2.x - pl->org1.x));
	}
	else
	{
		pl->u0 = ((pl->t1.y - pl->org1.y) * 900 /
				(pl->org2.y - pl->org1.y));
		pl->u1 = ((pl->t2.y - pl->org1.y) * 900 /
				(pl->org2.y - pl->org1.y));
	}
}

/*
** **************************************************************************
**	int ft_game_engine_cross(t_new_player *pl, int sec_n, unsigned s)
**	Function to find intersections and set t1 & t2
**	t1.y was tz1 before recontruction
** **************************************************************************
*/

int				ft_game_engine_cross(t_new_player *pl)
{
	t_vector3	i1;
	t_vector3	i2;
	t_vector3	v_start;
	t_vector3	v_end;

	ft_game_xy_vertex_of_sectors(&v_start, &v_end, pl);
	if ((pl->t1.y <= 0) && (pl->t2.y <= 0))
	{
		return (0);
	}
	pl->u0 = 0;
	pl->u1 = 900;
	if ((pl->t1.y <= 0) || (pl->t2.y <= 0))
	{
		pl->near_point.x = pl->near_point.x * (-1);
		pl->far_point.x = pl->far_point.x * (-1);
		i1 = ft_math_intersect(pl->t1, pl->t2, pl->near_point, pl->far_point);
		pl->near_point.x = pl->near_point.x * (-1);
		pl->far_point.x = pl->far_point.x * (-1);
		i2 = ft_math_intersect(pl->t1, pl->t2, pl->near_point, pl->far_point);
		if (i1.y < 0 && i2.y < 0)
			return (0);
		ft_game_engine_cross2(pl, i1, i2);
	}
	return (1);
}

int				ft_game_engine_cross_sprite(t_new_player *pl)
{
	t_vector3	i1;
	t_vector3	i2;
	t_vector3	v_start;
	t_vector3	v_end;

	ft_game_xy_vertex_of_sectors_sprite(&v_start, &v_end, pl);
	if ((pl->t1.y <= 0) && (pl->t2.y <= 0))
	{
		return (0);
	}
	pl->u0 = 0;
	pl->u1 = 900;
	if ((pl->t1.y <= 0) || (pl->t2.y <= 0))
	{
		pl->near_point.x = pl->near_point.x * (-1);
		pl->far_point.x = pl->far_point.x * (-1);
		i1 = ft_math_intersect(pl->t1, pl->t2, pl->near_point, pl->far_point);
		pl->near_point.x = pl->near_point.x * (-1);
		pl->far_point.x = pl->far_point.x * (-1);
		i2 = ft_math_intersect(pl->t1, pl->t2, pl->near_point, pl->far_point);
		if (i1.y < 0 && i2.y < 0)
			return (0);
		ft_game_engine_cross2(pl, i1, i2);
	}

	return (1);
}

