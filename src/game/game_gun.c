/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_gun.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjuana <tjuana@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/15 17:40:12 by nshelly           #+#    #+#             */
/*   Updated: 2020/02/19 20:15:13 by tjuana           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

static void	ft_game_draw_gun(t_new_player *pl, int width, int height, int n)
{
	t_draw_gun g;

	g.y = 0;
	(void)((g.y *= 0 | (int)(g.y_num *= 0)));
	while (g.y < pl->tex[n].h && height < WIN_H)
	{
		g.x = 0;
		g.x_num = 0;
		g.x_img = width - 200;
		while (g.x < pl->tex[n].w - 1 && g.x_img < WIN_W)
		{
			g.x_num += 0.8;
			g.x = (int)g.x_num;
			g.p = (g.y % pl->tex[n].h) * pl->tex[n].w + g.x % pl->tex[n].w;
			g.hex = ft_rgb_to_hex(pl->tex[n].pixels[g.p].r, \
			pl->tex[n].pixels[g.p].g, pl->tex[n].pixels[g.p].b);
			if (pl->tex[n].pixels[g.p].a != 0)
				pl->pix[height * WIN_W + g.x_img] = \
				ft_hex_transform(g.hex, pl->light);
			g.x_img++;
		}
		g.y_num += 1;
		g.y = (int)g.y_num;
		height++;
	}
	//if (n > 9)
	//	sound(pl, "Sounds/pistol.wav");
}

void		ft_game_draw_pistol(t_gun *wpn, t_new_player *pl)
{
	int n;

	n = GUN;
	if (wpn->sprite_counter == 1)
		ft_game_draw_gun(pl, WIN_W - 400, WIN_H - 310, n);
	else if (wpn->sprite_counter > 1)
	{
		ft_game_draw_gun(pl, WIN_W - 430, WIN_H - 340, n + 1);
		wpn->sprite_counter += 1;
	}
	if (wpn->sprite_counter > 3)
		wpn->sprite_counter = 1;
}
