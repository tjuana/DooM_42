/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   editor_event_win_setsector.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dorange- <dorange-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/26 15:17:00 by dorange-          #+#    #+#             */
/*   Updated: 2020/02/07 17:30:25 by dorange-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

void	ft_gui_mousebuttonup_win_setsector_walltxtr(void *data, SDL_Event e, \
			t_list *dom, int type)
{
	t_wolf3d	*w;
	t_list		*list;
	int			i;
	int			width;
	int			height;
	int			margin_x;
	int			margin_y;
	int			max_elem_to_line;
	t_gui_coord	c;
	t_gui_coord	v1;
	t_gui_coord	v2;
	t_gui_elem	*elem;
	t_sector	*s;
	t_txtr		*txtr;

	w = (t_wolf3d*)data;
	elem = dom->content;
	list = w->txtr;
	width = 40;
	height = 40;
	margin_x = 8;
	margin_y = 8;
	max_elem_to_line = (elem->w - margin_x * 2) / width - 1;
	i = 0;
	while (list)
	{
		c = (t_gui_coord){\
			margin_x + (width + margin_x) * (i % max_elem_to_line), \
			margin_y + (height + margin_y) * (i / max_elem_to_line), \
			0};
		v1 = (t_gui_coord){elem->v1.x + c.x, elem->v1.y + c.y, 0};
		v2 = (t_gui_coord){elem->v1.x + c.x + width, \
			elem->v1.y + c.y + height, 0};
		if (ft_gui_check_event_area(w->gui.mouse_pos, v1, v2))
		{
			if (w->sector)
			{
				txtr = list->content;
				s = w->sector->content;
				s->txtr_walls = txtr->id;
			}
			return ;
		}
		i++;
		list = list->next;
	}
}

void	ft_gui_mousebuttonup_win_setsector_btnsavemap(void *data, SDL_Event e, \
			t_list *dom, int type)
{
	t_wolf3d	*w;
	t_list		*list;
	t_sector	*s;

	w = (t_wolf3d*)data;
	ft_gui_elem_set_status(\
		ft_gui_search_elem_by_name(w->gui.dom, "win_editor_setsector"), \
		GUI_ELEM_HIDDEN);
	ft_gui_elem_set_status(\
		ft_gui_search_elem_by_name(w->gui.dom, "win_editor_menu"), \
		GUI_ELEM_VISIBLE);
	w->gui.mode = GUI_MD_ME;
	w->sector_status = 0;
	s = w->sector->content;
	s->height = ft_atoi(\
		ft_gui_elem_get_value(\
		ft_gui_search_elem_by_name(w->gui.dom, \
			"win_editor_setsector_inputheight")));
	s->floor = ft_atoi(\
		ft_gui_elem_get_value(\
		ft_gui_search_elem_by_name(w->gui.dom, \
			"win_editor_setsector_inputfloor")));
	ft_map_set_new_sector(w, s);
}

void	ft_gui_mousebuttonup_win_setsector_btncancel(void *data, SDL_Event e, \
			t_list *dom, int type)
{
	t_wolf3d	*w;
	t_list		*list;

	w = (t_wolf3d*)data;
	ft_gui_elem_set_status(\
		ft_gui_search_elem_by_name(w->gui.dom, "win_editor_setsector"), \
		GUI_ELEM_HIDDEN);
	ft_gui_elem_set_status(\
		ft_gui_search_elem_by_name(w->gui.dom, "win_editor_menu"), \
		GUI_ELEM_VISIBLE);
	w->gui.mode = GUI_MD_ME;
	if (w->sector == NULL)
		return ;
	if (w->sector_status == 0 && ((t_sector*)w->sector->content)->status == 1)
		return ;
	ft_delete_sector(w);
	w->sector_status = 0;
}
