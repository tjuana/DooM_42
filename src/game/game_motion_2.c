/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_motion_2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: drafe <drafe@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/25 18:20:12 by drafe             #+#    #+#             */
/*   Updated: 2020/02/08 20:44:17 by drafe            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

static float	motion_dist_to_pt(t_new_vector3 *pt, t_new_vector3 *line_start, \
t_new_vector3 *line_end)
{
	float			line_len;
	float			coef;
	t_new_vector3	tmp;

	tmp = ft_new_vec3_sub(*line_start, *line_end);
	line_len = ft_new_vec3_magnitude(tmp);
	coef = ((pt->x - line_start->x) * (line_end->x - line_start->x) + \
	(pt->y - line_start->y) * (line_end->y - line_start->y) + \
	(pt->z - line_start->z) * (line_end->z - line_start->z)) / \
	(line_len * line_len);
	if (coef < 0 || coef > 1)
		return (-1);
	tmp.x = line_start->x + coef * (line_end->x - line_start->x);
	tmp.y = line_start->y + coef * (line_end->y - line_start->y);
	tmp.z = line_start->z + coef * (line_end->z - line_start->z);
	tmp = ft_new_vec3_sub(tmp, *pt);
	return (ft_new_vec3_magnitude(tmp));
}
/*
	float Magnitude( XYZ *LineEnd, XYZ *LineStart )
    Vector.X = LineStart->X - LineEnd->X;
	
   float LineMag;
    float U;
    XYZ Intersection;
 
    LineMag = Magnitude( LineEnd, LineStart );
 
    U = ( ( ( Point->X - LineStart->X ) * ( LineEnd->X - LineStart->X ) ) +
        ( ( Point->Y - LineStart->Y ) * ( LineEnd->Y - LineStart->Y ) ) +
        ( ( Point->Z - LineStart->Z ) * ( LineEnd->Z - LineStart->Z ) ) ) /
        ( LineMag * LineMag );
 
    if( U < 0.0f || U > 1.0f )
        return 0;   // closest point does not fall within the line segment
 
    Intersection.X = LineStart->X + U * ( LineEnd->X - LineStart->X );
    Intersection.Y = LineStart->Y + U * ( LineEnd->Y - LineStart->Y );
    Intersection.Z = LineStart->Z + U * ( LineEnd->Z - LineStart->Z );
 
    *Distance = Magnitude( Point, &Intersection );
 Vector.X = Intersection->X - Point->X;


    return 1;

*/

/*
** **************************************************************************
**	int motion_dist(t_new_xy *dist, t_new_player *pl, int i)
**	Function to manage degree wall and player
** **************************************************************************
*/

int				motion_dist(t_new_xy *dist, t_new_player *pl, int i)
{
	t_new_vector3	vec;
	t_new_vector3	vec2;
	float			deg;
	float			tmp_dist;

	dist->x = 0;
	vec.x = pl->sectors[pl->sector].vertex[i + 1].x - pl->sectors[pl->sector].vertex[i].x;
	vec.y = pl->sectors[pl->sector].vertex[i + 1].y - pl->sectors[pl->sector].vertex[i].y;
	vec.x = vec.x - pl->where.x;
	vec.y = vec.y - pl->where.y;
	tmp_dist = sqrt(pow(vec.x, 2) + pow(vec.y, 2));
	vec2.x = pl->anglecos;
	vec2.y = pl->anglesin;
	vec = ft_new_vec3_normalize(vec);
	vec2 = ft_new_vec3_normalize(vec2);
	deg = to_deg(acos(vec2_cos(vec, vec2)));

	vec.x = pl->sectors[pl->sector].vertex[i].x;
	vec.y = pl->sectors[pl->sector].vertex[i].y;
	vec.z = pl->where.z;
	vec2.x = pl->sectors[pl->sector].vertex[i + 1].x;
	vec2.y = pl->sectors[pl->sector].vertex[i + 1].y;
	vec2.z = pl->where.z;
	/*if (i == pl->sectors[pl->sector].npoints)
	{
		vec2.x = pl->sectors[pl->sector].vertex[0].x;
		vec2.y = pl->sectors[pl->sector].vertex[0].y;
	}
	else
	{
		vec2.x = pl->sectors[pl->sector].vertex[i + 1].x;
		vec2.y = pl->sectors[pl->sector].vertex[i + 1].y;
	}*/
	dist->x *= 1.1;
	dist->y *= 1.1;
	tmp_dist = motion_dist_to_pt(&(t_new_vector3)\
	{pl->where.x + dist->x, pl->where.y + dist->y, pl->where.z}, &vec, &vec2);
	printf("s==%d tmp_dist==%f deg==%f", i, tmp_dist, deg);
	if (tmp_dist != -1 && tmp_dist < 0.38 && pl->sectors[pl->sector].neighbors[i] < 0)
	{
				pl->velocity.x = 0;
		pl->velocity.y = 0;
		return (0);
		printf("ok \n");
	}
	else
		printf("\n");
/*	if (tmp_dist != -1 && tmp_dist < 1)
	{
		return (0);
	}
	
	if (tmp_dist != -1 && (tmp_dist < 1.5 || (deg < 93 && deg > 87)))
	{
		pl->angle *= 1.1;
		pl->anglesin = sinf(pl->angle);
		pl->anglecos = cosf(pl->angle);
		pl->velocity.x = 0;
		pl->velocity.y = 0;
		return (1);
	}

	if (tmp_dist != -1 && tmp_dist < pl->w_dist)
	{
		pl->w_dist = tmp_dist;
		pl->velocity.x = 0;
		pl->velocity.y = 0;
	}
	
	if (pl->sectors[pl->sector].neighbors[i] < 0)
	{
		printf("tmp_dist==%f deg==%f\n", tmp_dist, deg);
	}*/

	return (1);
}
