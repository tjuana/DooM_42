/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_color.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjuana <tjuana@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/14 18:20:00 by dorange-          #+#    #+#             */
/*   Updated: 2020/02/16 19:55:56 by tjuana           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

/*
** **************************************************************************
**	int ft_rgb_to_hex(int r, int g, int b)
**
**	Function that return hex color.
**
**	Arguments:
**	int r	| red channel
**	int g	| green channel
**	int b	| blue channel
** **************************************************************************
*/

int		ft_rgb_to_hex(int r, int g, int b)
{
	return ((r << 16) | (g << 8) | b);
}

int		ft_color_struct_to_hex(t_new_color color)
{
	return (ft_rgb_to_hex(color.r, color.g, color.b));
}

int		ft_hex_transform(int color, float percent)
{
	t_new_color	rgb;

	rgb.a = (color >> 24) & 0xFF * 0;
	rgb.r = ((color >> 16) & 0xFF) * percent;
	rgb.g = ((color >> 8) & 0xFF) * percent;
	rgb.b = ((color >> 0) & 0xFF) * percent;
	color = ((rgb.a << 24) | (rgb.r << 16) | (rgb.g << 8) | rgb.b << 0);
	return (color);
}
