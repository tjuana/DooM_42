/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_motion.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dorange- <dorange-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/25 18:20:12 by drafe             #+#    #+#             */
/*   Updated: 2020/02/16 14:26:51 by dorange-         ###   ########.fr       */
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
	t_new_xy		pt;
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
	float	point_side;
	int		inter;

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
		inter = intersectbox(
			(t_new_xy){op->px, op->py},
			(t_new_xy){op->px + op->dx, op->py + op->dy},
			(t_new_xy){op->vert[i].x, op->vert[i].y},
			(t_new_xy){op->vert[i + 1].x, op->vert[i + 1].y}
		);
		point_side = pointside(
			(t_new_xy){op->px + op->dx, op->py + op->dy},
			(t_new_xy){op->vert[i].x, op->vert[i].y},
			(t_new_xy){op->vert[i + 1].x, op->vert[i + 1].y}
		);
		if (inter && point_side < 0)
			ot->moving = motion_chk_2(op, pl, i);
	}
	motion_move_pl(&(t_new_xy){pl->velocity.x, pl->velocity.y}, pl);
}
