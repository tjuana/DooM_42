/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_math_functions2.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dorange- <dorange-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/15 17:34:04 by nshelly           #+#    #+#             */
/*   Updated: 2020/02/16 13:00:17 by dorange-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

/*
** intersectbox: Determine whether two 2D-boxes intersect.
*/

int			intersectbox(t_new_xy v0, t_new_xy v1, t_new_xy v2, t_new_xy v3)
{
	return (overlap(v0.x, v1.x, v2.x, v3.x) && overlap(v0.y, v1.y, v2.y, v3.y));
}

/*
** pointside: Determine which side of a line the point is on.
** Return value: <0, =0 or >0.
*/

float		pointside(t_new_xy p, t_new_xy v0, t_new_xy v1)
{
	return (vxs((v1.x) - (v0.x), (v1.y) - (v0.y), \
	(p.x) - (v0.x), (p.y) - (v0.y)));
}

/*
** Intersect: Calculate the point of intersection between two lines.
*/

t_new_xy	intersect(t_new_xy v1, t_new_xy v2, t_new_xy v3, t_new_xy v4)
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
		return ((t_new_xy){(v1.x + v2.x) / 2, (v1.y + v2.y) / 2});
	if (ABS(denom) < FLT_EPSILON)
		return ((t_new_xy){-1, -1});
	u_x = num_x / denom;
	u_y = num_y / denom;
	if (u_x < 0 || u_x > 1 || u_y < 0 || u_y > 1)
		return ((t_new_xy){ -1, -1});
	return ((t_new_xy){v1.x + u_x * (v2.x - v1.x), v1.y + u_x * (v2.y - v1.y)});
}

float		yaw(float y, float z, t_new_player *player)
{
	return (y + z * player->yaw);
}

float		to_deg(float radians)
{
	return (radians * (180.0 / M_PI));
}
