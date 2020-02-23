/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gui_fonts.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dorange- <dorange-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/15 14:58:08 by dorange-          #+#    #+#             */
/*   Updated: 2020/02/21 18:22:21 by dorange-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

/*
** **************************************************************************
**	void ft_gui_set_font(t_wolf3d *w, char *font_path, int size)
**
**	Function that set new font.
** **************************************************************************
*/

void		ft_gui_set_font(t_wolf3d *w, char *font_path, int size)
{
	t_list		*new_list;
	t_gui_font	new_font;

	new_font.path = ft_strdup(font_path);
	new_font.f_sz = size;
	new_font.ptr = w->sdl->font.ptr;
	new_list = ft_lstnew(&new_font, sizeof(t_gui_font));
	if (w->gui.fonts == NULL)
		w->gui.fonts = new_list;
	else
		ft_lstadd(&w->gui.fonts, new_list);
}

/*
** **************************************************************************
**	void ft_gui_check_glyph_metrics(t_font *f)
**
**	Function that check glyph metrics.
** **************************************************************************
*/

void		ft_gui_check_glyph_metrics(t_font *f)
{
	if (TTF_GlyphMetrics(f->ptr, 'W', 0, 0, 0, 0, &f->g_sz) == -1)
		ft_error("FONT SET ERROR");
}

/*
** **************************************************************************
**	int ft_gui_font_preset_fsc(t_wolf3d *w, char *font_path,
**		int size, int color)
**
**	Function to set font colot and size
** **************************************************************************
*/

int			ft_gui_font_preset_fsc(t_wolf3d *w, char *font_path, \
				int size, int color)
{
	t_list		*f_list;
	t_gui_font	*font;
	t_font		*f;

	f = &w->sdl->font;
	(size > 72) || (size < 1) ? size = 72 : 0;
	ft_gui_set_sdl_color(&f->color, color);
	f->f_sz = size;
	f_list = w->gui.fonts;
	while (f_list)
	{
		font = f_list->content;
		if (ft_strcmp(font_path, font->path) == 0 && size == font->f_sz)
		{
			f->ptr = font->ptr;
			ft_gui_check_glyph_metrics(f);
			return (0);
		}
		f_list = f_list->next;
	}
	if (!(f->ptr = TTF_OpenFont(font_path, f->f_sz)))
		ft_error("FONT SET ERROR (2)");
	ft_gui_set_font(w, font_path, size);
	ft_gui_check_glyph_metrics(f);
	return (0);
}

/*
** **************************************************************************
**	void ft_gui_font_rect(t_wolf3d *w, SDL_Texture *txtr, \
**		t_font *f, t_gui_coord c)
**
**	Function to render copy from rect.
** **************************************************************************
*/

void		ft_gui_font_rect(t_wolf3d *w, SDL_Texture *txtr, \
				t_font *f, t_gui_coord c)
{
	SDL_Rect	*rect;

	rect = ft_gui_create_sdl_rect(f->w, f->h, c.x, c.y);
	if (SDL_RenderCopy(w->sdl->renderer, txtr, 0, rect) != 0)
		ft_error("FONT ERROR (7)");
	free(rect);
}

/*
** **************************************************************************
**	void ft_font_putstr_sdl(t_wolf3d *w, char *str, int x, int y)
**
**	Function to print words
** **************************************************************************
*/

void		ft_gui_font_putstr_sdl(t_wolf3d *w, \
				char *str, t_gui_coord c)
{
	SDL_Surface	*txtr_s;
	SDL_Texture	*txtr;
	t_font		*f;

	f = &w->sdl->font;
	if ((c.x < 0) || (c.y < 0) || (str == NULL) || \
		(c.x > w->gui.win_w) || (c.y > w->gui.win_h))
		return ;
	txtr = NULL;
	if (TTF_SizeText(f->ptr, str, &f->w, &f->h) == -1)
		ft_error("FONT ERROR (4)");
	if (!(txtr_s = TTF_RenderText_Blended(f->ptr, str, f->color)))
		ft_error("FONT ERROR (5)");
	else
	{
		txtr = SDL_CreateTextureFromSurface(w->sdl->renderer, txtr_s);
		(txtr == NULL) ? ft_error("FONT ERROR (6)") : 0;
	}
	if (txtr_s)
		SDL_FreeSurface(txtr_s);
	ft_gui_font_rect(w, txtr, f, c);
	if (txtr)
		SDL_DestroyTexture(txtr);
}
