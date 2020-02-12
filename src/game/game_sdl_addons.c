/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_sdl_addons.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjuana <tjuana@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/20 18:23:39 by drafe             #+#    #+#             */
/*   Updated: 2020/02/12 16:41:41 by tjuana           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

/*
** **************************************************************************
**	SDL_Rect *ft_create_rect(int w, int h, int x, int y)
**	Function to create SDL_Rect
** **************************************************************************
*/

SDL_Rect	*ft_create_rect(int w, int h, int x, int y)
{
	SDL_Rect	*tmp;

	tmp = (SDL_Rect*)ft_my_malloc(sizeof(tmp));
	tmp->h = h;
	tmp->w = w;
	tmp->x = x;
	tmp->y = y;
	return (tmp);
}

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
