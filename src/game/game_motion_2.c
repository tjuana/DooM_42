/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_motion_2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dorange- <dorange-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/25 18:20:12 by drafe             #+#    #+#             */
/*   Updated: 2020/02/15 20:43:05 by dorange-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

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
		// if (sect_next->neighbors[i] >= 0 && pl->sectors[sec_nb].floor - pl->where.z > -4.0)
			// return (-666);
		if (sect_next->neighbors[i] < 0 && inter && point_side < 0)
			return (-666);
		if (inter && point_side < 0)
			return (sect_next->neighbors[i]);
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
	if (inter && point_side < 0)
		return (motion_chk_next_sec(delt, pl, sect->neighbors[i]));
	return (-777);
}