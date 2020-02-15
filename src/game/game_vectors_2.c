/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_vectors_2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: drafe <drafe@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/24 13:44:37 by tjuana            #+#    #+#             */
/*   Updated: 2020/02/11 17:15:55 by drafe            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

float			ft_new_vec3_dot_product(t_new_vector3 this, t_new_vector3 rhs)
{
	float	res;

	res = this.x * rhs.x + this.y * rhs.y + this.z * rhs.z;
	return (res);
}

float			ft_new_vec3_cosinus(t_new_vector3 this, t_new_vector3 rhs)
{
	float	res;

	res = ft_new_vec3_dot_product(this, rhs) / (ft_new_vec3_magnitude(this) * \
	sqrt(pow(rhs.x, 2) + pow(rhs.y, 2) + pow(rhs.z, 2)));
	return (res);
}

t_new_vector3	ft_new_vec3_opposite(t_new_vector3 this)
{
	t_new_vector3	res;

	res.x = -this.x;
	res.y = -this.y;
	res.z = -this.z;
	res.w = this.w;
	return (res);
}

t_new_vector3	ft_new_vec3_scalar_product(t_new_vector3 this, float k)
{
	t_new_vector3	res;

	res.x = this.x * k;
	res.y = this.y * k;
	res.z = this.z * k;
	res.w = this.w;
	return (res);
}

t_new_vector3	ft_new_vec3_normalize(t_new_vector3 vtc)
{
	t_new_vector3	v0;
	t_new_vector3	v1;

	if (ft_new_vec3_magnitude(vtc) == 1)
		return (vtc);
	v0.x = 0;
	v0.y = 0;
	v0.z = 0;
	v1.x = vtc.x / ft_new_vec3_magnitude(vtc);
	v1.y = vtc.y / ft_new_vec3_magnitude(vtc);
	v1.z = vtc.z / ft_new_vec3_magnitude(vtc);
	return (ft_new_vec3_create(&v0, &v1));
}
