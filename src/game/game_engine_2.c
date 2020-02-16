/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_engine_2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dorange- <dorange-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/15 17:32:04 by nshelly           #+#    #+#             */
/*   Updated: 2020/02/16 12:47:29 by dorange-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

static	void	operation_cero(int x, t_new_player *pl)
{
	pl->txtx = (int)((pl->u0 * ((pl->x2 - x) * pl->t2.y) + pl->u1 * \
		((x - pl->x1) * pl->t1.y)) / ((pl->x2 - x) * pl->t2.y +\
		(x - pl->x1) * pl->t1.y));
	pl->floor.ya = (x - pl->x1) * (pl->ceil.y2a - pl->ceil.y1a) / (pl->x2\
		- pl->x1) + pl->ceil.y1a;
	pl->ceil.cya = clamp(pl->floor.ya, pl->y_top[x], pl->y_bot[x]);
	pl->floor.yb = (x - pl->x1) * (pl->floor.y2b - pl->floor.y1b) / (pl->x2\
		- pl->x1) + pl->floor.y1b;
	pl->ceil.cyb = clamp(pl->floor.yb, pl->y_top[x], pl->y_bot[x]);
}

void			engine_calcs(int x, t_new_player *pl, int operation)
{
	if (operation == 0)
		operation_cero(x, pl);
	if (operation == 1)
	{
		pl->t.hei = pl->t.y < pl->ceil.cya ? pl->ceil.yceil : pl->floor.yfloor;
		pl->t.mapz = pl->t.hei * WIN_H * V_FOV / ((WIN_H / 2 - \
		(float)pl->t.y) - pl->yaw * WIN_H * V_FOV);
		pl->t.mapx = pl->t.mapz * (WIN_W / 2 - (float)pl->t.x) \
		/ (WIN_W * (H_FOV));
		pl->t.txtx1 = (unsigned int)(((pl->t.mapz * pl->anglecos + pl->t.mapx *\
		pl->anglesin) + pl->where.x) * 256);
		pl->t.txtz = (unsigned int)(((pl->t.mapz * pl->anglesin - pl->t.mapx * \
		pl->anglecos) + pl->where.y) * 256);
	}
	else if (operation == 2)
	{
		pl->floor.nya = (x - pl->x1) * (pl->ceil.ny2a - pl->ceil.ny1a) /\
		(pl->x2 - pl->x1) + pl->ceil.ny1a;
		pl->ceil.cnya = clamp(pl->floor.nya, pl->y_top[x], pl->y_bot[x]);
		pl->floor.nyb = (x - pl->x1) * (pl->floor.ny2b - pl->floor.ny1b)\
		/ (pl->x2 - pl->x1) + pl->floor.ny1b;
		pl->ceil.cnyb = clamp(pl->floor.nyb, pl->y_top[x], pl->y_bot[x]);
	}
}

void			draw_ceil_floor(int x, t_new_player *pl)
{
	pl->t.y = pl->y_top[x];
	pl->t.x = x;
	while (++pl->t.y <= pl->y_bot[x])
	{
		if (pl->t.y >= pl->ceil.cya && pl->t.y <= pl->ceil.cyb)
		{
			pl->t.y = pl->ceil.cyb;
			continue;
		}
		// continue;
		engine_calcs(x, pl, 1);
		if (pl->t.y < pl->ceil.cya && pl->sect->ceil != 20)
			pix1(pl, ROCK2);
		if (pl->t.y < pl->ceil.cya && pl->sect->ceil == 20)
			pix_sky(&pl->t, pl);
			// ft_put_pixel_to_surface(pl, &pl->t, SKY);
		if (pl->t.y >= pl->ceil.cya)
			pix1(pl, GREEN);
			// ft_put_pixel_to_surface(pl, &pl->t, GREEN);
	}
}

/*
** **************************************************************************
**	static void engine_ceil_floor(t_new_player *pl, int x, int *z, int neib)
**	Function to draw ceil and floor lines and lines betwen them
** **************************************************************************
*/

static void		engine_ceil_floor(t_new_player *pl, int x, int neib)
{
	engine_calcs(x, pl, 0);
	draw_ceil_floor(x, pl);
	if (neib >= 0)
	{
		engine_calcs(x, pl, 2);
		draw_walls(x, pl, WALL_TOP, pl->n);
		pl->y_top[x] = clamp(max(pl->ceil.cya, pl->ceil.cnya),\
		pl->y_top[x], WIN_H - 1);
		draw_walls(x, pl, WALL_BOTT, pl->n);
		pl->y_bot[x] = clamp(min(pl->ceil.cyb, pl->ceil.cnyb), 0, pl->y_bot[x]);
	}
	else
	{
		draw_walls(x, pl, WALL_FULL, pl->n);
		draw_graffiti(x, pl, WALL_FULL, 12);
	}
}

/*
** **************************************************************************
**	void engine_ceil_floor(t_new_player *pl, int neib)
**	Function to draw all needed lines
** **************************************************************************
*/

void			engine_put_lines(t_new_player *pl, int neib)
{
	int	x;

	pl->beginx = (int)fmax((double)pl->x1, (double)pl->cycle.current->sx1);
	pl->endx = (int)fmin((double)pl->x2, (double)pl->cycle.current->sx2);
	x = pl->beginx;
	while (++x <= pl->endx)
		engine_ceil_floor(pl, x, neib);
	if (neib >= 0 && pl->endx >= pl->beginx && (pl->cycle.head + MAX_QUEUE \
		+ 1 - pl->cycle.tail) % MAX_QUEUE)
	{
		pl->cycle.head->sec_nb = neib;
		pl->cycle.head->sx1 = pl->beginx;
		pl->cycle.head->sx2 = pl->endx;
		if (++pl->cycle.head == pl->cycle.queue + MAX_QUEUE)
			pl->cycle.head = pl->cycle.queue;
	}
}
