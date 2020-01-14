/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dorange- <dorange-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/12 12:07:54 by dorange-          #+#    #+#             */
/*   Updated: 2020/01/14 14:40:58 by dorange-         ###   ########.fr       */
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

void		ft_editor_init_ui_child_elem(t_ui_elem *child, t_ui_elem *parent)
{
	child->parent = parent;
	child->pos.top = child->v1.y - parent->v1.y;
	child->pos.bottom = parent->v2.y - child->v2.y;
	child->pos.left = child->v1.x - parent->v1.x;
	child->pos.right = parent->v2.x - child->v2.x;
}

void		ft_editor_init_ui_elem_reset(t_ui_elem *child, t_ui_elem *parent)
{
	child->v1.x = parent->v1.x + child->pos.left;
	child->v1.y = parent->v1.y + child->pos.top;
	child->v2.x = parent->v2.x - child->pos.right;
	child->v2.y = parent->v2.y - child->pos.bottom;
}

void		ft_editor_init_ui_elem(t_ui_elem *elem, t_ui_coord v1, t_ui_coord v2, int status)
{
	if (elem == NULL)
		return ;
	elem->v1 = v1;
	elem->v2 = v2;
	elem->w = elem->v2.x - elem->v1.x;
	elem->h = elem->v2.y - elem->v1.y;
	elem->status = status;
	elem->trigger = 0;
	elem->parent = NULL;
	elem->pos.top = 0;
	elem->pos.bottom = 0;
	elem->pos.left = 0;
	elem->pos.right = 0;
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
	w->txtr_opt_type = 1;

	ft_editor_init_ui_elem(&w->ui_map, (t_ui_coord){20, 20, 0}, (t_ui_coord){1720, 1060, 0}, 1);
	ft_editor_init_ui_elem(&w->ui_act_s, (t_ui_coord){1740, 20, 0}, (t_ui_coord){1900, 180, 0}, 1);
	ft_editor_init_ui_elem(&w->ui_act_s_floor, (t_ui_coord){1740, 150, 0}, (t_ui_coord){1900, 180, 0}, 1);
	ft_editor_init_ui_elem(&w->ui_act_s_wall, (t_ui_coord){1740, 50, 0}, (t_ui_coord){1900, 150, 0}, 1);
	ft_editor_init_ui_elem(&w->ui_act_s_ceil, (t_ui_coord){1740, 20, 0}, (t_ui_coord){1900, 50, 0}, 1);
	ft_editor_init_ui_elem(&w->ui_txtr_opt, (t_ui_coord){1430, 20, 0}, (t_ui_coord){1730, 220, 0}, 0);
	ft_editor_init_ui_elem(&w->ui_txtr_opt_close, (t_ui_coord){1709, 20, 0}, (t_ui_coord){1725, 36, 0}, 0);
	ft_editor_init_ui_child_elem(&w->ui_txtr_opt_close, &w->ui_txtr_opt);

	// me_menu
	ft_editor_init_ui_elem(&w->ui_me_menu, (t_ui_coord){1740, 20, 0}, (t_ui_coord){1900, 1060, 0}, 1);

	w->act_s = NULL;
}