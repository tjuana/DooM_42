/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dorange- <dorange-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/10 19:06:08 by dorange-          #+#    #+#             */
/*   Updated: 2020/01/13 20:42:50 by dorange-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

int		ft_editor_check_mouse_vertex_pos(t_wolf3d *w, int x, int y)
{
	int			x_s;
	int			y_s;

	SDL_GetMouseState(&x, &y);
	if ((x < 0 || x >= WIN_WIDTH) ||
		(y < 0 || y >= WIN_HEIGHT))
		return (0);
	x_s = ((int)(x - 20) % E_GRID_L);
	y_s = ((int)(y - 20) % E_GRID_L);
	if ((x_s < E_GRID_V_D || x_s > E_GRID_L - E_GRID_V_D) && \
		(y_s < E_GRID_V_D || y_s > E_GRID_L - E_GRID_V_D))
		return (1);
	return (0);
}

void	ft_editor_mouse_move_map(t_wolf3d *w)
{
	if (ft_editor_check_mouse_vertex_pos(w, w->mouse_pos.x, w->mouse_pos.y))
	{
		w->mouse_vertex = (t_vector3){
			(20 + ((int)w->mouse_pos.x + E_GRID_V_D - 20) / E_GRID_L * E_GRID_L), \
			(20 + ((int)w->mouse_pos.y + E_GRID_V_D - 20) / E_GRID_L * E_GRID_L), \
			0, 1
		};
		w->mouse_pos = w->mouse_vertex;
	}
	else
		w->mouse_vertex = (t_vector3){0, 0, 0, 0};
}

int		ft_editor_check_event_area(t_vector3 v, t_ui_elem c)
{
	return (v.x >= c.v1.x && v.x < c.v2.x && v.y >= c.v1.y && v.y < c.v2.y && c.status);
}

int		ft_editor_check_event_area_map(t_wolf3d *w, t_vector3 v)
{
	if (
		(int)v.x >= w->ui_map.v1.x - 4 &&
		(int)v.x < w->ui_map.v2.x + 4 &&
		(int)v.y >= w->ui_map.v1.y - 4 &&
		(int)v.y < w->ui_map.v2.y + 4
	)
		return (1);
	return (0);
}

int		ft_editor_check_event_area_act_s(t_wolf3d *w, t_vector3 v)
{
	if (
		(int)v.x >= w->ui_act_s.v1.x &&
		(int)v.x < w->ui_act_s.v2.x &&
		(int)v.y >= w->ui_act_s.v1.y &&
		(int)v.y < w->ui_act_s.v2.y
	)
		return (1);
	return (0);
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
	ft_bzero(p, sizeof(t_vector3));
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

int		ft_editor_map_check_area(t_wolf3d *w)
{
	t_vector3	vector;
	t_vector3	temp_vector;
	t_sector	*sector;
	double		d;
	t_vector3	temp_vertex_1;
	t_vector3	temp_vertex_2;
	t_vector3	temp_vertex_3;
	t_vector3	check_vector;	// для проверки (по часовой / против часовой)

	t_vector3	i; // intersect point

	if (w->sector == NULL)
		return (1);
	if (ft_sector_check_sector(w, w->mouse_pos)) // check sector intersect
		return (0);

	sector = w->sector->content;
	if (sector->status == 1)
		return (1);
	if (sector->vertex_count < 3)
		return (1);

	temp_vertex_1 = ft_editor_map_get_xy_vertex_pos(w, *sector->vertex[0]);
	temp_vertex_2 = ft_editor_map_get_xy_vertex_pos(w, *sector->vertex[1]);
	check_vector = (t_vector3){
		temp_vertex_2.x - temp_vertex_1.x,
		temp_vertex_2.y - temp_vertex_1.y,
		0, 0
	};

	// first check
	temp_vertex_1 = ft_editor_map_get_xy_vertex_pos(w, *sector->vertex[sector->vertex_count - 1]);
	vector = (t_vector3){
		w->mouse_pos.x - temp_vertex_1.x,
		w->mouse_pos.y - temp_vertex_1.y,
		0, 0
	};
	temp_vertex_2 = ft_editor_map_get_xy_vertex_pos(w, *sector->vertex[sector->vertex_count - 2]);
	temp_vector = (t_vector3){
		temp_vertex_1.x - temp_vertex_2.x,
		temp_vertex_1.y - temp_vertex_2.y,
		0, 0
	};
	d = vector.x * temp_vector.y - temp_vector.x * vector.y;
	// if ((check_vector.x > 0.0 && check_vector.y >= 0) || (check_vector.x < 0.0 && check_vector.y < 0))
	// 	d *= (-1);
	if (d < 0.0)
		return (0);



	// check 2
	temp_vertex_2 = ft_editor_map_get_xy_vertex_pos(w, *sector->vertex[0]);
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
		return (0);



	// check 3 (intersect)
	temp_vertex_1 = ft_editor_map_get_xy_vertex_pos(w, *sector->vertex[1]);
	temp_vertex_3 = ft_editor_map_get_xy_vertex_pos(w, *sector->vertex[sector->vertex_count - 1]);
	i = ft_find_intersect(
		temp_vertex_1.x, temp_vertex_1.y, \
		temp_vertex_2.x, temp_vertex_2.y, \
		temp_vertex_3.x, temp_vertex_3.y, \
		w->mouse_pos.x, w->mouse_pos.y
	);

	if(ft_check_point_in_line_segment(i, temp_vertex_3, w->mouse_pos))
		return (0);

	return (1);
}

// ?!
void	ft_editor_sector_draw_line_to_vertex(t_wolf3d *w)
{
	t_sector	*sector;
	t_vector3	c;

	if (w->sector == NULL)
	{
		w->sector_status = 0;
		return ;
	}
	sector = w->sector->content;
	c = ft_editor_map_get_xy_vertex_pos(w, *sector->vertex[sector->vertex_count - 1]);

	if (sector->vertex_count > 2)
	{
		if (!ft_editor_map_check_area(w))
			return ; // t_vector3
	}

	if (w->mouse_vertex.w == 1)
	{
		ft_fdf_wu_color(&w->mouse_vertex, &c, w, 0xCCCCCC);
	}
	else
		ft_fdf_wu_color(&(t_vector3){w->mouse_pos.x, w->mouse_pos.y, 0, 0}, &c, w, 0xCCCCCC);
}

void	ft_editor_mouse_click_txtr_opt_close(t_wolf3d *w, SDL_Event e)
{
	w->ui_txtr_opt.status = 0;
	w->ui_txtr_opt_close.status = 0;
}

void	ft_editor_mouse_click_txtr_opt(t_wolf3d *w, SDL_Event e)
{
	w->ui_txtr_opt.trigger = 2;
	return ;
}

void	ft_editor_mouse_btn_up_txtr_opt(t_wolf3d *w, SDL_Event e)
{
	w->ui_txtr_opt.trigger = 0;
	return ;
}

void	ft_editor_mouse_click_map(t_wolf3d *w, SDL_Event e)
{
	int			x;
	int			y;
	int			x_c;
	int			y_c;
	t_sector	*sector;

	int			n;

	x = 0;
	y = 0;
	SDL_GetMouseState(&x, &y);

	n = ft_sector_check_sector(w, w->mouse_pos);
	if (n > 0)
	{
		sector = ft_editor_search_sector_by_id(w, w->sector, n);
		if (w->act_s == sector)
			w->act_s = NULL;
		else
			w->act_s = sector;
	}

	if (ft_editor_check_mouse_vertex_pos(w, x, y) && ft_editor_map_check_area(w))
	{
		if (w->sector_status == 0)
		{
			w->sector_status = 1;
			ft_editor_sector_create(w);
			w->sector_count++;
		}
		x_c = (int)((x + E_GRID_V_D - 20) / E_GRID_L);
		y_c = (int)((y + E_GRID_V_D - 20) / E_GRID_L);

		ft_editor_sector_set_vertex(w, w->sector->content, (t_vector3){x_c, y_c, 0, 0});

		sector = w->sector->content;
		if (sector->vertex_count > 1 && ft_editor_sector_compare_vertexes(*sector->vertex[0], *sector->vertex[sector->vertex_count - 1]))
		{
			ft_editor_delete_last_vertex(w);
			if (ft_editor_sector_search_neighbors(w, sector))
			{
				sector->status = 1;
				w->sector_status = 0;
				ft_editor_init_sectors_item_area(w, sector);
			}
		}

		printf("===\n");
		ft_editor_sector_special_debug(w->sector);
	}
}

void	ft_editor_mouse_move_act_s_mark(t_wolf3d *w)
{
	t_ui_coord	c;

	if (!ft_editor_check_event_area(w->mouse_pos, w->ui_act_s) || w->act_s == NULL)
		return ;
	ft_font_preset_sc(w, 14, 0xcccccc);
	c = (t_ui_coord){(int)w->mouse_pos.x + 10, (int)w->mouse_pos.y + 10, 0};
	if (ft_editor_check_event_area(w->mouse_pos, w->ui_act_s_floor))
		ft_font_putstr_sdl(w, "floor", c);
	if (ft_editor_check_event_area(w->mouse_pos, w->ui_act_s_wall))
		ft_font_putstr_sdl(w, "wall", c);
	if (ft_editor_check_event_area(w->mouse_pos, w->ui_act_s_ceil))
		ft_font_putstr_sdl(w, "ceil", c);
	// printf("yes! %f %f\n", w->mouse_pos.x, w->mouse_pos.y);
}

void	ft_editor_mouse_click_act_s(t_wolf3d *w, SDL_Event e)
{
	if (w->act_s == NULL)
		return ;
	w->ui_txtr_opt.status = 1;
	w->ui_txtr_opt_close.status = 1;
	if (ft_editor_check_event_area(w->mouse_pos, w->ui_act_s_floor))
		w->txtr_opt_type = 0;
	if (ft_editor_check_event_area(w->mouse_pos, w->ui_act_s_wall))
		w->txtr_opt_type = 1;
	if (ft_editor_check_event_area(w->mouse_pos, w->ui_act_s_ceil))
		w->txtr_opt_type = 2;
}

void	ft_editor_ui_elem_add_offset(t_wolf3d *w, t_ui_elem *elem, int xrel, int yrel)
{
	if (elem->w > WIN_WIDTH || elem->h > WIN_HEIGHT)
		return ;
	elem->v1 = (t_ui_coord){elem->v1.x + xrel, elem->v1.y + yrel, 0};
	elem->v2 = (t_ui_coord){elem->v2.x + xrel, elem->v2.y + yrel, 0};

	if (elem->v1.x < 0)
		ft_editor_ui_elem_add_offset(w, elem, -elem->v1.x, 0);
	if (elem->v2.x > WIN_WIDTH)
		ft_editor_ui_elem_add_offset(w, elem, (WIN_WIDTH - elem->v2.x), 0);

	if (elem->v1.y < 0)
		ft_editor_ui_elem_add_offset(w, elem, 0, -elem->v1.y);
	if (elem->v2.y > WIN_HEIGHT)
		ft_editor_ui_elem_add_offset(w, elem, 0, (WIN_HEIGHT - elem->v2.y));
}

void	ft_editor_mouse_move_txtr_opt(t_wolf3d *w, SDL_Event e)
{
	if (w->ui_txtr_opt.trigger == 2)
	{
		ft_editor_ui_elem_add_offset(w, &w->ui_txtr_opt, e.motion.xrel, e.motion.yrel);
		ft_editor_init_ui_elem_reset(&w->ui_txtr_opt_close, &w->ui_txtr_opt);
		// ft_editor_ui_elem_add_offset(w, &w->ui_txtr_opt_close, e.motion.xrel, e.motion.yrel);
	}
}

void	ft_editor_mouse_click(t_wolf3d *w, SDL_Event e)
{
	int			x;
	int			y;

	x = 0;
	y = 0;
	SDL_GetMouseState(&x, &y);
	w->mouse_pos = (t_vector3){x, y, 0, 0};
	w->mouse_vertex = (t_vector3){0, 0, 0, 0};

	// layers
	if (ft_editor_check_event_area(w->mouse_pos, w->ui_txtr_opt_close))
		ft_editor_mouse_click_txtr_opt_close(w, e);
	else if (ft_editor_check_event_area(w->mouse_pos, w->ui_txtr_opt))
		ft_editor_mouse_click_txtr_opt(w, e);
	else if (ft_editor_check_event_area(w->mouse_pos, w->ui_act_s))
		ft_editor_mouse_click_act_s(w, e);
	else if (ft_editor_check_event_area(w->mouse_pos, w->ui_map))
		ft_editor_mouse_click_map(w, e);
}

void	ft_editor_mouse_btn_up(t_wolf3d *w, SDL_Event e)
{
	int			x;
	int			y;

	x = 0;
	y = 0;
	SDL_GetMouseState(&x, &y);
	w->mouse_pos = (t_vector3){x, y, 0, 0};
	w->mouse_vertex = (t_vector3){0, 0, 0, 0};

	w->ui_txtr_opt.trigger = 0;

	if (ft_editor_check_event_area(w->mouse_pos, w->ui_txtr_opt))
		ft_editor_mouse_btn_up_txtr_opt(w, e);
}

void	ft_editor_mouse_move(t_wolf3d *w, SDL_Event e)
{
	int			x;
	int			y;

	x = 0;
	y = 0;
	SDL_GetMouseState(&x, &y);
	w->mouse_pos = (t_vector3){x, y, 0, 0};
	w->mouse_vertex = (t_vector3){0, 0, 0, 0};

	if (ft_editor_check_event_area(w->mouse_pos, w->ui_txtr_opt_close))
		return ;
	if (ft_editor_check_event_area(w->mouse_pos, w->ui_txtr_opt))
		ft_editor_mouse_move_txtr_opt(w, e);
		// ft_editor_mouse_move_txtr_opt_close(w, e);
	// else if (ft_editor_check_event_area(w->mouse_pos, w->ui_txtr_opt))
	// 	ft_editor_mouse_move_txtr_opt(w, e);
	else if (ft_editor_check_event_area(w->mouse_pos, w->ui_map))
		ft_editor_mouse_move_map(w);
	// if (ft_editor_check_event_area_act_s(w, w->mouse_pos))
		// ft_editor_mouse_move_act_s(w);
}