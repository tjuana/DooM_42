/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   func_struct.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dorange- <dorange-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/20 20:26:25 by dorange-          #+#    #+#             */
/*   Updated: 2020/01/21 20:51:26 by dorange-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FUNC_STRUCT_H
# define FUNC_STRUCT_H

# include <libft.h>
# include "SDL2/SDL.h"
# include "SDL2/SDL_ttf.h"

typedef struct	s_fdf_wu
{
	double		x1;
	double		y1;
	double		x2;
	double		y2;
	double		p;
	double		dx;
	double		dy;
	double		gradient;
	double		xend;
	double		yend;
	double		xgap;
	double		xpxl1;
	double		ypxl1;
	double		xpxl2;
	double		ypxl2;
	double		intery;
	int			steep;
	int			steps;
	int			step;
	int			color1;
	int			color2;
	int			check_color_rev;
	double		temp_f;
}				t_fdf_wu;

typedef struct	s_fdf_get_color
{
	int			color1;
	int			color2;
	double		f1;
	int			a1;
	int			r1;
	int			g1;
	int			b1;
	int			r2;
	int			g2;
	int			b2;
	int			r_rez;
	int			g_rez;
	int			b_rez;
}				t_fdf_get_color;

#endif
