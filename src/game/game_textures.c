/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_textures.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjuana <tjuana@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/28 21:41:14 by dorange-          #+#    #+#             */
/*   Updated: 2020/02/08 13:34:31 by tjuana           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

int		color_transoform(int color, float percent)
{
	int	rgb[4];

	rgb[0] = ((color >> 0) & 0xFF) * percent;
	rgb[1] = ((color >> 8) & 0xFF) * percent;
	rgb[2] = ((color >> 16) & 0xFF) * percent;
	rgb[3] = (color >> 24) & 0xFF * 0;
	color = (rgb[3] << 24 | rgb[2] << 16 | rgb[1] << 8 | rgb[0] << 0);
	return (color);
}

void	pix1(t_new_player *pl, int image)
{
	unsigned int	p;
	int				hex;

	p = (pl->t.txtz % pl->tex[image].h) * pl->tex[image].w + (pl->t.txtx1 \
	% pl->tex[image].w);
	hex = hexcolor(pl->tex[image].pixels[p].r, pl->tex[image].pixels[p].g,\
	pl->tex[image].pixels[p].b);
	pl->pix[pl->t.y * WIN_W + pl->t.x] = color_transoform(hex, pl->light);
}
