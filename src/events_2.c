/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events_2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: drafe <drafe@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/25 18:04:05 by drafe             #+#    #+#             */
/*   Updated: 2020/01/25 20:28:37 by drafe            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

/*
** **************************************************************************
**	static void events_vel_2(t_player *pl, t_sub_ev *se, t_others *ot)
**	Function manage player move
** **************************************************************************
*/

static void	events_vel_2(t_player *pl, t_sub_ev *se, t_others *ot)
{
	float	speed;
	int		push;

	push = (se->wsad[0] || se->wsad[1] || se->wsad[2] || se->wsad[3]);
	speed = push ? 0.4 : 0.2;
	pl->velocity.x = pl->velocity.x * (1 - speed) + ot->move_vec[0] * speed;
	pl->velocity.y = pl->velocity.y * (1 - speed) + ot->move_vec[1] * speed;
	push == 1 ? ot->moving = 1 : ot->moving;
}

/*
** **************************************************************************
**	void events_vel_dir(t_player *pl, t_sub_ev *se, t_others *ot)
**	Function manage player velocity
** **************************************************************************
*/

void		events_vel(t_player *pl, t_sub_ev *se, t_others *ot)
{
	ot->move_vec[0] = 0.f;
	ot->move_vec[1] = 0.f;
	if (se->wsad[0])
	{
		ot->move_vec[0] += pl->anglecos * 0.2f;
		ot->move_vec[1] += pl->anglesin * 0.2f;
	}
	if (se->wsad[1])
	{
		ot->move_vec[0] -= pl->anglecos * 0.2f;
		ot->move_vec[1] -= pl->anglesin * 0.2f;
	}
	if (se->wsad[2])
	{
		ot->move_vec[0] += pl->anglesin * 0.2f;
		ot->move_vec[1] -= pl->anglecos * 0.2f;
	}
	if (se->wsad[3])
	{
		ot->move_vec[0] -= pl->anglesin * 0.2f;
		ot->move_vec[1] += pl->anglecos * 0.2f;
	}
	events_vel_2(pl, se, ot);
}

/*
** **************************************************************************
**	void jumps(t_subevents *se, t_player *pl, t_sector_ops *op, t_others *ot)
**	Function manage jumps
** **************************************************************************
*/

void		events_jumps(t_sub_ev *se, t_player *pl, \
				t_sect_ops *op, t_others *ot)
{
	float	nextz;

	nextz = 0;
	if (se->falling == 0)
		return ;
	pl->velocity.z -= 0.015f;
	nextz = pl->where.z + pl->velocity.z;
	if (pl->velocity.z < 0 && nextz < pl->sectors[pl->sector].floor + op->eye_h)
	{
		pl->where.z = pl->sectors[pl->sector].floor + op->eye_h;
		pl->velocity.z = 0;
		se->falling = 0;
		se->ground = 1;
	}
	else if (pl->velocity.z > 0 && nextz > pl->sectors[pl->sector].ceil)
	{
		pl->velocity.z = 0;
		se->falling = 1;
	}
	if (se->falling)
	{
		pl->where.z += pl->velocity.z;
		ot->moving = 1;
	}
}

/*
** **************************************************************************
**	void mouse_movement(t_mouse *ms, t_player *pl)
**	Function manage mouse
** **************************************************************************
*/

void		events_mouse_move(t_mouse *ms, t_player *pl)
{
	SDL_SetRelativeMouseMode(1);
	SDL_GetRelativeMouseState(&ms->x, &ms->y);
	pl->angle += ms->x * 0.03f;
	ms->yaw = clamp(ms->yaw + ms->y * 0.05f, -5, 5);
	pl->yaw = ms->yaw - pl->velocity.z * 0.5f;
}
