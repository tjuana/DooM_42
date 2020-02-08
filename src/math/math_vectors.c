/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   math_vectors.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjuana <tjuana@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/20 12:40:11 by dorange-          #+#    #+#             */
/*   Updated: 2020/02/08 14:17:16 by tjuana           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

/*
**	Check vertexes compare
**	
**	ft_editor_sector_compare_vertexes -> ft_compare_vertexes
*/
int		ft_compare_vertexes(t_vector3 v1, t_vector3 v2)
{
	if ((int)v1.x == (int)v2.x && \
		(int)v1.y == (int)v2.y && \
		(int)v1.z == (int)v2.z && \
		(int)v1.w == (int)v2.w)
		return (1);
	return (0);
}

/*
**	[!]
**	vxs: Vector cross product
**	
**	Need to add for vector library
*/
double		ft_vxs_vector(t_vector3 v1, t_vector3 v2)
{
	return (v1.x * v2.y - v2.x * v1.y);
}

double		ft_vxs_double(double x1, double y1, double x2, double y2)
{
	return (x1 * y2 - x2 * y1);
}

int			ft_check_div_vector(t_vector3 v1, t_vector3 v2, t_vector3 v3, t_vector3 v4)
{
	double		d;

	d = ft_vxs_double(v1.x - v2.x, v1.y - v2.y, v3.x - v4.x, v3.y - v4.y);
	if (d == 0.0)
		return (0);
	return 1;
}

int			ft_check_div(double x1, double y1, double x2, double y2,double x3, double y3, double x4, double y4)
{
	double		d;

	d = ft_math_vxs((x1)-(x2), (y1)-(y2), (x3)-(x4), (y3)-(y4));
	if (d == 0.0)
		return (0);
	return 1;
}

int			ft_check_point(t_vector3 p, t_vector3 p1, t_vector3 p2, t_vector3 p1_pl, t_vector3 p2_pl)
{
	// Определяем, в верном ли направлении лежит точка
	double l1;
	double l2;

	l1 = sqrt(pow((p.x - p1_pl.x), 2) + pow((p.y - p1_pl.y), 2));
	l2 = sqrt(pow((p.x - p2_pl.x), 2) + pow((p.y - p2_pl.y), 2));

	if (l1 < l2 && l2 - l1 > 0.999999)
		return (0);

	// Определить, лежит ли точка на отрезке
	if (ft_check_point_in_line_segment(p, p1, p2))
		return (1);
	return (0);
}

/*
 * vxs: Vector cross product
 */
double		ft_math_vxs(double x0, double y0, double x1, double y1)
{
	return ((x0)*(y1) - (x1)*(y0));
}

t_vector3		ft_find_intersect(double x1, double y1, double x2, double y2,double x3, double y3, double x4, double y4)
{
	t_vector3		xy;
	double		d;

	d = ft_math_vxs((x1)-(x2), (y1)-(y2), (x3)-(x4), (y3)-(y4));
	xy.x = ft_math_vxs(ft_math_vxs(x1,y1, x2,y2), (x1)-(x2), ft_math_vxs(x3,y3, x4,y4), (x3)-(x4)) / d;
	xy.y = ft_math_vxs(ft_math_vxs(x1,y1, x2,y2), (y1)-(y2), ft_math_vxs(x3,y3, x4,y4), (y3)-(y4)) / d;
	return (xy);
}