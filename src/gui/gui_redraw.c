/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gui_redraw.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjuana <tjuana@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/14 16:22:56 by dorange-          #+#    #+#             */
/*   Updated: 2020/02/08 13:33:29 by tjuana           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"


void	ft_gui_draw_image_area(t_wolf3d *w, t_gui_rect rect, SDL_Surface *surf)
{
	int			x;
	int			y;
	int			pos;
	int			*ptr_color;
	t_gui_elem	*elem;

	// elem = list->content;

	pos = 0;
	y = rect.v1.y >= 0 ? rect.v1.y : 0;
	while (y <= rect.v2.y && y < w->gui.win_h)
	{
		x = rect.v1.x >= 0 ? rect.v1.x : 0;
		while (x <= rect.v2.x && x < w->gui.win_w)
		{
			pos = ((y - rect.v1.y) * surf->h / (rect.v2.y - rect.v1.y) % surf->h) * surf->h + \
				((x - rect.v1.x) * surf->w / (rect.v2.x - rect.v1.x) % surf->w);

			pos %= (surf->h * surf->w);
			ptr_color = (int*)(surf->pixels) + pos;
			if (*ptr_color != 0x00ffffff && *ptr_color != 0x00000000)
			{
				((int*)w->sdl->srf->pixels)[x + (y * w->gui.win_w)] = (int)*ptr_color;
			}
			x++;
			pos++;
		}
		y++;
	}
}
// Image (?)
/*
**	PNG -> put pixel
**	Скорректировать
*/
void	ft_gui_draw_image(t_wolf3d *w, t_list *list)
{
	int			x;
	int			y;
	int			pos;
	int			*ptr_color;
	t_gui_elem	*elem;

	elem = list->content;

	pos = 0;
	y = elem->v1.y >= 0 ? elem->v1.y : 0;
	while (y <= elem->v2.y && y < w->gui.win_h)
	{
		x = elem->v1.x >= 0 ? elem->v1.x : 0;
		while (x <= elem->v2.x && x < w->gui.win_w)
		{
			pos = ((y - elem->v1.y) * elem->surf->h / (elem->v2.y - elem->v1.y) % elem->surf->h) * elem->surf->h + \
				((x - elem->v1.x) * elem->surf->w / (elem->v2.x - elem->v1.x) % elem->surf->w);

			pos %= (elem->surf->h * elem->surf->w);
			ptr_color = (int*)(elem->surf->pixels) + pos;
			if (*ptr_color != 0x00ffffff && *ptr_color != 0x00000000)
			{
				((int*)w->sdl->srf->pixels)[x + (y * w->gui.win_w)] = (int)*ptr_color;
			}
			// else
				// // printf();
			// else
			// {
			// 	((int*)w->sdl->srf->pixels)[x + (y * w->gui.win_w)] = ft_fdf_get_color(*ptr_color, \
			// 		((int*)w->sdl->srf->pixels)[x + (y * w->gui.win_w)], (double)(*ptr_color >> 24 & 0xFF) / 0xFF);
			// }
			x++;
			pos++;
		}
		y++;
	}
}

/*
** **************************************************************************
**	void ft_gui_fill_area(t_wolf3d *w, t_gui_coord v1, t_gui_coord v2, int color)
**	
**	Function that fill area screen.
** **************************************************************************
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
	while (y <= v2.y && y < w->gui.win_h)
	{
		x = v1.x >= 0 ? v1.x : 0;
		while (x <= v2.x && x < w->gui.win_w)
		{
			if (d == 0.0)
				((int*)w->sdl->srf->pixels)[x + (y * w->gui.win_w)] = color;
			else
				((int*)w->sdl->srf->pixels)[x + (y * w->gui.win_w)] = ft_fdf_get_color(color, \
					((int*)w->sdl->srf->pixels)[x + (y * w->gui.win_w)], d);
			x++;
		}
		y++;
	}
}

/*
** **************************************************************************
**	void ft_gui_draw_border(t_wolf3d *w, t_list *list, int color, int border_width)
**	
**	Function that draw border for gui elem.
** **************************************************************************
*/
void	ft_gui_draw_border(t_wolf3d *w, t_list *list, int color, int border_width)
{
	int			x;
	int			y;
	t_gui_elem	*elem;

	elem = list->content;
	if (elem->status & GUI_ELEM_HOVER)
	{
		color = ft_fdf_get_color(color, 0xffffff, 0.3);
	}
	if (elem->status & GUI_ELEM_ACTIVE || elem->status & GUI_ELEM_FOCUS)
	{
		color = ft_fdf_get_color(color, 0xffffff, 0.5);
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
** **************************************************************************
**	void ft_gui_fill_elem(t_wolf3d *w, t_list *list, int color)
**	
**	Function that fill gui elem area.
** **************************************************************************
*/
void	ft_gui_fill_elem(t_wolf3d *w, t_list *list, int color)
{
	int			x;
	int			y;
	t_gui_elem	*elem;

	elem = list->content;

	if (elem == NULL)
		ft_error("ERROR (N5)");

	if (elem->status & GUI_ELEM_HOVER)
	{
		color = ft_fdf_get_color(color, 0xffffff, 0.5);
	}
	if (elem->status & GUI_ELEM_ACTIVE)
	{
		color = ft_fdf_get_color(color, 0x000000, 0.5);
	}

	ft_gui_fill_area(w, elem->v1, elem->v2, color);
}

/*
** **************************************************************************
**	[TEMPORARY] [TESTING]
**	void ft_gui_redraw_elem(t_wolf3d *w)
**	
**	Function that redraw gui elem.
** **************************************************************************
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
** **************************************************************************
**	void ft_gui_redraw(t_wolf3d *w)
**	
**	Function that redraw frame.
** **************************************************************************
*/
int		ft_gui_redraw_frame(t_wolf3d *w)
{
	return (0);
}

/*
** **************************************************************************
**	void ft_gui_fill_elem(t_wolf3d *w, t_list *list, int color)
**	
**	Function that put text for elem area.
** **************************************************************************
*/
void	ft_gui_putstr_elem_font(t_wolf3d *w, t_list *list, int color)
{
	int			x;
	int			y;
	t_gui_elem	*elem;

	elem = list->content;
	if (elem == NULL)
		ft_error("ERROR (N6)");
	
	if (elem->type == GUI_BUTTON)
	{
		if (elem->status & GUI_ELEM_HOVER)
			color = ft_fdf_get_color(color, 0xffffff, 0.5);
		if (elem->status & GUI_ELEM_ACTIVE)
			color = ft_fdf_get_color(color, 0x000000, 0.5);
		if ((((color & C_R) >> 16) + ((color & C_G) >> 8) + (color & C_B)) / 3 > 128)
			color = 0x000000;
		else
			color = 0xffffff;
		ft_gui_font_preset_fsc(w, "fonts/RobotoMono-Medium.ttf", elem->fs, color);
		ft_gui_font_putstr_sdl(w, elem->str, (t_gui_coord){elem->v1.x + 10, elem->v1.y + 10, 0});
	}

	if (elem->type == GUI_TEXT)
	{
		ft_gui_font_preset_fsc(w, "fonts/RobotoMono-Medium.ttf", elem->fs, color);
		ft_gui_font_putstr_sdl(w, elem->str, (t_gui_coord){elem->v1.x + 10, elem->v1.y + 10, 0});
	}
	if (elem->type == GUI_INPUT || elem->type == GUI_INPUT_NUMB)
	{
		ft_gui_font_preset_fsc(w, "fonts/RobotoMono-Medium.ttf", elem->fs, color);
		ft_gui_font_putstr_sdl(w, elem->str, (t_gui_coord){elem->v1.x + 10, elem->v1.y + 10, 0});
	}
}

/*
** **************************************************************************
**	void ft_gui_redraw_elem(t_wolf3d *w, t_list *dom)
**	
**	Function that print font for elements.
** **************************************************************************
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
** **************************************************************************
**	void ft_gui_redraw(t_wolf3d *w)
**	
**	Function that redraw windows.
** **************************************************************************
*/

int		ft_gui_redraw(t_wolf3d *w)
{
	if (w->gui.redraw == GUI_REDRAW_FRAME)
		return (ft_gui_redraw_frame(w));
	ft_bzero(w->sdl->srf->pixels, 4 * w->gui.win_w * w->gui.win_h);
	SDL_RenderClear(w->sdl->renderer);
	ft_gui_redraw_elem(w, w->gui.dom);
	w->sdl->text = SDL_CreateTextureFromSurface(w->sdl->renderer,w->sdl->srf);
	w->sdl->text == NULL ? ft_putstr_fd(SDL_GetError(), 2) : 0;
	SDL_RenderCopy(w->sdl->renderer, w->sdl->text, 0, 0) != 0 ? ft_putstr_fd(SDL_GetError(), 2) : 0;
	ft_gui_redraw_elem_font(w, w->gui.dom);
	SDL_RenderPresent(w->sdl->renderer);
	w->gui.redraw = GUI_NOT_REDRAW;
	ft_gui_delete_status(w->gui.dom);
	return (0);
}