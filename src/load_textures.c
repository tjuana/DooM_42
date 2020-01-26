/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_textures.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: drafe <drafe@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/23 18:05:31 by drafe             #+#    #+#             */
/*   Updated: 2020/01/26 18:28:18 by drafe            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

/*void			component_image(t_texture img, t_xy pos,
t_xy buf_size, t_color *buf)
{
	size_t x;
	size_t y;

	if (img.pixels)
	{
		x = pos.x;
		while (x < img.w + pos.x && x < (size_t)buf_size.x)
		{
			y = pos.y;
			while (y < img.h + pos.y && y < (size_t)buf_size.y)
			{
				if (img.pixels[x - pos.x + (y - pos.y) * img.w].a > 0)
					buf[x + y * buf_size.x] = img.pixels[x - pos.x + (y
					- pos.y) * img.w];
				y++;
			}
			x++;
		}
	}
}*/

SDL_Texture			*texture_new(t_player *pl)
{
	SDL_Texture	*texture;
	t_color		*pixels;
	int			trash;

	pixels = pl->textures[0].pixels;
	texture = SDL_CreateTexture(pl->rend, SDL_PIXELFORMAT_RGBA32,\
			SDL_TEXTUREACCESS_STREAMING, pl->textures[0].w, pl->textures[0].h);
	SDL_LockTexture(texture, NULL, (void **)&pixels, (int *)&trash);
	SDL_UnlockTexture(texture);
	return (texture);
}

void		texture_init(t_player *pl)
{
	pl->texture = texture_new(pl);
}

/*
** **************************************************************************
**	t_texture *load_all_textures(t_player *pl)
**	Function to load textures
** **************************************************************************
*/

t_texture			*load_textures(t_player *pl)
{
	t_texture	*t_arr;

	pl->textures_nb = 4;
	if (!(t_arr = (t_texture *)malloc(sizeof(t_texture) * pl->textures_nb)))
	{
		ft_putstr_fd("Can't allocate memory for textures array.\n", 2);
		exit(EXIT_FAILURE);
	}
	t_arr[0] = texture_parse("wall.tga", 0);
	return (t_arr);
}

