/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gui_fonts.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dorange- <dorange-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/15 14:58:08 by dorange-          #+#    #+#             */
/*   Updated: 2020/01/18 18:39:48 by dorange-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

/*
** **************************************************************************
**	SDL_Rect *ft_create_rect(int w, int h, int x, int y)

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
**	void ft_gui_set_font(t_wolf3d *w, char *font_path, int size)

**	Function that set new font.
** **************************************************************************
*/

void		ft_gui_set_font(t_wolf3d *w, char *font_path, int size)
{
	t_list		*new_list;
	t_gui_font	*new_font;

	new_font = ft_my_malloc(sizeof(t_gui_font));
	new_font->path = ft_strdup(font_path);
	new_font->f_sz = size;
	new_font->ptr = w->sdl->font.ptr;
	new_list = ft_lstnew(new_font, sizeof(t_gui_font));
	if (w->gui.fonts == NULL)
		w->gui.fonts = new_list;
	else
		ft_lstadd(&w->gui.fonts, new_list);
}

/*
** **************************************************************************
**	int ft_font_preset_fsc(t_wolf3d *w, int size, int color)

**	Function to set font colot and size
** **************************************************************************
*/

int			ft_gui_font_preset_fsc(t_wolf3d *w, char *font_path, int size, int color)
{
	t_list		*fonts_list;
	t_gui_font	*font;

	(size > 72) || (size < 1) ? size = 72 : 0;
	w->sdl->font.color.a = 0;
	w->sdl->font.color.r = (Uint8)((color & C_R) >> 16);
	w->sdl->font.color.g = (Uint8)((color & C_G) >> 8);
	w->sdl->font.color.b = (Uint8)(color & C_B);
	w->sdl->font.f_sz = size;

	fonts_list = w->gui.fonts;
	while (fonts_list)
	{
		font = fonts_list->content;
		// printf("f: %d : %d %d\n", font->f_sz, ft_strcmp(font_path, font->path), size == font->f_sz);
		// printf("\n");
		if (ft_strcmp(font_path, font->path) == 0 && size == font->f_sz)
		{
			w->sdl->font.ptr = font->ptr;
			if (TTF_GlyphMetrics(w->sdl->font.ptr, 'A', 0, 0, 0, 0, &w->sdl->font.g_sz) == -1)
				ft_error("FONT SET ERROR (1)");
			return (0);
		}
		fonts_list = fonts_list->next;
	}
	if (!(w->sdl->font.ptr = TTF_OpenFont(font_path, w->sdl->font.f_sz)))
		ft_error("FONT SET ERROR (2)");
	ft_gui_set_font(w, font_path, size);
	if (TTF_GlyphMetrics(w->sdl->font.ptr, 'A', 0, 0, 0, 0, &w->sdl->font.g_sz) == -1)
		ft_error("FONT SET ERROR (3)");
	printf("=======\n");
	return (0);
}

/*
** **************************************************************************
**	void ft_font_putstr_sdl(t_wolf3d *w, char *str, int x, int y)

**	Function to print words
** **************************************************************************
*/

void			ft_gui_font_putstr_sdl(t_wolf3d *w, char *str, t_ui_coord c)
{
	SDL_Surface	*text_surf;
	SDL_Texture	*tmp_texture;
	SDL_Rect	*tmp_rect;

	if ((c.x < 0) || (c.y < 0) || (str == NULL) || (c.x > WIN_WIDTH) || (c.y > WIN_HEIGHT))
		return ;
	tmp_texture = NULL;
	if (TTF_SizeText(w->sdl->font.ptr, str, &w->sdl->font.w, &w->sdl->font.h) == -1)
		ft_error("FONT ERROR (4)");
	tmp_rect = ft_gui_create_sdl_rect(w->sdl->font.w, w->sdl->font.h, c.x, c.y);
	if (!(text_surf = TTF_RenderText_Blended(w->sdl->font.ptr, str, w->sdl->font.color)))
		ft_error("FONT ERROR (5)");
	else
	{
		tmp_texture = SDL_CreateTextureFromSurface(w->sdl->renderer, text_surf);
		tmp_texture == NULL ? ft_error("FONT ERROR (6)") : 0;
		SDL_FreeSurface(text_surf);
	}
	if (SDL_RenderCopy(w->sdl->renderer, tmp_texture, 0, tmp_rect) != 0)
		ft_error("FONT ERROR (7)");
	free(tmp_rect);
	SDL_DestroyTexture(tmp_texture);
}
