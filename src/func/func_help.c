/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   func_help.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjuana <tjuana@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/24 14:10:50 by tjuana            #+#    #+#             */
/*   Updated: 2020/02/23 19:37:27 by tjuana           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

int				ft_error(char *code)
{
	system("osascript -e \'display notification\"Look to the terminal!\"with \
				title \"ERRROOOORRR!\"\'");
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
	if (w->sdl->text)
		SDL_DestroyTexture(w->sdl->text);
	if (w->sdl->renderer)
		SDL_DestroyRenderer(w->sdl->renderer);
	if (w->sdl->win)
		SDL_DestroyWindow(w->sdl->win);
	Mix_FreeMusic(w->sdl->music);
	Mix_CloseAudio();
	SDL_Delay(777);
	IMG_Quit();
	SDL_Quit();
}
