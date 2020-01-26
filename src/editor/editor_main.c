/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   editor_main.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dorange- <dorange-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/10 16:05:19 by dorange-          #+#    #+#             */
/*   Updated: 2020/01/26 18:39:56 by dorange-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

/*
** **************************************************************************
**	void ft_editor_main(int c, char **v)
**
**	Function for map editor programm.
** **************************************************************************
*/

void			ft_editor_main(int c, char **v)
{
	t_wolf3d	w;

	w.sdl = sdl_init(w.sdl);
	ft_init_wolf(&w);
	ft_gui_init(&w);
	ft_editor_init(&w);
	ft_editor_gui_init(&w);
	ft_gui_redraw(&w);
	while (w.sdl->running)
		ft_gui_events(&w);
	ft_editor_sector_special_debug(w.sector);
	ft_editor_desctuct(&w);
}

int				main(int c, char **v)
{
	ft_editor_main(c, v);
	return (0);
}