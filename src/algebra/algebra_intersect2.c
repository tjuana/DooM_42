/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   algebra_intersect2.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjuana <tjuana@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/20 12:40:11 by dorange-          #+#    #+#             */
/*   Updated: 2020/02/21 14:23:12 by tjuana           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

int			ft_check_point_in_line_segment_diameter(t_vector3 p, t_vector3 p1, \
				t_vector3 p2, double diameter)
{
	double	d;

	d = (p.x - p1.x) * (p2.y - p1.y) - (p.y - p1.y) * (p2.x - p1.x);
	if (\
		(p1.x < p.x && p.x < p2.x) || (p2.x < p.x && p.x < p1.x) ||
		(p1.y < p.y && p.y < p2.y) || (p2.y < p.y && p.y < p1.y))
	{
		if ((fabs(d) - diameter) < 0)
			return (1);
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

int			ft_check_general_segment_line(t_vector3 v1, t_vector3 v2, \
				t_vector3 v3, t_vector3 v4)
{
	return ((ft_compare_vertexes(v1, v3) && ft_compare_vertexes(v2, v4)) ||
			(ft_compare_vertexes(v1, v4) && ft_compare_vertexes(v2, v3)));
}
