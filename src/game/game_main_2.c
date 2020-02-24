/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_main_2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dorange- <dorange-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/21 19:28:15 by tjuana            #+#    #+#             */
/*   Updated: 2020/02/24 18:20:38 by dorange-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

/*
** **************************************************************************
**	void ft_game_init(t_wolf3d *w, char *path)
** **************************************************************************
*/

void		ft_game_init(t_wolf3d *w, char *path)
{
	t_new_temp	*data;

	data = w->new_data;
	data->pl->const_hfov = (0.73f * WIN_H);
	data->pl->const_vfov = (0.2f * WIN_H);
	data->pl->const_hfov_spec = (1.0 * 0.73f * WIN_H / WIN_W);
	data->pl->const_vfov_spec = (1.0 * .2f);
	data->pl->wolf3d = w;
	data->pl->sectors_nb = 0;
	data->se.quit = 0;
	data->pl->pixels = w->sdl->pixels;
	ft_game_my_parse_map(data->pl, path);
	data->pl->y_top = ft_my_malloc(sizeof(int) * WIN_WIDTH);
	data->pl->y_bot = ft_my_malloc(sizeof(int) * WIN_WIDTH);
	data->se.wsad[0] = 0;
	data->se.wsad[1] = 0;
	data->se.wsad[2] = 0;
	data->se.wsad[3] = 0;
	data->se.falling = 1;
	data->se.ground = 0;
	data->ot.moving = 0;
	data->se.ducking = 0;
	data->ms.yaw = 0;
}
