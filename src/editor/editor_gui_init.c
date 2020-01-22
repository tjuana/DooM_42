/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   editor_gui_init.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dorange- <dorange-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/20 15:33:59 by dorange-          #+#    #+#             */
/*   Updated: 2020/01/22 15:34:24 by dorange-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

/*
	Рассмотреть возможность структуризации и типизации
	блоков меню, объектов и событий.
*/

void	ft_gui_init_win_menu(t_list *head)
{
	t_gui_elem	*elem;

	elem = head->content;
	ft_gui_elem_init(&elem->child, "win_menu_btn_title", (t_gui_coord){1640, 5, 0}, \
		(t_gui_coord){WIN_WIDTH - 20, 45, 0});
	ft_gui_elem_set_color(elem->child, 0xffffff);
	ft_gui_elem_set_text(elem->child, "Map editor menu");
	ft_gui_elem_set_parent(head, elem->child);

	ft_gui_elem_init(&elem->child, "win_menu_btn_sector", (t_gui_coord){1640, 50, 0}, \
		(t_gui_coord){WIN_WIDTH - 20, 90, 0});
	ft_gui_elem_set_color(elem->child, GUI_CL_SECTOR);
	ft_gui_elem_set_button(elem->child, "Add sector");
	ft_gui_elem_set_event(elem->child, ft_gui_mousebuttonup_win_menu_btn_sector, SDL_MOUSEBUTTONUP, 0);
	ft_gui_elem_set_parent(head, elem->child);

	ft_gui_elem_init(&elem->child, "win_menu_btn_player", (t_gui_coord){1640, 100, 0}, \
		(t_gui_coord){WIN_WIDTH - 20, 140, 0});
	ft_gui_elem_set_color(elem->child, GUI_CL_PLAYER);
	ft_gui_elem_set_button(elem->child, "Add player");
	ft_gui_elem_set_event(elem->child, ft_gui_mousebuttonup_win_menu_btn_player, SDL_MOUSEBUTTONUP, 0);
	ft_gui_elem_set_parent(head, elem->child);

	ft_gui_elem_init(&elem->child, "win_menu_btn_sprite", (t_gui_coord){1640, 150, 0}, \
		(t_gui_coord){WIN_WIDTH - 20, 190, 0});
	ft_gui_elem_set_color(elem->child, GUI_CL_SPRITE);
	ft_gui_elem_set_button(elem->child, "Add sprite");
	ft_gui_elem_set_event(elem->child, ft_gui_mousebuttonup_win_menu_btn_sprite, SDL_MOUSEBUTTONUP, 0);
	ft_gui_elem_set_parent(head, elem->child);

	ft_gui_elem_init(&elem->child, "win_menu_btn_enemy", (t_gui_coord){1640, 200, 0}, \
		(t_gui_coord){WIN_WIDTH - 20, 240, 0});
	ft_gui_elem_set_color(elem->child, GUI_CL_ENEMY);
	ft_gui_elem_set_button(elem->child, "Add enemy");
	ft_gui_elem_set_event(elem->child, ft_gui_mousebuttonup_in_menu_btn_enemy, SDL_MOUSEBUTTONUP, 0);
	ft_gui_elem_set_parent(head, elem->child);

	ft_gui_elem_init(&elem->child, "win_menu_btn_title_input", (t_gui_coord){1640, 400, 0}, \
		(t_gui_coord){WIN_WIDTH - 20, 440, 0});
	ft_gui_elem_set_color(elem->child, 0xffffff);
	ft_gui_elem_set_text(elem->child, "Save map as:");
	ft_gui_elem_set_parent(head, elem->child);

	ft_gui_elem_init(&elem->child, "win_menu_inputmapname", (t_gui_coord){1640, 440, 0}, \
		(t_gui_coord){WIN_WIDTH - 20, 480, 0});
	ft_gui_elem_set_color(elem->child, 0xaaaaaa);
	ft_gui_elem_set_input(elem->child, " ", 0);
	ft_gui_elem_set_parent(head, elem->child);

	ft_gui_elem_init(&elem->child, "win_menu_btnsavemap", (t_gui_coord){1640, 490, 0}, \
		(t_gui_coord){WIN_WIDTH - 20, 530, 0});
	ft_gui_elem_set_color(elem->child, 0x50c878);
	ft_gui_elem_set_button(elem->child, "Save map");
	ft_gui_elem_set_event(elem->child, ft_gui_mousebuttonup_win_menu_btnsavemap, SDL_MOUSEBUTTONUP, 0);
	ft_gui_elem_set_parent(head, elem->child);
}

void	ft_gui_init_win_setsector(t_list *head)
{
	t_gui_elem	*elem;

	elem = head->content;
	ft_gui_elem_init(&elem->child, "win_setsector_title", (t_gui_coord){1640, 5, 0}, \
		(t_gui_coord){WIN_WIDTH - 20, 45, 0});
	ft_gui_elem_set_color(elem->child, 0x000000);
	ft_gui_elem_set_text(elem->child, "Set sector");
	ft_gui_elem_set_parent(head, elem->child);

	ft_gui_elem_init(&elem->child, "win_setsector_walltxtr", (t_gui_coord){1640, 50, 0}, \
		(t_gui_coord){WIN_WIDTH - 20, 310, 0});
	ft_gui_elem_set_color(elem->child, 0x000000);
	ft_gui_elem_set_redraw(elem->child, ft_editor_redraw_txtr);
	ft_gui_elem_set_event(elem->child, ft_gui_mousebuttonup_win_setsector_walltxtr, SDL_MOUSEBUTTONUP, 0);
	// ft_gui_elem_set_block(elem->child);
	ft_gui_elem_set_parent(head, elem->child);

	ft_gui_elem_init(&elem->child, "win_setsector_titleinputfloor", (t_gui_coord){1640, 400, 0}, \
		(t_gui_coord){WIN_WIDTH - 20, 440, 0});
	ft_gui_elem_set_color(elem->child, 0x000000);
	ft_gui_elem_set_text(elem->child, "Floor:");
	ft_gui_elem_set_parent(head, elem->child);

	ft_gui_elem_init(&elem->child, "win_setsector_inputfloor", (t_gui_coord){1640, 440, 0}, \
		(t_gui_coord){WIN_WIDTH - 20, 480, 0});
	ft_gui_elem_set_color(elem->child, 0x333333);
	ft_gui_elem_set_input(elem->child, "0", 1);
	ft_gui_elem_set_parent(head, elem->child);

	ft_gui_elem_init(&elem->child, "win_setsector_titleinputheight", (t_gui_coord){1640, 500, 0}, \
		(t_gui_coord){WIN_WIDTH - 20, 540, 0});
	ft_gui_elem_set_color(elem->child, 0x000000);
	ft_gui_elem_set_text(elem->child, "Height:");
	ft_gui_elem_set_parent(head, elem->child);

	ft_gui_elem_init(&elem->child, "win_setsector_inputheight", (t_gui_coord){1640, 540, 0}, \
		(t_gui_coord){WIN_WIDTH - 20, 580, 0});
	ft_gui_elem_set_color(elem->child, 0x333333);
	ft_gui_elem_set_input(elem->child, "0", 1);
	ft_gui_elem_set_parent(head, elem->child);

	ft_gui_elem_init(&elem->child, "win_setsector_btnsavemap", (t_gui_coord){1640, 1080 - 110, 0}, \
		(t_gui_coord){WIN_WIDTH - 20, 1080 - 70, 0});
	ft_gui_elem_set_color(elem->child, 0x50c878);
	ft_gui_elem_set_button(elem->child, "Save sector");
	ft_gui_elem_set_event(elem->child, ft_gui_mousebuttonup_win_setsector_btnsavemap, SDL_MOUSEBUTTONUP, 0);
	ft_gui_elem_set_parent(head, elem->child);

	ft_gui_elem_init(&elem->child, "win_setsector_btncancel", (t_gui_coord){1640, 1080 - 60, 0}, \
		(t_gui_coord){WIN_WIDTH - 20, 1080 - 20, 0});
	ft_gui_elem_set_color(elem->child, 0xcc0605);
	ft_gui_elem_set_button(elem->child, "Cancel");
	ft_gui_elem_set_event(elem->child, ft_gui_mousebuttonup_win_setsector_btncancel, SDL_MOUSEBUTTONUP, 0);
	ft_gui_elem_set_parent(head, elem->child);
}

void	ft_gui_init_win_setplayer(t_list *head)
{
	t_gui_elem	*elem;

	elem = head->content;
	ft_gui_elem_init(&elem->child, "win_setplayer_btntitle", (t_gui_coord){1640, 5, 0}, \
		(t_gui_coord){WIN_WIDTH - 20, 45, 0});
	ft_gui_elem_set_color(elem->child, 0x000000);
	ft_gui_elem_set_text(elem->child, "Set player");
	ft_gui_elem_set_parent(head, elem->child);

	ft_gui_elem_init(&elem->child, "win_setplayer_playervec", (t_gui_coord){1640, 50, 0}, \
		(t_gui_coord){WIN_WIDTH - 20, 310, 0});
	ft_gui_elem_set_color(elem->child, 0x000000);
	ft_gui_elem_set_block(elem->child);
	ft_gui_elem_set_parent(head, elem->child);

	ft_gui_elem_init(&elem->child, "win_setplayer_btnsaveplayer", (t_gui_coord){1640, 1080 - 110, 0}, \
		(t_gui_coord){WIN_WIDTH - 20, 1080 - 70, 0});
	ft_gui_elem_set_color(elem->child, 0x50c878);
	ft_gui_elem_set_button(elem->child, "Save player");
	ft_gui_elem_set_event(elem->child, ft_gui_mousebuttonup_win_setplayer_btnsaveplayer, SDL_MOUSEBUTTONUP, 0);
	ft_gui_elem_set_parent(head, elem->child);

	ft_gui_elem_init(&elem->child, "win_setplayer_btncancel", (t_gui_coord){1640, 1080 - 60, 0}, \
		(t_gui_coord){WIN_WIDTH - 20, 1080 - 20, 0});
	ft_gui_elem_set_color(elem->child, 0xcc0605);
	ft_gui_elem_set_button(elem->child, "Cancel");
	ft_gui_elem_set_event(elem->child, ft_gui_mousebuttonup_win_setplayer_btncancel, SDL_MOUSEBUTTONUP, 0);
	ft_gui_elem_set_parent(head, elem->child);
}

void	ft_gui_init_win_setsprite(t_list *head)
{
	t_gui_elem	*elem;

	elem = head->content;
	ft_gui_elem_init(&elem->child, "win_setsprite_btntitle", (t_gui_coord){1640, 5, 0}, \
		(t_gui_coord){WIN_WIDTH - 20, 45, 0});
	ft_gui_elem_set_color(elem->child, 0x000000);
	ft_gui_elem_set_text(elem->child, "Set player");
	ft_gui_elem_set_parent(head, elem->child);

	ft_gui_elem_init(&elem->child, "win_setsprite_playervec", (t_gui_coord){1640, 50, 0}, \
		(t_gui_coord){WIN_WIDTH - 20, 310, 0});
	ft_gui_elem_set_color(elem->child, 0x000000);
	ft_gui_elem_set_block(elem->child);
	ft_gui_elem_set_parent(head, elem->child);

	ft_gui_elem_init(&elem->child, "win_setsprite_btnsaveplayer", (t_gui_coord){1640, 1080 - 110, 0}, \
		(t_gui_coord){WIN_WIDTH - 20, 1080 - 70, 0});
	ft_gui_elem_set_color(elem->child, 0x50c878);
	ft_gui_elem_set_button(elem->child, "Save player");
	ft_gui_elem_set_event(elem->child, ft_gui_mousebuttonup_win_setsprite_btnsaveplayer, SDL_MOUSEBUTTONUP, 0);
	ft_gui_elem_set_parent(head, elem->child);

	ft_gui_elem_init(&elem->child, "win_setsprite_btncancel", (t_gui_coord){1640, 1080 - 60, 0}, \
		(t_gui_coord){WIN_WIDTH - 20, 1080 - 20, 0});
	ft_gui_elem_set_color(elem->child, 0xcc0605);
	ft_gui_elem_set_button(elem->child, "Cancel");
	ft_gui_elem_set_event(elem->child, ft_gui_mousebuttonup_win_setsprite_btncancel, SDL_MOUSEBUTTONUP, 0);
	ft_gui_elem_set_parent(head, elem->child);
}

void	ft_gui_init_win_setenemy(t_list *head)
{
	t_gui_elem	*elem;

	elem = head->content;
	ft_gui_elem_init(&elem->child, "win_setenemy_btntitle", (t_gui_coord){1640, 5, 0}, \
		(t_gui_coord){WIN_WIDTH - 20, 45, 0});
	ft_gui_elem_set_color(elem->child, 0x000000);
	ft_gui_elem_set_text(elem->child, "Set player");
	ft_gui_elem_set_parent(head, elem->child);

	ft_gui_elem_init(&elem->child, "win_setenemy_playervec", (t_gui_coord){1640, 50, 0}, \
		(t_gui_coord){WIN_WIDTH - 20, 310, 0});
	ft_gui_elem_set_color(elem->child, 0x000000);
	ft_gui_elem_set_block(elem->child);
	ft_gui_elem_set_parent(head, elem->child);

	ft_gui_elem_init(&elem->child, "win_setenemy_btnsaveplayer", (t_gui_coord){1640, 1080 - 110, 0}, \
		(t_gui_coord){WIN_WIDTH - 20, 1080 - 70, 0});
	ft_gui_elem_set_color(elem->child, 0x50c878);
	ft_gui_elem_set_button(elem->child, "Save player");
	ft_gui_elem_set_event(elem->child, ft_gui_mousebuttonup_win_setenemy_btnsaveplayer, SDL_MOUSEBUTTONUP, 0);
	ft_gui_elem_set_parent(head, elem->child);

	ft_gui_elem_init(&elem->child, "win_setenemy_btncancel", (t_gui_coord){1640, 1080 - 60, 0}, \
		(t_gui_coord){WIN_WIDTH - 20, 1080 - 20, 0});
	ft_gui_elem_set_color(elem->child, 0xcc0605);
	ft_gui_elem_set_button(elem->child, "Cancel");
	ft_gui_elem_set_event(elem->child, ft_gui_mousebuttonup_win_setenemy_btncancel, SDL_MOUSEBUTTONUP, 0);
	ft_gui_elem_set_parent(head, elem->child);
}

/*
**	void ft_gui_init(t_wolf3d *w)
**	
**	Function that set dom.
*/
void	ft_gui_init_win(t_list *head)
{
	t_gui_elem	*win;

	win = head->content;

	ft_gui_elem_init(&win->child, "win_map", (t_gui_coord){0, 0, 0}, \
		(t_gui_coord){1620, WIN_HEIGHT, 0});
	ft_gui_elem_set_color(win->child, 0x000000);
	ft_gui_elem_set_map(win->child);
	ft_gui_elem_set_parent(head, win->child);
	ft_gui_elem_set_redraw(win->child, ft_gui_draw_map);

	ft_gui_elem_init(&win->child, "win_menu", (t_gui_coord){1620, 0, 0}, \
		(t_gui_coord){WIN_WIDTH, WIN_HEIGHT, 0});
	ft_gui_elem_set_color(win->child, 0x151719);
	ft_gui_elem_set_block(win->child);
	ft_gui_elem_set_parent(head, win->child);
	ft_gui_init_win_menu(win->child);

	ft_gui_elem_init(&win->child, "win_setsector", (t_gui_coord){1620, 0, 0}, \
		(t_gui_coord){WIN_WIDTH, WIN_HEIGHT, 0});
	ft_gui_elem_set_color(win->child, GUI_CL_SECTOR);
	ft_gui_elem_set_block(win->child);
	ft_gui_elem_set_status(win->child, GUI_ELEM_HIDDEN);
	ft_gui_elem_set_parent(head, win->child);
	ft_gui_init_win_setsector(win->child);

	ft_gui_elem_init(&win->child, "win_setplayer", (t_gui_coord){1620, 0, 0}, \
		(t_gui_coord){WIN_WIDTH, WIN_HEIGHT, 0});
	ft_gui_elem_set_color(win->child, GUI_CL_PLAYER);
	ft_gui_elem_set_block(win->child);
	ft_gui_elem_set_status(win->child, GUI_ELEM_HIDDEN);
	ft_gui_elem_set_parent(head, win->child);
	ft_gui_init_win_setplayer(win->child);

	ft_gui_elem_init(&win->child, "win_setsprite", (t_gui_coord){1620, 0, 0}, \
		(t_gui_coord){WIN_WIDTH, WIN_HEIGHT, 0});
	ft_gui_elem_set_color(win->child, GUI_CL_SPRITE);
	ft_gui_elem_set_block(win->child);
	ft_gui_elem_set_status(win->child, GUI_ELEM_HIDDEN);
	ft_gui_elem_set_parent(head, win->child);
	ft_gui_init_win_setsprite(win->child);

	ft_gui_elem_init(&win->child, "win_setenemy", (t_gui_coord){1620, 0, 0}, \
		(t_gui_coord){WIN_WIDTH, WIN_HEIGHT, 0});
	ft_gui_elem_set_color(win->child, GUI_CL_ENEMY);
	ft_gui_elem_set_block(win->child);
	ft_gui_elem_set_status(win->child, GUI_ELEM_HIDDEN);
	ft_gui_elem_set_parent(head, win->child);
	ft_gui_init_win_setenemy(win->child);
}

/*
**	void ft_gui_init(t_wolf3d *w)
**	
**	Function that set gui.
*/
void	ft_editor_gui_init(t_wolf3d *w)
{
	w->gui.redraw = 0;
	w->gui.redraw_elem = NULL;
	w->gui.search_elem = GUI_EVENT_OFF;
	w->gui.dom = NULL;
	w->gui.fonts = NULL;
	w->gui.mode = GUI_MD_ME;

	w->gui_map.grid_scale = 32;
	w->gui_map.v = (t_vector3){-5.2, -5.5, 0, 0};
	// w->gui_map.v = (t_vector3){-2.2, -2.2, 0, 0};
	w->gui_map.check_vertex = 0;

	w->player_status = 0;
	w->sector_status = 0;
	w->sprite_status = 0;
	w->enemy_status = 0;

	w->sector = NULL;
	w->sprite = NULL;
	w->enemy = NULL;

	ft_gui_elem_init(&w->gui.dom, "win", (t_gui_coord){0, 0, 0}, \
		(t_gui_coord){WIN_WIDTH, WIN_HEIGHT, 0});
	ft_gui_elem_set_color(w->gui.dom, 0x000000);
	ft_gui_init_win(w->gui.dom);
	
	w->gui_map.ptr = ft_gui_search_elem_by_name(w->gui.dom, "win_map");
}