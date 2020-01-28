/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_events.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dorange- <dorange-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/28 14:51:11 by dorange-          #+#    #+#             */
/*   Updated: 2020/01/28 20:32:58 by dorange-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

// Особенность: при отрисовке по событию нет динамических объектов.
// Фиксится добавлением в специальный цикл events и gui_redraw для game.
void	ft_main_events(t_wolf3d *w)
{
	t_new_temp	*data;

	if (w->gui.mode == GUI_MD_GAME)
	{
		data = w->new_data;
		ft_game_events(data);
		if (data->se.quit == 1)
		{
			ft_gui_elem_set_status(\
				ft_gui_search_elem_by_name(w->gui.dom, "win_game"), \
				GUI_ELEM_HIDDEN);
			ft_gui_elem_set_status(\
				ft_gui_search_elem_by_name(w->gui.dom, "win_menu"), \
				GUI_ELEM_VISIBLE);
			w->gui.mode = GUI_MD_ME;
			w->player_status = 0;
			SDL_ShowCursor(SDL_ENABLE);
		}
		ft_gui_redraw(w);
	}
	else
		ft_gui_events(w);
}
