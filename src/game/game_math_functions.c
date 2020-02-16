/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_math_functions.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: drafe <drafe@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/08 12:08:45 by nshelly           #+#    #+#             */
/*   Updated: 2020/02/16 14:55:22 by drafe            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

/*
** min: Choose smaller of two scalars.
*/

float		min(float a, float b)
{
	return (((a) < (b)) ? (a) : (b));
}

/*
** max: Choose greater of two scalars.
*/

float		max(float a, float b)
{
	return (((a) > (b)) ? (a) : (b));
}

/*
** clamp: fijar los valores  eun rango establecido
*/

float		clamp(float a, float mi, float ma)
{
	return (min(max(a, mi), ma));
}

/*
** vxs: Vector cross product
*/

float		vxs(float x1, float y1, float x2, float y2)
{
	return ((x1) * (y2) - (x2) * (y1));
}

/*
** overlap:  Determine whether the two number ranges overlap.
*/

int			overlap(float a1, float a2, float b1, float b2)
{
	return (min(a1, a2) <= max(b1, b2) && min(b1, b2) <= max(a1, a2));
}
