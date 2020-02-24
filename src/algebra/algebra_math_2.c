/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   algebra_math_2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dorange- <dorange-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/15 17:34:04 by nshelly           #+#    #+#             */
/*   Updated: 2020/02/19 20:03:09 by dorange-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

/*
** **************************************************************************
**	int t_game_intersectbox(t_vector3 v1, t_vector3 v2, t_vector3 v3, t_vector3 v4)
**
**	ft_math_intersectbox: Determine whether two 2D-boxes intersect.
** **************************************************************************
*/

int			ft_math_intersectbox(t_vector3 v1, t_vector3 v2, t_vector3 v3, t_vector3 v4)
{
	return (ft_math_overlap(v1.x, v2.x, v3.x, v4.x) && ft_math_overlap(v1.y, v2.y, v3.y, v4.y));
}

/*
** **************************************************************************
**	float ft_math_min(float a, float b)
**
**	ft_math_pointside: Determine which side of a line the point is on.
**	Return value: <0, =0 or >0.
** **************************************************************************
*/

float		ft_math_pointside(t_vector3 p, t_vector3 v1, t_vector3 v2)
{
	return (ft_math_vxs((v2.x) - (v1.x), (v2.y) - (v1.y), \
	(p.x) - (v1.x), (p.y) - (v1.y)));
}

/*
** **************************************************************************
**	t_vector3	ft_math_intersect(t_vector3 v1, t_vector3 v2, t_vector3 v3, t_vector3 v4)
**
**	Intersect: Calculate the point of intersection between two lines.
** **************************************************************************
*/

t_vector3	ft_math_intersect(t_vector3 v1, t_vector3 v2, t_vector3 v3, t_vector3 v4)
{
	float		u_x;
	float		u_y;
	float		denom;
	float		num_x;
	float		num_y;

	denom = (v4.y - v3.y) * (v2.x - v1.x) - (v4.x - v3.x) * (v2.y - v1.y);
	num_x = (v4.x - v3.x) * (v1.y - v3.y) - (v4.y - v3.y) * (v1.x - v3.x);
	num_y = (v2.x - v1.x) * (v1.y - v3.y) - (v2.y - v1.y) * (v1.x - v3.x);
	if (fabs(num_x) < FLT_EPSILON && fabs(num_y) < \
	FLT_EPSILON && fabs(denom) < FLT_EPSILON)
		return ((t_vector3){(v1.x + v2.x) / 2, (v1.y + v2.y) / 2, 0, 0});
	if (ABS(denom) < FLT_EPSILON)
		return ((t_vector3){-1, -1, 0, 0});
	u_x = num_x / denom;
	u_y = num_y / denom;
	if (u_x < 0 || u_x > 1 || u_y < 0 || u_y > 1)
		return ((t_vector3){ -1, -1, 0, 0});
	return ((t_vector3){v1.x + u_x * (v2.x - v1.x), v1.y + u_x * (v2.y - v1.y), 0, 0});
}

/*
** **************************************************************************
**	float ft_math_yaw(float y, float z, float yaw)
** **************************************************************************
*/

float		ft_math_yaw(float y, float z, float yaw)
{
	return (y + z * yaw);
}

/*
** **************************************************************************
**	float ft_math_to_deg(float radians)
** **************************************************************************
*/

float		ft_math_to_deg(float radians)
{
	return (radians * (180 / M_PI));
}
