/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   editor_event_win_menu_save_map.c                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dorange- <dorange-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/26 15:16:02 by dorange-          #+#    #+#             */
/*   Updated: 2020/01/26 15:16:12 by dorange-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

void	ft_gui_mousebuttonup_win_menu_btnsavemap(void *data, SDL_Event e, \
			t_list *dom, int type)
{
	t_wolf3d	*w;

	w = (t_wolf3d*)data;
	w->file.name = ft_gui_elem_get_value(\
		ft_gui_search_elem_by_name(w->gui.dom, "win_menu_inputmapname"));
	ft_save_the_file(w);
}