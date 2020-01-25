/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   motion.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: drafe <drafe@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/25 18:20:12 by drafe             #+#    #+#             */
/*   Updated: 2020/01/25 21:00:10 by drafe            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

/*
** **************************************************************************
**	void motion_move_pl(float dx, float dy, t_player *pl)
**	Function to move player and update anglesin/anglecos/sector
**	Check if this movement crosses one of this sector's edges
**	that have a neighboring sector on the other side.
**	Because the edge vertices of each sector are defined in
**	clockwise order, PointSide will always return -1 for a point
**	that is outside the sector and 0 or 1 for a point that is inside
** **************************************************************************
*/

void		motion_move_pl(float dx, float dy, t_player *pl)
{
	t_sector	*sect;
	t_xy		*vert;
	float		px;
	float		py;
	int			i;

	px = pl->where.x;
	py = pl->where.y;
	sect = &pl->sectors[pl->sector];
	vert = sect->vertex;
	i = -1;
	while (++i < sect->npoints)
		if (sect->neighbors[i] >= 0
			&& IntersectBox(px, py, px + dx, py + dy, vert[i].x, \
			vert[i].y, vert[i + 1].x, vert[i + 1].y)
			&& PointSide(px + dx, py + dy, vert[i].x, vert[i].y, \
			vert[i + 1].x, vert[i + 1].y) < 0)
		{
			pl->sector = sect->neighbors[i];
			break ;
		}
	pl->where.x += dx;
	pl->where.y += dy;
	pl->anglesin = sinf(pl->angle);
	pl->anglecos = cosf(pl->angle);
}

/*
** **************************************************************************
**	void motion_check(t_sect_ops *op, t_player *pl, t_others *ot, t_sub_ev *se)
**	Function to detect collisions when player move
** **************************************************************************
*/

static int	motion_chk_2(t_sect_ops *op, t_player *pl, int i)
{
	/* Check where the hole is. */
	op->hole_low = op->sect->neighbors[i] < 0 ? 9e9 : \
	max(op->sect->floor, pl->sectors[op->sect->neighbors[i]].floor);
	op->hole_high = op->sect->neighbors[i] < 0 ? -9e9 : \
	min(op->sect->ceil, pl->sectors[op->sect->neighbors[i]].ceil);
	/* Check whether we're bumping into a wall. */
	if (op->hole_high < pl->where.z + HEAD_H || \
	op->hole_low > pl->where.z - op->eye_h + NOT_JUMP_H)
	{
		/* Bumps into a wall! Slide along the wall. */
		/* This formula is from Wikipedia article "vector projection". */
		op->xd = op->vert[i + 1].x - op->vert[i].x;
		op->yd = op->vert[i + 1].y - op->vert[i].y;
		op->dx = op->xd * (op->dx * op->xd + op->yd * op->dy) / \
		(op->xd * op->xd + op->yd * op->yd);
		op->dy = op->yd * (op->dx * op->xd + op->yd * op->dy) / \
		(op->xd * op->xd + op->yd * op->yd);
		return (0);
	}
	return (1);
}

/*
** **************************************************************************
**	void motion_check(t_sect_ops *op, t_player *pl, t_others *ot, t_sub_ev *se)
**	Function to detect collisions when player move
** **************************************************************************
*/

void		motion_chk(t_sect_ops *op, t_player *pl, t_others *ot, t_sub_ev *se)
{
	int	i;

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
		if (IntersectBox(op->px, op->py, op->px + op->dx, op->py + op->dy, \
		op->vert[i].x, op->vert[i].y, op->vert[i + 1].x, op->vert[i + 1].y) \
		&& PointSide(op->px + op->dx, op->py + op->dy, op->vert[i].x, \
		op->vert[i].y, op->vert[i + 1].x, op->vert[i + 1].y) < 0)
			ot->moving = motion_chk_2(op, pl, i);
	}
	motion_move_pl(op->dx, op->dy, pl);
	se->falling = 1;
}
