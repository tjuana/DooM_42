/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   func_wu_init.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dorange- <dorange-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/08 19:23:13 by dorange-          #+#    #+#             */
/*   Updated: 2020/02/16 12:46:06 by dorange-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

void		ft_fdf_init_wu(t_fdf_wu **wu, t_vector3 *dot_1, t_vector3 *dot_2)
{
	(*wu) = ft_memalloc(sizeof(t_fdf_wu));
	ft_bzero(*wu, sizeof(t_fdf_wu));
	(*wu)->x1 = dot_1->x + 0;
	(*wu)->y1 = dot_1->y + 0;
	(*wu)->x2 = dot_2->x + 0;
	(*wu)->y2 = dot_2->y + 0;
	(*wu)->rx1 = 0;
	(*wu)->ry1 = 0;
	(*wu)->rx2 = WIN_WIDTH;
	(*wu)->ry2 = WIN_HEIGHT;
	(*wu)->color1 = 0xFFFF00;
}

void		ft_fdf_init_wu_color(t_fdf_wu **wu, t_vector3 *dot_1, \
				t_vector3 *dot_2, int color)
{
	(*wu) = ft_memalloc(sizeof(t_fdf_wu));
	ft_bzero(*wu, sizeof(t_fdf_wu));
	(*wu)->x1 = dot_1->x + 0;
	(*wu)->y1 = dot_1->y + 0;
	(*wu)->x2 = dot_2->x + 0;
	(*wu)->y2 = dot_2->y + 0;
	(*wu)->rx1 = 0;
	(*wu)->ry1 = 0;
	(*wu)->rx2 = WIN_WIDTH;
	(*wu)->ry2 = WIN_HEIGHT;
	(*wu)->color1 = color;
}

void		ft_fdf_init_wu_rect_color(t_fdf_wu **wu, t_gui_rect coord, \
				t_gui_rect area, int color)
{
	(*wu) = ft_memalloc(sizeof(t_fdf_wu));
	ft_bzero(*wu, sizeof(t_fdf_wu));
	(*wu)->x1 = coord.v1.x + 0;
	(*wu)->y1 = coord.v1.y + 0;
	(*wu)->x2 = coord.v2.x + 0;
	(*wu)->y2 = coord.v2.y + 0;
	(*wu)->rx1 = area.v1.x >= 0 ? area.v1.x : 0;
	(*wu)->ry1 = area.v1.y >= 0 ? area.v1.y : 0;
	(*wu)->rx2 = area.v2.x <= WIN_WIDTH ? area.v2.x : WIN_WIDTH;
	(*wu)->ry2 = area.v2.x <= WIN_HEIGHT ? area.v2.x : WIN_HEIGHT;
	(*wu)->color1 = color;
}
