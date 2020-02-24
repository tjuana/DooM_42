/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_bullet.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dorange- <dorange-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/22 14:12:23 by dorange-          #+#    #+#             */
/*   Updated: 2020/02/23 19:51:28 by dorange-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

static int	ft_gui_draw_bullet_picture_get_pos(t_new_player *pl, \
				t_draw_gun g, double scale, int n)
{
	int	pos;

	pos = (((int)(g.y / scale) % pl->tex[n].h) * pl->tex[n].w + \
		(int)(g.x / scale) % pl->tex[n].w);
	if (pos >= 0 && pos < WIN_W * WIN_H)
		return (pos);
	return (-1);
}

static void	ft_game_draw_bullet_picture(t_new_player *pl, t_draw_gun g)
{
	g.y = 0;
	(void)(g.y *= 0 | (int)(g.y_num *= 0));
	while (g.y / g.scale < pl->tex[g.n].h && g.height < WIN_H)
	{
		g.x = 0;
		g.x_img = g.width - 200;
		while (g.x / g.scale < pl->tex[g.n].w - 1 && g.x_img < WIN_W)
		{
			g.p = ft_gui_draw_bullet_picture_get_pos(pl, g, g.scale, g.n);
			if (pl->tex[g.n].pixels[g.p].a != 0 && g.p != -1)
			{
				g.hex = ft_rgb_to_hex(pl->tex[g.n].pixels[g.p].r, \
					pl->tex[g.n].pixels[g.p].g, pl->tex[g.n].pixels[g.p].b);
				g.hex = ft_hex_transform(g.hex, pl->light);
				g.hex = ft_fdf_get_color(g.hex, pl->pix[g.height * \
					WIN_W + g.x_img], 1.0 - g.scale);
				pl->pix[g.height * WIN_W + g.x_img] = g.hex;
			}
			g.x++;
			g.x_img++;
		}
		g.y_num += 1;
		g.y = (int)g.y_num;
		g.height++;
	}
}

void		ft_game_draw_bullet(t_gun *wpn, t_new_player *pl)
{
	int			n;
	t_draw_gun	g;

	(void)wpn;
	n = GUN;
	g.scale = (30.0 - pl->bullet_frame) / 30.0;
	g.n = BULLET;
	if (pl->bullet_status)
	{
		if (pl->bullet_frame > 30)
			pl->bullet_status = 0;
		else
		{
			g.width = (WIN_W - 400) + (600) * (g.scale - 1.0);
			g.height = powf(1.0 - g.scale, 2) * (WIN_H - 340) + \
					2 * g.scale * (1.0 - g.scale) * (10) + \
					powf(g.scale, 2) * (WIN_H - 340);
			ft_game_draw_bullet_picture(pl, g);
			pl->bullet_frame++;
		}
	}
}
