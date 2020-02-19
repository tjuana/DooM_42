/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   func_color.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dorange- <dorange-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/14 18:20:00 by dorange-          #+#    #+#             */
/*   Updated: 2020/02/19 17:44:01 by dorange-         ###   ########.fr       */
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

Uint32		ft_rgb_to_hex(Uint32 r, Uint32 g, Uint32 b)
{
	return ((r << 16) | (g << 8) | b);
}

Uint32		ft_color_struct_to_hex(t_color color)
{
	return (ft_rgb_to_hex(color.r, color.g, color.b));
}

Uint32		ft_hex_transform(int color, float percent)
{
	t_color	rgb;

	rgb.a = (color >> 24) & 0xFF * 0;
	rgb.r = ((color >> 16) & 0xFF) * percent;
	rgb.g = ((color >> 8) & 0xFF) * percent;
	rgb.b = ((color >> 0) & 0xFF) * percent;
	color = ((rgb.a << 24) | (rgb.r << 16) | (rgb.g << 8) | rgb.b << 0);
	return (color);
}
