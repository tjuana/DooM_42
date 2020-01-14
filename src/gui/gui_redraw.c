/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gui_redraw.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dorange- <dorange-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/14 16:22:56 by dorange-          #+#    #+#             */
/*   Updated: 2020/01/14 22:03:01 by dorange-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

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
		// color = 0x000000;
		// printf("%d   %d\n", elem->status, GUI_ELEM_HOVER);
		color = ft_fdf_get_color(color, 0xffffff, 0.5);
	}
	y = elem->v1.y >= 0 ? elem->v1.y : 0;
	while (y <= elem->v2.y && y < WIN_HEIGHT)
	{
		x = elem->v1.x >= 0 ? elem->v1.x : 0;
		while (x <= elem->v2.x && x < WIN_WIDTH)
		{
			w->sdl->pixels[x + (y * WIN_WIDTH)] = color;
			x++;
		}
		y++;
	}
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
		ft_gui_fill_elem(w, list, elem->color);
		ft_gui_elem_set_status(list, GUI_ELEM_NORMAL);
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
	// ft_gui_print_element_list(w->gui.dom, 0);

	SDL_UpdateTexture(w->sdl->text, 0, w->sdl->pixels, WIN_WIDTH * 4);
	SDL_RenderCopy(w->sdl->renderer, w->sdl->text, NULL, NULL);

	SDL_RenderPresent(w->sdl->renderer);

	w->gui.redraw = GUI_NOT_REDRAW;
	return (0);
}