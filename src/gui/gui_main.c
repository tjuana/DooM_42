/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gui_main.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dorange- <dorange-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/14 15:14:16 by dorange-          #+#    #+#             */
/*   Updated: 2020/01/15 16:00:56 by dorange-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

/*
**	void ft_gui_main(void)
**	
**	This is a gui main function that compiles ./gui test programm with
**	some gui elements.
*/
void			ft_gui_main(void)
{
	t_wolf3d	w;

	w.sdl = sdl_init(w.sdl);
	ft_init_wolf(&w);

	// Not use
	ft_load_textures(&w);
	ft_init_sound(&w);

	ft_gui_init(&w);
	ft_gui_print_element_list(w.gui.dom, 0);
	ft_gui_redraw(&w);
	while (w.sdl->running)
	{
		ft_gui_events(&w);
		// render -> redraw -> ft_gui_events
	}
	ft_gui_desctuct(w.gui.dom);
	ft_gui_desctuct_fonts(w.gui.fonts);
	ft_clean_sdl(&w);
}

int				main(void)
{
	ft_gui_main();
	return (0);
}