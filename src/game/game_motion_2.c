/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_motion_2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dorange- <dorange-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/25 18:20:12 by drafe             #+#    #+#             */
/*   Updated: 2020/02/19 18:26:12 by dorange-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

/*
** **************************************************************************
**	void ft_game_motion_move_pl(float dx, float dy, t_new_player *pl)
**	Function to check next sector in the way of the player
** **************************************************************************
*/

static int	ft_game_motion_chk_next_sec(t_new_xy *delt, t_new_player *pl, int sec_nb)
{
	t_new_sector	*sect_next;
	t_new_xy		*vert;
	float			point_side;
	int				inter;
	int				i;

	if ((i = -1) && sec_nb < 0)
		return (-777);
	sect_next = &pl->sectors[sec_nb];
	vert = sect_next->vertex;
	while (++i < sect_next->npoints)
	{
		inter = ft_math_intersectbox((t_new_xy){pl->pos.x, pl->pos.y}, (t_new_xy)\
		{pl->pos.x + delt->x, pl->pos.y + delt->y}, vert[i], vert[i + 1]);
		point_side = ft_math_pointside((t_new_xy){pl->pos.x + delt->x, pl->pos.y + \
		delt->y}, vert[i], vert[i + 1]);
		if (sect_next->neighbors[i] >= 0 && \
		pl->sectors[sec_nb].floor - pl->pos.z > -4)
			return (-666);
		if (sect_next->neighbors[i] < 0 && inter && point_side < 0)
			return (-666);
		if (inter && point_side < 0)
			return (ft_game_motion_chk_next_sec(delt, pl, sect_next->neighbors[i]));
	}
	return (sec_nb);
}

/*
** **************************************************************************
**	void ft_game_motion_move_pl(float dx, float dy, t_new_player *pl)
**	Function to check neighbor sector in the way of the player
** **************************************************************************
*/

int			ft_game_motion_chk_sec(t_new_sector *sect, \
t_new_xy *delt, int i, t_new_player *pl)
{
	t_new_xy		*vert;
	float			point_side;
	int				inter;

	vert = sect->vertex;
	inter = ft_math_intersectbox((t_new_xy){pl->pos.x, pl->pos.y}, (t_new_xy)\
	{pl->pos.x + delt->x, pl->pos.y + delt->y}, vert[i], vert[i + 1]);
	point_side = ft_math_pointside((t_new_xy){pl->pos.x + delt->x, pl->pos.y + \
	delt->y}, vert[i], vert[i + 1]);
	if (sect->neighbors[i] < 0 && inter && point_side < 0)
		return (-666);
	if (inter && point_side < 0)
		return (ft_game_motion_chk_next_sec(delt, pl, sect->neighbors[i]));
	return (-777);
}
