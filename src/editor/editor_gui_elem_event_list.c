/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   editor_gui_elem_event_list.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dorange- <dorange-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/16 14:41:00 by dorange-          #+#    #+#             */
/*   Updated: 2020/01/20 19:15:49 by dorange-         ###   ########.fr       */
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

void	ft_gui_mousebuttonup_win_menu_btn_sector(void *data, SDL_Event e, t_list *dom, int type)
{
	t_wolf3d	*w;
	t_list	*list;

	w = (t_wolf3d*)data;
	ft_gui_elem_set_status(ft_gui_search_elem_by_name(w->gui.dom, "win_menu"), GUI_ELEM_HIDDEN);
	ft_gui_elem_set_status(ft_gui_search_elem_by_name(w->gui.dom, "win_setsector"), GUI_ELEM_VISIBLE);
	// ft_gui_print_element_list(w->gui.dom, 0);
	w->gui.mode = GUI_MD_ME_SET_SECTOR;
	w->sector_status = 0;
}

void	ft_gui_mousebuttonup_win_menu_btn_player(void *data, SDL_Event e, t_list *dom, int type)
{
	t_wolf3d	*w;
	t_list	*list;

	w = (t_wolf3d*)data;
	ft_gui_elem_set_status(ft_gui_search_elem_by_name(w->gui.dom, "win_menu"), GUI_ELEM_HIDDEN);
	ft_gui_elem_set_status(ft_gui_search_elem_by_name(w->gui.dom, "win_setplayer"), GUI_ELEM_VISIBLE);
	w->gui.mode = GUI_MD_ME_SET_PLAYER;
	w->player_status = 0;
}

void	ft_gui_mousebuttonup_win_menu_btn_sprite(void *data, SDL_Event e, t_list *dom, int type)
{
	t_wolf3d	*w;
	t_list	*list;

	w = (t_wolf3d*)data;
	ft_gui_elem_set_status(ft_gui_search_elem_by_name(w->gui.dom, "win_menu"), GUI_ELEM_HIDDEN);
	ft_gui_elem_set_status(ft_gui_search_elem_by_name(w->gui.dom, "win_setsprite"), GUI_ELEM_VISIBLE);
	w->gui.mode = GUI_MD_ME_SET_SPRITE;
	w->sprite_status = 0;
}

void	ft_gui_mousebuttonup_in_menu_btn_enemy(void *data, SDL_Event e, t_list *dom, int type)
{
	t_wolf3d	*w;
	t_list	*list;

	w = (t_wolf3d*)data;
	ft_gui_elem_set_status(ft_gui_search_elem_by_name(w->gui.dom, "win_menu"), GUI_ELEM_HIDDEN);
	ft_gui_elem_set_status(ft_gui_search_elem_by_name(w->gui.dom, "win_setenemy"), GUI_ELEM_VISIBLE);
	w->gui.mode = GUI_MD_ME_SET_ENEMY;
	w->enemy_status = 0;
}

void	ft_gui_mousebuttonup_win_menu_btnsavemap(void *data, SDL_Event e, t_list *dom, int type)
{
	t_wolf3d	*w;

	w = (t_wolf3d*)data;
	w->file.name = ft_gui_elem_get_value(ft_gui_search_elem_by_name(w->gui.dom, "win_menu_inputmapname"));
	ft_save_the_file(w);
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



// cancel change
void	ft_gui_mousebuttonup_win_setsector_btn_cancel(void *data, SDL_Event e, t_list *dom, int type)
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