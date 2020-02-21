/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gui_redraw.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjuana <tjuana@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/14 16:22:56 by dorange-          #+#    #+#             */
/*   Updated: 2020/02/21 20:24:25 by tjuana           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

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
**	Function that redraw windows.
** **************************************************************************
*/

int		ft_gui_redraw(t_wolf3d *w)
{
	ft_bzero(w->sdl->pixels, 4 * WIN_WIDTH * WIN_HEIGHT);
	SDL_SetRenderDrawColor(w->sdl->renderer, 0x00, 0x00, 0x00, 0xff) != 0 ? \
		ft_sdl_error(w->sdl) : 0;
	SDL_RenderClear(w->sdl->renderer) != 0 ? \
		ft_sdl_error(w->sdl) : 0;
	ft_gui_redraw_elem(w, w->gui.dom);
	SDL_UpdateTexture(w->sdl->text, 0, w->sdl->pixels, \
		WIN_WIDTH * 4) != 0 ? \
		ft_sdl_error(w->sdl) : 0;
	SDL_RenderCopy(w->sdl->renderer, w->sdl->text, NULL, NULL) != 0 ? \
		ft_sdl_error(w->sdl) : 0;
	ft_gui_redraw_elem_font(w, w->gui.dom);
	SDL_RenderPresent(w->sdl->renderer);
	w->gui.redraw = GUI_NOT_REDRAW;
	ft_gui_delete_status(w->gui.dom);
	return (0);
}
