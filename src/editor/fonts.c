/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fonts.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjuana <tjuana@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/13 12:46:18 by dorange-          #+#    #+#             */
/*   Updated: 2020/01/18 14:54:53 by tjuana           ###   ########.fr       */
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

/*
** **************************************************************************
**	int ft_font_preset_sc(t_wolf3d *w, int size, int color)

**	Function to set font colot and size
** **************************************************************************
*/

int			ft_font_preset_sc(t_wolf3d *w, int size, int color)
{
	(size > 72) || (size < 1) ? size = 72 : 0;
	w->sdl->font.color.a = 0;
	w->sdl->font.color.r = (Uint8)((color & C_R) >> 16);
	w->sdl->font.color.g = (Uint8)((color & C_G) >> 8);
	w->sdl->font.color.b = (Uint8)(color & C_B);
	w->sdl->font.f_sz = size;

	if (size == 14)
		w->sdl->font.ptr = w->sdl->font.ptr_font_14_m;
	else if (size == 18)
		w->sdl->font.ptr = w->sdl->font.ptr_font_18_m;
	else
		if (!(w->sdl->font.ptr = TTF_OpenFont(FONT_PATH, w->sdl->font.f_sz)))
			ft_error("FONT ERROR (1)");

	// ??!
	if (TTF_GlyphMetrics(w->sdl->font.ptr, 'A', 0, 0, 0, 0, &w->sdl->font.g_sz) == -1)
		ft_error("FONT ERROR (2)");
	return (0);
}

/*
** **************************************************************************
**	void ft_font_putstr_sdl(t_wolf3d *w, char *str, int x, int y)

**	Function to print words
** **************************************************************************
*/

void			ft_font_putstr_sdl(t_wolf3d *w, char *str, t_ui_coord c)
{
	SDL_Surface	*text_surf;
	SDL_Texture	*tmp_texture;
	SDL_Rect	*tmp_rect;

	if ((c.x < 0) || (c.y < 0) || (str == NULL) || (c.x > WIN_WIDTH) || (c.y > WIN_HEIGHT))
		return ;
	tmp_texture = NULL;
	if (TTF_SizeText(w->sdl->font.ptr, str, &w->sdl->font.w, &w->sdl->font.h) == -1)
		ft_error("FONT ERROR (3)");
	tmp_rect = ft_create_rect(w->sdl->font.w, w->sdl->font.h, c.x, c.y);
	if (!(text_surf = TTF_RenderText_Blended(w->sdl->font.ptr, str, w->sdl->font.color)))
		ft_error("FONT ERROR (4)");
	else
	{
		tmp_texture = SDL_CreateTextureFromSurface(w->sdl->renderer, text_surf);
		tmp_texture == NULL ? ft_error("FONT ERROR (5)") : 0;
		SDL_FreeSurface(text_surf);
	}
	if (SDL_RenderCopy(w->sdl->renderer, tmp_texture, 0, tmp_rect) != 0)
		ft_error("FONT ERROR (6)");
	SDL_DestroyTexture(tmp_texture);
	free(tmp_rect);
}
