/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   editor_gui_txtr.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dorange- <dorange-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/22 13:56:33 by dorange-          #+#    #+#             */
/*   Updated: 2020/02/07 17:31:29 by dorange-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

void	*ft_editor_redraw_txtr(void *data, t_list *dom)
{
	t_wolf3d	*w;
	t_gui_elem	*elem;
	t_list		*list;
	t_txtr		*txtr;
	int			i;
	t_gui_coord	c;
	int			border_color;
	int			width;
	int			height;
	int			margin_x;
	int			margin_y;
	int			padding_x;
	int			padding_y;
	int			max_elem_to_line;
	int			pos;
	t_gui_coord	v1;
	t_gui_coord	v2;
	t_sector	*s;

	w = (t_wolf3d*)data;
	elem = dom->content;
	list = w->txtr;
	width = 40;
	height = 40;
	margin_x = 8;
	margin_y = 8;
	padding_x = 4;
	padding_y = 4;
	max_elem_to_line = (elem->w - margin_x * 2) / width - 1;
	i = 0;
	if (w->sector)
		s = w->sector->content;
	else
		s = NULL;
	while (list)
	{
		c = (t_gui_coord){\
			margin_x + (width + margin_x) * (i % max_elem_to_line), \
			margin_y + (height + margin_y) * (i / max_elem_to_line), \
			0};

		v1 = (t_gui_coord){elem->v1.x + c.x, elem->v1.y + c.y, 0};
		v2 = (t_gui_coord){elem->v1.x + c.x + width, elem->v1.y + c.y + height, 0};

		txtr = list->content;

		if (ft_gui_check_event_area(w->gui.mouse_pos, v1, v2))
			border_color = 0x888888;
		else
			border_color = 0x333333;

		if (s)
		{
			if (s->txtr_walls == txtr->id)
				border_color = 0xbbbbbb;
		}

		ft_gui_fill_area(w, v1, v2, border_color);
		ft_gui_draw_image_area(w, (t_gui_rect){(t_gui_coord){v1.x + padding_x, v1.y + padding_y, 0}, (t_gui_coord){v2.x - padding_x, v2.y - padding_y, 0}, v2.x - v1.x - padding_x, v2.y - v1.y - padding_y}, txtr->surf);
		ft_gui_fill_area(w, (t_gui_coord){v1.x + padding_x, v1.y + padding_y, 0}, \
			(t_gui_coord){v2.x - padding_x, v2.y - padding_y, 0}, \
			txtr->color);
		i++;
		list = list->next;
	}
	return (NULL);
}
