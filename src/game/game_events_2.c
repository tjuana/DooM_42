/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_events_2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjuana <tjuana@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/25 18:04:05 by drafe             #+#    #+#             */
/*   Updated: 2020/02/13 15:22:18 by tjuana           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

/*
** **************************************************************************
**	static void events_vel_2(t_new_player *pl, t_new_sub_ev *se,
**	\ t_new_others *ot)
**	Function manage player move
** **************************************************************************
*/

static void	events_vel_2(t_new_player *pl, t_new_sub_ev *se, t_new_others *ot)
{
	float	speed;
	int		push;

	if (se->wsad[3])
	{
		ot->move_vec[0] -= pl->anglesin * 0.37;
		ot->move_vec[1] += pl->anglecos * 0.37;
	}
	push = (se->wsad[0] || se->wsad[1] || se->wsad[2] || se->wsad[3]);
	speed = push ? 0.4 : 0.2;
	pl->velocity.x = pl->velocity.x * (1 - speed) + ot->move_vec[0] * speed;
	pl->velocity.y = pl->velocity.y * (1 - speed) + ot->move_vec[1] * speed;
	push == 1 ? ot->moving = 1 : ot->moving;
}

/*
** **************************************************************************
**	void events_vel_dir(t_new_player *pl, t_new_sub_ev *se, t_new_others *ot)
**	Function manage player velocity
** **************************************************************************
*/

void		events_vel(t_new_player *pl, t_new_sub_ev *se, t_new_others *ot)
{
	float	speed;

	speed = 0.37;
	ot->move_vec[0] = 0;
	ot->move_vec[1] = 0;
	if (se->wsad[0])
	{
		ot->move_vec[0] += pl->anglecos * (speed + speed * se->wsad[6]);
		ot->move_vec[1] += pl->anglesin * (speed + speed * se->wsad[6]);
	}
	if (se->wsad[1])
	{
		ot->move_vec[0] -= pl->anglecos * speed;
		ot->move_vec[1] -= pl->anglesin * speed;
	}
	if (se->wsad[2])
	{
		ot->move_vec[0] += pl->anglesin * speed;
		ot->move_vec[1] -= pl->anglecos * speed;
	}
	events_vel_2(pl, se, ot);
}

/*
** **************************************************************************
**	void jumps(t_subevents *se, t_new_player *pl,
**	t_new_sector_ops *op, t_new_others *ot)
**	Function manage jumps
** **************************************************************************
*/

void		events_jumps(t_new_sub_ev *se, t_new_player *pl, \
				t_new_sect_ops *op, t_new_others *ot)
{
	float	z;

	z = 0;
	if (se->falling == 0)
		return ;
	pl->velocity.z -= 0.005;//0.0005;//0.015;
	z = pl->where.z + pl->velocity.z;
	if (pl->velocity.z < 0 && z < pl->sectors[pl->sector].floor + op->eye_h)
	{
		pl->where.z = pl->sectors[pl->sector].floor + op->eye_h;
		pl->velocity.z = 0;
		se->falling = 0;
		se->ground = 1;
	}
	else if (pl->velocity.z > 0 && z > pl->sectors[pl->sector].ceil)
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
**	void mouse_movement(t_new_mouse *ms, t_new_player *pl)
**	Function manage mouse
** **************************************************************************
*/

void		events_new_mouse_move(t_new_mouse *ms, t_new_player *pl)
{
	SDL_GetRelativeMouseState(&ms->x, &ms->y);
	SDL_SetRelativeMouseMode(1);
	pl->angle += ms->x * 0.03f;
	ms->yaw = clamp(ms->yaw + ms->y * 0.05f, -5, 5);
	pl->yaw = ms->yaw - pl->velocity.z * 0.5f;
	pl->anglesin = sinf(pl->angle);
	pl->anglecos = cosf(pl->angle);
}
