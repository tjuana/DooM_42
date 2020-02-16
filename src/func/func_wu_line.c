/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   func_wu_line.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dorange- <dorange-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/08 19:25:23 by dorange-          #+#    #+#             */
/*   Updated: 2020/02/16 12:46:12 by dorange-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

void		ft_fdf_draw_line_swap(t_fdf_wu **wu)
{
	if ((*wu)->steep)
	{
		ft_fdf_swap_double(&(*wu)->x1, &(*wu)->y1);
		ft_fdf_swap_double(&(*wu)->x2, &(*wu)->y2);
	}
	if ((*wu)->y2 < (*wu)->y1 || (*wu)->x1 > (*wu)->x2)
	{
		ft_fdf_swap_double(&(*wu)->x1, &(*wu)->x2);
		ft_fdf_swap_double(&(*wu)->y1, &(*wu)->y2);
	}
	if ((*wu)->x1 > (*wu)->x2)
	{
		ft_fdf_swap_double(&(*wu)->x1, &(*wu)->x2);
		ft_fdf_swap_double(&(*wu)->y1, &(*wu)->y2);
	}
}

void		ft_fdf_draw_line_param(t_wolf3d *data, t_fdf_wu **wu)
{
	(*wu)->dx = (*wu)->x2 - (*wu)->x1;
	(*wu)->dy = (*wu)->y2 - (*wu)->y1;
	(*wu)->gradient = (*wu)->dy / (*wu)->dx;
	if ((*wu)->dx == 0.0)
		(*wu)->gradient = 1.0;
	(*wu)->xend = ft_fdf_round((*wu)->x1);
	(*wu)->yend = (*wu)->y1 + (*wu)->gradient * ((*wu)->xend - (*wu)->x1);
	(*wu)->xgap = 1 - ft_fdf_fpart((*wu)->x1 + 0.5);
	(*wu)->xpxl1 = (*wu)->xend;
	(*wu)->ypxl1 = ft_fdf_ipart((*wu)->yend);
	ft_fdf_draw_line_first_pixels(data, wu);
	(*wu)->intery = (*wu)->yend + (*wu)->gradient;
	(*wu)->xend = ft_fdf_round((*wu)->x2);
	(*wu)->yend = (*wu)->y2 + (*wu)->gradient * ((*wu)->xend - (*wu)->x2);
	(*wu)->xgap = ft_fdf_fpart((*wu)->x2 + 0.5);
	(*wu)->xpxl2 = (*wu)->xend;
	(*wu)->ypxl2 = ft_fdf_ipart((*wu)->yend);
	ft_fdf_draw_line_last_pixels(data, wu);
}
