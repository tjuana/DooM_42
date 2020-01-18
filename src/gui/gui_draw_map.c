/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gui_draw_map.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dorange- <dorange-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/16 17:33:46 by dorange-          #+#    #+#             */
/*   Updated: 2020/01/18 20:39:46 by dorange-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

/*
**	T	|	top
**	B	|	bottom
**	L	|	left
**	R	|	right
*/

#define GUI_MAP_GRID_LIMIT_TL	0x1
#define GUI_MAP_GRID_LIMIT_TR	0x2
#define GUI_MAP_GRID_LIMIT_BL	0x3
#define GUI_MAP_GRID_LIMIT_BR	0x4

void	ft_gui_draw_map_grid_limit_sector(t_wolf3d *w, t_gui_rect rect, \
	t_vector3 v, int type)
{
	t_ui_coord	pos;

	pos = ft_gui_map_vertex_to_coord(w, rect, v);
	if (type == GUI_MAP_GRID_LIMIT_TL || type == GUI_MAP_GRID_LIMIT_TR)
		ft_gui_fill_area(w, (t_ui_coord){rect.v1.x, rect.v1.y, 0}, \
			(t_ui_coord){rect.v2.x, pos.y, 0}, 0x222222);
	else
		ft_gui_fill_area(w, (t_ui_coord){rect.v1.x, pos.y, 0}, \
			(t_ui_coord){rect.v2.x, rect.v2.y, 0}, 0x222222);
	if (type == GUI_MAP_GRID_LIMIT_TL || type == GUI_MAP_GRID_LIMIT_BL)
		ft_gui_fill_area(w, (t_ui_coord){rect.v1.x, rect.v1.y, 0}, \
				(t_ui_coord){pos.x, rect.v2.y, 0}, 0x222222);
	else
		ft_gui_fill_area(w, (t_ui_coord){pos.x, rect.v1.y, 0}, \
			(t_ui_coord){rect.v2.x, rect.v2.y, 0}, 0x222222);
}

/*
**	void ft_gui_draw_map(t_wolf3d *w, t_list *list)
**	
**	Function that draw limit line for map grid.
*/
void	ft_gui_draw_map_grid_limit_line(t_wolf3d *w, t_gui_rect rect, t_vector3 v, int scale)
{
	t_ui_coord	pos;

	pos = ft_gui_map_vertex_to_coord(w, rect, v);
	ft_fdf_wu_color(
		&(t_vector3){rect.v1.x, pos.y, 0, 0}, \
		&(t_vector3){rect.v2.x, pos.y, 0, 0}, \
		w, 0x888888 \
	);
	ft_fdf_wu_color(
		&(t_vector3){pos.x, rect.v1.y, 0, 0}, \
		&(t_vector3){pos.x, rect.v2.y, 0, 0}, \
		w, 0x888888 \
	);
}

/*
**	void ft_gui_draw_map(t_wolf3d *w, t_list *list)
**	
**	Function that draw map grid.
*/
void	ft_gui_draw_map_grid(t_wolf3d *w, t_gui_rect rect, int scale)
{
	t_ui_coord	pos;

	pos = ft_gui_map_vertex_to_coord(w, rect, \
		(t_vector3){floor(w->gui_map.v.x), floor(w->gui_map.v.y), 0, 0});
	while (pos.y < rect.v2.y)
	{
		ft_fdf_wu_color(
			&(t_vector3){rect.v1.x, pos.y, 0, 0}, \
			&(t_vector3){rect.v2.x, pos.y, 0, 0}, \
			w, 0x333333 \
		);
		pos.y += w->gui_map.grid_scale;
	}
	while (pos.x < rect.v2.x)
	{
		ft_fdf_wu_color(
			&(t_vector3){pos.x, rect.v1.y, 0, 0}, \
			&(t_vector3){pos.x, rect.v2.y, 0, 0}, \
			w, 0x333333 \
		);
		pos.x += w->gui_map.grid_scale;
	}
}

int		ft_gui_draw_map_vertex(t_wolf3d *w, t_ui_coord c, int status)
{
	int	v_d;
	int	color;

	v_d = w->gui_map.grid_scale / 8;
	if (v_d < 2)
		v_d = 2;
	if (status == 1 && w->gui.mode != GUI_MD_ME)
	{
		color = GUI_CL_STANDART;
		if (w->gui.mode == GUI_MD_ME_SET_SECTOR)
			color = GUI_CL_SECTOR;
		if (w->gui.mode == GUI_MD_ME_SET_PLAYER)
			color = GUI_CL_PLAYER;
		if (w->gui.mode == GUI_MD_ME_SET_SPRITE)
			color = GUI_CL_SPRITE;
		if (w->gui.mode == GUI_MD_ME_SET_ENEMY)
			color = GUI_CL_ENEMY;
		ft_gui_fill_area(w, (t_ui_coord){c.x - v_d, c.y - v_d, 0}, \
			(t_ui_coord){c.x + v_d, c.y + v_d, 0}, color);

	}
	return (0);
}

// function that draw line
int		ft_gui_draw_map_vertex_line(t_wolf3d *w, t_ui_coord c1)
{
	t_sector	*s;
	t_ui_coord	c2;

	if (w->gui.mode == GUI_MD_ME_SET_SECTOR && w->sector)
	{
		s = w->sector->content;
		if (s->status == 0 && ft_new_editor_map_check_area(w))
		{
			c2 = ft_gui_map_vertex_to_coord(w, (t_gui_rect){0, 0, 0, 0}, *s->vertex[s->vertex_count - 1]);
			ft_fdf_wu_color(&(t_vector3){c1.x, c1.y, 0, 0}, &(t_vector3){c2.x, c2.y, 0, 0}, w, 0x888888);
		}
	}
	return (0);
}

/*
	void ft_editor_map_draw_walls(t_wolf3d *w, t_sector *ptr_sector)

	Draw walls on the map.
*/
void		ft_gui_draw_map_sector_walls(t_wolf3d *w, t_sector *ptr_sector)
{
	int				i;
	t_ui_coord		c1;
	t_ui_coord		c2;
	int				vtx1_n; // vertex number
	int				vtx2_n;

	i = 0;
	if (ptr_sector->status == 0)
		ptr_sector->color = 0x7b68ee;
	else
		ptr_sector->color = 0xf8f32b;
	while (i < ptr_sector->vertex_count)
	{
		vtx1_n = i;
		vtx2_n = i + 1;
		if (vtx2_n == ptr_sector->vertex_count)
		{
			if (ptr_sector->status == 1)
				vtx2_n = 0;
			else
				break ;
		}

		// Get line coordinates  
		c1 = ft_gui_map_vertex_to_coord(w, (t_gui_rect){0, 0, 0, 0}, *ptr_sector->vertex[vtx1_n]);
		c2 = ft_gui_map_vertex_to_coord(w, (t_gui_rect){0, 0, 0, 0}, *ptr_sector->vertex[vtx2_n]);

		// if (ft_editor_check_line_for_map(c1, c2)) -> all TRUE
		ft_fdf_wu_color(&(t_vector3){c1.x, c1.y, 0, 0}, &(t_vector3){c2.x, c2.y, 0, 0}, w, ptr_sector->color);

		i++;
	}

	i = 0;
	while (i < ptr_sector->vertex_count)
	{
		c1 = ft_gui_map_vertex_to_coord(w, (t_gui_rect){0, 0, 0, 0}, *ptr_sector->vertex[i]);
		// ft_editor_draw_point(w, c1, ptr_sector->color);
		ft_gui_draw_map_vertex(w, c1, 1);
		i++;
	}
}

void	ft_gui_draw_map_sector(t_wolf3d *w, t_list *list)
{
	if (list)
	{
		ft_gui_draw_map_sector(w, list->next);
		ft_gui_draw_map_sector_walls(w, (t_sector*)list->content);
	}
}

/*
**	void ft_gui_draw_map(t_wolf3d *w, t_list *list)
**	
**	Function that draw map.
*/
void	ft_gui_draw_map(t_wolf3d *w, t_list *list)
{
	t_gui_elem	*elem;

	elem = list->content;
	ft_gui_draw_map_grid_limit_sector(w, (t_gui_rect){elem->v1, elem->v2, elem->w, \
		elem->h}, (t_vector3){0, 0, 0, 0}, GUI_MAP_GRID_LIMIT_TL);
	ft_gui_draw_map_grid(w, (t_gui_rect){elem->v1, elem->v2, elem->w, \
		elem->h}, w->gui_map.grid_scale);
	ft_gui_draw_map_grid_limit_line(w, (t_gui_rect){elem->v1, elem->v2, elem->w, \
		elem->h}, (t_vector3){0, 0, 0, 0}, w->gui_map.grid_scale);
	w->gui_map.check_vertex = ft_gui_draw_map_vertex(w, w->gui.mouse_pos, \
		w->gui_map.check_vertex);
	ft_gui_draw_map_vertex_line(w, w->gui.mouse_pos);
	ft_gui_draw_map_sector(w, w->sector);
}