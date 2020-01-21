/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   editor_main.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjuana <tjuana@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/10 16:05:19 by dorange-          #+#    #+#             */
/*   Updated: 2020/01/21 20:40:42 by tjuana           ###   ########.fr       */
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

	ft_editor_init(&w);
	ft_editor_gui_init(&w);

	if (c >= 2)
	{
		if ((w.fd = open(v[1], O_RDONLY)) < 0)
			ft_error("Error: bad file");
		ft_parser_nnmp(w.fd, &w);
	}

	// Not use
	ft_load_textures(&w);
	ft_init_sound(&w);

	ft_gui_print_element_list(w.gui.dom, 0);
	ft_gui_redraw(&w);
	while (w.sdl->running)
		ft_gui_events(&w);
	// ft_save_the_file(&w);
	ft_editor_sector_special_debug(w.sector);
	ft_gui_desctuct(w.gui.dom);
	ft_gui_desctuct_fonts(w.gui.fonts);
	ft_clean_sdl(&w);
}

int				main(int c, char **v)
{
	ft_editor_main(c, v);
	return (0);
}