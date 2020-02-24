/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   algebra_intersect.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjuana <tjuana@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/20 12:40:11 by dorange-          #+#    #+#             */
/*   Updated: 2020/02/21 14:23:30 by tjuana           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

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
** **************************************************************************
**	int ft_check_line_segment_intersect_vector(t_vector3 v1, \
**		t_vector3 v2, t_vector3 v3, t_vector3 v4)
**
**	Function that check line segment intersect.
** **************************************************************************
*/

int			ft_check_line_segment_intersect_vector(t_vector3 v1, \
				t_vector3 v2, t_vector3 v3, t_vector3 v4)
{
	t_vector3	p;

	if (!ft_check_div_vector(v1, v2, v3, v4))
		return (0);
	p = ft_find_line_intersect(v1, v2, v3, v4);
	if (ft_check_point_in_line_segment(p, v3, v4) &&
		ft_check_point_in_line_segment(p, v1, v2))
		return (1);
	return (0);
}

/*
** **************************************************************************
**	int ft_check_intersect_line_and_line_segment(t_vector3 v1, \
**		t_vector3 v2, t_vector3 v3, t_vector3 v4)
**
**	Function that check intersect between line and line segment
**
**	Arguments:
**	v1, v2	| line segment vertexes
**	p1, p2	| line points
**
**	Return:
**	0		| if line and line segment don't intersect
**	1		| if line and line segment intersect
**	2		| if line segment line vertex lies in the line
** **************************************************************************
*/

int			ft_check_intersect_line_and_line_segment(t_vector3 v1, \
				t_vector3 v2, t_vector3 p1, t_vector3 p2)
{
	t_vector3	p;

	if (!ft_check_div_vector(v1, v2, p1, p2))
		return (0);
	p = ft_find_line_intersect(v1, v2, p1, p2);
	if (ft_check_point_in_line_segment(p, v1, v2))
	{
		if (ft_check_point_in_line(v2, p1, p2))
			return (2);
		return (1);
	}
	return (0);
}

/*
** **************************************************************************
**	int ft_check_point_in_line(t_vector3 p, t_vector3 p1, t_vector3 p2)
**
**	Function that check point in the line.
** **************************************************************************
*/

int			ft_check_point_in_line(t_vector3 p, t_vector3 p1, t_vector3 p2)
{
	double	d;
	int		p_d;

	d = (p.x - p1.x) * (p2.y - p1.y) - (p.y - p1.y) * (p2.x - p1.x);
	p_d = abs((int)(d * 100));
	if (p_d < 1)
		return (1);
	else
		return (0);
	return (0);
}

/*
** **************************************************************************
**	int ft_check_point_in_line_segment(t_vector3 p, \
**		t_vector3 p1, t_vector3 p2)
**
**	Function that check point in the line segment.
** **************************************************************************
*/

int			ft_check_point_in_line_segment(t_vector3 p, \
				t_vector3 p1, t_vector3 p2)
{
	double	d;
	int		p_d;

	d = (p.x - p1.x) * (p2.y - p1.y) - (p.y - p1.y) * (p2.x - p1.x);
	if (\
		(p1.x < p.x && p.x < p2.x) || (p2.x < p.x && p.x < p1.x) ||
		(p1.y < p.y && p.y < p2.y) || (p2.y < p.y && p.y < p1.y))
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
