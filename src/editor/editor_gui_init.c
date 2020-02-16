/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   editor_gui_init.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dorange- <dorange-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/20 15:33:59 by dorange-          #+#    #+#             */
/*   Updated: 2020/02/16 12:44:55 by dorange-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

/*
** **************************************************************************
**	void ft_gui_elem_set_map(t_list *list)
** **************************************************************************
*/

void	ft_gui_elem_set_map(t_list *list)
{
	t_gui_elem	*elem;

	elem = list->content;
	elem->type = GUI_MAP;
	ft_gui_elem_set_event(list, ft_gui_mousemotion_win_map, \
		SDL_MOUSEMOTION, 0);
	ft_gui_elem_set_event(list, ft_gui_mousebuttondown_win_map, \
		SDL_MOUSEBUTTONDOWN, 0);
	ft_gui_elem_set_event(list, ft_gui_mousebuttonup_win_map, \
		SDL_MOUSEBUTTONUP, 0);
	ft_gui_elem_set_event(list, ft_gui_mousewheel_win_map, \
		SDL_MOUSEWHEEL, 0);
}

void	ft_editor_gui_init_win_me_1(t_list *head)
{
	t_gui_elem	*win;

	win = head->content;
	ft_gui_elem_init_grid(head, "win_me_map", 1, (t_gui_coord){3, 1});
	ft_gui_elem_set_color(win->child, 0x000000);
	ft_gui_elem_set_map(win->child);
	ft_gui_elem_set_redraw(win->child, ft_gui_draw_map);
	ft_gui_elem_init_grid(head, "win_me_menu", 4, (t_gui_coord){1, 1});
	ft_gui_elem_set_grid(win->child, (t_gui_coord){2, 14}, 10);
	ft_gui_elem_set_color(win->child, 0x151719);
	ft_gui_elem_set_block(win->child);
	ft_gui_init_win_menu(win->child);
	ft_gui_elem_init_grid(head, "win_me_sctr", 4, (t_gui_coord){1, 1});
	ft_gui_elem_set_grid(win->child, (t_gui_coord){2, 14}, 10);
	ft_gui_elem_set_color(win->child, GUI_CL_SECTOR);
	ft_gui_elem_set_block(win->child);
	ft_gui_elem_set_status(win->child, GUI_ELEM_HIDDEN);
	ft_gui_init_win_setsector(win->child);
	ft_gui_elem_init_grid(head, "win_me_pl", 4, (t_gui_coord){1, 1});
	ft_gui_elem_set_grid(win->child, (t_gui_coord){2, 14}, 10);
	ft_gui_elem_set_color(win->child, GUI_CL_PLAYER);
	ft_gui_elem_set_block(win->child);
	ft_gui_elem_set_status(win->child, GUI_ELEM_HIDDEN);
	ft_gui_init_win_setplayer(win->child);
}

/*
** **************************************************************************
**	void ft_editor_gui_init_win_me(t_list *head)
** **************************************************************************
*/

void	ft_editor_gui_init_win_me(t_list *head)
{
	t_gui_elem	*win;

	win = head->content;
	ft_editor_gui_init_win_me_1(head);
	ft_gui_elem_init_grid(head, "win_me_sprt", 4, (t_gui_coord){1, 1});
	ft_gui_elem_set_grid(win->child, (t_gui_coord){2, 14}, 10);
	ft_gui_elem_set_color(win->child, GUI_CL_SPRITE);
	ft_gui_elem_set_block(win->child);
	ft_gui_elem_set_status(win->child, GUI_ELEM_HIDDEN);
	ft_gui_init_win_setsprite(win->child);
	ft_gui_elem_init_grid(head, "win_me_enemy", 4, (t_gui_coord){1, 1});
	ft_gui_elem_set_grid(win->child, (t_gui_coord){2, 14}, 10);
	ft_gui_elem_set_color(win->child, GUI_CL_ENEMY);
	ft_gui_elem_set_block(win->child);
	ft_gui_elem_set_status(win->child, GUI_ELEM_HIDDEN);
	ft_gui_elem_set_parent(head, win->child);
	ft_gui_init_win_setenemy(win->child);
	ft_gui_elem_init_grid(head, "win_me_door", 4, (t_gui_coord){1, 1});
	ft_gui_elem_set_grid(win->child, (t_gui_coord){2, 14}, 10);
	ft_gui_elem_set_color(win->child, GUI_CL_DOOR);
	ft_gui_elem_set_block(win->child);
	ft_gui_elem_set_status(win->child, GUI_ELEM_HIDDEN);
	ft_gui_elem_set_parent(head, win->child);
	ft_gui_init_win_setdoor(win->child);
}

/*
** **************************************************************************
**	void ft_gui_init(t_wolf3d *w)
**
**	Function that set gui.
** **************************************************************************
*/

void	ft_editor_gui_init(t_wolf3d *w)
{
	w->gui.redraw = 0;
	w->gui.redraw_elem = NULL;
	w->gui.search_elem = GUI_EVENT_OFF;
	w->gui_map.grid_scale = 32;
	w->gui_map.v = (t_vector3){-5.2, -5.5, 0, 0};
	w->gui_map.check_vertex = 0;
	w->player_status = 0;
	w->sector_status = 0;
	w->sprite_status = 0;
	w->enemy_status = 0;
	w->sector = NULL;
	w->sprite = NULL;
	w->enemy = NULL;
	w->gui_map.ptr = ft_gui_search_elem_by_name(w->gui.dom, "win_me_map");
}

void	ft_gui_init_win_setsector_1(t_list *head)
{
	t_gui_elem	*elem;

	elem = head->content;
	ft_gui_elem_init_grid(head, "win_me_sctr_title", 1, (t_gui_coord){2, 1});
	ft_gui_elem_set_color(elem->child, 0x000000);
	ft_gui_elem_set_text(elem->child, "Set sector", 16);
	ft_gui_elem_init_grid(head, "win_me_sctr_title", 5, (t_gui_coord){2, 1});
	ft_gui_elem_set_color(elem->child, 0x333333);
	ft_gui_elem_set_text(elem->child, "[Space] -> Save sector", 14);
	ft_gui_elem_init_grid(head, "win_me_sctr_title", 7, (t_gui_coord){2, 1});
	ft_gui_elem_set_color(elem->child, 0x333333);
	ft_gui_elem_set_text(elem->child, "[ESC] -> Cancel", 14);
	ft_gui_elem_init_grid(head, "win_me_sctr_titlef", 17, (t_gui_coord){2, 1});
	ft_gui_elem_set_color(elem->child, 0x000000);
	ft_gui_elem_set_text(elem->child, "Floor:", 16);
	ft_gui_elem_init_grid(head, "win_me_sctr_inputf", 19, (t_gui_coord){2, 1});
	ft_gui_elem_set_color(elem->child, 0x333333);
	ft_gui_elem_set_input(elem->child, "0", 1);
}
