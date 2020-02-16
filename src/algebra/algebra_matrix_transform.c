/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   algebra_matrix_transform.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dorange- <dorange-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/25 16:38:34 by tjuana            #+#    #+#             */
/*   Updated: 2020/02/14 15:31:52 by dorange-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

t_matrix_4x4	ft_rx_matrix(t_matrix_4x4 neo, double angle)
{
	neo.matrix[0][0] = 1.00;
	neo.matrix[1][1] = cos(angle);
	neo.matrix[1][2] = -sin(angle);
	neo.matrix[2][1] = sin(angle);
	neo.matrix[2][2] = cos(angle);
	neo.matrix[3][3] = 1.00;
	return (neo);
}

t_matrix_4x4	ft_ry_matrix(t_matrix_4x4 neo, double angle)
{
	neo.matrix[0][0] = cos(angle);
	neo.matrix[0][2] = sin(angle);
	neo.matrix[1][1] = 1.00;
	neo.matrix[2][0] = -sin(angle);
	neo.matrix[2][2] = cos(angle);
	neo.matrix[3][3] = 1.00;
	return (neo);
}

t_matrix_4x4	ft_rz_matrix(t_matrix_4x4 neo, double angle)
{
	neo.matrix[0][0] = cos(angle);
	neo.matrix[0][1] = -sin(angle);
	neo.matrix[1][0] = sin(angle);
	neo.matrix[1][1] = cos(angle);
	neo.matrix[2][2] = 1.00;
	neo.matrix[3][3] = 1.00;
	return (neo);
}

t_vector3		ft_transform_vertex(t_vector3 this, t_matrix_4x4 neo)
{
	t_vector3	res;

	res.x = (this.x * neo.matrix[0][0]) + (this.y * neo.matrix[0][1]) + \
		(this.z * neo.matrix[0][2]) + (this.w * neo.matrix[0][3]);
	res.y = (this.x * neo.matrix[1][0]) + (this.y * neo.matrix[1][1]) + \
		(this.z * neo.matrix[1][2]) + (this.w * neo.matrix[1][3]);
	res.z = (this.x * neo.matrix[2][0]) + (this.y * neo.matrix[2][1]) + \
		(this.z * neo.matrix[2][2]) + (this.w * neo.matrix[2][3]);
	res.w = (this.x * neo.matrix[3][0]) + (this.y * neo.matrix[3][1]) + \
		(this.z * neo.matrix[3][2]) + (this.w * neo.matrix[3][3]);
	return (res);
}

/*
** **************************************************************************
**	t_matrix_4x4 ft_mult_matrix(t_matrix_4x4 this, t_matrix_4x4 rhs)
**
**	Function that calculate multy matrix
**
**	t_matrix_4x4 re -> reload (new matrix)
** **************************************************************************
*/

t_matrix_4x4	ft_mult_matrix(t_matrix_4x4 this, t_matrix_4x4 rhs)
{
	t_matrix_4x4	re;

	re.i = -1;
	while (++re.i < 4)
	{
		re.j = -1;
		while (++re.j < 4)
			re.matrix[re.i][re.j] = 0;
	}
	re.i = -1;
	while (++re.i < 4)
	{
		re.j = -1;
		while (++re.j < 4)
		{
			re.matrix[re.i][re.j] += this.matrix[re.i][0] * rhs.matrix[0][re.j];
			re.matrix[re.i][re.j] += this.matrix[re.i][1] * rhs.matrix[1][re.j];
			re.matrix[re.i][re.j] += this.matrix[re.i][2] * rhs.matrix[2][re.j];
			re.matrix[re.i][re.j] += this.matrix[re.i][3] * rhs.matrix[3][re.j];
		}
	}
	return (re);
}
