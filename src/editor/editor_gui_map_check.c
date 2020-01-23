/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   editor_gui_map_check.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dorange- <dorange-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/20 12:45:52 by dorange-          #+#    #+#             */
/*   Updated: 2020/01/23 15:08:25 by dorange-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

int		ft_check_point_in_sector_line_diameter(t_sector *s, t_vector3 v, double d)
{
	int				i;
	int				vtx1_n; // vertex number
	int				vtx2_n;
	int				count;

	i = 0;
	count = 0;
	while (i < s->vertex_count)
	{
		vtx1_n = i;
		vtx2_n = (i + 1) % s->vertex_count;

		// Если точка лежит на отрезке сектора в некотором диаметре,
		// то это наша стена -- возвращаем номер вершины
		if (ft_check_point_in_line_segment_diameter(\
			v, *s->vertex[vtx1_n], *s->vertex[vtx2_n], d))
			return (i);
		i++;
	}
	return (-1);
}

/*
	Проверка, не лежит ли точка не линии сектора
	(в области некоторого диаметра)
*/
int		ft_search_point_in_sector_line_diameter(void *a, t_vector3 v, double d)
{
	t_wolf3d	*w;
	t_list		*list;
	t_sector	*sector;
	int			i;

	w = (t_wolf3d*)a;

	list = w->sector;
	i = 0;
	while (list)
	{
		sector = list->content;
		if (sector->status == 1)
		{
			if (!ft_check_point_in_sector(w, sector, v))
				if (ft_check_point_in_sector_line_diameter(sector, v, d) != -1)
					return (sector->id);
		}
		list = list->next;
		i++;
	}
	return (0);
}



/*
**	Проверяем, находится ли мышка игрока в секторе
**	
**	
*/
int		ft_check_point_in_sector(t_wolf3d *w, t_sector *s, t_vector3 v)
{
	int				i;
	int				vtx1_n; // vertex number
	int				vtx2_n;
	int				count;

	i = 0;
	count = 0;
	while (i < s->vertex_count)
	{
		vtx1_n = i;
		vtx2_n = (i + 1) % s->vertex_count;

		// Если наша вершина совпадает с одной из вершин сектора,
		// то никаких пересечений нет
		if (ft_compare_vertexes(v, *s->vertex[vtx1_n]) || \
			ft_compare_vertexes(v, *s->vertex[vtx2_n]))
			return (0);

		// Если точка лежит на отрезке сектора, то это считается пересечением
		if (ft_check_point_in_line_segment(v, *s->vertex[vtx1_n], *s->vertex[vtx2_n]))
			return (2);

		// Проверяем, есть ли пересечение с отрезком
		if (ft_check_line_segment_intersect_vector((t_vector3){-10.0, -10.0, 0, 0}, v, \
			*s->vertex[vtx1_n], *s->vertex[vtx2_n]))
			count++;

		i++;
	}

	// Если число пересечений кратно двум, то мы находимся за пределами сектора,
	// в обратном случае -- внутри
	return (count % 2);
}

/*
**	Проверяем, находится ли точка в каком-то секторе.
**	Если находится, то возвращается id сектора.
**	
*/
int		ft_search_point_in_sector(void *a, t_vector3 v)
{
	t_wolf3d	*w;
	t_list		*list;
	t_sector	*sector;
	int			i;

	w = (t_wolf3d*)a;

	list = w->sector;
	i = 0;
	while (list)
	{
		sector = list->content;
		if (sector->status == 1)
		{
			if (ft_check_point_in_sector(w, sector, v))
				return (sector->id);
		}
		list = list->next;
		i++;
	}
	return (0);
}








/*
**	new check
**	
**	
**	
**	
**	
**	
*/
int		ft_new_editor_map_check_area(t_wolf3d *w)
{
	t_vector3	vec1;
	t_vector3	vec2;
	t_sector	*s;
	t_vector3	pos;

	if (w->sector == NULL)
		return (1);

	pos = ft_gui_map_coord_to_vertex(w, (t_gui_rect){0, 0, 0, 0}, w->gui.mouse_pos);

	// Ф-ия определяет, не находится ли точка в секторе
	if (ft_search_point_in_sector(w, pos))
		return (0);

	s = w->sector->content;
	// Если нет режима, то выходим из проверки
	if (s->status == 1)
		return (1);
	// Если точек меньше 3, нет смысла проверять
	if (s->vertex_count < 3)
		return (1);

	// Проверяем первую полуплоскость
	vec1 = ft_vec3_create(s->vertex[s->vertex_count - 1], &pos);
	vec2 = ft_vec3_create(s->vertex[s->vertex_count - 2], \
		s->vertex[s->vertex_count - 1]);
	if (ft_vxs_vector(vec1, vec2) < 0.0)
		return (0);

	// Проверяем вторую полуплоскость
	vec2 = ft_vec3_create(s->vertex[0], s->vertex[s->vertex_count - 1]);
	if (ft_vxs_vector(vec1, vec2) < 0.0)
		return (0);

	// ?!
	if (ft_check_line_segment_intersect_vector(*s->vertex[1], *s->vertex[0], \
		*s->vertex[s->vertex_count - 1], pos))
		return (0);

	return (1);
}