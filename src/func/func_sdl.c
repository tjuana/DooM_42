/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   func_sdl.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dorange- <dorange-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/20 16:41:04 by dorange-          #+#    #+#             */
/*   Updated: 2020/01/26 23:17:14 by dorange-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

t_sdl		*sdl_init(t_sdl *sdl)
{
	sdl = ft_my_malloc(sizeof(t_sdl));
	// sdl->pixels = ft_my_malloc((sizeof(Uint32) * WIN_WIDTH) * WIN_HEIGHT);
	// sdl->srf = NULL;
	if (SDL_Init(SDL_INIT_EVERYTHING) < 0)
	{
		SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, \
		"Couldn't initialize SDL: %s", SDL_GetError());
		return (0);
	}

	IMG_Init(IMG_INIT_PNG) == 0 ? ft_putstr_fd(IMG_GetError(), 2) : 0;
	if (SDL_CreateWindowAndRenderer(WIN_WIDTH, WIN_HEIGHT, \
	0, &sdl->win, &sdl->renderer) < 0)
	{
		SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, \
		"Couldn't create window and renderer: %s", SDL_GetError());
		return (0);
	}

	!sdl->srf ? ft_putstr_fd(SDL_GetError(), 2) : 0;
	sdl->srf = SDL_CreateRGBSurface(0, WIN_WIDTH, WIN_HEIGHT, 32, 0, 0, 0, 0);

	if (!(sdl->text = SDL_CreateTexture(sdl->renderer, SDL_PIXELFORMAT_ARGB8888\
	, SDL_TEXTUREACCESS_STREAMING, WIN_WIDTH, WIN_HEIGHT)))
		ft_error("SDL non textures");
	sdl->running = 1;
	// new??
	if (TTF_Init() != 0)
		ft_error("ft_sdl_error(w)\n");
	return (sdl);
}

void		ft_init_wolf(t_wolf3d *w)
{
	w->file.name = "fuck_you.txt";
	// w->sdl->textures = ft_my_malloc(sizeof(SDL_Surface *) * TEXTURES_NUMBER);
	w->t.flag = 1;
	ft_we_need_more_init(w);
}

void		ft_we_need_more_init(t_wolf3d *w)
{
	w->t.time = 0;
	w->t.old_time = 0;
	w->t.sound_old_time = 0;
	w->t.play_time = 1000;
	w->t.sound_sum_time = 0;
}
