/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gui_redraw_fill.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dorange- <dorange-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/06 17:44:00 by dorange-          #+#    #+#             */
/*   Updated: 2020/02/06 17:48:06 by dorange-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

/*
** **************************************************************************
**	void ft_gui_fill_area(t_wolf3d *w, t_gui_coord v1,
**		t_gui_coord v2, int color)
**
**	Function that fill area screen.
** **************************************************************************
*/

void	ft_gui_fill_area(t_wolf3d *w, t_gui_coord v1, \
			t_gui_coord v2, int color)
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
				((int*)w->sdl->srf->pixels)[x + (y * w->gui.win_w)] = \
					ft_fdf_get_color(color, \
					((int*)w->sdl->srf->pixels)[x + (y * w->gui.win_w)], d);
			x++;
		}
		y++;
	}
}

/*
** **************************************************************************
**	void ft_gui_draw_border(t_wolf3d *w, t_list *list,
**	int color, int border_width)
**
**	Function that draw border for gui elem.
** **************************************************************************
*/

void	ft_gui_draw_border(t_wolf3d *w, t_list *list, \
			int color, int border_width)
{
	int			x;
	int			y;
	t_gui_elem	*elem;

	elem = list->content;
	if (elem->status & GUI_ELEM_HOVER)
		color = ft_fdf_get_color(color, 0xffffff, 0.3);
	if (elem->status & GUI_ELEM_ACTIVE || elem->status & GUI_ELEM_FOCUS)
		color = ft_fdf_get_color(color, 0xffffff, 0.5);
	ft_gui_fill_area(w, (t_gui_coord){elem->v1.x, elem->v1.y, 0}, \
		(t_gui_coord){elem->v1.x + border_width, elem->v2.y, 0}, color);
	ft_gui_fill_area(w, (t_gui_coord){elem->v1.x, elem->v1.y, 0}, \
		(t_gui_coord){elem->v2.x, elem->v1.y + border_width, 0}, color);

	ft_gui_fill_area(w, (t_gui_coord){elem->v1.x + border_width, \
		elem->v2.y - border_width, 0}, \
		(t_gui_coord){elem->v2.x, elem->v2.y, 0}, color);
	ft_gui_fill_area(w, (t_gui_coord){elem->v2.x - border_width, \
		elem->v1.y + border_width, 0}, \
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
		color = ft_fdf_get_color(color, 0xffffff, 0.5);
	if (elem->status & GUI_ELEM_ACTIVE)
		color = ft_fdf_get_color(color, 0x000000, 0.5);
	ft_gui_fill_area(w, elem->v1, elem->v2, color);
}
