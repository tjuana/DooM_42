/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjuana <tjuana@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/27 20:31:00 by dorange-          #+#    #+#             */
/*   Updated: 2020/02/23 19:45:01 by tjuana           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

/*
** **************************************************************************
**	void ft_main(int c, char **v)
**
**	General programm function.
** **************************************************************************
*/

void	ft_main(int c, char **v)
{
	t_wolf3d	w;
	t_new_temp	data;

	if (c > 2)
		ft_error("WRONG arguments");
	// ft_unpack();
	ft_bzero(&data, sizeof(t_new_temp));
	data.pl = (t_new_player *)ft_my_malloc(sizeof(t_new_player));
	w.new_data = &data;
	w.sdl = sdl_init(w.sdl);
	ft_load_sounds(data.pl);
	ft_gui_init(&w);
	ft_editor_init(&w);
	ft_main_gui_init(&w);
	ft_editor_gui_init(&w);
	ft_game_init(&w, v[1]);
	data.pl->map_path = v[1];
	ft_gui_redraw(&w);
	data.pl->tex = ft_game_load_textures(data.pl);
	while (w.sdl->running)
		ft_main_events(&w);
	ft_editor_desctuct(&w);
	ft_clean_sdl(&w);
	// ft_check_folders();
}

int		main(int c, char **v)
{
	ft_main(c, v);
	return (0);
}
