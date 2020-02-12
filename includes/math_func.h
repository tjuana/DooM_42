/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   math_func.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dorange- <dorange-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/26 18:41:23 by dorange-          #+#    #+#             */
/*   Updated: 2020/02/09 14:09:01 by dorange-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MATH_FUNC_H
# define MATH_FUNC_H

# include <libft.h>

/*
** **************************************************************************
**	math_intersect.c
** **************************************************************************
*/
t_vector3		ft_find_line_intersect(t_vector3 v1, t_vector3 v2, \
					t_vector3 v3, t_vector3 v4);
int				ft_check_line_segment_intersect_vector(t_vector3 v1, \
					t_vector3 v2, t_vector3 v3, t_vector3 v4);
int				ft_check_point_in_line_segment(t_vector3 p, \
					t_vector3 p1, t_vector3 p2);
int				ft_check_point_in_line_segment_diameter(t_vector3 p, \
					t_vector3 p1, t_vector3 p2, double diameter);
int				ft_check_general_segment_line(t_vector3 v1, t_vector3 v2, \
					t_vector3 v3, t_vector3 v4);

/*
** **************************************************************************
**	math_vectors.c
** **************************************************************************
*/
int				ft_compare_vertexes(t_vector3 v1, t_vector3 v2);
double			ft_vxs_vector(t_vector3 v1, t_vector3 v2);
double			ft_vxs_double(double x1, double y1, double x2, double y2);
int				ft_check_div_vector(t_vector3 v1, t_vector3 v2, \
					t_vector3 v3, t_vector3 v4);
double			ft_math_vxs(double x0, double y0, double x1, double y1);

#endif
