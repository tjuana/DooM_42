/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_math_functions.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjuana <nshelly@student.42.fr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/08 12:08:45 by nshelly           #+#    #+#             */
/*   Updated: 2020/02/13 17:54:21 by nshelly          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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

float		vxs(float x0, float y0, float x1, float y1)
{
	return ((x0) * (y1) - (x1) * (y0));
}

/*
** overlap:  Determine whether the two number ranges overlap.
*/

int			overlap(float a0, float a1, float b0, float b1)
{
	return (min(a0, a1) <= max(b0, b1) && min(b0, b1) <= max(a0, a1));
}
