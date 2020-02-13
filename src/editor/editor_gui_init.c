/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   editor_gui_init.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dorange- <dorange-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/20 15:33:59 by dorange-          #+#    #+#             */
/*   Updated: 2020/02/13 17:15:07 by dorange-         ###   ########.fr       */
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

/*
** **************************************************************************
**	void ft_gui_init_win_menu_add(t_list *head)
** **************************************************************************
*/

void	ft_gui_init_win_menu_add(t_list *head)
{
	t_gui_elem	*elem;

	elem = head->content;
	ft_gui_elem_init_grid(head, "win_editor_menu_title", 3, (t_gui_coord){1, 2});
	ft_gui_elem_set_color(elem->child, 0xcccccc);
	ft_gui_elem_set_text(elem->child, "Add:", 16);
	ft_gui_elem_init_grid(head, "win_editor_menu_btnsector", 5, (t_gui_coord){1, 1});
	ft_gui_elem_set_color(elem->child, GUI_CL_SECTOR);
	ft_gui_elem_set_button(elem->child, "Sector");
	ft_gui_elem_set_event(elem->child, \
		ft_gui_mousebuttonup_win_menu_btnsector, SDL_MOUSEBUTTONUP, 0);
	ft_gui_elem_init_grid(head, "win_editor_menu_btnplayer", 6, (t_gui_coord){1, 1});
	ft_gui_elem_set_color(elem->child, GUI_CL_PLAYER);
	ft_gui_elem_set_button(elem->child, "Player");
	ft_gui_elem_set_event(elem->child, \
		ft_gui_mousebuttonup_win_menu_btnplayer, SDL_MOUSEBUTTONUP, 0);
	ft_gui_elem_init_grid(head, "win_editor_menu_btndoor", 7, (t_gui_coord){1, 1});
	ft_gui_elem_set_color(elem->child, GUI_CL_DOOR);
	ft_gui_elem_set_button(elem->child, "Door");
	ft_gui_elem_set_event(elem->child, \
		ft_gui_mousebuttonup_win_menu_btndoor, SDL_MOUSEBUTTONUP, 0);
	ft_gui_elem_init_grid(head, "win_editor_menu_btnsprite", 8, (t_gui_coord){1, 1});
	ft_gui_elem_set_color(elem->child, GUI_CL_SPRITE);
	ft_gui_elem_set_button(elem->child, "Sprite");
	ft_gui_elem_set_event(elem->child, \
		ft_gui_mousebuttonup_win_menu_btnsprite, SDL_MOUSEBUTTONUP, 0);
	ft_gui_elem_init_grid(head, "win_editor_menu_btnenemy", 9, (t_gui_coord){1, 1});
	ft_gui_elem_set_color(elem->child, GUI_CL_ENEMY);
	ft_gui_elem_set_button(elem->child, "Enemy");
	ft_gui_elem_set_event(elem->child, \
		ft_gui_mousebuttonup_win_menu_btnenemy, SDL_MOUSEBUTTONUP, 0);
}

/*
** **************************************************************************
**	void ft_gui_init_win_menu_set(t_list *head)
** **************************************************************************
*/

void	ft_gui_init_win_menu_set(t_list *head)
{
	t_gui_elem	*elem;

	elem = head->content;
	ft_gui_elem_init_grid(head, "win_editor_menu_title", 11, (t_gui_coord){1, 2});
	ft_gui_elem_set_color(elem->child, 0xcccccc);
	ft_gui_elem_set_text(elem->child, "Set:", 16);

	ft_gui_elem_init_grid(head, "win_editor_menu_btntxtr", 13, (t_gui_coord){1, 1});
	ft_gui_elem_set_color(elem->child, 0xcccccc);
	ft_gui_elem_set_button(elem->child, "Textures");

	ft_gui_elem_init_grid(head, "win_editor_menu_btnskybox", 14, (t_gui_coord){1, 1});
	ft_gui_elem_set_color(elem->child, 0xcccccc);
	ft_gui_elem_set_button(elem->child, "Skybox");

	ft_gui_elem_init_grid(head, "win_editor_menu_btnendplace", 15, (t_gui_coord){2, 1});
	ft_gui_elem_set_color(elem->child, 0xcccccc);
	ft_gui_elem_set_button(elem->child, "Point to end game");
}

/*
** **************************************************************************
**	void ft_gui_init_win_menu_save(t_list *head)
** **************************************************************************
*/

void	ft_gui_init_win_menu_save(t_list *head)
{
	t_gui_elem	*elem;

	elem = head->content;
	ft_gui_elem_init_grid(head, "win_editor_menu_titleinput", 21, (t_gui_coord){2, 1});
	ft_gui_elem_set_color(elem->child, 0xffffff);
	ft_gui_elem_set_text(elem->child, "Save map as:", 16);
	ft_gui_elem_init_grid(head, "win_editor_menu_inputmapname", 23, (t_gui_coord){2, 1});
	ft_gui_elem_set_color(elem->child, 0xaaaaaa);
	ft_gui_elem_set_input(elem->child, " ", 0);
	ft_gui_elem_init_grid(head, "win_editor_menu_btnendplace", 25, (t_gui_coord){2, 1});
	ft_gui_elem_set_color(elem->child, 0x50c878);
	ft_gui_elem_set_button(elem->child, "Save map");
	ft_gui_elem_set_event(elem->child, \
		ft_gui_mousebuttonup_win_menu_btnsavemap, SDL_MOUSEBUTTONUP, 0);
	ft_gui_elem_init_grid(head, "win_editor_menu_btnmenu", 27, (t_gui_coord){2, 1});
	ft_gui_elem_set_color(elem->child, 0xcccccc);
	ft_gui_elem_set_button(elem->child, "Go to menu");
	ft_gui_elem_set_event(elem->child, \
		ft_gui_mousebuttonup_win_editor_menu_btnmenu, SDL_MOUSEBUTTONUP, 0);
}

/*
** **************************************************************************
**	void ft_gui_init_win_menu(t_list *head)
** **************************************************************************
*/

void	ft_gui_init_win_menu(t_list *head)
{
	t_gui_elem	*elem;

	elem = head->content;
	ft_gui_elem_init_grid(head, "win_menu_btngame", 1, (t_gui_coord){1, 2});
	ft_gui_elem_set_color(elem->child, 0xffffff);
	ft_gui_elem_set_text(elem->child, "M A P   E D I T O R", 16);
	ft_gui_elem_set_parent(head, elem->child);
	ft_gui_init_win_menu_add(head);
	ft_gui_init_win_menu_set(head);
	ft_gui_init_win_menu_save(head);
}

/*
** **************************************************************************
**	void ft_gui_init_win_setsector(t_list *head)
** **************************************************************************
*/

void	ft_gui_init_win_setsector(t_list *head)
{
	t_gui_elem	*elem;

	elem = head->content;
	ft_gui_elem_init_grid(head, "win_editor_setsector_title", 1, (t_gui_coord){2, 1});
	ft_gui_elem_set_color(elem->child, 0x000000);
	ft_gui_elem_set_text(elem->child, "Set sector", 16);
	ft_gui_elem_init_grid(head, "win_editor_setsector_titleinputfloor", 17, (t_gui_coord){2, 1});
	ft_gui_elem_set_color(elem->child, 0x000000);
	ft_gui_elem_set_text(elem->child, "Floor:", 16);
	ft_gui_elem_init_grid(head, "win_editor_setsector_inputfloor", 19, (t_gui_coord){2, 1});
	ft_gui_elem_set_color(elem->child, 0x333333);
	ft_gui_elem_set_input(elem->child, "0", 1);
	ft_gui_elem_init_grid(head, "win_editor_setsector_titleinputheight", 21, (t_gui_coord){2, 1});
	ft_gui_elem_set_color(elem->child, 0x000000);
	ft_gui_elem_set_text(elem->child, "Height:", 16);
	ft_gui_elem_init_grid(head, "win_editor_setsector_inputheight", 23, (t_gui_coord){2, 1});
	ft_gui_elem_set_color(elem->child, 0x333333);
	ft_gui_elem_set_input(elem->child, "0", 1);
	ft_gui_elem_init_grid(head, "win_editor_setsector_btnsavemap", 25, (t_gui_coord){2, 1});
	ft_gui_elem_set_color(elem->child, 0x50c878);
	ft_gui_elem_set_button(elem->child, "Save sector");
	ft_gui_elem_set_event(elem->child, \
		ft_gui_mousebuttonup_win_setsector_btnsavemap, SDL_MOUSEBUTTONUP, 0);
	ft_gui_elem_init_grid(head, "win_editor_setsector_btncancel", 27, (t_gui_coord){2, 1});
	ft_gui_elem_set_color(elem->child, 0xcc0605);
	ft_gui_elem_set_button(elem->child, "Cancel");
	ft_gui_elem_set_event(elem->child, \
		ft_gui_mousebuttonup_win_setsector_btncancel, SDL_MOUSEBUTTONUP, 0);
}

/*
** **************************************************************************
**	void ft_gui_init_win_setplayer(t_list *head)
** **************************************************************************
*/

void	ft_gui_init_win_setplayer(t_list *head)
{
	t_gui_elem	*elem;

	elem = head->content;
	ft_gui_elem_init_grid(head, "win_editor_setplayer_btntitle", 1, (t_gui_coord){2, 1});
	ft_gui_elem_set_color(elem->child, 0x000000);
	ft_gui_elem_set_text(elem->child, "Set player", 16);
	ft_gui_elem_init_grid(head, "win_editor_setplayer_btnsaveplayer", 25, (t_gui_coord){2, 1});
	ft_gui_elem_set_color(elem->child, 0x50c878);
	ft_gui_elem_set_button(elem->child, "Save player");
	ft_gui_elem_set_event(elem->child, \
		ft_gui_mousebuttonup_win_setplayer_btnsaveplayer, SDL_MOUSEBUTTONUP, 0);
	ft_gui_elem_init_grid(head, "win_editor_setplayer_btncancel", 27, (t_gui_coord){2, 1});
	ft_gui_elem_set_color(elem->child, 0xcc0605);
	ft_gui_elem_set_button(elem->child, "Cancel");
	ft_gui_elem_set_event(elem->child, \
		ft_gui_mousebuttonup_win_setplayer_btncancel, SDL_MOUSEBUTTONUP, 0);
}

/*
** **************************************************************************
**	void ft_gui_init_win_setsprite(t_list *head)
** **************************************************************************
*/

void	ft_gui_init_win_setsprite(t_list *head)
{
	t_gui_elem	*elem;

	elem = head->content;
	ft_gui_elem_init_grid(head, "win_editor_setsprite_btntitle", 1, (t_gui_coord){2, 1});
	ft_gui_elem_set_color(elem->child, 0x000000);
	ft_gui_elem_set_text(elem->child, "Set player", 16);
	ft_gui_elem_init_grid(head, "win_editor_setsprite_btnsaveplayer", 25, (t_gui_coord){2, 1});
	ft_gui_elem_set_color(elem->child, 0x50c878);
	ft_gui_elem_set_button(elem->child, "Save player");
	ft_gui_elem_set_event(elem->child, \
		ft_gui_mousebuttonup_win_setsprite_btnsaveplayer, SDL_MOUSEBUTTONUP, 0);
	ft_gui_elem_init_grid(head, "win_editor_setsprite_btncancel", 27, (t_gui_coord){2, 1});
	ft_gui_elem_set_color(elem->child, 0xcc0605);
	ft_gui_elem_set_button(elem->child, "Cancel");
	ft_gui_elem_set_event(elem->child, \
		ft_gui_mousebuttonup_win_setsprite_btncancel, SDL_MOUSEBUTTONUP, 0);
}

/*
** **************************************************************************
**	void ft_gui_init_win_setenemy(t_list *head)
** **************************************************************************
*/

void	ft_gui_init_win_setenemy(t_list *head)
{
	t_gui_elem	*elem;

	elem = head->content;
	ft_gui_elem_init_grid(head, "win_editor_setenemy_btntitle", 1, (t_gui_coord){2, 1});
	ft_gui_elem_set_color(elem->child, 0x000000);
	ft_gui_elem_set_text(elem->child, "Set player", 16);
	ft_gui_elem_set_parent(head, elem->child);
	ft_gui_elem_init_grid(head, "win_editor_setenemy_btnsaveplayer", 25, (t_gui_coord){2, 1});
	ft_gui_elem_set_color(elem->child, 0x50c878);
	ft_gui_elem_set_button(elem->child, "Save player");
	ft_gui_elem_set_event(elem->child, \
		ft_gui_mousebuttonup_win_setenemy_btnsaveplayer, SDL_MOUSEBUTTONUP, 0);
	ft_gui_elem_set_parent(head, elem->child);
	ft_gui_elem_init_grid(head, "win_editor_setenemy_btncancel", 27, (t_gui_coord){2, 1});
	ft_gui_elem_set_color(elem->child, 0xcc0605);
	ft_gui_elem_set_button(elem->child, "Cancel");
	ft_gui_elem_set_event(elem->child, \
		ft_gui_mousebuttonup_win_setenemy_btncancel, SDL_MOUSEBUTTONUP, 0);
	ft_gui_elem_set_parent(head, elem->child);
}

/*
** **************************************************************************
**	void ft_gui_init_win_setdoor(t_list *head)
** **************************************************************************
*/

void	ft_gui_init_win_setdoor(t_list *head)
{
	t_gui_elem	*elem;

	elem = head->content;
	ft_gui_elem_init_grid(head, "win_editor_setdoor_title", 1, (t_gui_coord){2, 1});
	ft_gui_elem_set_color(elem->child, 0x000000);
	ft_gui_elem_set_text(elem->child, "Set door", 16);
	ft_gui_elem_init_grid(head, "win_editor_setdoor_text", 3, (t_gui_coord){2, 1});
	ft_gui_elem_set_color(elem->child, 0x000000);
	ft_gui_elem_set_text(elem->child, "Draw line between two sector walls", 16);
	ft_gui_elem_init_grid(head, "win_editor_setdoor_btnsave", 25, (t_gui_coord){2, 1});
	ft_gui_elem_set_color(elem->child, 0x50c878);
	ft_gui_elem_set_button(elem->child, "Save door");
	ft_gui_elem_set_event(elem->child, \
		ft_gui_mousebuttonup_win_setdoor_btnsave, SDL_MOUSEBUTTONUP, 0);
	ft_gui_elem_init_grid(head, "win_editor_setdoor_btncancel", 27, (t_gui_coord){2, 1});
	ft_gui_elem_set_color(elem->child, 0xcc0605);
	ft_gui_elem_set_button(elem->child, "Cancel");
	ft_gui_elem_set_event(elem->child, \
		ft_gui_mousebuttonup_win_setdoor_btncancel, SDL_MOUSEBUTTONUP, 0);
}

/*
** **************************************************************************
**	void ft_editor_gui_init_win_editor(t_list *head)
** **************************************************************************
*/

void	ft_editor_gui_init_win_editor(t_list *head)
{
	t_gui_elem	*win;

	win = head->content;

	ft_gui_elem_init(&win->child, "win_editor_map", \
		(t_gui_coord){0, 0, 0}, \
		(t_gui_coord){WIN_WIDTH - 300, WIN_HEIGHT, 0});
	ft_gui_elem_set_color(win->child, 0x000000);
	ft_gui_elem_set_map(win->child);
	ft_gui_elem_set_parent(head, win->child);
	ft_gui_elem_set_redraw(win->child, ft_gui_draw_map);
	ft_gui_elem_init(&win->child, "win_editor_menu", \
		(t_gui_coord){WIN_WIDTH - 300, 0, 0}, \
		(t_gui_coord){WIN_WIDTH, WIN_HEIGHT, 0});
	ft_gui_elem_set_grid(win->child, (t_gui_coord){2, 14}, 10);
	ft_gui_elem_set_color(win->child, 0x151719);
	ft_gui_elem_set_block(win->child);
	ft_gui_elem_set_parent(head, win->child);
	ft_gui_init_win_menu(win->child);
	ft_gui_elem_init(&win->child, "win_editor_setsector", \
		(t_gui_coord){WIN_WIDTH - 300, 0, 0}, \
		(t_gui_coord){WIN_WIDTH, WIN_HEIGHT, 0});
	ft_gui_elem_set_grid(win->child, (t_gui_coord){2, 14}, 10);
	ft_gui_elem_set_color(win->child, GUI_CL_SECTOR);
	ft_gui_elem_set_block(win->child);
	ft_gui_elem_set_status(win->child, GUI_ELEM_HIDDEN);
	ft_gui_elem_set_parent(head, win->child);
	ft_gui_init_win_setsector(win->child);
	ft_gui_elem_init(&win->child, "win_editor_setplayer", \
		(t_gui_coord){WIN_WIDTH - 300, 0, 0}, \
		(t_gui_coord){WIN_WIDTH, WIN_HEIGHT, 0});
	ft_gui_elem_set_grid(win->child, (t_gui_coord){2, 14}, 10);
	ft_gui_elem_set_color(win->child, GUI_CL_PLAYER);
	ft_gui_elem_set_block(win->child);
	ft_gui_elem_set_status(win->child, GUI_ELEM_HIDDEN);
	ft_gui_elem_set_parent(head, win->child);
	ft_gui_init_win_setplayer(win->child);
	ft_gui_elem_init(&win->child, "win_editor_setsprite", \
		(t_gui_coord){WIN_WIDTH - 300, 0, 0}, \
		(t_gui_coord){WIN_WIDTH, WIN_HEIGHT, 0});
	ft_gui_elem_set_grid(win->child, (t_gui_coord){2, 14}, 10);
	ft_gui_elem_set_color(win->child, GUI_CL_SPRITE);
	ft_gui_elem_set_block(win->child);
	ft_gui_elem_set_status(win->child, GUI_ELEM_HIDDEN);
	ft_gui_elem_set_parent(head, win->child);
	ft_gui_init_win_setsprite(win->child);
	ft_gui_elem_init(&win->child, "win_editor_setenemy", \
		(t_gui_coord){WIN_WIDTH - 300, 0, 0}, \
		(t_gui_coord){WIN_WIDTH, WIN_HEIGHT, 0});
	ft_gui_elem_set_grid(win->child, (t_gui_coord){2, 14}, 10);
	ft_gui_elem_set_color(win->child, GUI_CL_ENEMY);
	ft_gui_elem_set_block(win->child);
	ft_gui_elem_set_status(win->child, GUI_ELEM_HIDDEN);
	ft_gui_elem_set_parent(head, win->child);
	ft_gui_init_win_setenemy(win->child);
	ft_gui_elem_init(&win->child, "win_editor_setdoor", \
		(t_gui_coord){WIN_WIDTH - 300, 0, 0}, \
		(t_gui_coord){WIN_WIDTH, WIN_HEIGHT, 0});
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
	w->gui_map.ptr = ft_gui_search_elem_by_name(w->gui.dom, "win_editor_map");
}
