/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   algebra_vectors_func.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dorange- <dorange-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/20 12:40:11 by dorange-          #+#    #+#             */
/*   Updated: 2020/02/14 15:40:30 by dorange-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

int		ft_compare_vertexes(t_vector3 v1, t_vector3 v2)
{
	if ((int)v1.x == (int)v2.x && \
		(int)v1.y == (int)v2.y && \
		(int)v1.z == (int)v2.z && \
		(int)v1.w == (int)v2.w)
		return (1);
	return (0);
}

double	ft_vxs_vector(t_vector3 v1, t_vector3 v2)
{
	return (v1.x * v2.y - v2.x * v1.y);
}

double	ft_vxs_double(double x1, double y1, double x2, double y2)
{
	return (x1 * y2 - x2 * y1);
}

int		ft_check_div_vector(t_vector3 v1, t_vector3 v2, \
			t_vector3 v3, t_vector3 v4)
{
	double	d;

	d = ft_vxs_double(v1.x - v2.x, v1.y - v2.y, v3.x - v4.x, v3.y - v4.y);
	if (d == 0.0)
		return (0);
	return (1);
}

double	ft_math_vxs(double x0, double y0, double x1, double y1)
{
	return ((x0) * (y1) - (x1) * (y0));
}
