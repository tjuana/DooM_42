/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dorange- <dorange-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/10 16:34:19 by dorange-          #+#    #+#             */
/*   Updated: 2020/01/13 18:10:35 by dorange-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

void	ft_editor_draw_line(t_wolf3d *w)
{
	int			i;

	i = w->ui_map.v1.x;
	while (i < w->ui_map.v2.y)
	{
		ft_fdf_wu_color(
			&(t_vector3){w->ui_map.v1.x, i, 0, 0}, \
			&(t_vector3){w->ui_map.v2.x, i, 0, 0}, \
			w, \
			0x333333 \
		);
		i += 32;
	}
	i = w->ui_map.v1.y;
	while (i < w->ui_map.v2.x)
	{
		ft_fdf_wu_color(
			&(t_vector3){i, w->ui_map.v1.y, 0, 0}, \
			&(t_vector3){i, w->ui_map.v2.y, 0, 0}, \
			w, \
			0x333333 \
		);
		i += 32;
	}
}

t_sector	*ft_editor_search_sector_by_id(t_wolf3d *w, t_list *list, int i)
{
	t_sector	*sector;
	while (list)
	{
		sector = list->content;
		if (sector->id == i)
			return ((t_sector*)(list->content));
		list = list->next;
	}
	return (NULL);
}

void	ft_editor_map_fill_active_sector(t_wolf3d *w, t_vector3 v)
{
	int			n;
	int			x;
	int			y;
	int			pos;
	int			color;
	t_sector	*sector;

	n = ft_sector_check_sector(w, v);
	if (n == 0)
		return ;
	sector = ft_editor_search_sector_by_id(w, w->sector, n);
	y = sector->elem_2d.v1.y;
	while (y <= sector->elem_2d.v2.y)
	{
		x = sector->elem_2d.v1.x;
		while (x <= sector->elem_2d.v2.x)
		{
			if (ft_sector_check_cross(w, sector, (t_vector3){x, y, 0, 0}))
			{
				pos = x + (y * WIN_WIDTH);
				color = ft_fdf_get_color(0xffff00, (int)w->sdl->pixels[pos], 0.7);
				w->sdl->pixels[pos] = color;
			}
			x++;
		}
		y++;
	}
}

void	ft_editor_map_fill_sectors(t_wolf3d *w)
{
	int	y;
	int	x;
	int	color;
	int	pos;

	y = w->ui_map.v1.y;
	while (y < w->ui_map.v2.y)
	{
		x = w->ui_map.v1.x;
		while (x < w->ui_map.v2.x)
		{
			if (ft_sector_check_sector(w, (t_vector3){x, y, 0, 0}))
			{
				pos = x + (y * WIN_WIDTH);
				color = ft_fdf_get_color(0xffff00, (int)w->sdl->pixels[pos], 0.7);
				w->sdl->pixels[pos] = color;
			}
			x++;
		}
		y++;
	}
}

void		ft_editor_font_draw_sector_item(t_wolf3d *w, t_sector *sector, t_ui_coord c)
{
	char	*str;

	ft_font_preset_sc(w, 18, sector->color);
	ft_font_putstr_sdl(w, "Sector", c);

	c.x += 70;
	str = ft_itoa(sector->id);
	ft_font_putstr_sdl(w, str, c);
	free(str);

	c.x -= 70;
	c.y += 25;
	ft_font_preset_sc(w, 14, 0xdddddd);
	ft_font_putstr_sdl(w, "floor:", c);

	c.x += 50;
	str = ft_itoa(sector->floor);
	ft_font_putstr_sdl(w, str, c);
	free(str);

	c.x += 25;
	ft_font_putstr_sdl(w, "height:", c);

	c.x += 55;
	str = ft_itoa(sector->height);
	ft_font_putstr_sdl(w, str, c);
	free(str);

	if (sector->status == 1)
	{
		c.x = sector->elem_2d.v1.x + sector->elem_2d.w / 2;
		c.y = sector->elem_2d.v1.y + sector->elem_2d.h / 2;
		str = ft_itoa(sector->id);
		ft_font_putstr_sdl(w, str, c);
		free(str);
	}
}

void		ft_editor_font_draw_sector_list(t_wolf3d *w, t_list *sector, int i)
{
	t_ui_coord	c;

	if (sector)
	{
		ft_editor_font_draw_sector_list(w, sector->next, i + 1);
		c = (t_ui_coord){1740, 200 + i * 50, 0};
		ft_editor_font_draw_sector_item(w, (t_sector*)sector->content, c);
	}
}

void	ft_editor_draw_sector_to_elem(t_wolf3d *w, t_sector *s)
{
	int	x;
	int	y;
	int	pos;
	int	color;

	if (s == NULL)
		return ;

	y = w->ui_act_s_floor.v1.y;
	while (y <= w->ui_act_s_floor.v2.y)
	{
		x = w->ui_act_s_floor.v1.x;
		while (x <= w->ui_act_s_floor.v2.x)
		{
			pos = x + (y * WIN_WIDTH);
			color = ft_fdf_get_color(0xff0000, (int)w->sdl->pixels[pos], 0.7);
			w->sdl->pixels[pos] = color;
			x++;
		}
		y++;
	}

	y = w->ui_act_s_wall.v1.y;
	while (y <= w->ui_act_s_wall.v2.y)
	{
		x = w->ui_act_s_wall.v1.x;
		while (x <= w->ui_act_s_wall.v2.x)
		{
			pos = x + (y * WIN_WIDTH);
			color = ft_fdf_get_color(0x00ff00, (int)w->sdl->pixels[pos], 0.7);
			w->sdl->pixels[pos] = color;
			x++;
		}
		y++;
	}

	y = w->ui_act_s_ceil.v1.y;
	while (y <= w->ui_act_s_ceil.v2.y)
	{
		x = w->ui_act_s_ceil.v1.x;
		while (x <= w->ui_act_s_ceil.v2.x)
		{
			pos = x + (y * WIN_WIDTH);
			color = ft_fdf_get_color(0x0000ff, (int)w->sdl->pixels[pos], 0.7);
			w->sdl->pixels[pos] = color;
			x++;
		}
		y++;
	}

	// 2 варианта:
	// -- отрисовывать сектор в изометрической (или иной) проекции
	// -- отрисовывать псевдопроекцию, демонстрирующую текстуры пола и потолка



	// ft_fdf_wu_color( \
	// 	&(t_vector3){1800, 100, 0, 0}, \
	// 	&(t_vector3){1830, 130, 0, 0}, \
	// 	w, \
	// 	0xff0000 \
	// );
}

void		ft_editor_draw_txtr_opt_elem_draw(t_wolf3d *w)
{
	if (w->ui_txtr_opt.status == 0)
		return ;
	ft_editor_fill_elem(w, w->ui_txtr_opt, 0xffffff);
	if (ft_editor_check_event_area(w->mouse_pos, w->ui_txtr_opt_close))
		ft_editor_fill_elem(w, w->ui_txtr_opt_close, 0xff2400);
	else
		ft_editor_fill_elem(w, w->ui_txtr_opt_close, 0xcc0605);
}

void		ft_editor_draw_txtr_opt_elem_font(t_wolf3d *w)
{
	t_ui_coord	c;

	if (w->ui_txtr_opt.status == 0)
		return ;
	c = w->ui_txtr_opt.v1;
	c.x += 5;
	c.y += 5;
	ft_font_preset_sc(w, 14, 0x333333);
	ft_font_putstr_sdl(w, "Select a texture:", c);
}

/*
** **************************************************************************
**	void ft_editor_renderer(t_wolf3d *wolf)
**
**	Function that render all images to window.
** **************************************************************************
*/

void	ft_editor_renderer(t_wolf3d *wolf)
{
	ft_bzero(wolf->sdl->pixels, 4 * WIN_WIDTH * WIN_HEIGHT);
	SDL_SetRenderDrawColor(wolf->sdl->renderer, 0x00, 0x00, 0x00, 0xff);
	SDL_RenderClear(wolf->sdl->renderer);

	ft_editor_draw_line(wolf);
	ft_editor_draw_map_2d(wolf, wolf->sector);

	ft_editor_draw_sector_to_elem(wolf, wolf->act_s);

	// ft_editor_threading(wolf); // sectors color fill
	// ft_editor_map_fill_sectors(wolf);

	if (ft_editor_check_event_area_map(wolf, wolf->mouse_pos))
	{
		ft_editor_draw_mouse_vertex(wolf);
		ft_editor_map_fill_active_sector(wolf, wolf->mouse_pos);
		if (wolf->sector_status == 1)
		{
			if (!ft_sector_check_sector(wolf, wolf->mouse_pos))
				ft_editor_sector_draw_line_to_vertex(wolf);
		}
	}

	ft_editor_draw_txtr_opt_elem_draw(wolf);

	SDL_UpdateTexture(wolf->sdl->text, 0, wolf->sdl->pixels, WIN_WIDTH * 4);
	SDL_RenderCopy(wolf->sdl->renderer, wolf->sdl->text, NULL, NULL);

	ft_editor_font_draw_sector_list(wolf, wolf->sector, 0); // draw sector list
	ft_editor_mouse_move_act_s_mark(wolf); // mark
	ft_editor_draw_txtr_opt_elem_font(wolf);

	// ft_editor_draw_txtr_opt_elem_draw(wolf); // mark

	// TTF_CloseFont(wolf->sdl->font.ptr);
	SDL_RenderPresent(wolf->sdl->renderer);
}