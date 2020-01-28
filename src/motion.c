/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   motion.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: drafe <drafe@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/25 18:20:12 by drafe             #+#    #+#             */
/*   Updated: 2020/01/28 21:27:26 by drafe            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

/*
static int	motion_dist(t_player *pl, float dx, float dy, t_xy *vert, t_xy *vert2)
{	
	t_vector3	vec1;
	t_vector3	vec2;
	int		tmp_dist;

	tmp_dist = 2;
	vec1.x = vert2->x - vert->x;
	vec1.y = vert2->y - vert->y;//BC
	vec2.x = (pl->where.x + dx) - vert->x;
	vec2.y = (pl->where.y + dy) - vert->y;//AB
	tmp_dist = vxs(vec1.x, vec1.y, vec2.x, vec2.y);
	printf("dist==%d\n", tmp_dist);
	if (tmp_dist >= 1)
		return (1);
	return (0);
}


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
	//t_xy		*vec1;
	//t_xy		*vec2;
	t_sector	*sect;
	t_xy		*vert;
	float		px;
	float		py;
	int			i;

	sect = &pl->sectors[pl->sector];
	vert = sect->vertex;
	i = -1;
	px = pl->where.x;
	py = pl->where.y;
	while (++i < sect->npoints)
	{
		if (sect->neighbors[i] < 0 &&
			IntersectBox(px, py, px + dx, py + dy, vert[i].x, \
			vert[i].y, vert[i + 1].x, vert[i + 1].y)
			&& PointSide(px + dx, py + dy, vert[i].x, vert[i].y, \
			vert[i + 1].x, vert[i + 1].y) < 0)
		{
			return ;
		}
		if ((sect->neighbors[i] >= 0
			&& IntersectBox(px, py, px + dx, py + dy, vert[i].x, \
			vert[i].y, vert[i + 1].x, vert[i + 1].y)
			&& PointSide(px + dx, py + dy, vert[i].x, vert[i].y, \
			vert[i + 1].x, vert[i + 1].y) < 0))
		{
			pl->sector = sect->neighbors[i];
			break ;
		}
	}

	//motion_dist(pl, dx, dy, vec1, vec2);
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
		printf("bump\n");
		/* Bumps into a wall! Slide along the wall. */
		/* This formula is from Wikipedia article "vector projection". */
		op->xd = op->vert[i + 1].x - op->vert[i].x;
		op->yd = op->vert[i + 1].y - op->vert[i].y;;
		op->dx = op->xd * (op->dx * op->xd + op->yd * op->dy) / \
		(op->xd * op->xd + op->yd * op->yd);
		op->dy = op->yd * (op->dx * op->xd + op->yd * op->dy) / \
		(op->xd * op->xd + op->yd * op->yd);		/**/
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
		{
			ot->moving = motion_chk_2(op, pl, i);
		}
	}

	motion_move_pl(op->dx, op->dy, pl);
	se->falling = 1;
	return ;

}
