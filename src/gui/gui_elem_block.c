/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gui_elem_block.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dorange- <dorange-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/16 14:02:35 by dorange-          #+#    #+#             */
/*   Updated: 2020/01/16 14:04:08 by dorange-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

/*
**	void ft_gui_mousebuttonup_block(void *data, SDL_Event e, t_list *dom, int type)
**	
**	Function that transform block status for mousemotuin event.
*/
void	ft_gui_mousebuttonup_block(void *data, SDL_Event e, t_list *dom, int type)
{
	t_wolf3d	*w;

	w = (t_wolf3d*)data;
	ft_gui_delete_status_focus(w->gui.dom);
	w->gui.focus_elem = NULL;
}
