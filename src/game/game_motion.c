/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_motion.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjuana <tjuana@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/25 18:20:12 by drafe             #+#    #+#             */
/*   Updated: 2020/02/13 14:34:25 by tjuana           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

static int	motion_move_pl2(t_new_sector *sect, \
t_new_xy *delt, int i, t_new_xy *pt)
{
	t_new_xy	*vert;
	float		point_side;
	int			inter;

	vert = sect->vertex;
	inter = intersectbox(*pt, sum_vectors_xy(*pt, *delt), vert[i], vert[i + 1]);
	point_side = pointside(sum_vectors_xy(*pt, *delt), vert[i], vert[i + 1]);
	if (sect->neighbors[i] < 0 && inter && point_side < 0)
		return (-666);
	if (inter && point_side < 0)
	{
		return (sect->neighbors[i]);
	}
	return (-777);
}

static int	motion_corner(t_new_sector *sect, int i, t_new_player *pl)
{
	float		len;
	float		len2;
	float		x;
	float		y;
	t_new_xy	*vert;

	vert = sect->vertex;
	x = pl->where.x + pl->velocity.x;
	y = pl->where.y + pl->velocity.y;
	len = sqrt(pow(vert[i].x - x, 2) + pow(vert[i].y - y, 2));
	len2 = sqrt(pow(vert[i + 1].x - x, 2) + pow(vert[i + 1].y - y, 2));
	if (len <= 0.1777 || len2 <= 0.1777)
	{
		pl->velocity.x = 0;
		pl->velocity.y = 0;
		return (0);
	}
	return (1);
}

/*
** **************************************************************************
**	void motion_move_pl(float dx, float dy, t_new_player *pl)
**	Function to move player and update anglesin/anglecos/sector
** **************************************************************************
*/

void		motion_move_pl(t_new_xy *delt, t_new_player *pl)
{
	t_new_sector	*sect;
	t_new_xy		pt;
	int				res;
	int				i;

	pt.x = pl->where.x;
	pt.y = pl->where.y;
	sect = &pl->sectors[pl->sector];
	i = -1;
	res = -1;
	while (++i < sect->npoints)
	{
		if ((res = motion_move_pl2(sect, delt, i, &pt)) == -777)
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
		return (0);
	}
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
	op->p.x = pl->where.x;
	op->p.y = pl->where.y;
	op->d.x = pl->velocity.x;
	op->d.y = pl->velocity.y;
	op->sect = &pl->sectors[pl->sector];
	op->vert = op->sect->vertex;
	while (++i < op->sect->npoints)
	{
		if (!motion_corner(&pl->sectors[pl->sector], i, pl))
			return ;
		if ((intersectbox(op->p, sum_vectors_xy(op->p, op->d), op->vert[i], op->vert[i + 1]) \
 && pointside(sum_vectors_xy(op->p, op->d), op->vert[i], op->vert[i + 1]) < 0))
			ot->moving = motion_chk_2(op, pl, i);
	}
	motion_move_pl(&(t_new_xy){pl->velocity.x, pl->velocity.y}, pl);
}
