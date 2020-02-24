/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   algebra_camera.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dorange- <dorange-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/25 16:38:34 by tjuana            #+#    #+#             */
/*   Updated: 2020/02/14 15:27:27 by dorange-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

t_vector3	ft_camera_get_screen_vertex(t_vector3 world_vertex, \
				t_matrix_4x4 t_mult, t_matrix_4x4 t_proj)
{
	t_vector3		screen_vertex;

	screen_vertex = ft_transform_vertex(world_vertex, t_mult);
	screen_vertex = ft_transform_vertex(screen_vertex, t_proj);
	screen_vertex.x = (1 - screen_vertex.x) / (screen_vertex.z / 11.3) * \
		WIDTH / 2;
	screen_vertex.y = (1 - screen_vertex.y) / (screen_vertex.z / 11.3) * \
		HIGHT / 2;
	return (screen_vertex);
}

t_vector3	ft_camera(t_vector3 vtx_orig, t_matrix_4x4 orient, \
				t_vector3 world_vertex)
{
	t_vector3		vertex0;
	t_vector3		oppv;
	t_matrix_4x4	trans;
	t_matrix_4x4	t_mult;
	t_matrix_4x4	t_proj;

	t_mult = ft_identify(t_mult);
	trans = ft_identify(trans);
	t_proj = ft_identify(t_proj);
	vertex0.x = 0;
	vertex0.y = 0;
	vertex0.z = 0;
	vertex0.w = 1;
	oppv = ft_vec3_create(&vtx_orig, &vertex0);
	trans = ft_translitation(trans, &oppv);
	orient = ft_oppositive_matrix(orient);
	t_mult = ft_mult_matrix(orient, trans);
	t_proj = ft_projection(t_proj, WIDTH / HIGHT, NEAR, FAR);
	return (ft_camera_get_screen_vertex(world_vertex, t_mult, t_proj));
}
