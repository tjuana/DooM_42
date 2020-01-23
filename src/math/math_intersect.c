/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   math_intersect.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dorange- <dorange-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/20 12:40:11 by dorange-          #+#    #+#             */
/*   Updated: 2020/01/23 15:08:09 by dorange-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

/*
**	
**	
**	
*/
t_vector3	ft_find_line_intersect(t_vector3 v1, t_vector3 v2, \
				t_vector3 v3, t_vector3 v4)
{
	t_vector3	v;
	double		d;

	d = ft_vxs_double(v1.x - v2.x, v1.y - v2.y, v3.x - v4.x, v3.y - v4.y);
	v.x = ft_vxs_double(ft_vxs_double(v1.x, v1.y, v2.x, v2.y), v1.x - v2.x, \
		ft_vxs_double(v3.x, v3.y, v4.x, v4.y), v3.x - v4.x) / d;
	v.y = ft_vxs_double(ft_vxs_double(v1.x, v1.y, v2.x, v2.y), v1.y - v2.y, \
		ft_vxs_double(v3.x, v3.y, v4.x, v4.y), v3.y - v4.y) / d;
	return (v);
}

/*
**	int	 ft_check_line_segment_intersect_vector(t_vector3 v1, t_vector3 v2, \
**		t_vector3 v3, t_vector3 v4)
**	
**	
*/
int		ft_check_line_segment_intersect_vector(t_vector3 v1, t_vector3 v2, \
			t_vector3 v3, t_vector3 v4)
{
	t_vector3	p;

	// Если прямые параллельны, то они не пересекаются
	if (!ft_check_div_vector(v1, v2, v3, v4))
		return (0);
	
	// Находим точку пересечения
	p = ft_find_line_intersect(v1, v2, v3, v4);

	// Проверяем, лежит ли точка пересечения на отрезках
	if (
		ft_check_point_in_line_segment(p, v3, v4) &&
		ft_check_point_in_line_segment(p, v1, v2)
	)
		return (1);
	return (0);
}


// Проверяем, лежит ли точка на отрезке (?!)
int			ft_check_point_in_line_segment(t_vector3 p, t_vector3 p1, t_vector3 p2)
{
	double	d;
	int		p_d;

	d = (p.x - p1.x) * (p2.y - p1.y) - (p.y - p1.y) * (p2.x - p1.x);
	if (
		(p1.x < p.x && p.x < p2.x) || (p2.x < p.x && p.x < p1.x) ||
		(p1.y < p.y && p.y < p2.y) || (p2.y < p.y && p.y < p1.y)
	)
	{
		p_d = abs((int)(d * 100));
		if (p_d < 1)
			return (1);
		else
			return (0);
	}
	else
		return (0);
	return (0);
}

// Проверяем, лежит ли точка на отрезке в определённом диаметре
int			ft_check_point_in_line_segment_diameter(t_vector3 p, t_vector3 p1, t_vector3 p2, double diameter)
{
	double	d;

	d = (p.x - p1.x) * (p2.y - p1.y) - (p.y - p1.y) * (p2.x - p1.x);
	if (
		(p1.x < p.x && p.x < p2.x) || (p2.x < p.x && p.x < p1.x) ||
		(p1.y < p.y && p.y < p2.y) || (p2.y < p.y && p.y < p1.y)
	)
	{
		if ((fabs(d) - diameter) < 0)
		{
			// printf("%f  %f\n", d, diameter);
			return (1);
		}
		else
			return (0);
	}
	else
		return (0);
	return (0);
}

/*
** **************************************************************************
**	int		ft_check_general_segment_line(t_vector3 v1, t_vector3 v2,
**				t_vector3 v3, t_vector3 v4)
**
**	Function that check general segment line.
**
**	Arguments:
**	t_vector3 *v1, t_vector3 *v2	|	first segment coordinates
**	t_vector3 *v3, t_vector3 *v4	|	second segment coordinates
**
**	Return:
** **************************************************************************
*/

int		ft_check_general_segment_line(t_vector3 v1, t_vector3 v2, \
			t_vector3 v3, t_vector3 v4)
{
	return ((ft_compare_vertexes(v1, v3) && ft_compare_vertexes(v2, v4)) ||
			(ft_compare_vertexes(v1, v4) && ft_compare_vertexes(v2, v3)));
}