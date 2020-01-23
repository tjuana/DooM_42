/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vectors_3.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: drafe <drafe@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/23 19:20:46 by drafe             #+#    #+#             */
/*   Updated: 2020/01/23 19:21:23 by drafe            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

/*
** **************************************************************************
**	float vec2_cos(t_vector3 vec1, t_vector3 vec2)
**	Function to define cos of two vec
** **************************************************************************
*/

float	vec2_cos(t_vector3 vec1, t_vector3 vec2)
{
	float	res;
	float	tmp1;
	float	tmp2;

	tmp1 = sqrt(pow(vec1.x, 2) + pow(vec1.y, 2));
	tmp2 = sqrt(pow(vec2.x, 2) + pow(vec2.y, 2));
	res = (vec1.x * vec2.x + vec1.y * vec2.y);
	res = res / (tmp1 * tmp2);
	return (res);
}