/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   algebra_matrix_2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dorange- <dorange-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/21 20:55:10 by dorange-          #+#    #+#             */
/*   Updated: 2020/02/21 21:01:30 by dorange-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

double	ft_math_deg_to_rad(double angle_degrees)
{
	return ((angle_degrees) * M_PI / 180.0);
}

double	ft_math_rad_to_deg(double angle_radians)
{
	return ((angle_radians) * 180.0 / M_PI);
}
