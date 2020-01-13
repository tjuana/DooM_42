/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dorange- <dorange-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/12 12:07:54 by dorange-          #+#    #+#             */
/*   Updated: 2020/01/13 14:25:56 by dorange-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

/*
**	void ft_editor_close_fonts(t_wolf3d *w)
**
**	Function that close fonts.
*/
void		ft_editor_close_fonts(t_wolf3d *w)
{
	TTF_CloseFont(w->sdl->font.ptr_font_14_m);
	TTF_CloseFont(w->sdl->font.ptr_font_18_m);
	// TTF_CloseFont(w->sdl->font.ptr;
}

/*
**	void ft_editor_init_fonts(t_wolf3d *w)
**
**	Function that preset some fonts.
*/
void		ft_editor_init_fonts(t_wolf3d *w)
{
	if (!(w->sdl->font.ptr_font_14_m = TTF_OpenFont(FONT_PATH, 14)))
		ft_error("FONT ERROR (0)");
	if (!(w->sdl->font.ptr_font_18_m = TTF_OpenFont(FONT_PATH, 18)))
		ft_error("FONT ERROR (0)");
}

/*
**	void ft_editor_init(t_wolf3d *w)
**
**	Function that init. some values...
*/
void		ft_editor_init(t_wolf3d *w)
{
	w->sector = NULL;
	w->sector_status = 0;
	w->mouse_pos = (t_vector3){0, 0, 0, 0};
	w->status = 1;
	w->sector_count = 0;

	// ui_map values
	w->ui_map.v1 = (t_ui_coord){20, 20, 0};
	w->ui_map.v2 = (t_ui_coord){1720, 1060, 0};
	w->ui_map.w = w->ui_map.v2.x - w->ui_map.v1.x;
	w->ui_map.h = w->ui_map.v2.y - w->ui_map.v1.y;
}