/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dorange- <dorange-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/12 12:07:54 by dorange-          #+#    #+#             */
/*   Updated: 2020/01/13 14:57:41 by dorange-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

/*
**	void ft_editor_init_sectors_item_area(t_wolf3d *w, t_sector *sector)
**
**	Function that set one sector as ui element.
*/
void		ft_editor_init_sectors_item_area(t_wolf3d *w, t_sector *s)
{
	t_vector3	v1;
	t_vector3	v2;
	int			i;

	if (s->vertex_count == 0)
		return ;
	v1 = *s->vertex[0];
	v2 = *s->vertex[0];
	i = 0;
	while (i < s->vertex_count)
	{
		v1.x = (s->vertex[i]->x < v1.x) ? s->vertex[i]->x : v1.x;
		v1.y = (s->vertex[i]->y < v1.y) ? s->vertex[i]->y : v1.y;
		v2.x = (s->vertex[i]->x > v2.x) ? s->vertex[i]->x : v2.x;
		v2.y = (s->vertex[i]->y > v2.y) ? s->vertex[i]->y : v2.y;
		i++;
	}
	v1 = ft_editor_map_get_xy_vertex_pos(w, v1);
	v2 = ft_editor_map_get_xy_vertex_pos(w, v2);
	s->elem_2d.v1 = (t_ui_coord){(int)v1.x, (int)v1.y, 0};
	s->elem_2d.v2 = (t_ui_coord){(int)v2.x, (int)v2.y, 0};
	s->elem_2d.w = s->elem_2d.v2.x - s->elem_2d.v1.x;
	s->elem_2d.h = s->elem_2d.v2.y - s->elem_2d.v1.y;
}

/*
**	void ft_editor_init_sector_areas(t_wolf3d *w)
**
**	Function that set sectors as interface elements.
*/
void		ft_editor_init_sectors_areas(t_wolf3d *w, t_list *sector)
{
	if (sector)
	{
		ft_editor_init_sectors_areas(w, sector->next);
		ft_editor_init_sectors_item_area(w, (t_sector*)sector->content);
	}
}

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