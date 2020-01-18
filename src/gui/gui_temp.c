/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gui_temp.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dorange- <dorange-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/18 17:21:12 by dorange-          #+#    #+#             */
/*   Updated: 2020/01/18 20:46:49 by dorange-         ###   ########.fr       */
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
**	Special convert
**	
**	
*/
t_vector3	ft_t_ui_coord_to_t_vector3(t_ui_coord c)
{
	return ((t_vector3){(double)c.x, (double)c.y, 0.0, 0.0});
}





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
						ft_editor_sector_compare_vertexes(*ptr_sector->vertex[vtx1_n], *v1) ||
						ft_editor_sector_compare_vertexes(*ptr_sector->vertex[vtx2_n], *v2)
					) ||
					(
						ft_editor_sector_compare_vertexes(*ptr_sector->vertex[vtx1_n], *v2) ||
						ft_editor_sector_compare_vertexes(*ptr_sector->vertex[vtx1_n], *v1)
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
						ft_editor_sector_compare_vertexes(*ptr_sector->vertex[vtx1_n], *v1) &&
						ft_editor_sector_compare_vertexes(*ptr_sector->vertex[vtx2_n], *v2)
					) ||
					(
						ft_editor_sector_compare_vertexes(*ptr_sector->vertex[vtx1_n], *v2) &&
						ft_editor_sector_compare_vertexes(*ptr_sector->vertex[vtx2_n], *v1)
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
	v1 = ft_t_ui_coord_to_t_vector3(ft_gui_map_vertex_to_coord(w, (t_gui_rect){0, 0, 0, 0}, v1));
	v2 = ft_t_ui_coord_to_t_vector3(ft_gui_map_vertex_to_coord(w, (t_gui_rect){0, 0, 0, 0}, v2));
	s->elem_2d.v1 = (t_ui_coord){(int)v1.x, (int)v1.y, 0};
	s->elem_2d.v2 = (t_ui_coord){(int)v2.x, (int)v2.y, 0};
	s->elem_2d.w = s->elem_2d.v2.x - s->elem_2d.v1.x;
	s->elem_2d.h = s->elem_2d.v2.y - s->elem_2d.v1.y;
}

/*
**	void ft_editor_init_sector_areas(t_wolf3d *w)
**
**	Function that set sectors as interface elements.
*/
void		ft_editor_init_sectors_areas(t_wolf3d *w, t_list *sector)
{
	if (sector)
	{
		ft_editor_init_sectors_areas(w, sector->next);
		ft_editor_init_sectors_item_area(w, (t_sector*)sector->content);
	}
}

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











int		ft_new_sector_check_cross(t_wolf3d *w, t_sector *ptr_sector, t_vector3 v)
{
	int				i;
	int				vtx1_n; // vertex number
	int				vtx2_n;
	t_vector3		p;
	int				count;

	t_vector3		vertex3;
	t_vector3		vertex4;
	t_vector3		vertex5;

	t_sector		*sector;

	int				m;

	i = 0;
	count = 0;
	m = 0;
	while (i < ptr_sector->vertex_count)
	{
		vtx1_n = i;
		vtx2_n = i + 1;
		if (vtx2_n == ptr_sector->vertex_count)
			vtx2_n = 0;


		vertex3 = ft_t_ui_coord_to_t_vector3(ft_gui_map_vertex_to_coord(w, (t_gui_rect){0, 0, 0, 0}, *ptr_sector->vertex[vtx1_n]));
		vertex4 = ft_t_ui_coord_to_t_vector3(ft_gui_map_vertex_to_coord(w, (t_gui_rect){0, 0, 0, 0}, *ptr_sector->vertex[vtx2_n]));

		// ft_editor_sector_compare_vertexes -> standart function
		if (ft_editor_sector_compare_vertexes(v, vertex3) || ft_editor_sector_compare_vertexes(v, vertex4))
		{
			// sector = (t_sector*)(w->sector->content);
			// if (sector->status == 0)
			// {
			// 	// Проверяем, не лежит ли прямая внутри сектора
			// 	vertex5 = (t_vector3){
			// 		(sector->vertex[sector->vertex_count - 1]->x + v.x) / 2, \
			// 		(sector->vertex[sector->vertex_count - 1]->y + v.y) / 2, \
			// 		0, 0
			// 	};
			// 	// Скорее всего, нужно добавить рекурсию.
			// 	// > ввести для ft_sector_check_cross разные returns:
			// 	// 0: нет пересечений, 1: точка внутри сектора, 2: есть точка на линии

			// 	return (1);
			// }
			// else
			return (0);
		}

		// ft_check_point_in_line_segment -> standart function
		if (ft_check_point_in_line_segment(v, vertex3, vertex4))
			return (2);

		// debug
		// printf("%f   %f   %f   %f   %f   %f   %f   %f\n", 0.0, 0.0, v.x, v.y, vertex3.x, vertex3.y, vertex4.x, vertex4.y);

		// ft_check_div -> standart function
		if (!ft_check_div(
			0.0,
			0.0,
			v.x,
			v.y,
			vertex3.x,
			vertex3.y,
			vertex4.x,
			vertex4.y
		))
		{
			// count++;
			i++;
			continue;
		}
		
		// ft_find_intersect -> standart function
		p = ft_find_intersect(
			0.0,
			0.0,
			v.x,
			v.y,
			vertex3.x,
			vertex3.y,
			vertex4.x,
			vertex4.y
		);

		// ft_check_point_in_line_segment -> standart function
		if (
			ft_check_point_in_line_segment(p, vertex3, vertex4) &&
			ft_check_point_in_line_segment(p, (t_vector3){0.0, 0.0, 0.0, 0.0}, v)
			//!ft_check_point_in_line_segment(p, *ptr_sector->vertex[0], w->pl.pos)
		)
		{
			count++;
		}

		i++;
	}

	// printf("count: %d\n", count);

	if (count % 2 == 0)
		return (0);
	return (1);
}


int		ft_new_sector_check_sector(void *a, t_vector3 v)
{
	t_wolf3d	*w;
	t_list		*ptr_list;
	t_sector	*ptr_sector;
	int			i;

	w = (t_wolf3d*)a;

	ptr_list = w->sector;
	i = 0;
	while (ptr_list)
	{
		ptr_sector = ptr_list->content;

		if (ptr_sector->status == 0)
		{
			ptr_list = ptr_list->next;
			i++;
			continue ;
		}
		if (ft_new_sector_check_cross(w, ptr_sector, v))
			return (ptr_sector->id);

		ptr_list = ptr_list->next;
		i++;
	}
	return (0);
}






// ft_t_ui_coord_to_t_vector3(t_ui_coord c)


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
	t_vector3	vector;
	t_vector3	temp_vector;
	t_sector	*s;
	double		d;
	t_vector3	temp_vertex_1;
	t_vector3	temp_vertex_2;
	t_vector3	temp_vertex_3;
	t_vector3	check_vector;	// для проверки (по часовой / против часовой)

	t_vector3	pos;

	t_list		*list;

	t_vector3	i; // intersect point

	// Сохранять указатель на win_map в начале программы
	list = ft_gui_search_elem_by_name(w->gui.dom, "win_map");


	if (w->sector == NULL)
	{
		printf("check 1\n");
		return (1);
	}

	// Временно отключено
	/*if (ft_new_sector_check_sector(w, w->mouse_pos)) // check sector intersect
	{
		printf("check 2\n");
		return (0);
	}*/

	s = w->sector->content;
	// Если нет режима, то выходим из проверки
	if (s->status == 1)
	{
		printf("check 3\n");
		return (1);
	}
	// Если точек меньше 3, нет смысла проверять
	if (s->vertex_count < 3)
	{
		printf("check 4\n");
		return (1);
	}


	// temp_vertex_1 = *s->vertex[0];
	// temp_vertex_2 = *s->vertex[1];
	// check_vector = (t_vector3){
	// 	temp_vertex_2.x - temp_vertex_1.x,
	// 	temp_vertex_2.y - temp_vertex_1.y,
	// 	0, 0
	// };

	pos = ft_gui_map_coord_to_vertex(w, (t_gui_rect){0, 0, 0, 0}, w->gui.mouse_pos);

	// first check
	temp_vertex_1 = *s->vertex[s->vertex_count - 1];
	vector = (t_vector3){
		pos.x - temp_vertex_1.x,
		pos.y - temp_vertex_1.y,
		0, 0
	};
	temp_vertex_2 = *s->vertex[s->vertex_count - 2];
	temp_vector = (t_vector3){
		temp_vertex_1.x - temp_vertex_2.x,
		temp_vertex_1.y - temp_vertex_2.y,
		0, 0
	};
	d = vector.x * temp_vector.y - temp_vector.x * vector.y;
	// if ((check_vector.x > 0.0 && check_vector.y >= 0) || (check_vector.x < 0.0 && check_vector.y < 0))
	// 	d *= (-1);
	if (d < 0.0)
	{
		printf("check 5\n");
		printf("v1.x%f   v1.y%f   v2.x%f   v2.y%f\n", vector.x, vector.y, temp_vector.x, temp_vector.y);
		return (0);
	}



	// check 2
	temp_vertex_2 = *s->vertex[0];
	temp_vector = (t_vector3){
		temp_vertex_1.x - temp_vertex_2.x,
		temp_vertex_1.y - temp_vertex_2.y,
		0, 0
	};
	d = vector.x * temp_vector.y - temp_vector.x * vector.y;
	// if ((check_vector.x > 0.0 && check_vector.y >= 0) || (check_vector.x < 0.0 && check_vector.y < 0))
	// {
	// 	printf("%d\t%d\n", (int)check_vector.x, (int)check_vector.y);
	// 	d *= (-1);
	// }
	if (d < 0.0)
	{
		printf("check 6\n");
		return (0);
	}



	// check 3 (intersect)
	temp_vertex_1 = *s->vertex[1];
	temp_vertex_3 = *s->vertex[s->vertex_count - 1];
	i = ft_find_intersect(
		temp_vertex_1.x, temp_vertex_1.y, \
		temp_vertex_2.x, temp_vertex_2.y, \
		temp_vertex_3.x, temp_vertex_3.y, \
		pos.x, pos.y
	);

	if(ft_check_point_in_line_segment(i, temp_vertex_3, pos))
	{
		printf("check 7\n");
		return (0);
	}

	printf("check 8\n");
	return (1);
}