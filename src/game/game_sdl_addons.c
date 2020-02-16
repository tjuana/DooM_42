/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_sdl_addons.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dorange- <dorange-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/20 18:23:39 by drafe             #+#    #+#             */
/*   Updated: 2020/02/16 12:50:32 by dorange-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

void		ft_sdl_error(t_sdl *sdl)
{
	SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, \
	"Couldn't create window and renderer: %s", SDL_GetError());
	if (sdl->text)
		SDL_DestroyTexture(sdl->text);
	if (sdl->srf)
		SDL_FreeSurface(sdl->srf);
	if (sdl->renderer)
		SDL_DestroyRenderer(sdl->renderer);
	if (sdl->win)
		SDL_DestroyWindow(sdl->win);
	IMG_Quit();
	SDL_Quit();
	exit(EXIT_FAILURE);
}
