/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_load_textures.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dorange- <dorange-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/23 18:05:31 by drafe             #+#    #+#             */
/*   Updated: 2020/01/28 16:32:52 by dorange-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

/*void			component_image(t_new_texture img, t_new_xy pos,
t_new_xy buf_size, t_new_color *buf)
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

SDL_Texture			*texture_new(t_new_player *pl)
{
	SDL_Texture	*texture;
	t_new_color		*pixels;
	int			trash;

	pixels = pl->textures[0].pixels;
	texture = SDL_CreateTexture(pl->rend, SDL_PIXELFORMAT_RGBA32,\
			SDL_TEXTUREACCESS_STREAMING, pl->textures[0].w, pl->textures[0].h);
	SDL_LockTexture(texture, NULL, (void **)&pixels, (int *)&trash);
	SDL_UnlockTexture(texture);
	return (texture);
}

void		texture_init(t_new_player *pl)
{
	pl->texture = texture_new(pl);
}

/*
** **************************************************************************
**	t_new_texture *load_all_textures(t_new_player *pl)
**	Function to load textures
** **************************************************************************
*/

t_new_texture			*load_textures(t_new_player *pl)
{
	t_new_texture	*t_arr;

	pl->textures_nb = 4;
	if (!(t_arr = (t_new_texture *)malloc(sizeof(t_new_texture) * pl->textures_nb)))
	{
		ft_putstr_fd("Can't allocate memory for textures array.\n", 2);
		exit(EXIT_FAILURE);
	}
	t_arr[0] = texture_parse("wall.tga", 0);
	return (t_arr);
}
