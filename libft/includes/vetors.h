/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vetors.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjuana <tjuana@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/21 18:00:00 by tjuana            #+#    #+#             */
/*   Updated: 2020/01/21 19:05:21 by tjuana           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#ifndef VECTORS_H
# define VECTORS_H

# include <math.h>
# include <stdbool.h>
# include <stddef.h>

# include <sys/cdefs.h>
# ifndef __always_inline
#  define __always_inline inline __attribute__((__always_inline__))
# endif

# ifndef __lvec_always_inline
#  define __lvec_always_inline static __always_inline
# endif

#  define V4DF typedef double t_v4df __attribute__((vector_size(32),aligned))
#  define V2DF typedef double t_v2df __attribute__((vector_size(16),aligned))
#  define V4DU typedef size_t t_v4du __attribute__((vector_size(32),aligned))

V4DF;
V2DF;
V4DU;

# define X(v) (v)[0]
# define Y(v) (v)[1]
# define Z(v) (v)[2]
# define W(v) (v)[3]

# define VDISC(a, b, c) ((b) * (b) - 4.0 * (a) * (c))

__lvec_always_inline double_t
v_dot(t_v4df const v1, t_v4df const v2)
{
	return X(v1) * X(v2) + Y(v1) * Y(v2) + Z(v1) * Z(v2);
}

__lvec_always_inline double_t
v_len(t_v4df const v)
{
	return sqrt(v_dot(v, v));
}

__lvec_always_inline t_v4df
v_norm(t_v4df const v)
{
	double_t const	vlen = v_len(v);
	return (t_v4df){X(v) / vlen, Y(v) / vlen, Z(v) / vlen, 0.0};
}

__lvec_always_inline t_v4df
v_mul_d(t_v4df const v, double_t const d)
{
	return (t_v4df){X(v) * d, Y(v) * d, Z(v) * d, 0.0};
}
__lvec_always_inline t_v4df
v_add_d(t_v4df const v, double_t const d)
{
	return (t_v4df){X(v) + d, Y(v) + d, Z(v) + d, 0.0};
}
__lvec_always_inline t_v4df
v_sub_d(t_v4df const v, double_t const d)
{
	return (t_v4df){X(v) - d, Y(v) - d, Z(v) - d, 0.0};
}
__lvec_always_inline t_v4df
v_div_d(t_v4df const v, double_t const d)
{
	return (t_v4df){X(v) / d, Y(v) / d, Z(v) / d, 0.0};
}

__lvec_always_inline t_v4df
v_mul_v(t_v4df const a, t_v4df const b)
{
	return a * b;
}
__lvec_always_inline t_v4df
v_add_v(t_v4df const a, t_v4df const b)
{
	return a + b;
}
__lvec_always_inline t_v4df
v_sub_v(t_v4df const a, t_v4df const b)
{
	return a - b;
}
__lvec_always_inline t_v4df
v_div_v(t_v4df const a, t_v4df const b)
{
	return a / b;
}

__lvec_always_inline t_v4df
v_invert(t_v4df const v)
{
	return -v;
}

/*
**	u_ prefix is short name for utils.
*/
__lvec_always_inline bool
u_vec_range(t_v4df const v,
			double_t const max_range,
			double_t const min_range)
{
	if (max_range < X(v) || max_range < Y(v) || max_range < Z(v))
		return false;
	if (min_range > X(v) || min_range > Y(v) || min_range > Z(v))
		return false;
	return true;
}
__lvec_always_inline bool
u_isd_range(double_t const x,
			double_t const max_range,
			double_t const min_range)
{
	if (max_range < x || x < min_range)
		return false;
	return true;
}
__lvec_always_inline double_t
u_d_range(double_t const x,
		double_t const max_range,
		double_t const min_range)
{
	if (max_range < x)
		return max_range;
	if (min_range > x)
		return min_range;
	return x;
}

#endif