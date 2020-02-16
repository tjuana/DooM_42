/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_textures.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjuana <tjuana@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/28 21:41:14 by dorange-          #+#    #+#             */
/*   Updated: 2020/02/16 16:11:12 by tjuana           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

/*
** **************************************************************************
**	void pix1(t_new_player *pl, int image)
**
**	Function that put pixel color for texture.
** **************************************************************************
*/

void	pix1(t_new_player *pl, int img)
{
	unsigned int	p;
	int				hex;

	p = (pl->t.txtz % pl->tex[img].h) * pl->tex[img].w + (pl->t.txtx1 % \
			pl->tex[img].w);
	hex = ft_color_struct_to_hex(pl->tex[img].pixels[p]);
	pl->pix[pl->t.y * WIN_W + pl->t.x] = ft_hex_transform(hex, pl->light);
}

/*
** **************************************************************************
**	void pix_sky(t_textures *t, t_new_player *pl)
**
**	Function that put pixel color for skybox.
**
**	pix1 <-> pix_sky
** **************************************************************************
*/

void	pix_sky(t_textures *t, t_new_player *pl)
{
	int				hex;
	unsigned int	p;

	p = (t->y % pl->tex[SKY].h) * pl->tex[SKY].w + (t->x % pl->tex[SKY].w);
	hex = ft_color_struct_to_hex(pl->tex[SKY].pixels[p]);
	pl->pix[t->y * WIN_W + t->x] = hex;
}

/*
** **************************************************************************
**	void ft_draw_walls_put_pixel_to_surface(int x, t_new_player *pl, int img)
** **************************************************************************
*/

void	ft_draw_walls_put_pixel_to_surface(int x, t_new_player *pl, int img)
{
	unsigned		txty;
	int				hex;
	unsigned int	p;

	txty = scr_nxt(&pl->ty);
	p = (txty % pl->tex[img].h) * pl->tex[img].w + (pl->txtx % pl->tex[img].w);
	hex = ft_hex_transform(ft_color_struct_to_hex(pl->tex[img].pixels[p]), \
													pl->light);
	if (pl->tex[img].pixels[p].a == 0)
	{
		p = (pl->y % pl->tex[SKY].h) * pl->tex[SKY].w + x % pl->tex[SKY].w;
		hex = ft_color_struct_to_hex(pl->tex[SKY].pixels[p]);
	}
	pl->pix[pl->y * WIN_W + x] = hex;
}

/*
** **************************************************************************
**	void ft_draw_graffiti_put_pixel_to_surface(int x, t_new_player *pl,
**		int img)
** **************************************************************************
*/

void	ft_draw_graffiti_put_pixel_to_surface(int x, t_new_player *pl, \
			int img)
{
	unsigned		txty;
	unsigned int	p;
	int				hex;

	txty = -(scr_nxt(&pl->ty) + 220);
	p = (txty % pl->tex[img].h) * pl->tex[img].w + (pl->txtx % pl->tex[img].w);
	hex = ft_hex_transform(ft_color_struct_to_hex(pl->tex[img].pixels[p]), \
													pl->light);
	if (hex >= 16000000)
	{
		pl->tex[img].pixels[p].a = 0;
	}
	if (pl->tex[img].pixels[p].a != 0)
		pl->pix[pl->y * WIN_W + x] = hex;
}
