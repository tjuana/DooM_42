/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dorange- <dorange-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/27 20:31:00 by dorange-          #+#    #+#             */
/*   Updated: 2020/01/27 22:11:49 by dorange-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

typedef	struct		s_new_temp
{
    t_new_sub_ev se;
    t_new_mouse ms;
    t_new_player pl;
    t_new_others ot;
    t_new_sect_ops op;
	t_new_wolf3d w;
}					t_new_temp;

/*
** **************************************************************************
**	void ft_main(int c, char **v)
**
**	General programm function.
** **************************************************************************
*/

void			ft_main(int c, char **v)
{
	t_wolf3d	w;
	t_new_temp	data;

	ft_bzero(&data, sizeof(t_new_temp));
	// ft_game_init(&data, ag[1]);

	w.sdl = sdl_init(w.sdl);
	ft_init_wolf(&w);
	ft_gui_init(&w);
	// init
	ft_editor_init(&w);
	// gui init
	ft_main_gui_init(&w);
	ft_editor_gui_init(&w);
	ft_gui_redraw(&w);
	while (w.sdl->running)
		ft_gui_events(&w);
	ft_editor_sector_special_debug(w.sector);
	ft_editor_desctuct(&w);
	ft_gui_desctuct(w.gui.dom);
	ft_gui_desctuct_fonts(w.gui.fonts);
}

int				main(int c, char **v)
{
	ft_main(c, v);
	return (0);
}