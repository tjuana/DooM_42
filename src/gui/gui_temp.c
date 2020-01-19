/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gui_temp.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dorange- <dorange-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/18 17:21:12 by dorange-          #+#    #+#             */
/*   Updated: 2020/01/19 16:10:05 by dorange-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
**	[!]
**	
**	It's temp. file for sector editor.
**	
*/

#include "wolf3d.h"

/*
**	Check vertexes compare
**	
**	ft_editor_sector_compare_vertexes -> ft_compare_vertexes
*/
int		ft_compare_vertexes(t_vector3 v1, t_vector3 v2)
{
	if ((int)v1.x == (int)v2.x && \
		(int)v1.y == (int)v2.y && \
		(int)v1.z == (int)v2.z && \
		(int)v1.w == (int)v2.w)
		return (1);
	return (0);
}

/*
**	[!]
**	vxs: Vector cross product
**	
**	Need to add for vector library
*/
double		ft_vxs_vector(t_vector3 v1, t_vector3 v2)
{
	return (v1.x * v2.y - v2.x * v1.y);
}

double		ft_vxs_double(double x1, double y1, double x2, double y2)
{
	return (x1 * y2 - x2 * y1);
}

int			ft_check_div_vector(t_vector3 v1, t_vector3 v2, t_vector3 v3, t_vector3 v4)
{
	double		d;

	d = ft_vxs_double(v1.x - v2.x, v1.y - v2.y, v3.x - v4.x, v3.y - v4.y);
	if (d == 0.0)
		return (0);
	return 1;
}

/*
**	
**	
**	
*/
t_vector3	ft_find_line_intersect(t_vector3 v1, t_vector3 v2, \
				t_vector3 v3, t_vector3 v4)
{
	t_vector3	v;
	double		d;

	d = ft_vxs_double(v1.x - v2.x, v1.y - v2.y, v3.x - v4.x, v3.y - v4.y);
	v.x = ft_vxs_double(ft_vxs_double(v1.x, v1.y, v2.x, v2.y), v1.x - v2.x, \
		ft_vxs_double(v3.x, v3.y, v4.x, v4.y), v3.x - v4.x) / d;
	v.y = ft_vxs_double(ft_vxs_double(v1.x, v1.y, v2.x, v2.y), v1.y - v2.y, \
		ft_vxs_double(v3.x, v3.y, v4.x, v4.y), v3.y - v4.y) / d;
	return (v);
}









// /////////////////

void	ft_editor_sector_create(t_wolf3d *w)
{
	t_sector	*sector;
	t_list		*list_item;

	sector = ft_my_malloc(sizeof(t_sector));
	sector->id = w->sector_count + 1;
	sector->vertex = NULL;
	sector->vertex_count = 0;
	sector->status = 0;
	sector->floor = 0;
	sector->height = 10;
	list_item = ft_lstnew(sector, sizeof(t_sector));
	if (w->sector == NULL)
		w->sector = list_item;
	else
		ft_lstadd(&(w->sector), list_item);
}

void	ft_editor_sector_set_vertex(t_wolf3d *w, t_sector *sector, t_vector3 v)
{
	t_vector3	**vertex;
	t_vector3	*p;
	int			i;

	vertex = ft_my_malloc(sizeof(void*) * sector->vertex_count + 1);
	i = 0;
	while (i < sector->vertex_count)
	{
		vertex[i] = sector->vertex[i];
		i++;
	}
	p = malloc(sizeof(t_vector3));
	ft_bzero_char(p, sizeof(t_vector3));
	*p = v;
	vertex[i] = p;
	free(sector->vertex);
	sector->vertex = vertex;
	sector->vertex_count++;
}

void	ft_editor_sector_del_last_vertex(t_wolf3d *w, t_sector *sector)
{
	t_vector3	**vertex;
	int			i;

	vertex = ft_my_malloc(sizeof(void*) * sector->vertex_count - 1);
	i = 0;
	while (i < sector->vertex_count - 1)
	{
		vertex[i] = sector->vertex[i];
		i++;
	}
	free(sector->vertex);
	sector->vertex = vertex;
	sector->vertex_count--;
	if (sector->status == 1)
	{
		sector->status = 0;
		w->sector_status = 1;
	}
}

void		ft_editor_delete_last_vertex(t_wolf3d *w)
{
	t_sector	*sector;

	if (w->sector == NULL)
		return ;
	sector = w->sector->content;
	if (sector == NULL)
		return ;
	if (sector->status == 1)
	{
		sector->status = 0;
		w->sector_status = 1;
	}
	else
	{
		ft_editor_sector_del_last_vertex(w, sector);
	}
	if (sector->vertex_count == 0)
	{
		w->sector_count--;
	 	w->sector = w->sector->next;
		w->sector_status = 0;
	}
	else
	{
		sector->status = 0;
		w->sector_status = 1;
	}
}

int				ft_editor_sector_search_neighbors_vertex(t_wolf3d *w, t_vector3 *v1, t_vector3 *v2)
{
	t_list		*ptr_list;
	t_sector	*ptr_sector;
	int			vtx1_n;
	int			vtx2_n;
	int			i;

	ptr_list = w->sector;
	while (ptr_list)
	{
		ptr_sector = ptr_list->content;

		if (ptr_sector->status)
		{
			i = 0;
			while (i < ptr_sector->vertex_count)
			{
				vtx1_n = i;
				vtx2_n = (i + 1) % ptr_sector->vertex_count;

				if (
					(
						ft_compare_vertexes(*ptr_sector->vertex[vtx1_n], *v1) ||
						ft_compare_vertexes(*ptr_sector->vertex[vtx2_n], *v2)
					) ||
					(
						ft_compare_vertexes(*ptr_sector->vertex[vtx1_n], *v2) ||
						ft_compare_vertexes(*ptr_sector->vertex[vtx1_n], *v1)
					)
				)
				{
					return (ptr_sector->id);
				}
				i++;
			}
		}
		ptr_list = ptr_list->next;
	}
	return (0);
}

int				ft_editor_sector_search_neighbors_item(t_wolf3d *w, t_sector *sector, t_vector3 *v1, t_vector3 *v2)
{
	t_list		*ptr_list;
	t_sector	*ptr_sector;
	int			vtx1_n;
	int			vtx2_n;
	int			i;

	ptr_list = w->sector;
	while (ptr_list)
	{
		ptr_sector = ptr_list->content;

		if (ptr_sector->status)
		{
			i = 0;
			while (i < ptr_sector->vertex_count)
			{
				vtx1_n = i;
				vtx2_n = (i + 1) % ptr_sector->vertex_count;

				if (
					(
						ft_compare_vertexes(*ptr_sector->vertex[vtx1_n], *v1) &&
						ft_compare_vertexes(*ptr_sector->vertex[vtx2_n], *v2)
					) ||
					(
						ft_compare_vertexes(*ptr_sector->vertex[vtx1_n], *v2) &&
						ft_compare_vertexes(*ptr_sector->vertex[vtx2_n], *v1)
					)
				)
				{
					ptr_sector->neighbors[i] = sector->id;
					return (ptr_sector->id);
				}
				i++;
			}
		}
		ptr_list = ptr_list->next;
	}
	return (0);
}

/*
**	int ft_editor_sector_search_neighbors(t_wolf3d *w, t_sector *sector)
**
**	Function that set neigbors for sector.
*/
int				ft_editor_sector_search_neighbors(t_wolf3d *w, t_sector *sector)
{

	int			vtx1_n;
	int			vtx2_n;
	int			i;
	int			n;
	int			v;

	sector->neighbors = ft_my_malloc(sizeof(void*) * sector->vertex_count);

	i = 0;
	while (i < sector->vertex_count)
	{
		vtx1_n = i;
		vtx2_n = (i + 1) % sector->vertex_count;

		n = ft_editor_sector_search_neighbors_item( \
			w, \
			sector, \
			sector->vertex[vtx1_n], \
			sector->vertex[vtx2_n]);

		// v = ft_editor_sector_search_neighbors_item( \
		// 	w, sector->vertex[vtx1_n], \
		// 	sector->vertex[vtx2_n]);

		// if (n == 0 && v > 0)
		// {
		// 	free(sector->neighbors);
		// 	return (0);
		// }

		sector->neighbors[i] = n;
		i++;
	}

	return (1);
}

/*
**	void ft_editor_init_sectors_item_area(t_wolf3d *w, t_sector *sector)
**
**	Function that set one sector as ui element.
**	
**	[!] Устаревшая функция
*/
void		ft_editor_init_sectors_item_area(t_wolf3d *w, t_sector *s)
{
	t_vector3	v1;
	t_vector3	v2;
	int			i;

	if (s->vertex_count == 0)
		return ;
	v1 = *s->vertex[0];
	v2 = *s->vertex[0];
	i = 0;
	while (i < s->vertex_count)
	{
		v1.x = (s->vertex[i]->x < v1.x) ? s->vertex[i]->x : v1.x;
		v1.y = (s->vertex[i]->y < v1.y) ? s->vertex[i]->y : v1.y;
		v2.x = (s->vertex[i]->x > v2.x) ? s->vertex[i]->x : v2.x;
		v2.y = (s->vertex[i]->y > v2.y) ? s->vertex[i]->y : v2.y;
		i++;
	}
	s->elem_2d.v1 = (t_ui_coord){(int)v1.x, (int)v1.y, 0};
	s->elem_2d.v2 = (t_ui_coord){(int)v2.x, (int)v2.y, 0};
	s->elem_2d.w = s->elem_2d.v2.x - s->elem_2d.v1.x;
	s->elem_2d.h = s->elem_2d.v2.y - s->elem_2d.v1.y;

	// Реализовать расчёт средней точки сектора
}

/*
**	void ft_editor_init_sector_areas(t_wolf3d *w)
**
**	Function that set sectors as interface elements.
**	
**	[!] Устаревшая функция
*/
void		ft_editor_init_sectors_areas(t_wolf3d *w, t_list *sector)
{
	if (sector)
	{
		ft_editor_init_sectors_areas(w, sector->next);
		ft_editor_init_sectors_item_area(w, (t_sector*)sector->content);
	}
}

// [TEMP]
void	ft_editor_sector_special_debug(t_list *ptr_list)
{
	t_sector	*ptr_sector;
	int			i;
	int			j;

	i = 0;
	while (ptr_list != NULL)
	{
		// Get sector values
		ptr_sector = (t_sector*)ptr_list->content;

		printf("SECTOR #%d   VERTEX_COUNT %d   STATUS: %d\n", ptr_sector->id, \
			ptr_sector->vertex_count, (int)ptr_sector->status);

		printf("vertexes:   ");

		j = 0;
		while (j < ptr_sector->vertex_count)
		{
			if (j > 0)
				printf(" | ");
			printf(
				"[%02.0f, %02.0f]AAAA[%.f]",
				ptr_sector->vertex[j]->x,
				ptr_sector->vertex[j]->y,
				ptr_sector->vertex[j]->w
			);
			j++;
		}

		printf("\n");

		if (ptr_sector->status == 1)
		{
			printf ("neighbors:  ");

			j = 0;
			while (j < ptr_sector->vertex_count)
			{
				if (j > 0)
					printf(" ");
				printf(
					"%d",
					ptr_sector->neighbors[j]
				);
				
				j++;
			}

			printf ("\n");
		}
		
		// Get next sector
		ptr_list = ptr_list->next;
		i++;
	}
}










// /////////////////









/*
**	int	 ft_check_line_segment_intersect_vector(t_vector3 v1, t_vector3 v2, \
**		t_vector3 v3, t_vector3 v4)
**	
**	
*/
int		ft_check_line_segment_intersect_vector(t_vector3 v1, t_vector3 v2, \
			t_vector3 v3, t_vector3 v4)
{
	t_vector3	p;

	// Если прямые параллельны, то они не пересекаются
	if (!ft_check_div_vector(v1, v2, v3, v4))
		return (0);
	
	// Находим точку пересечения
	p = ft_find_line_intersect(v1, v2, v3, v4);

	// Проверяем, лежит ли точка пересечения на отрезках
	if (
		ft_check_point_in_line_segment(p, v3, v4) &&
		ft_check_point_in_line_segment(p, v1, v2)
	)
		return (1);
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