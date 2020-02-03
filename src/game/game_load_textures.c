/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_load_textures.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjuana <tjuana@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/23 18:05:31 by drafe             #+#    #+#             */
/*   Updated: 2020/02/03 17:07:41 by tjuana           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

/*
** **************************************************************************
**	t_new_texture *load_all_textures(t_new_player *pl)
**	Function to load textures
** **************************************************************************
*/

t_new_texture			*load_textures(t_new_player *pl)
{
	t_new_texture	*t_arr;

	pl->textures_nb = 11;
	if (!(t_arr = (t_new_texture *)malloc(sizeof(t_new_texture) * pl->textures_nb)))
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
	return (t_arr);
}
