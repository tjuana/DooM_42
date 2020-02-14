/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dorange- <dorange-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/27 20:31:00 by dorange-          #+#    #+#             */
/*   Updated: 2020/02/14 17:33:40 by dorange-         ###   ########.fr       */
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

	ft_bzero(&data, sizeof(t_new_temp));
	w.new_data = &data;
	w.sdl = sdl_init(w.sdl);
	ft_init_wolf(&w);
	ft_gui_init(&w);
	ft_editor_init(&w);
	ft_main_gui_init(&w);
	ft_editor_gui_init(&w);
	ft_game_init(&w, v[1]);
	ft_gui_redraw(&w);
	data.pl.tex = load_textures(&data.pl);
	fpsinit();
	while (w.sdl->running)
	{
		ft_main_events(&w);
		fpsthink();
	}
	ft_editor_desctuct(&w);
}

int		main(int c, char **v)
{
	ft_main(c, v);
	return (0);
}
