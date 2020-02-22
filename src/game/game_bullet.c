/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_bullet.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dorange- <dorange-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/22 14:12:23 by dorange-          #+#    #+#             */
/*   Updated: 2020/02/22 16:54:41 by dorange-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

static void	ft_game_draw_gun(t_new_player *pl, int width, int height, int n)
{
	t_draw_gun	g;
	double		scale;

	scale = (40.0 - pl->bullet_frame) / 40.0;
	printf("%f\n", scale);
	g.y = 0;
	(void)((g.y *= 0 | (int)(g.y_num *= 0)));
	while (g.y / scale < pl->tex[n].h && height < WIN_H)
	{
		g.x = 0;
		g.x_num = 0;
		g.x_img = width - 200;
		while (g.x / scale < pl->tex[n].w - 1 && g.x_img < WIN_W)
		{
			g.x_num += 0.8;
			g.x = (int)g.x_num;
			g.p = ((int)(g.y / scale) % pl->tex[n].h) * pl->tex[n].w + (int)(g.x / scale) % pl->tex[n].w;

			// g.p = (g.y % pl->tex[n].h) * pl->tex[n].w * scale + g.x % pl->tex[n].w * scale;

			// g.p = 


			
			g.hex = ft_rgb_to_hex(pl->tex[n].pixels[g.p].r, \
				pl->tex[n].pixels[g.p].g, pl->tex[n].pixels[g.p].b);
			g.hex = ft_hex_transform(g.hex, pl->light);

			// g.hex = ft_fdf_get_color(g.hex, )
			if (pl->tex[n].pixels[g.p].a != 0 && \
				(height * WIN_W + g.x_img >= 0 && \
				height * WIN_W + g.x_img < WIN_W * WIN_H))
			{
				g.hex = ft_fdf_get_color(g.hex, pl->pix[height * WIN_W + g.x_img], 1.0 - scale);
				pl->pix[height * WIN_W + g.x_img] = g.hex;
			}
			g.x_img++;
		}
		g.y_num += 1;
		g.y = (int)g.y_num;
		height++;
	}
}

void		ft_game_draw_bullet(t_gun *wpn, t_new_player *pl)
{
	int		n;
	double	scale;

	(void)wpn;
	n = GUN;
	scale = (40.0 - pl->bullet_frame) / 40.0;
	if (pl->bullet_status)
	{
		if (pl->bullet_frame > 40)
			pl->bullet_status = 0;
		else
		{
			ft_game_draw_gun(pl, \
				sqrtf(1.0 - scale) * 400 + 2 * scale * (1.0 - scale) * -400 + sqrtf(scale) * (WIN_W - 400), \
				sqrtf(1.0 - scale) * 340 + 2 * scale * (1.0 - scale) * -400 + sqrtf(scale) * (WIN_H - 340), BULLET);
			pl->bullet_frame++;
		}
	}
}
