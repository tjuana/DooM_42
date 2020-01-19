/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gui_redraw.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dorange- <dorange-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/14 16:22:56 by dorange-          #+#    #+#             */
/*   Updated: 2020/01/19 18:54:36 by dorange-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

/*
**	void ft_gui_fill_area(t_wolf3d *w, t_ui_coord v1, t_ui_coord v2, int color)
**	
**	Function that fill area screen.
*/
void	ft_gui_fill_area(t_wolf3d *w, t_ui_coord v1, t_ui_coord v2, int color)
{
	int			x;
	int			y;

	y = v1.y >= 0 ? v1.y : 0;
	while (y <= v2.y && y < WIN_HEIGHT)
	{
		x = v1.x >= 0 ? v1.x : 0;
		while (x <= v2.x && x < WIN_WIDTH)
		{
			w->sdl->pixels[x + (y * WIN_WIDTH)] = color;
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
		color = ft_fdf_get_color(color, 0xffffff, 0.3);
	}
	if (elem->status & GUI_ELEM_ACTIVE || elem->status & GUI_ELEM_FOCUS)
	{
		color = ft_fdf_get_color(color, 0xffffff, 0.5);
	}

	ft_gui_fill_area(w, (t_ui_coord){elem->v1.x, elem->v1.y, 0}, \
		(t_ui_coord){elem->v1.x + border_width, elem->v2.y, 0}, color);
	ft_gui_fill_area(w, (t_ui_coord){elem->v1.x, elem->v1.y, 0}, \
		(t_ui_coord){elem->v2.x, elem->v1.y + border_width, 0}, color);

	ft_gui_fill_area(w, (t_ui_coord){elem->v1.x + border_width, elem->v2.y - border_width, 0}, \
		(t_ui_coord){elem->v2.x, elem->v2.y, 0}, color);
	ft_gui_fill_area(w, (t_ui_coord){elem->v2.x - border_width, elem->v1.y + border_width, 0}, \
		(t_ui_coord){elem->v2.x, elem->v2.y, 0}, color);
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
		color = ft_fdf_get_color(color, 0xffffff, 0.5);
	}
	if (elem->status & GUI_ELEM_ACTIVE)
	{
		color = ft_fdf_get_color(color, 0x000000, 0.5);
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
		if (elem->type == GUI_ELEM_TYPE_MAP)
			ft_gui_draw_map(w, list);
		else if (elem->type == GUI_ELEM_TYPE_BLOCK || \
			elem->type == GUI_ELEM_TYPE_BUTTON)
			ft_gui_fill_elem(w, list, elem->color);
		else if (elem->type == GUI_ELEM_TYPE_INPUT)
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

	if (elem->type == GUI_ELEM_TYPE_BUTTON)
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
		ft_gui_font_putstr_sdl(w, elem->str, (t_ui_coord){elem->v1.x + 10, elem->v1.y + 10, 0});
	}

	if (elem->type == GUI_ELEM_TYPE_TEXT)// || elem->type == GUI_ELEM_TYPE_INPUT)
	{
		ft_gui_font_preset_fsc(w, "fonts/RobotoMono-Medium.ttf", 16, color);
		ft_gui_font_putstr_sdl(w, elem->str, (t_ui_coord){elem->v1.x + 10, elem->v1.y + 10, 0});
	}
	if (elem->type == GUI_ELEM_TYPE_INPUT)
	{
		// color = ft_fdf_get_color(color, 0xffffff, 1);
		ft_gui_font_preset_fsc(w, "fonts/RobotoMono-Medium.ttf", 16, color);
		ft_gui_font_putstr_sdl(w, elem->str, (t_ui_coord){elem->v1.x + 10, elem->v1.y + 10, 0});
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
	ft_gui_draw_sprites(w);
	ft_gui_draw_enemies(w);

	// ft_gui_print_element_list(w->gui.dom, 0);

	SDL_UpdateTexture(w->sdl->text, 0, w->sdl->pixels, WIN_WIDTH * 4);
	SDL_RenderCopy(w->sdl->renderer, w->sdl->text, NULL, NULL);

	ft_gui_redraw_elem_font(w, w->gui.dom);

	SDL_RenderPresent(w->sdl->renderer);

	w->gui.redraw = GUI_NOT_REDRAW;

	ft_gui_delete_status(w->gui.dom);

	return (0);
}