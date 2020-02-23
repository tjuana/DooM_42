/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   algebra.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dorange- <dorange-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/24 15:22:19 by tjuana            #+#    #+#             */
/*   Updated: 2020/02/22 13:39:36 by dorange-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ALGEBRA_H
# define ALGEBRA_H

# include "doom.h"

/*
** **************************************************************************
**	Constant
** **************************************************************************
*/
# define FOV	90.0
# define NEAR	1.0
# define FAR	100.0

typedef struct	s_vector3
{
	double		x;
	double		y;
	double		z;
	double		w;
}				t_vector3;

typedef struct	s_matrix_4x4
{
	double		matrix[4][4];
	int			i;
	int			j;
}				t_matrix_4x4;

/*
** **************************************************************************
**	algebra_intersect.c
** **************************************************************************
*/

t_vector3		ft_find_line_intersect(t_vector3 v1, t_vector3 v2, \
					t_vector3 v3, t_vector3 v4);
int				ft_check_line_segment_intersect_vector(t_vector3 v1, \
					t_vector3 v2, t_vector3 v3, t_vector3 v4);
int				ft_check_intersect_line_and_line_segment(t_vector3 v1, \
					t_vector3 v2, t_vector3 p1, t_vector3 p2);
int				ft_check_point_in_line(t_vector3 p, t_vector3 p1, \
					t_vector3 p2);
int				ft_check_point_in_line_segment(t_vector3 p, \
					t_vector3 p1, t_vector3 p2);

/*
** **************************************************************************
**	algebra_intersect2.c
** **************************************************************************
*/
int				ft_check_point_in_line_segment_diameter(t_vector3 p, \
					t_vector3 p1, t_vector3 p2, double diameter);
int				ft_check_general_segment_line(t_vector3 v1, t_vector3 v2, \
					t_vector3 v3, t_vector3 v4);

/*
** **************************************************************************
**	algebra_math_1.c
** **************************************************************************
*/

float			ft_math_min(float a, float b);
float			ft_math_max(float a, float b);
float			ft_math_clamp(float a, float mi, float ma);
int				ft_math_overlap(float a1, float a2, float b1, float b2);

/*
** **************************************************************************
**	algebra_math_2.c
** **************************************************************************
*/
int				ft_math_intersectbox(t_vector3 v1, t_vector3 v2, t_vector3 v3, \
					t_vector3 v4);
float			ft_math_pointside(t_vector3 p, t_vector3 v1, t_vector3 v2);
t_vector3		ft_math_intersect(t_vector3 v1, t_vector3 v2, t_vector3 v3, \
					t_vector3 v4);
float			ft_math_yaw(float y, float z, float yaw);
float			ft_math_to_deg(float radians);

/*
** **************************************************************************
**	algebra_math_3.c
** **************************************************************************
*/
t_vector3		ft_math_sum_vectors_xy(t_vector3 v0, t_vector3 v1);

/*
** **************************************************************************
**	algebra_matrix.c
** **************************************************************************
*/
t_matrix_4x4	ft_identify(t_matrix_4x4 neo);
t_matrix_4x4	ft_scale(t_matrix_4x4 neo, double scale);
t_matrix_4x4	ft_translitation(t_matrix_4x4 neo, t_vector3 *vtc);
t_matrix_4x4	ft_projection(t_matrix_4x4 neo, double ratio, \
					double near, double far);
t_matrix_4x4	ft_oppositive_matrix(t_matrix_4x4 neo);

/*
** **************************************************************************
**	algebra_matrix_2.c
** **************************************************************************
*/
double			ft_math_deg_to_rad(double angle_degrees);
double			ft_math_rad_to_deg(double angle_radians);

/*
** **************************************************************************
**	algebra_matrix_transform.c
** **************************************************************************
*/
t_matrix_4x4	ft_rx_matrix(t_matrix_4x4 neo, double angle);
t_matrix_4x4	ft_ry_matrix(t_matrix_4x4 neo, double angle);
t_matrix_4x4	ft_rz_matrix(t_matrix_4x4 neo, double angle);
t_vector3		ft_transform_vertex(t_vector3 this, t_matrix_4x4 neo);

/*
** **************************************************************************
**	algebra_matrix_transform.c
** **************************************************************************
*/
t_matrix_4x4	ft_mult_matrix(t_matrix_4x4 this, t_matrix_4x4 rhs);

/*
** **************************************************************************
**	algebra_vectors_1.c
** **************************************************************************
*/
t_vector3		ft_vec3_create(t_vector3 *orig, t_vector3 *dest);
double			ft_vec3_magnitude(t_vector3 this);
t_vector3		ft_vec3_add(t_vector3 this, t_vector3 rhs);
t_vector3		ft_vec3_sub(t_vector3 this, t_vector3 rhs);
t_vector3		ft_vec3_cross_product(t_vector3 this, t_vector3 rhs);

/*
** **************************************************************************
**	algebra_vectors_2.c
** **************************************************************************
*/
double			ft_vec3_dot_product(t_vector3 this, t_vector3 rhs);
double			ft_vec3_cosinus(t_vector3 this, t_vector3 rhs);
t_vector3		ft_vec3_opposite(t_vector3 this);
t_vector3		ft_vec3_scalar_product(t_vector3 this, double k);
t_vector3		ft_vec3_normalize(t_vector3 vtc);

/*
** **************************************************************************
**	algebra_vectors_3.c
** **************************************************************************
*/
float			ft_vec2_cos(t_vector3 vec1, t_vector3 vec2);

/*
** **************************************************************************
**	algebra_vectors_3.c
** **************************************************************************
*/
int				ft_compare_vertexes(t_vector3 v1, t_vector3 v2);
double			ft_vxs_vector(t_vector3 v1, t_vector3 v2);
double			ft_vxs_double(double x1, double y1, double x2, double y2);
int				ft_check_div_vector(t_vector3 v1, t_vector3 v2, \
					t_vector3 v3, t_vector3 v4);
double			ft_math_vxs(double x0, double y0, double x1, double y1);

#endif
