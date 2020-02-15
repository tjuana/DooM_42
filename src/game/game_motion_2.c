/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_motion_2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: drafe <drafe@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/25 18:20:12 by drafe             #+#    #+#             */
/*   Updated: 2020/02/15 21:23:10 by drafe            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

// static int	motion_chk_z(t_new_xy *delt, t_new_player *pl, int i, int sec_nb)
// {
// 	float hole_low = 1000;
// 	float hole_high = -1000;
// 	if (pl->sectors[sec_nb].neighbors >= 0)
// 	{
// 		hole_low = max(sect->floor, \
// 		pl->sectors[sect->neighbors[i]].floor);
// 		hole_high = min(sect->ceil, \
// 		pl->sectors[op->sect->neighbors[i]].ceil);
// 	}
// 	if ((hole_high < pl->where.z + HEAD_H || \
// 	hole_low > pl->where.z - op->eye_h + NOT_JUMP_H))
// 	{
// 		op->xd = op->vert[i + 1].x - op->vert[i].x;
// 		op->yd = op->vert[i + 1].y - op->vert[i].y;
// 		pl->velocity.x = op->xd * ((op->dx * op->xd + op->dy * op->yd) / (\
// 		op->xd * op->xd + op->yd * op->yd));
// 		pl->velocity.y = op->yd * ((op->dx * op->xd + op->dy * op->yd) / (\
// 		op->xd * op->xd + op->yd * op->yd));
// 		printf("CASE:::1\n");
// 		return (0);
// 	}
// }

/*
** **************************************************************************
**	void motion_move_pl(float dx, float dy, t_new_player *pl)
**	Function to check next sector in the way of the player
** **************************************************************************
*/

static int	motion_chk_next_sec(t_new_xy *delt, t_new_player *pl, int sec_nb)
{
	t_new_sector	*sect_next;
	t_new_xy		*vert;
	float			point_side;
	int				inter;
	int				i;

	i = -1;
	if (sec_nb < 0)
		return (-777);
	sect_next = &pl->sectors[sec_nb];
	vert = sect_next->vertex;
	while (++i < sect_next->npoints)
	{
		inter = IntersectBox(pl->where.x, pl->where.y, pl->where.x + delt->x, \
		pl->where.y + delt->y, vert[i].x, vert[i].y, vert[i + 1].x, \
		vert[i + 1].y);
		point_side = PointSide(pl->where.x + delt->x, pl->where.y + delt->y, \
		vert[i].x, vert[i].y, vert[i + 1].x, vert[i + 1].y);
		if (sect_next->neighbors[i] < 0 && inter && point_side < 0)
			return (-666);
		if (inter && point_side < 0 )
			return (motion_chk_next_sec(delt, pl, sect_next->neighbors[i]));
	}
	return (sec_nb);
}

/*
** **************************************************************************
**	void motion_move_pl(float dx, float dy, t_new_player *pl)
**	Function to check neighbor sector in the way of the player
** **************************************************************************
*/

int			motion_chk_sec(t_new_sector *sect, \
t_new_xy *delt, int i, t_new_player *pl)
{
	t_new_xy		*vert;
	float			point_side;
	int				inter;

	vert = sect->vertex;
	inter = IntersectBox(pl->where.x, pl->where.y, pl->where.x + delt->x, \
	pl->where.y + delt->y, vert[i].x, vert[i].y, vert[i + 1].x, vert[i + 1].y);
	point_side = PointSide(pl->where.x + delt->x, pl->where.y + delt->y, \
	vert[i].x, vert[i].y, vert[i + 1].x, vert[i + 1].y);
	if (sect->neighbors[i] < 0 && inter && point_side < 0)
		return (-666);
	//motion_chk_z(delt, pl, sect->neighbors[i]);
	if (inter && point_side < 0)
		return (motion_chk_next_sec(delt, pl, sect->neighbors[i]));
	return (-777);
}
