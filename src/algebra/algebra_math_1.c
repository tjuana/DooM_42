/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   algebra_math_1.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjuana <tjuana@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/08 12:08:45 by nshelly           #+#    #+#             */
/*   Updated: 2020/02/21 14:20:07 by tjuana           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

/*
** **************************************************************************
**	float ft_math_min(float a, float b)
**
**	min: Choose smaller of two scalars.
** **************************************************************************
*/

float		ft_math_min(float a, float b)
{
	return (((a) < (b)) ? (a) : (b));
}

/*
** **************************************************************************
**	float ft_math_max(float a, float b)
**
**	max: Choose greater of two scalars.
** **************************************************************************
*/

float		ft_math_max(float a, float b)
{
	return (((a) > (b)) ? (a) : (b));
}

/*
** **************************************************************************
**	float		ft_math_clamp(float a, float mi, float ma)
**
**	clamp: fijar los valores  eun rango establecido
** **************************************************************************
*/

float		ft_math_clamp(float a, float mi, float ma)
{
	return (ft_math_min(ft_math_max(a, mi), ma));
}

/*
** **************************************************************************
**	int ft_math_overlap(float a1, float a2, float b1, float b2)
**
**	overlap:  Determine whether the two number ranges overlap.
** **************************************************************************
*/

int			ft_math_overlap(float a1, float a2, float b1, float b2)
{
	return (ft_math_min(a1, a2) <= ft_math_max(b1, b2) && \
					ft_math_min(b1, b2) <= ft_math_max(a1, a2));
}
