/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sdl_addons.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: drafe <drafe@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/20 18:23:39 by drafe             #+#    #+#             */
/*   Updated: 2020/01/26 18:42:26 by drafe            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

/*
** **************************************************************************
**	SDL_Rect *ft_create_rect(int w, int h, int x, int y)
**	Function to create SDL_Rect
** **************************************************************************
*/

SDL_Rect	*ft_create_rect(int w, int h, int x, int y)
{
	SDL_Rect	*tmp;

	if (!(tmp = (SDL_Rect*)malloc(sizeof(tmp))))
		return (0);
	tmp->h = h;
	tmp->w = w;
	tmp->x = x;
	tmp->y = y;
	return (tmp);
}

void		ft_sdl_error(t_wolf3d *w)
{
	const char	*out;

	out = SDL_GetError();
	ft_putstr_fd("SDL_Error:", 2);
	ft_putstr_fd(out, 2);
	ft_putstr_fd("\n", 2);
	/*if (w->sdl->text)
		SDL_DestroyTexture(w->sdl->text);
	if (w->surf)
		SDL_FreeSurface(w->sdl->surf);
	if (w->sdl->renderer)
		SDL_DestroyRenderer(w->sdl->renderer);
	if (w->sdl->win)
		SDL_DestroyWindow(w->sdl->win);*/
	SDL_Quit();
	if (w)
		free(w);
	w = NULL;
	exit(EXIT_FAILURE);
}