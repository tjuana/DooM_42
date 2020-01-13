/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   editor.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dorange- <dorange-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/10 16:05:19 by dorange-          #+#    #+#             */
/*   Updated: 2020/01/13 14:41:54 by dorange-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

int		main(int c, char **v)
{
	t_wolf3d	w;

	ft_editor_init(&w);
	if (c >= 2)
	{
		if ((w.fd = open(v[1], O_RDONLY)) < 0)
			ft_error("Error: bad file");
		ft_parser_nnmp(w.fd, &w);
	}

	ft_editor_sector_special_debug(w.sector);

	w.sdl = sdl_init(w.sdl);
	ft_init_wolf(&w);
	ft_editor_init_fonts(&w);
	ft_editor_init_sectors_areas(&w, w.sector);

	ft_load_textures(&w);
	ft_init_anim(&w);
	ft_init_view_map(&w);
	ft_init_sound(&w);
	fpsinit();
	while (w.sdl->running)
	{
		ft_editor_renderer(&w);
		ft_editor_handle_events(&w);
		ft_editor_use_events(&w);
		fpsthink();
	}
	ft_editor_close_fonts(&w);
	ft_clean_sdl(&w);
	return (0);
}