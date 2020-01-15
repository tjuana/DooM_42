/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gui_elem_button.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dorange- <dorange-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/15 13:39:41 by dorange-          #+#    #+#             */
/*   Updated: 2020/01/15 14:44:58 by dorange-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

/*
**	void ft_gui_mousemotion_button(void *data, SDL_Event e, t_list *dom, int type)
**	
**	Function that transform button status for mousemotuin event.
*/
void	ft_gui_mousemotion_button(void *data, SDL_Event e, t_list *dom, int type)
{
	t_wolf3d	*w;
	t_gui_elem	*elem;

	w = (t_wolf3d*)data;
	elem = dom->content;
	ft_gui_elem_set_status(dom, GUI_ELEM_HOVER);
}

/*
**	void ft_gui_mousebuttondown_button(void *data, SDL_Event e, t_list *dom, int type)
**	
**	Function that transform button status for mousebuttondown event.
*/
void	ft_gui_mousebuttondown_button(void *data, SDL_Event e, t_list *dom, int type)
{
	t_wolf3d	*w;

	w = (t_wolf3d*)data;
	ft_gui_elem_set_status(dom, GUI_ELEM_ACTIVE);
}

/*
**	void ft_gui_mousebuttonup_button(void *data, SDL_Event e, t_list *dom, int type)
**	
**	Function that transform button status for mousebuttonup event.
*/
void	ft_gui_mousebuttonup_button(void *data, SDL_Event e, t_list *dom, int type)
{
	t_wolf3d	*w;

	w = (t_wolf3d*)data;
	ft_gui_elem_set_status(dom, GUI_ELEM_HOVER);
}