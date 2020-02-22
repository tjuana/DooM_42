/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   algebra_matrix.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dorange- <dorange-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/25 16:38:34 by tjuana            #+#    #+#             */
/*   Updated: 2020/02/21 20:58:44 by dorange-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

t_matrix_4x4	ft_identify(t_matrix_4x4 neo)
{
	neo.i = -1;
	while (++neo.i < 4)
	{
		neo.j = -1;
		while (++neo.j < 4)
			neo.matrix[neo.i][neo.j] = 0;
	}
	neo.matrix[0][0] = 1.00;
	neo.matrix[1][1] = 1.00;
	neo.matrix[2][2] = 1.00;
	neo.matrix[3][3] = 1.00;
	return (neo);
}

t_matrix_4x4	ft_scale(t_matrix_4x4 neo, double scale)
{
	neo.matrix[0][0] = scale;
	neo.matrix[1][1] = scale;
	neo.matrix[2][2] = scale;
	neo.matrix[3][3] = 1.00;
	return (neo);
}

t_matrix_4x4	ft_translitation(t_matrix_4x4 neo, t_vector3 *vtc)
{
	neo.matrix[0][0] = 1.00;
	neo.matrix[1][1] = 1.00;
	neo.matrix[2][2] = 1.00;
	neo.matrix[3][3] = 1.00;
	neo.matrix[0][3] = vtc->x;
	neo.matrix[1][3] = vtc->y;
	neo.matrix[2][3] = vtc->z;
	return (neo);
}

t_matrix_4x4	ft_projection(t_matrix_4x4 neo, double ratio, \
					double near, double far)
{
	neo.matrix[1][1] = 1 / tan(0.5 * ft_math_deg_to_rad(FOV));
	neo.matrix[0][0] = neo.matrix[1][1] / ratio;
	neo.matrix[2][2] = -1 * (-near - far) / (near - far);
	neo.matrix[3][2] = -1.00;
	neo.matrix[2][3] = (2 * near * far) / (near - far);
	neo.matrix[3][3] = 0.00;
	return (neo);
}

t_matrix_4x4	ft_oppositive_matrix(t_matrix_4x4 neo)
{
	t_matrix_4x4	trinity;

	trinity.i = -1;
	while (++trinity.i < 4)
	{
		trinity.j = -1;
		while (++trinity.j < 4)
			trinity.matrix[trinity.i][trinity.j] = 0;
	}
	trinity.i = -1;
	while (++trinity.i < 4)
	{
		trinity.j = -1;
		while (++trinity.j < 4)
			trinity.matrix[trinity.i][trinity.j] = \
				neo.matrix[trinity.j][trinity.i];
	}
	return (trinity);
}
