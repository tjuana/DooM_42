/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_walls.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dorange- <dorange-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/28 21:41:49 by dorange-          #+#    #+#             */
/*   Updated: 2020/02/14 18:20:19 by dorange-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

t_scaler	scalar_create(int a, int b, int c, int d, int f)
{
    t_scaler	s;
    if (c - a == 0)
        c += 1;
    s.result = d + (b - 1 - a) * (f - d) / (c - a);
    s.bop = ((f < d) ^ (c < a)) ? -1 : 1;
    s.fd = abs(f - d);
    s.ca = abs(c - a);
    s.cache = (int)((b - 1 - a) * abs(f - d)) % abs(c - a);
    return (s);
}

int			scr_nxt(t_scaler *i)
{
    i->cache += i->fd;
    while (i->cache >= i->ca)
    {
        i->result += i->bop;
        i->cache -= i->ca;
    }
    return (i->result);
}

static void draw_limits_for_walls(int wall_type, t_new_player *pl, int n)
{
	if(wall_type == 0)
	{
		pl->y1 = pl->ceil.cya;
		pl->y2 = pl->ceil.cnya - 1;
	}
	else if(wall_type == 1)
	{
		pl->y1 = pl->ceil.cnyb + 1;
		pl->y2 = pl->ceil.cyb;
	}
	else if(wall_type == 2)
	{
		pl->y1 = pl->ceil.cya;
		pl->y2 = pl->ceil.cyb;
	}
	pl->ty = scalar_create(pl->floor.ya, pl->y1, pl->floor.yb, 0, pl->tex[n].w - 1);
	pl->y = pl->y1;
	pl->y1 = clamp(pl->y1, 0, WIN_H-1);
	pl->y2 = clamp(pl->y2, 0, WIN_H-1);
}

void draw_walls(int x, t_new_player *pl, int wall_type, int img)
{
	draw_limits_for_walls(wall_type, pl, img);
	if (pl->y2 >= pl->y1)
		while (pl->y++ <= pl->y2)
			ft_draw_walls_put_pixel_to_surface(x, pl, img);
}

/*
** **************************************************************************
**	void draw_graffiti(int x, t_new_player *pl, int wall_type, int img)
**
**	>
**	draw_graffiti, we just draw over an already drawn wall, so we can draw
**	in every wall we want, with this logic we also can draw on floors
**	and ceilings.
** **************************************************************************
*/

void draw_graffiti(int x, t_new_player *pl, int wall_type, int img)
{
	draw_limits_for_walls(wall_type, pl, img);
	if (pl->y2 >= pl->y1)
		while (pl->y++ <= pl->y2)
			ft_draw_graffiti_put_pixel_to_surface(x, pl, img);
}
