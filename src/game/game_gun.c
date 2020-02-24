/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_gun.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dorange- <dorange-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/15 17:40:12 by nshelly           #+#    #+#             */
/*   Updated: 2020/02/24 18:11:16 by dorange-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

static int	ft_gui_draw_gun_picture_get_pos(t_new_player *pl, \
				t_draw_gun g)
{
	int	pos;

	pos = (g.y % pl->tex[g.n].h) * pl->tex[g.n].w + g.x % pl->tex[g.n].w;
	if (pos >= 0 && pos < WIN_W * WIN_H)
		return (pos);
	return (-1);
}

static void	ft_game_draw_gun(t_new_player *pl, t_draw_gun g)
{
	g.y = 0;
	(void)((g.y *= 0 | (int)(g.y_num *= 0)));
	while (g.y < pl->tex[g.n].h && g.height < WIN_H)
	{
		g.x = 0;
		g.x_num = 0;
		g.x_img = g.width - 200;
		while (g.x < pl->tex[g.n].w - 1 && g.x_img < WIN_W)
		{
			g.x_num += 0.8;
			g.x = (int)g.x_num;
			g.p = ft_gui_draw_gun_picture_get_pos(pl, g);
			g.hex = ft_rgb_to_hex(pl->tex[g.n].pixels[g.p].r, \
			pl->tex[g.n].pixels[g.p].g, pl->tex[g.n].pixels[g.p].b);
			if (pl->tex[g.n].pixels[g.p].a != 0 && g.p != -1)
				pl->pix[g.height * WIN_W + g.x_img] = \
				ft_hex_transform(g.hex, pl->light);
			g.x_img++;
		}
		g.y_num += 1;
		g.y = (int)g.y_num;
		g.height++;
	}
}

void		ft_game_draw_pistol(t_gun *wpn, t_new_player *pl)
{
	t_draw_gun	g;

	if (wpn->sprite_counter == 1)
	{
		g.n = GUN;
		g.width = WIN_W - 400;
		g.height = WIN_H - 310;
		ft_game_draw_gun(pl, g);
	}
	else if (wpn->sprite_counter > 1)
	{
		g.n = GUN + 1;
		g.width = WIN_W - 430;
		g.height = WIN_H - 340;
		ft_game_draw_gun(pl, g);
		wpn->sprite_counter += 1;
	}
	if (wpn->sprite_counter > 3)
		wpn->sprite_counter = 1;
}
