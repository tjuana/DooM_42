/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   editor_gui_elem_event_list.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dorange- <dorange-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/16 14:41:00 by dorange-          #+#    #+#             */
/*   Updated: 2020/01/24 16:36:36 by dorange-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
**	[!] [TEMPORARY]
**	
**	It's temporary list with some events.
*/

/*
	Продумать систематизацию и упрощение ряда функций.

	Возможно, стоит добавить структуру, следящую за всеми
	действиями пользователя.

	Возможно, стоит добавить листы, хранящие каждое действие пользователя.
	(Любое прямое действие пользователя может быть лишь созидательным).
*/

#include "wolf3d.h"

void	ft_gui_mousebuttonup_win_menu_btnsector(void *data, SDL_Event e, t_list *dom, int type)
{
	t_wolf3d	*w;
	t_list	*list;

	w = (t_wolf3d*)data;
	ft_gui_elem_set_status(ft_gui_search_elem_by_name(w->gui.dom, "win_menu"), GUI_ELEM_HIDDEN);
	ft_gui_elem_set_status(ft_gui_search_elem_by_name(w->gui.dom, "win_setsector"), GUI_ELEM_VISIBLE);
	// ft_gui_print_element_list(w->gui.dom, 0);
	w->gui.mode = GUI_MD_ME_SET_SECTOR;
	w->sector_status = 0;

	// Меняем порядок действий
	if (w->sector_status == 0)
	{
		ft_editor_sector_create(w);
		w->sector_count++;
		w->sector_status = 1;
	}
}

void	ft_gui_mousebuttonup_win_menu_btnplayer(void *data, SDL_Event e, t_list *dom, int type)
{
	t_wolf3d	*w;
	t_list	*list;

	w = (t_wolf3d*)data;
	ft_gui_elem_set_status(ft_gui_search_elem_by_name(w->gui.dom, "win_menu"), GUI_ELEM_HIDDEN);
	ft_gui_elem_set_status(ft_gui_search_elem_by_name(w->gui.dom, "win_setplayer"), GUI_ELEM_VISIBLE);
	w->gui.mode = GUI_MD_ME_SET_PLAYER;
	w->player_status = 0;
}

void	ft_gui_mousebuttonup_win_menu_btnsprite(void *data, SDL_Event e, t_list *dom, int type)
{
	t_wolf3d	*w;
	t_list	*list;

	w = (t_wolf3d*)data;
	ft_gui_elem_set_status(ft_gui_search_elem_by_name(w->gui.dom, "win_menu"), GUI_ELEM_HIDDEN);
	ft_gui_elem_set_status(ft_gui_search_elem_by_name(w->gui.dom, "win_setsprite"), GUI_ELEM_VISIBLE);
	w->gui.mode = GUI_MD_ME_SET_SPRITE;
	w->sprite_status = 0;
}

void	ft_gui_mousebuttonup_win_menu_btnenemy(void *data, SDL_Event e, t_list *dom, int type)
{
	t_wolf3d	*w;
	t_list	*list;

	w = (t_wolf3d*)data;
	ft_gui_elem_set_status(ft_gui_search_elem_by_name(w->gui.dom, "win_menu"), GUI_ELEM_HIDDEN);
	ft_gui_elem_set_status(ft_gui_search_elem_by_name(w->gui.dom, "win_setenemy"), GUI_ELEM_VISIBLE);
	w->gui.mode = GUI_MD_ME_SET_ENEMY;
	w->enemy_status = 0;
}

void	ft_gui_mousebuttonup_win_menu_btndoor(void *data, SDL_Event e, t_list *dom, int type)
{
	t_wolf3d	*w;
	t_list	*list;

	w = (t_wolf3d*)data;
	ft_gui_elem_set_status(ft_gui_search_elem_by_name(w->gui.dom, "win_menu"), GUI_ELEM_HIDDEN);
	ft_gui_elem_set_status(ft_gui_search_elem_by_name(w->gui.dom, "win_setdoor"), GUI_ELEM_VISIBLE);
	w->gui.mode = GUI_MD_ME_SET_DOOR;
	w->door_status = 0;
	ft_create_sector_door(w);
}


void	ft_gui_mousebuttonup_win_menu_btnsavemap(void *data, SDL_Event e, t_list *dom, int type)
{
	t_wolf3d	*w;

	w = (t_wolf3d*)data;
	w->file.name = ft_gui_elem_get_value(ft_gui_search_elem_by_name(w->gui.dom, "win_menu_inputmapname"));
	ft_save_the_file(w);
}

void	ft_gui_mousebuttonup_win_setsector_walltxtr(void *data, SDL_Event e, t_list *dom, int type)
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
		v2 = (t_gui_coord){elem->v1.x + c.x + width, elem->v1.y + c.y + height, 0};

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


// save change
void	ft_gui_mousebuttonup_win_setsector_btnsavemap(void *data, SDL_Event e, t_list *dom, int type)
{
	t_wolf3d	*w;
	t_list		*list;
	t_sector	*s;

	w = (t_wolf3d*)data;
	ft_gui_elem_set_status(ft_gui_search_elem_by_name(w->gui.dom, "win_setsector"), GUI_ELEM_HIDDEN);
	ft_gui_elem_set_status(ft_gui_search_elem_by_name(w->gui.dom, "win_menu"), GUI_ELEM_VISIBLE);
	w->gui.mode = GUI_MD_ME;
	w->sector_status = 0;
	s = w->sector->content;
	// Считываем значения
	s->height = ft_atoi(ft_gui_elem_get_value(ft_gui_search_elem_by_name(w->gui.dom, "win_setsector_inputheight")));
	s->floor = ft_atoi(ft_gui_elem_get_value(ft_gui_search_elem_by_name(w->gui.dom, "win_setsector_inputfloor")));
	ft_map_set_new_sector(w, s); // Сохраняем данные
}

void	ft_gui_mousebuttonup_win_setplayer_btnsaveplayer(void *data, SDL_Event e, t_list *dom, int type)
{
	t_wolf3d	*w;
	t_list	*list;

	w = (t_wolf3d*)data;
	ft_gui_elem_set_status(ft_gui_search_elem_by_name(w->gui.dom, "win_setplayer"), GUI_ELEM_HIDDEN);
	ft_gui_elem_set_status(ft_gui_search_elem_by_name(w->gui.dom, "win_menu"), GUI_ELEM_VISIBLE);
	w->gui.mode = GUI_MD_ME;
}

void	ft_gui_mousebuttonup_win_setsprite_btnsaveplayer(void *data, SDL_Event e, t_list *dom, int type)
{
	t_wolf3d	*w;
	t_list	*list;

	w = (t_wolf3d*)data;
	ft_gui_elem_set_status(ft_gui_search_elem_by_name(w->gui.dom, "win_setsprite"), GUI_ELEM_HIDDEN);
	ft_gui_elem_set_status(ft_gui_search_elem_by_name(w->gui.dom, "win_menu"), GUI_ELEM_VISIBLE);
	w->gui.mode = GUI_MD_ME;
}

void	ft_gui_mousebuttonup_win_setenemy_btnsaveplayer(void *data, SDL_Event e, t_list *dom, int type)
{
	t_wolf3d	*w;
	t_list	*list;

	w = (t_wolf3d*)data;
	ft_gui_elem_set_status(ft_gui_search_elem_by_name(w->gui.dom, "win_setenemy"), GUI_ELEM_HIDDEN);
	ft_gui_elem_set_status(ft_gui_search_elem_by_name(w->gui.dom, "win_menu"), GUI_ELEM_VISIBLE);
	w->gui.mode = GUI_MD_ME;
}

void	ft_gui_mousebuttonup_win_setdoor_btnsave(void *data, SDL_Event e, t_list *dom, int type)
{
	t_wolf3d	*w;
	t_list	*list;
	t_sector	*s;

	w = (t_wolf3d*)data;
	s = w->sector->content;
	ft_map_set_new_sector(w, s);

	s->status = SECTOR_STATUS_SET;
	ft_gui_elem_set_status(ft_gui_search_elem_by_name(w->gui.dom, "win_setdoor"), GUI_ELEM_HIDDEN);
	ft_gui_elem_set_status(ft_gui_search_elem_by_name(w->gui.dom, "win_menu"), GUI_ELEM_VISIBLE);
	w->gui.mode = GUI_MD_ME;
}



// cancel change
void	ft_gui_mousebuttonup_win_setsector_btncancel(void *data, SDL_Event e, t_list *dom, int type)
{
	t_wolf3d	*w;
	t_list	*list;

	w = (t_wolf3d*)data;
	ft_gui_elem_set_status(ft_gui_search_elem_by_name(w->gui.dom, "win_setsector"), GUI_ELEM_HIDDEN);
	ft_gui_elem_set_status(ft_gui_search_elem_by_name(w->gui.dom, "win_menu"), GUI_ELEM_VISIBLE);
	w->gui.mode = GUI_MD_ME;
	if (w->sector == NULL)
		return ;
	if (w->sector_status == 0 && ((t_sector*)w->sector->content)->status == 1)
		return ;
	
	// delete last sector (?)
	ft_delete_sector(w);
	w->sector_status = 0;
}

void	ft_gui_mousebuttonup_win_setplayer_btncancel(void *data, SDL_Event e, t_list *dom, int type)
{
	t_wolf3d	*w;
	t_list	*list;

	w = (t_wolf3d*)data;
	ft_gui_elem_set_status(ft_gui_search_elem_by_name(w->gui.dom, "win_setplayer"), GUI_ELEM_HIDDEN);
	ft_gui_elem_set_status(ft_gui_search_elem_by_name(w->gui.dom, "win_menu"), GUI_ELEM_VISIBLE);
	w->gui.mode = GUI_MD_ME;

	w->player_status = 0;
}

void	ft_gui_mousebuttonup_win_setsprite_btncancel(void *data, SDL_Event e, t_list *dom, int type)
{
	t_wolf3d	*w;
	t_list	*list;

	w = (t_wolf3d*)data;
	ft_gui_elem_set_status(ft_gui_search_elem_by_name(w->gui.dom, "win_setsprite"), GUI_ELEM_HIDDEN);
	ft_gui_elem_set_status(ft_gui_search_elem_by_name(w->gui.dom, "win_menu"), GUI_ELEM_VISIBLE);
	w->gui.mode = GUI_MD_ME;
	if (w->sprite == NULL)
		return ;
	if (w->sprite_status == 0 && ((t_sector*)w->sprite->content)->status == 1)
		return ;
	ft_delete_sprite(w);
}

void	ft_gui_mousebuttonup_win_setenemy_btncancel(void *data, SDL_Event e, t_list *dom, int type)
{
	t_wolf3d	*w;
	t_list	*list;

	w = (t_wolf3d*)data;
	ft_gui_elem_set_status(ft_gui_search_elem_by_name(w->gui.dom, "win_setenemy"), GUI_ELEM_HIDDEN);
	ft_gui_elem_set_status(ft_gui_search_elem_by_name(w->gui.dom, "win_menu"), GUI_ELEM_VISIBLE);
	w->gui.mode = GUI_MD_ME;
	if (w->enemy == NULL)
		return ;
	if (w->enemy_status == 0 && ((t_sector*)w->enemy->content)->status == 1)
		return ;
	ft_delete_enemy(w);
}

void	ft_gui_mousebuttonup_win_setdoor_btncancel(void *data, SDL_Event e, t_list *dom, int type)
{
	t_wolf3d	*w;
	t_list	*list;

	w = (t_wolf3d*)data;
	ft_gui_elem_set_status(ft_gui_search_elem_by_name(w->gui.dom, "win_setdoor"), GUI_ELEM_HIDDEN);
	ft_gui_elem_set_status(ft_gui_search_elem_by_name(w->gui.dom, "win_menu"), GUI_ELEM_VISIBLE);
	w->gui.mode = GUI_MD_ME;
	if (w->sector == NULL)
		return ;
	if (w->door_status == 0 && ((t_sector*)w->sector->content)->status == 1)
		return ;

	// delete last sector (?)
	printf("delete door?");
	ft_delete_sector(w);
	w->door_status = 0;
}
