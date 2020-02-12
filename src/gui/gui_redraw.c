/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gui_redraw.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dorange- <dorange-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/14 16:22:56 by dorange-          #+#    #+#             */
/*   Updated: 2020/02/12 14:09:36 by dorange-         ###   ########.fr       */
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
	ft_bzero(w->sdl->srf->pixels, 4 * w->gui.win_w * w->gui.win_h);
	// Заполняем render чёрным цветом
	SDL_SetRenderDrawColor(w->sdl->renderer, 0x00, 0x00, 0x00, 0x00);
	SDL_RenderClear(w->sdl->renderer);
	// Заполняем пиксели в surface
	ft_gui_redraw_elem(w, w->gui.dom);
	// Создаём текстуру из surface
	w->sdl->text = SDL_CreateTextureFromSurface(\
		w->sdl->renderer, w->sdl->srf);
	w->sdl->text == NULL ? ft_putstr_fd(SDL_GetError(), 2) : 0;
	// Помещаем текстуру в renderer
	SDL_RenderCopy(w->sdl->renderer, w->sdl->text, 0, 0) != 0 ? \
		ft_putstr_fd(SDL_GetError(), 2) : 0;
	// Добавляем надписи
	ft_gui_redraw_elem_font(w, w->gui.dom);
	// Отображаем изменения
	SDL_RenderPresent(w->sdl->renderer);
	// Удаляем текстуру, созданную из surface
	SDL_DestroyTexture(w->sdl->text);
	w->gui.redraw = GUI_NOT_REDRAW;
	ft_gui_delete_status(w->gui.dom);
	// usleep(777);
	return (0);
}
