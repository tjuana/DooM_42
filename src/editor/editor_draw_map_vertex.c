/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   editor_draw_map_vertex.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dorange- <dorange-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/25 21:54:19 by dorange-          #+#    #+#             */
/*   Updated: 2020/01/26 14:48:41 by dorange-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

/*
** **************************************************************************
**	void	ft_gui_draw_point(t_wolf3d *w, t_gui_coord c, int color)
**	
**	Function that draw point (vertex).
** **************************************************************************
*/

void	ft_gui_draw_point(t_wolf3d *w, t_gui_coord c, int color)
{
	int	v_d;

	v_d = w->gui_map.grid_scale / 8;
	if (v_d < 2)
		v_d = 2;
	ft_gui_fill_area(w, (t_gui_coord){c.x - v_d, c.y - v_d, 0}, \
		(t_gui_coord){c.x + v_d, c.y + v_d, 0}, color);
}

/*
** **************************************************************************
**	int		ft_gui_draw_map_vertex(t_wolf3d *w, t_gui_coord c, int status,
**				int mode)
**	
**	Function that draw map vertex.
** **************************************************************************
*/

int		ft_gui_draw_map_vertex(t_wolf3d *w, t_gui_coord c, int status, int mode)
{
	int	color;

	if (status == 1 && mode != GUI_MD_ME)
	{
		color = GUI_CL_STANDART;
		if (mode == GUI_MD_ME_SET_SECTOR)
			color = GUI_CL_SECTOR;
		if (mode == GUI_MD_ME_SET_PLAYER)
			color = GUI_CL_PLAYER;
		if (mode == GUI_MD_ME_SET_SPRITE)
			color = GUI_CL_SPRITE;
		if (mode == GUI_MD_ME_SET_ENEMY)
			color = GUI_CL_ENEMY;
		ft_gui_draw_point(w, c, color);
	}
	return (0);
}

/*
** **************************************************************************
**	int		ft_gui_draw_map_vertex_line(t_wolf3d *w, t_gui_coord c1)
**	
**	Function that draw map vertex special line.
** **************************************************************************
*/

int		ft_gui_draw_map_vertex_line(t_wolf3d *w, t_gui_coord c1)
{
	t_sector	*s;
	t_gui_coord	c2;

	if (w->gui.mode == GUI_MD_ME_SET_SECTOR && w->sector)
	{
		s = w->sector->content;
		if (s->status == 0 && s->vertex_count > 0 && ft_new_editor_map_check_area(w))
		{
			c2 = ft_gui_map_vertex_to_coord(w, *s->vertex[s->vertex_count - 1]);
			ft_fdf_wu_color(&(t_vector3){c1.x, c1.y, 0, 0}, &(t_vector3){c2.x, c2.y, 0, 0}, w, 0x888888);
		}
	}
	return (0);
}
