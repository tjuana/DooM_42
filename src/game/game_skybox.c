/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_skybox.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nshelly <nshelly@student.21school.>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/15 17:44:09 by nshelly           #+#    #+#             */
/*   Updated: 2020/02/15 17:44:09 by nshelly          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

void	pix_sky(t_textures *t, t_new_player *pl)
{
	int				hex;
	unsigned int	p;

	pl->pix = (int *)pl->srf->pixels;
	p = (t->y % pl->tex[SKY].h) * pl->tex[SKY].w + t->x % pl->tex[SKY].w;
	hex = hexcolor(pl->tex[SKY].pixels[p].r, pl->tex[SKY].pixels[p].g,\
	pl->tex[SKY].pixels[p].b);
	pl->pix[t->y * WIN_W + t->x] = hex;
}
