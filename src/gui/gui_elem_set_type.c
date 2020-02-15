/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gui_elem_set_type.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dorange- <dorange-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/06 17:16:09 by dorange-          #+#    #+#             */
/*   Updated: 2020/02/06 17:18:49 by dorange-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

/*
** **************************************************************************
**	void ft_gui_elem_set_redraw_font(t_list *list, void *func)
**
**	Function that set image for gui element.
** **************************************************************************
*/

void	ft_gui_elem_set_image(t_list *list, char *path)
{
	t_gui_elem		*elem;
	SDL_Surface		*temp_surf;

	elem = list->content;
	elem->type = GUI_IMAGE;
	temp_surf = SDL_CreateRGBSurface(0, 1000, 1000, 32, 0, 0, 0, 0);//IMG_Load(path);
	elem->surf = SDL_ConvertSurfaceFormat(temp_surf, \
		SDL_PIXELFORMAT_RGB888, 0);
	SDL_FreeSurface(temp_surf);
	elem->surf == NULL ? ft_error("IMAGE LOAD ERROR") : 0;
}

/*
** **************************************************************************
**	void ft_gui_elem_set_block(t_list *list)
**
**	Function that set block type for gui element.
** **************************************************************************
*/

void	ft_gui_elem_set_block(t_list *list)
{
	t_gui_elem	*elem;

	elem = list->content;
	elem->type = GUI_BLOCK;
	ft_gui_elem_set_event(list, \
		ft_gui_mousebuttonup_block, SDL_MOUSEBUTTONUP, 0);
}

/*
** **************************************************************************
**	void ft_gui_elem_set_button(t_list *list, void *str)
**
**	Function that set button type for gui element.
** **************************************************************************
*/

void	ft_gui_elem_set_button(t_list *list, void *str)
{
	t_gui_elem	*elem;

	elem = list->content;
	elem->type = GUI_BUTTON;
	elem->str = ft_strdup(str);
	elem->fs = 16;
	ft_gui_elem_set_event(list, \
		ft_gui_mousemotion_button, SDL_MOUSEMOTION, 0);
	ft_gui_elem_set_event(list, \
		ft_gui_mousebuttondown_button, SDL_MOUSEBUTTONDOWN, 0);
	ft_gui_elem_set_event(list, \
		ft_gui_mousebuttonup_button, SDL_MOUSEBUTTONUP, 0);
}

/*
** **************************************************************************
**	void ft_gui_elem_set_input(t_list *list, void *str)
**
**	Function that set input type for gui element.
** **************************************************************************
*/

void	ft_gui_elem_set_input(t_list *list, void *str, int flag_numb)
{
	t_gui_elem	*elem;

	elem = list->content;
	elem->type = GUI_INPUT;
	if (flag_numb)
		elem->type = GUI_INPUT_NUMB;
	elem->str = ft_strdup(str);
	elem->fs = 16;
	ft_gui_elem_set_event(list, \
		ft_gui_mousemotion_input, SDL_MOUSEMOTION, 0);
	ft_gui_elem_set_event(list, \
		ft_gui_mousebuttondown_input, SDL_MOUSEBUTTONDOWN, 0);
	ft_gui_elem_set_event(list, \
		ft_gui_mousebuttonup_input, SDL_MOUSEBUTTONUP, 0);
}
