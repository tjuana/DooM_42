/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   func_help.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dorange- <dorange-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/24 14:10:50 by tjuana            #+#    #+#             */
/*   Updated: 2020/01/27 00:49:58 by dorange-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

int				ft_error(char *code)
{
	ft_putendl(code);
	exit(EXIT_FAILURE);
	return (1);
}

void			*ft_my_malloc(size_t s)
{
	void	*p;

	if (!(p = malloc(s)))
	{
		perror("Malloc failed!");
		exit(EXIT_FAILURE);
	}
	return (p);
}

void			ft_clean_sdl(t_wolf3d *w)
{
	// free(w->sdl->textures);
	// free(w->sdl->srf);
	// ft_lstdel(&w->vertex, ft_bzero_char);
	SDL_DestroyTexture(w->sdl->text);
	SDL_DestroyRenderer(w->sdl->renderer);
	SDL_DestroyWindow(w->sdl->win);
	SDL_Delay(777);
	SDL_Quit();
}
