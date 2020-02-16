/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_motion.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjuana <tjuana@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/25 18:20:12 by drafe             #+#    #+#             */
/*   Updated: 2020/02/16 17:31:15 by tjuana           ###   ########.fr       */
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
	pl->pos.x += delt->x;
	pl->pos.y += delt->y;
}

/*
** **************************************************************************
**	void motion_check(t_new_player *pl, int i)
**	Function to slip the player
** **************************************************************************
*/

static int	motion_slide(t_new_player *pl, t_new_sector *sect, \
	t_new_xy *vert, int i)
{
	float	wall_dx;
	float	wall_dy;

	pl->hole.x = 1000;
	pl->hole.y = -1000;
	if (sect->neighbors[i] >= 0)
	{
		pl->hole.x = max(sect->floor, \
		pl->sectors[sect->neighbors[i]].floor);
		pl->hole.y = min(sect->ceil, \
		pl->sectors[sect->neighbors[i]].ceil);
	}
	if ((pl->hole.y < pl->pos.z + HEAD_H || \
	pl->hole.x > pl->pos.z - pl->hole.z + NOT_JUMP_H))
	{
		wall_dx = vert[i + 1].x - vert[i].x;
		wall_dy = vert[i + 1].y - vert[i].y;
		pl->velo.x = wall_dx * ((wall_dx * pl->velo.x + wall_dy * \
		pl->velo.y) / (pow(wall_dx, 2) + pow(wall_dy, 2)));
		pl->velo.y = wall_dy * ((wall_dx * pl->velo.x + wall_dy * \
		pl->velo.y) / (pow(wall_dx, 2) + pow(wall_dy, 2)));
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

void		motion_chk(t_new_player *pl, t_new_others *ot, t_new_sub_ev *se)
{
	int				i;
	int				inter;
	float			point_side;
	t_new_sector	*sect;
	t_new_xy		*vert;

	i = -1;
	if (ot->moving != 1)
		return ;
	sect = &pl->sectors[pl->sector];
	vert = sect->vertex;
	while (++i < sect->npoints)
	{
		inter = intersectbox((t_new_xy){pl->pos.x, pl->pos.y}, (t_new_xy){\
		pl->pos.x + pl->velo.x, pl->pos.y + pl->velo.y}, vert[i], vert[i + 1]);
		point_side = pointside((t_new_xy){pl->pos.x + pl->velo.x, \
		pl->pos.y + pl->velo.y}, vert[i], vert[i + 1]);
		if (inter && point_side < 0)
			ot->moving = motion_slide(pl, sect, vert, i);
	}
	motion_move_pl(&(t_new_xy){pl->velo.x, pl->velo.y}, pl);
}
