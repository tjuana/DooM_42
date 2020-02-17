/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_load_textures.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjuana <tjuana@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/23 18:05:31 by drafe             #+#    #+#             */
/*   Updated: 2020/02/16 19:40:27 by tjuana           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

static void		transform_venom(t_new_texture *venom)
{
	int i;
	int hex;

	i = 1;
	while (i < venom->h * venom->w)
	{
		hex = ft_rgb_to_hex(venom->pixels[i].r, venom->pixels[i].g, \
		venom->pixels[i].b);
		if (hex >= 15800000)
		{
			venom->pixels[i].a = 0;
		}
		i++;
	}
}

static void		load_textures_2(t_new_texture *t_arr)
{
	t_arr[11] = texture_parse("Img_tga/wall_orange.tga");
	t_arr[12] = texture_parse("Img_tga/venom_face.tga");
	t_arr[13] = texture_parse("Img_tga/graffiti.tga");
}

/*
** **************************************************************************
**	t_new_texture *load_all_textures(t_new_player *pl)
**	Function to load textures
** **************************************************************************
*/

t_new_texture	*load_textures(t_new_player *pl)
{
	t_new_texture	*t_arr;

	pl->textures_nb = 15;
	if (!(t_arr = (t_new_texture *)malloc(sizeof(t_new_texture) * \
	pl->textures_nb)))
	{
		ft_putstr_fd("Can't allocate memory for textures array.\n", 2);
		exit(EXIT_FAILURE);
	}
	t_arr[0] = texture_parse("Img_tga/rock.tga");
	t_arr[1] = texture_parse("Img_tga/ivy.tga");
	t_arr[2] = texture_parse("Img_tga/marble.tga");
	t_arr[3] = texture_parse("Img_tga/texture_leaf_burch.tga");
	t_arr[4] = texture_parse("Img_tga/rock1.tga");
	t_arr[5] = texture_parse("Img_tga/cosmos.tga");
	t_arr[6] = texture_parse("Img_tga/grid_black.tga");
	t_arr[7] = texture_parse("Img_tga/fence.tga");
	t_arr[8] = texture_parse("Img_tga/revolver0.tga");
	t_arr[9] = texture_parse("Img_tga/revolver1.tga");
	t_arr[10] = texture_parse("Img_tga/revolver2.tga");
	load_textures_2(t_arr);
	transform_venom(&t_arr[12]);
	return (t_arr);
}
