/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sdl_render.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dorange- <dorange-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/25 13:26:38 by tjuana            #+#    #+#             */
/*   Updated: 2020/01/21 15:07:47 by dorange-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

void		ft_game_render(t_wolf3d *w)
{
	threading(w);
	ft_draw_animation(w);
}

void		ft_game_render_font(t_wolf3d *w)
{
	return ;
}

void		renderer(t_wolf3d *wolf)
{
	ft_animation_play(wolf);
	ft_bzero(wolf->sdl->pixels, 4 * WIN_WIDTH * WIN_HEIGHT);
	SDL_SetRenderDrawColor(wolf->sdl->renderer, 0xff, 0xff, 0xff, 0xff);
	SDL_RenderClear(wolf->sdl->renderer);

	// render
	threading(wolf);
	ft_draw_animation(wolf);
	// ft_draw_map_new_sector(wolf);
	ft_draw_map_new_sector_iso(wolf);	
	SDL_UpdateTexture(wolf->sdl->text, 0, wolf->sdl->pixels, WIN_WIDTH * 4);
	SDL_RenderCopy(wolf->sdl->renderer, wolf->sdl->text, NULL, NULL);
	// text ?
	SDL_RenderPresent(wolf->sdl->renderer);
}
