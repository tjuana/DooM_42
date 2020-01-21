/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sdl_init.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dorange- <dorange-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/20 16:41:04 by dorange-          #+#    #+#             */
/*   Updated: 2020/01/20 16:41:11 by dorange-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

t_sdl		*sdl_init(t_sdl *sdl)
{
	sdl = ft_my_malloc(sizeof(t_sdl));
	sdl->pixels = ft_my_malloc((sizeof(Uint32) * WIN_WIDTH) * WIN_HEIGHT);
	if (SDL_Init(SDL_INIT_EVERYTHING) < 0)
	{
		SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, \
		"Couldn't initialize SDL: %s", SDL_GetError());
		return (0);
	}
	if (SDL_CreateWindowAndRenderer(WIN_WIDTH, WIN_HEIGHT, \
	0, &sdl->win, &sdl->renderer) < 0)
	{
		SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, \
		"Couldn't create window and renderer: %s", SDL_GetError());
		return (0);
	}
	if (!(sdl->text = SDL_CreateTexture(sdl->renderer, SDL_PIXELFORMAT_ARGB8888\
	, SDL_TEXTUREACCESS_STREAMING, WIN_WIDTH, WIN_HEIGHT)))
		ft_error("SDL non textures");
	sdl->running = 1;
	// new??
	if (TTF_Init() != 0)
		ft_error("ft_sdl_error(w)\n");
	return (sdl);
}