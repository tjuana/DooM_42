/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gui_sdl_func.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dorange- <dorange-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/07 16:24:11 by dorange-          #+#    #+#             */
/*   Updated: 2020/02/16 12:52:59 by dorange-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

/*
** **************************************************************************
**	SDL_Rect *ft_gui_create_sdl_rect(int w, int h, int x, int y)
**
**	Function to create SDL_Rect
** **************************************************************************
*/

SDL_Rect	*ft_gui_create_sdl_rect(int w, int h, int x, int y)
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

/*
** **************************************************************************
**	void ft_gui_set_sdl_color(SDL_Color *sdl_color, int color)
**
**	Function that set sdl color
** **************************************************************************
*/

void		ft_gui_set_sdl_color(SDL_Color *sdl_color, int color)
{
	sdl_color->a = 0;
	sdl_color->r = (Uint8)((color & C_R) >> 16);
	sdl_color->g = (Uint8)((color & C_G) >> 8);
	sdl_color->b = (Uint8)(color & C_B);
}
