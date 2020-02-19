/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_sdl_addons.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjuana <tjuana@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/20 18:23:39 by drafe             #+#    #+#             */
/*   Updated: 2020/02/19 20:15:46 by tjuana           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

void		ft_sdl_error(t_sdl *sdl)
{
	SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, \
	"Couldn't create window and renderer: %s", SDL_GetError());
	if (sdl->text)
		SDL_DestroyTexture(sdl->text);
	if (sdl->renderer)
		SDL_DestroyRenderer(sdl->renderer);
	if (sdl->win)
		SDL_DestroyWindow(sdl->win);
	free(sdl);
	IMG_Quit();
	Mix_CloseAudio();
	SDL_Quit();
	system("osascript -e \'display notification\"In terminal log of error\" \
		with title \"SDL, bro!\"\'");
	exit(EXIT_FAILURE);
}
