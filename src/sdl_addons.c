/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sdl_addons.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: drafe <drafe@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/20 18:23:39 by drafe             #+#    #+#             */
/*   Updated: 2020/01/20 18:23:49 by drafe            ###   ########.fr       */
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
