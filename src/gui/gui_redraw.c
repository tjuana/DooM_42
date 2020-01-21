/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gui_redraw.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dorange- <dorange-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/14 16:22:56 by dorange-          #+#    #+#             */
/*   Updated: 2020/01/21 15:58:28 by dorange-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

// Image (?)
void	ft_gui_draw_image(t_wolf3d *w, t_list *list)
{
	t_gui_elem	*elem;
	SDL_Texture	*tmp_texture;
	SDL_Rect	*tmp_rect;

	elem = list->content;
	tmp_texture = NULL;

	tmp_rect = ft_gui_create_sdl_rect(elem->w, elem->h, elem->v1.x, elem->v1.y);
	tmp_texture = SDL_CreateTextureFromSurface(w->sdl->renderer, elem->surf);
	tmp_texture == NULL ? ft_error("ERROR") : 0;
	SDL_SetTextureBlendMode(tmp_texture, SDL_BLENDMODE_BLEND) != 0 ? ft_error("ERROR") : 0;
	SDL_RenderCopy(w->sdl->renderer, tmp_texture, NULL, tmp_rect) != 0 ? ft_error("ERROR") : 0;
	SDL_DestroyTexture(tmp_texture);
}

/*
**	void ft_gui_fill_area(t_wolf3d *w, t_gui_coord v1, t_gui_coord v2, int color)
**	
**	Function that fill area screen.
*/
void	ft_gui_fill_area(t_wolf3d *w, t_gui_coord v1, t_gui_coord v2, int color)
{
	int			x;
	int			y;
	double		d;

	if (color & C_A)
		d = (double)((color & C_A) >> 24) / 255;
	else
		d = 0.0;

	y = v1.y >= 0 ? v1.y : 0;
	while (y <= v2.y && y < WIN_HEIGHT)
	{
		x = v1.x >= 0 ? v1.x : 0;
		while (x <= v2.x && x < WIN_WIDTH)
		{
			if (d == 0.0)
				w->sdl->pixels[x + (y * WIN_WIDTH)] = color;
			else
				w->sdl->pixels[x + (y * WIN_WIDTH)] = ft_fdf_get_color(color, \
					w->sdl->pixels[x + (y * WIN_WIDTH)], d);
			x++;
		}
		y++;
	}
}

/*
**	void ft_gui_draw_border(t_wolf3d *w, t_list *list, int color, int border_width)
**	
**	Function that draw border for gui elem.
*/
void	ft_gui_draw_border(t_wolf3d *w, t_list *list, int color, int border_width)
{
	int			x;
	int			y;
	t_gui_elem	*elem;

	elem = list->content;
	if (elem->status & GUI_ELEM_HOVER)
	{
		color = ft_fdf_get_color(color, 0xffffff, 0.3) + color & 0xff000000;
	}
	if (elem->status & GUI_ELEM_ACTIVE || elem->status & GUI_ELEM_FOCUS)
	{
		color = ft_fdf_get_color(color, 0xffffff, 0.5) + color & 0xff000000;
	}

	ft_gui_fill_area(w, (t_gui_coord){elem->v1.x, elem->v1.y, 0}, \
		(t_gui_coord){elem->v1.x + border_width, elem->v2.y, 0}, color);
	ft_gui_fill_area(w, (t_gui_coord){elem->v1.x, elem->v1.y, 0}, \
		(t_gui_coord){elem->v2.x, elem->v1.y + border_width, 0}, color);

	ft_gui_fill_area(w, (t_gui_coord){elem->v1.x + border_width, elem->v2.y - border_width, 0}, \
		(t_gui_coord){elem->v2.x, elem->v2.y, 0}, color);
	ft_gui_fill_area(w, (t_gui_coord){elem->v2.x - border_width, elem->v1.y + border_width, 0}, \
		(t_gui_coord){elem->v2.x, elem->v2.y, 0}, color);
}

/*
**	void ft_gui_fill_elem(t_wolf3d *w, t_list *list, int color)
**	
**	Function that fill gui elem area.
*/
void	ft_gui_fill_elem(t_wolf3d *w, t_list *list, int color)
{
	int			x;
	int			y;
	t_gui_elem	*elem;

	elem = list->content;

	if (elem == NULL)
		ft_error("ERROR");

	if (elem->status & GUI_ELEM_HOVER)
	{
		color = ft_fdf_get_color(color, 0xffffff, 0.5) + color & 0xff000000;
	}
	if (elem->status & GUI_ELEM_ACTIVE)
	{
		color = ft_fdf_get_color(color, 0x000000, 0.5) + color & 0xff000000;
	}

	ft_gui_fill_area(w, elem->v1, elem->v2, color);
}

/*
**	[TEMPORARY] [TESTING]
**	void ft_gui_redraw_elem(t_wolf3d *w)
**	
**	Function that redraw gui elem.
*/
void	ft_gui_redraw_elem(t_wolf3d *w, t_list *dom)
{
	t_list		*list;
	t_gui_elem	*elem;

	list = dom;
	while (list != NULL)
	{
		elem = list->content;
		if (elem->status & GUI_ELEM_HIDDEN)
		{
			list = list->next;
			continue ;
		}
		if (elem->redraw)
			elem->redraw(w, list);
		else if (elem->type == GUI_IMAGE)
			ft_gui_draw_image(w, list);
		else if (elem->type == GUI_BLOCK || \
			elem->type == GUI_BUTTON)
			ft_gui_fill_elem(w, list, elem->color);
		else if (elem->type == GUI_INPUT || elem->type == GUI_INPUT_NUMB)
			ft_gui_draw_border(w, list, elem->color, 3);
		ft_gui_redraw_elem(w, elem->child);
		list = list->next;
	}
}

/*
**	void ft_gui_redraw(t_wolf3d *w)
**	
**	Function that redraw frame.
*/
int		ft_gui_redraw_frame(t_wolf3d *w)
{
	return (0);
}

/*
**	void ft_gui_fill_elem(t_wolf3d *w, t_list *list, int color)
**	
**	Function that put text for elem area.
*/
void	ft_gui_putstr_elem_font(t_wolf3d *w, t_list *list, int color)
{
	int			x;
	int			y;
	t_gui_elem	*elem;

	elem = list->content;
	if (elem == NULL)
		ft_error("ERROR");
	
	if (elem->type == GUI_BUTTON)
	{
		if (elem->status & GUI_ELEM_HOVER)
			color = ft_fdf_get_color(color, 0xffffff, 0.5);
		if (elem->status & GUI_ELEM_ACTIVE)
			color = ft_fdf_get_color(color, 0x000000, 0.5);
		// hsl imitation
		if ((((color & C_R) >> 16) + ((color & C_G) >> 8) + (color & C_B)) / 3 > 128)
			color = 0x000000;
		else
			color = 0xffffff;
		// invertion
		// color = ~color & 0x00ffffff;
		ft_gui_font_preset_fsc(w, "fonts/RobotoMono-Medium.ttf", 16, color);
		ft_gui_font_putstr_sdl(w, elem->str, (t_gui_coord){elem->v1.x + 10, elem->v1.y + 10, 0});
	}

	if (elem->type == GUI_TEXT)// || elem->type == GUI_INPUT)
	{
		ft_gui_font_preset_fsc(w, "fonts/RobotoMono-Medium.ttf", 16, color);
		ft_gui_font_putstr_sdl(w, elem->str, (t_gui_coord){elem->v1.x + 10, elem->v1.y + 10, 0});
	}
	if (elem->type == GUI_INPUT || elem->type == GUI_INPUT_NUMB)
	{
		// color = ft_fdf_get_color(color, 0xffffff, 1);
		ft_gui_font_preset_fsc(w, "fonts/RobotoMono-Medium.ttf", 16, color);
		ft_gui_font_putstr_sdl(w, elem->str, (t_gui_coord){elem->v1.x + 10, elem->v1.y + 10, 0});
	}
}

/*
**	[TEMPORARY] [TESTING]
**	void ft_gui_redraw_elem(t_wolf3d *w, t_list *dom)
**	
**	Function that print font for elements.
*/
void	ft_gui_redraw_elem_font(t_wolf3d *w, t_list *dom)
{
	t_list		*list;
	t_gui_elem	*elem;

	list = dom;
	while (list != NULL)
	{
		elem = list->content;
		if (elem->status & GUI_ELEM_HIDDEN)
		{
			list = list->next;
			continue ;
		}
		ft_gui_putstr_elem_font(w, list, elem->color);
		ft_gui_redraw_elem_font(w, elem->child);
		list = list->next;
	}
}

/*
**	void ft_gui_redraw(t_wolf3d *w)
**	
**	Function that redraw windows.
*/
int		ft_gui_redraw(t_wolf3d *w)
{
	if (w->gui.redraw == GUI_REDRAW_FRAME)
		return (ft_gui_redraw_frame(w));
	ft_bzero(w->sdl->pixels, 4 * WIN_WIDTH * WIN_HEIGHT);
	SDL_SetRenderDrawColor(w->sdl->renderer, 0x00, 0x00, 0x00, 0xff);
	SDL_RenderClear(w->sdl->renderer);
	ft_gui_redraw_elem(w, w->gui.dom);
	SDL_UpdateTexture(w->sdl->text, 0, w->sdl->pixels, WIN_WIDTH * 4);
	SDL_RenderCopy(w->sdl->renderer, w->sdl->text, NULL, NULL);
	ft_gui_redraw_elem_font(w, w->gui.dom);
	SDL_RenderPresent(w->sdl->renderer);
	w->gui.redraw = GUI_NOT_REDRAW;
	ft_gui_delete_status(w->gui.dom);
	return (0);
}