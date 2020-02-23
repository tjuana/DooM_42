/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gui_redraw_image.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dorange- <dorange-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/06 17:41:25 by dorange-          #+#    #+#             */
/*   Updated: 2020/02/21 17:28:07 by dorange-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

/*
** **************************************************************************
**	int ft_gui_get_image_pixel_pos_elem(int x, int y, t_gui_elem *elem)
**
**	Function that get special pixel surface position for element.
** **************************************************************************
*/

int		ft_gui_get_image_pixel_pos_elem(int x, int y, t_gui_elem *elem)
{
	int	pos;

	if (!elem->surf)
	{
		ft_putstr("no surface valid");
		return (0);
	}
	pos = ((y - elem->v1.y) * elem->surf->h / \
		(elem->v2.y - elem->v1.y) % elem->surf->h) * elem->surf->w + \
		((x - elem->v1.x) * elem->surf->w / \
		(elem->v2.x - elem->v1.x) % elem->surf->w);
	pos %= (elem->surf->h * elem->surf->w);
	return (pos);
}

/*
** **************************************************************************
**	int ft_gui_get_image_pixel_pos(int x, int y, \
**		t_gui_rect rect, SDL_Surface *surf)
**
**	Function that get special pixel surface position.
** **************************************************************************
*/

int		ft_gui_get_image_pixel_pos(int x, int y, \
			t_gui_rect rect, SDL_Surface *surf)
{
	int	pos;

	pos = ((y - rect.v1.y) * surf->h / \
		(rect.v2.y - rect.v1.y) % surf->h) * surf->h + \
		((x - rect.v1.x) * surf->w / \
		(rect.v2.x - rect.v1.x) % surf->w);
	pos %= (surf->h * surf->w);
	return (pos);
}

/*
** **************************************************************************
**	void ft_gui_draw_image_put_pixel(t_wolf3d *w, int x, int y, int color)
**
**	Function that put pixel for main sdl surface.
** **************************************************************************
*/

void	ft_gui_draw_image_put_pixel(t_wolf3d *w, int x, int y, int color)
{
	if (color != 0x00ffffff && color != 0x00000000)
	{
		((int*)w->sdl->pixels)[x + (y * w->gui.win_w)] = \
			(int)color;
	}
}

/*
** **************************************************************************
**	void ft_gui_redraw(t_wolf3d *w)
**
**	Function that redraw image for area.
** **************************************************************************
*/

void	ft_gui_draw_image_area(t_wolf3d *w, t_gui_rect rect, \
			SDL_Surface *surf)
{
	int			x;
	int			y;
	int			pos;
	int			*ptr_color;

	pos = 0;
	y = rect.v1.y >= 0 ? rect.v1.y : 0;
	while (y <= rect.v2.y && y < w->gui.win_h)
	{
		x = rect.v1.x >= 0 ? rect.v1.x : 0;
		while (x <= rect.v2.x && x < w->gui.win_w)
		{
			pos = ft_gui_get_image_pixel_pos(x, y, rect, surf);
			ptr_color = (int*)(surf->pixels) + pos;
			ft_gui_draw_image_put_pixel(w, x, y, *ptr_color);
			x++;
			pos++;
		}
		y++;
	}
}

/*
** **************************************************************************
**	void ft_gui_draw_image(t_wolf3d *w, t_list *list)
**
**	Function that draw image.
** **************************************************************************
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
			pos = ft_gui_get_image_pixel_pos_elem(x, y, elem);
			ptr_color = (int*)(elem->surf->pixels) + pos;
			ft_gui_draw_image_put_pixel(w, x, y, *ptr_color);
			x++;
			pos++;
		}
		y++;
	}
}
