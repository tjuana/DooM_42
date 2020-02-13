/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_motion.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: drafe <drafe@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/25 18:20:12 by drafe             #+#    #+#             */
/*   Updated: 2020/02/13 18:59:33 by drafe            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

/*
** **************************************************************************
**	void motion_move_pl(float dx, float dy, t_new_player *pl)
**	Function to move player and update anglesin/anglecos/sector
** **************************************************************************
*/

void		motion_move_pl(t_new_xy *delt, t_new_player *pl)
{
	t_new_sector	*sect;
	int				res;
	int				i;

	sect = &pl->sectors[pl->sector];
	i = -1;
	res = -1;
	while (++i < sect->npoints)
	{
		if ((res = motion_chk_sec(sect, delt, i, pl)) == -777)
			continue ;
		else if (res == -666)
			return ;
		else
		{
			pl->sector = res;
			break ;
		}
	}
	pl->where.x += delt->x;
	pl->where.y += delt->y;
}

/*
** **************************************************************************
**	void motion_check(t_new_sect_ops *op, t_new_player *pl,
**	t_new_others *ot, t_new_sub_ev *se)
**	Function to detect collisions when player move
** **************************************************************************
*/

static int	motion_chk_2(t_new_sect_ops *op, t_new_player *pl, int i)
{
	op->hole_low = 1000;
	op->hole_high = -1000;
	if (op->sect->neighbors[i] >= 0)
	{
		op->hole_low = max(op->sect->floor, \
		pl->sectors[op->sect->neighbors[i]].floor);
		op->hole_high = min(op->sect->ceil, \
		pl->sectors[op->sect->neighbors[i]].ceil);
	}
	if ((op->hole_high < pl->where.z + HEAD_H || \
	op->hole_low > pl->where.z - op->eye_h + NOT_JUMP_H))
	{
		op->xd = op->vert[i + 1].x - op->vert[i].x;
		op->yd = op->vert[i + 1].y - op->vert[i].y;
		pl->velocity.x = op->xd * ((op->dx * op->xd + op->dy * op->yd) / (\
		op->xd * op->xd + op->yd * op->yd));
		pl->velocity.y = op->yd * ((op->dx * op->xd + op->dy * op->yd) / (\
		op->xd * op->xd + op->yd * op->yd));
		printf("CASE:::1\n");
		return (0);
	}
		printf("CASE:::2\n");
	return (1);
}

/*
** **************************************************************************
**	void motion_check(t_new_sect_ops *op, t_new_player *pl,
**	t_new_others *ot, t_new_sub_ev *se)
**	Function to detect collisions when player move
** **************************************************************************
*/

void		motion_chk(t_new_sect_ops *op, t_new_player *pl, \
t_new_others *ot, t_new_sub_ev *se)
{
	int		i;

	i = -1;
	if (ot->moving != 1)
		return ;
	op->px = pl->where.x;
	op->py = pl->where.y;
	op->dx = pl->velocity.x;
	op->dy = pl->velocity.y;
	op->sect = &pl->sectors[pl->sector];
	op->vert = op->sect->vertex;
	while (++i < op->sect->npoints)
	{
		if ((IntersectBox(op->px, op->py, op->px + op->dx, op->py + op->dy, \
		op->vert[i].x, op->vert[i].y, op->vert[i + 1].x, op->vert[i + 1].y) \
		&& PointSide(op->px + op->dx, op->py + op->dy, op->vert[i].x, \
		op->vert[i].y, op->vert[i + 1].x, op->vert[i + 1].y) < 0))
			ot->moving = motion_chk_2(op, pl, i);
	}
	motion_move_pl(&(t_new_xy){pl->velocity.x, pl->velocity.y}, pl);
	se->falling = 1;
}
