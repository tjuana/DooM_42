/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_events.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dorange- <dorange-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/28 14:51:11 by dorange-          #+#    #+#             */
/*   Updated: 2020/02/20 18:45:21 by dorange-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

void	ft_main_events(t_wolf3d *w)
{
	t_new_temp	*data;

	if (w->gui.mode == GUI_MD_GAME)
	{
		data = w->new_data;
		ft_game_events(data);
		ft_gui_redraw(w);
	}
	else
		ft_gui_events(w);
}
