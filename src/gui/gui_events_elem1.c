/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gui_events_elem1.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dorange- <dorange-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/15 12:38:39 by dorange-          #+#    #+#             */
/*   Updated: 2020/01/15 13:29:25 by dorange-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

/*
**	void ft_gui_mousemotion_elem1(void *data, SDL_Event e, t_list *dom, int type)
**	
**	Function that work with elem1.
*/
void	ft_gui_mousemotion_elem1(void *data, SDL_Event e, t_list *dom, int type)
{
	t_wolf3d	*w;

	w = (t_wolf3d*)data;
	ft_gui_elem_set_status(dom, GUI_ELEM_HOVER);
}