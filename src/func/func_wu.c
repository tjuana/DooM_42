/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   func_wu.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dorange- <dorange-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/14 16:50:24 by dorange-          #+#    #+#             */
/*   Updated: 2020/02/16 19:15:40 by dorange-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

void		ft_fdf_swap_double(double *n1, double *n2)
{
	double		p;

	p = *n1;
	*n1 = *n2;
	*n2 = p;
}

void		ft_fdf_wu(t_vector3 *dot_1, t_vector3 *dot_2, t_wolf3d *data)
{
	t_fdf_wu	*wu;
	double		x;

	ft_fdf_init_wu(&wu, dot_1, dot_2);
	wu->steep = fabs(wu->y2 - wu->y1) > fabs(wu->x2 - wu->x1);
	ft_fdf_draw_line_swap(&wu);
	ft_fdf_draw_line_param(data, &wu);
	x = wu->xpxl1 + 1;
	wu->steps = wu->xpxl2 - x;
	wu->step = 0;
	if (wu->steep)
		ft_fdf_wu_cycle_y(data, wu, x);
	else
		ft_fdf_wu_cycle_x(data, wu, x);
	free(wu);
}

void		ft_fdf_wu_color(t_vector3 *dot_1, t_vector3 *dot_2, \
				t_wolf3d *data, int color)
{
	t_fdf_wu	*wu;
	double		x;

	ft_fdf_init_wu_color(&wu, dot_1, dot_2, color);
	wu->steep = fabs(wu->y2 - wu->y1) > fabs(wu->x2 - wu->x1);
	ft_fdf_draw_line_swap(&wu);
	ft_fdf_draw_line_param(data, &wu);
	x = wu->xpxl1 + 1;
	wu->steps = wu->xpxl2 - x;
	wu->step = 0;
	if (wu->steep)
		ft_fdf_wu_cycle_y(data, wu, x);
	else
		ft_fdf_wu_cycle_x(data, wu, x);
	free(wu);
}

void		ft_fdf_wu_rect_color(t_wolf3d *data, t_gui_rect coord, \
				t_gui_rect area, int color)
{
	t_fdf_wu	*wu;
	double		x;

	ft_fdf_init_wu_rect_color(&wu, coord, area, color);
	wu->steep = fabs(wu->y2 - wu->y1) > fabs(wu->x2 - wu->x1);
	ft_fdf_draw_line_swap(&wu);
	ft_fdf_draw_line_param(data, &wu);
	x = wu->xpxl1 + 1;
	wu->steps = wu->xpxl2 - x;
	wu->step = 0;
	if (wu->steep)
		ft_fdf_wu_cycle_y(data, wu, x);
	else
		ft_fdf_wu_cycle_x(data, wu, x);
	free(wu);
}
