/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gui_draw_map.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dorange- <dorange-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/16 17:33:46 by dorange-          #+#    #+#             */
/*   Updated: 2020/01/16 22:01:53 by dorange-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

/*
**	void ft_gui_draw_map(t_wolf3d *w, t_list *list)
**	
**	Function that draw limit line for map grid.
*/
void	ft_gui_draw_map_grid_limit_line(t_wolf3d *w, t_gui_rect rect, int scale)
{
	t_ui_coord	pos;

	pos = (t_ui_coord){0, 0, 0};
	pos.x -= w->gui_map.v.x * scale;
	pos.y -= w->gui_map.v.y * scale;
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

	pos = (t_ui_coord){
		(rect.v1.x + (w->gui_map.v.x - floor(w->gui_map.v.x)) * w->gui_map.grid_scale), 
		(rect.v1.y + (w->gui_map.v.y - floor(w->gui_map.v.y)) * w->gui_map.grid_scale), 0};

	while (pos.y < rect.v2.y)
	{
		ft_fdf_wu_color(
			&(t_vector3){rect.v1.x, pos.y, 0, 0}, \
			&(t_vector3){rect.v2.x, pos.y, 0, 0}, \
			w, 0x333333 \
		);
		pos.y += scale;
	}
	while (pos.x < rect.v2.x)
	{
		ft_fdf_wu_color(
			&(t_vector3){pos.x, rect.v1.y, 0, 0}, \
			&(t_vector3){pos.x, rect.v2.y, 0, 0}, \
			w, 0x333333 \
		);
		pos.x += scale;
	}
}

int		ft_gui_draw_map_vertex(t_wolf3d *w, t_ui_coord c, int status)
{
	int	v_d;

	v_d = w->gui_map.grid_scale / 8;
	if (v_d < 2)
		v_d = 2;
	if (status == 1)
	{
		ft_gui_fill_area(w, (t_ui_coord){c.x - v_d, c.y - v_d, 0}, \
			(t_ui_coord){c.x + v_d, c.y + v_d, 0}, 0xff0000);
		// printf("x:%d   y:%d\n", w->gui.mouse_pos.x, w->gui.mouse_pos.y);

		// ft_fdf_wu_color(
		// 	&(t_vector3){c.x - v_d, c.y - v_d, 0, 0}, \
		// 	&(t_vector3){c.x + v_d, c.y + v_d, 0, 0}, \
		// 	w, 0xff0000 \
		// );
		// ft_fdf_wu_color(
		// 	&(t_vector3){c.x + v_d, c.y - v_d, 0, 0}, \
		// 	&(t_vector3){c.x - v_d, c.y + v_d, 0, 0}, \
		// 	w, 0xff0000 \
		// );
	}
	return (0);
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
	ft_gui_draw_map_grid(w, (t_gui_rect){elem->v1, elem->v2, elem->w, \
		elem->h}, w->gui_map.grid_scale);
	ft_gui_draw_map_grid_limit_line(w, (t_gui_rect){elem->v1, elem->v2, elem->w, \
		elem->h}, w->gui_map.grid_scale);
	w->gui_map.check_vertex = ft_gui_draw_map_vertex(w, w->gui.mouse_pos, \
		w->gui_map.check_vertex);
}