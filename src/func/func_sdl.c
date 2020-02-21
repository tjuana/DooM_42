/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   func_sdl.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dorange- <dorange-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/20 16:41:04 by dorange-          #+#    #+#             */
/*   Updated: 2020/02/21 21:04:06 by dorange-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

void		ft_set_window_icon(t_sdl *sdl)
{
	SDL_Surface		*sur_win;
	SDL_Surface		*sur_img;
	SDL_Surface		*conv_sur_img;

	if (!(sur_win = SDL_CreateRGBSurface(0, WIN_WIDTH, WIN_HEIGHT, \
		32, 0xFF000000, 0x00FF0000, 0x0000FF00, 0x000000FF)))
		ft_sdl_error(sdl);
	if (!(sur_img = IMG_Load("Textures/file.png")))
		ft_sdl_error(sdl);
	if (!(conv_sur_img = SDL_ConvertSurface(sur_img, sur_win->format, 0)))
		ft_sdl_error(sdl);
	(sur_win) ? SDL_FreeSurface(sur_win) : 0;
	(sur_img) ? SDL_FreeSurface(sur_img) : 0;
	SDL_SetWindowIcon(sdl->win, conv_sur_img);
	(conv_sur_img) ? SDL_FreeSurface(conv_sur_img) : 0;
}

void		sdl_create_background_music(t_sdl *sdl)
{
	if (!(sdl->music = Mix_LoadWAV("music/background.wav")))
		ft_error("no music, man");
	Mix_VolumeChunk(sdl->music, VOLUME);
	if (Mix_PlayChannel(0, sdl->music, -1) == -1)
		ft_error("music");
	else
		Mix_VolumeChunk(sdl->music,
		VOLUME);
}

void		sound(t_new_player *pl, char *name, int channel)
{
	if (!(pl->sound = Mix_LoadWAV(name)))
		ft_error("no sound, man");
	if (Mix_PlayChannel(channel, pl->sound, 0) == -1 || !pl->sound)
		ft_error("Audio play error");
	Mix_FreeChunk(pl->sound);
	pl->sound = NULL;
}

t_sdl		*sdl_init(t_sdl *sdl)
{
	sdl = ft_my_malloc(sizeof(t_sdl));
	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) < 0)
		ft_sdl_error(sdl);
	IMG_Init(IMG_INIT_PNG) == 0 ? ft_putstr_fd(IMG_GetError(), 2) : 0;
	if (SDL_CreateWindowAndRenderer(WIN_WIDTH, WIN_HEIGHT, \
	SDL_RENDERER_ACCELERATED, &sdl->win, &sdl->renderer) < 0)
		ft_sdl_error(sdl);
	sdl->pixels = ft_my_malloc((sizeof(Uint32) * WIN_WIDTH) * WIN_HEIGHT);
	if (!(sdl->text = SDL_CreateTexture(sdl->renderer, \
		SDL_PIXELFORMAT_ARGB8888, SDL_TEXTUREACCESS_STREAMING, \
		WIN_WIDTH, WIN_HEIGHT)))
		ft_error("SDL non textures");
	Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 4096);
	ft_set_window_icon(sdl);
	sdl_create_background_music(sdl);
	sdl->running = 1;
	if (TTF_Init() != 0)
		ft_error("ft_sdl_error(w)\n");
	return (sdl);
}
