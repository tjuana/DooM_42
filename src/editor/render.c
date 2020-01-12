/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dorange- <dorange-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/10 16:34:19 by dorange-          #+#    #+#             */
/*   Updated: 2020/01/12 20:22:52 by dorange-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

void	ft_editor_draw_line(t_wolf3d *w)
{
	int			i;

	i = w->ui_map.v1.x;
	while (i < w->ui_map.v2.y)
	{
		ft_fdf_wu_color(
			&(t_vector3){w->ui_map.v1.x, i, 0, 0}, \
			&(t_vector3){w->ui_map.v2.x, i, 0, 0}, \
			w, \
			0x333333 \
		);
		i += 32;
	}
	i = w->ui_map.v1.y;
	while (i < w->ui_map.v2.x)
	{
		ft_fdf_wu_color(
			&(t_vector3){i, w->ui_map.v1.y, 0, 0}, \
			&(t_vector3){i, w->ui_map.v2.y, 0, 0}, \
			w, \
			0x333333 \
		);
		i += 32;
	}
}

void	ft_editor_map_fill_sectors(t_wolf3d *w)
{
	int	y;
	int	x;
	int	color;
	int	pos;

	y = w->ui_map.v1.y;
	while (y < w->ui_map.v2.y)
	{
		x = w->ui_map.v1.x;
		while (x < w->ui_map.v2.x)
		{
			if (ft_sector_check_sector(w, (t_vector3){x, y, 0, 0}))
			{
				pos = x + (y * WIN_WIDTH);
				color = ft_fdf_get_color(0xffff00, (int)w->sdl->pixels[pos], 0.7);
				w->sdl->pixels[pos] = color;
			}
			x++;
		}
		y++;
	}
}

/*
** **************************************************************************
**	void ft_editor_renderer(t_wolf3d *wolf)
**
**	Function that render all images to window.
** **************************************************************************
*/

void	ft_editor_renderer(t_wolf3d *wolf)
{
	ft_bzero(wolf->sdl->pixels, 4 * WIN_WIDTH * WIN_HEIGHT);
	SDL_SetRenderDrawColor(wolf->sdl->renderer, 0x00, 0x00, 0x00, 0xff);
	SDL_RenderClear(wolf->sdl->renderer);

	ft_editor_draw_line(wolf);
	ft_editor_draw_map_2d(wolf, wolf->sector);

	ft_editor_threading(wolf);
	// ft_editor_map_fill_sectors(wolf);

	if (ft_editor_check_event_area_map(wolf, wolf->mouse_pos))
	{
		ft_editor_draw_mouse_vertex(wolf);
		if (wolf->sector_status == 1)
		{
			if (!ft_sector_check_sector(wolf, wolf->mouse_pos))
				ft_editor_sector_draw_line_to_vertex(wolf);
		}
	}

	SDL_UpdateTexture(wolf->sdl->text, 0, wolf->sdl->pixels, WIN_WIDTH * 4);
	SDL_RenderCopy(wolf->sdl->renderer, wolf->sdl->text, NULL, NULL);
	SDL_RenderPresent(wolf->sdl->renderer);
}