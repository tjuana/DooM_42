/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gui_init.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dorange- <dorange-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/14 17:00:08 by dorange-          #+#    #+#             */
/*   Updated: 2020/01/16 21:38:58 by dorange-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

void	ft_gui_init_win_menu(t_list *head)
{
	t_gui_elem	*elem;

	elem = head->content;
	ft_gui_elem_init(&elem->child, "win_menu_btn_title", (t_ui_coord){1640, 5, 0}, \
		(t_ui_coord){WIN_WIDTH - 20, 45, 0});
	ft_gui_elem_set_color(elem->child, 0xffffff);
	ft_gui_elem_set_text(elem->child, "Map editor menu");
	ft_gui_elem_set_parent(head, elem->child);

	ft_gui_elem_init(&elem->child, "win_menu_btn_sector", (t_ui_coord){1640, 50, 0}, \
		(t_ui_coord){WIN_WIDTH - 20, 90, 0});
	ft_gui_elem_set_color(elem->child, 0xffd700);
	ft_gui_elem_set_button(elem->child, "Add sector");
	ft_gui_elem_set_event(elem->child, ft_gui_mousebuttonup_win_menu_btn_sector, SDL_MOUSEBUTTONUP, 0);
	ft_gui_elem_set_parent(head, elem->child);

	ft_gui_elem_init(&elem->child, "win_menu_btn_player", (t_ui_coord){1640, 100, 0}, \
		(t_ui_coord){WIN_WIDTH - 20, 140, 0});
	ft_gui_elem_set_color(elem->child, 0xa496f2);
	ft_gui_elem_set_button(elem->child, "Add player");
	ft_gui_elem_set_parent(head, elem->child);

	ft_gui_elem_init(&elem->child, "win_menu_btn_sprite", (t_ui_coord){1640, 150, 0}, \
		(t_ui_coord){WIN_WIDTH - 20, 190, 0});
	ft_gui_elem_set_color(elem->child, 0xdf73ff);
	ft_gui_elem_set_button(elem->child, "Add sprite");
	ft_gui_elem_set_parent(head, elem->child);

	ft_gui_elem_init(&elem->child, "win_menu_btn_enemy", (t_ui_coord){1640, 200, 0}, \
		(t_ui_coord){WIN_WIDTH - 20, 240, 0});
	ft_gui_elem_set_color(elem->child, 0xfb607f);
	ft_gui_elem_set_button(elem->child, "Add enemy");
	ft_gui_elem_set_parent(head, elem->child);

	ft_gui_elem_init(&elem->child, "win_menu_btn_title_input", (t_ui_coord){1640, 400, 0}, \
		(t_ui_coord){WIN_WIDTH - 20, 440, 0});
	ft_gui_elem_set_color(elem->child, 0xffffff);
	ft_gui_elem_set_text(elem->child, "Save map as:");
	ft_gui_elem_set_parent(head, elem->child);

	ft_gui_elem_init(&elem->child, "win_menu_btn_input_name", (t_ui_coord){1640, 440, 0}, \
		(t_ui_coord){WIN_WIDTH - 20, 480, 0});
	ft_gui_elem_set_color(elem->child, 0xaaaaaa);
	ft_gui_elem_set_input(elem->child, " ");
	ft_gui_elem_set_parent(head, elem->child);

	ft_gui_elem_init(&elem->child, "win_menu_btn_save_map", (t_ui_coord){1640, 490, 0}, \
		(t_ui_coord){WIN_WIDTH - 20, 530, 0});
	ft_gui_elem_set_color(elem->child, 0x50c878);
	ft_gui_elem_set_button(elem->child, "Save map");
	ft_gui_elem_set_parent(head, elem->child);
}

void	ft_gui_init_win_setsector(t_list *head)
{
	t_gui_elem	*elem;

	elem = head->content;
	ft_gui_elem_init(&elem->child, "win_setsector_btn_title", (t_ui_coord){1640, 5, 0}, \
		(t_ui_coord){WIN_WIDTH - 20, 45, 0});
	ft_gui_elem_set_color(elem->child, 0x000000);
	ft_gui_elem_set_text(elem->child, "Set sector");
	ft_gui_elem_set_parent(head, elem->child);

	ft_gui_elem_init(&elem->child, "win_setsector_sector", (t_ui_coord){1640, 50, 0}, \
		(t_ui_coord){WIN_WIDTH - 20, 310, 0});
	ft_gui_elem_set_color(elem->child, 0x000000);
	ft_gui_elem_set_block(elem->child);
	ft_gui_elem_set_parent(head, elem->child);

	ft_gui_elem_init(&elem->child, "win_setsector_btn_title_inputfloor", (t_ui_coord){1640, 400, 0}, \
		(t_ui_coord){WIN_WIDTH - 20, 440, 0});
	ft_gui_elem_set_color(elem->child, 0x000000);
	ft_gui_elem_set_text(elem->child, "Floor:");
	ft_gui_elem_set_parent(head, elem->child);

	ft_gui_elem_init(&elem->child, "win_setsector_btn_inputfloor", (t_ui_coord){1640, 440, 0}, \
		(t_ui_coord){WIN_WIDTH - 20, 480, 0});
	ft_gui_elem_set_color(elem->child, 0x333333);
	ft_gui_elem_set_input(elem->child, "0");
	ft_gui_elem_set_parent(head, elem->child);

	ft_gui_elem_init(&elem->child, "win_setsector_btn_title_inputfloor", (t_ui_coord){1640, 500, 0}, \
		(t_ui_coord){WIN_WIDTH - 20, 540, 0});
	ft_gui_elem_set_color(elem->child, 0x000000);
	ft_gui_elem_set_text(elem->child, "Height:");
	ft_gui_elem_set_parent(head, elem->child);

	ft_gui_elem_init(&elem->child, "win_setsector_btn_inputfloor", (t_ui_coord){1640, 540, 0}, \
		(t_ui_coord){WIN_WIDTH - 20, 580, 0});
	ft_gui_elem_set_color(elem->child, 0x333333);
	ft_gui_elem_set_input(elem->child, "0");
	ft_gui_elem_set_parent(head, elem->child);

	ft_gui_elem_init(&elem->child, "win_setsector_btn_save_map", (t_ui_coord){1640, 1080 - 110, 0}, \
		(t_ui_coord){WIN_WIDTH - 20, 1080 - 70, 0});
	ft_gui_elem_set_color(elem->child, 0x50c878);
	ft_gui_elem_set_button(elem->child, "Save sector");
	ft_gui_elem_set_parent(head, elem->child);

	ft_gui_elem_init(&elem->child, "win_setsector_btn_cancel", (t_ui_coord){1640, 1080 - 60, 0}, \
		(t_ui_coord){WIN_WIDTH - 20, 1080 - 20, 0});
	ft_gui_elem_set_color(elem->child, 0xcc0605);
	ft_gui_elem_set_button(elem->child, "Cancel");
	ft_gui_elem_set_event(elem->child, ft_gui_mousebuttonup_win_setsector_btn_cancel, SDL_MOUSEBUTTONUP, 0);
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
	// t_list		child;

	win = head->content;

	ft_gui_elem_init(&win->child, "win_map", (t_ui_coord){0, 0, 0}, \
		(t_ui_coord){1620, WIN_HEIGHT, 0});
	ft_gui_elem_set_color(win->child, 0x000000);
	ft_gui_elem_set_map(win->child);
	ft_gui_elem_set_parent(head, win->child);
	ft_gui_init_win_menu(win->child);

	ft_gui_elem_init(&win->child, "win_menu", (t_ui_coord){1620, 0, 0}, \
		(t_ui_coord){WIN_WIDTH, WIN_HEIGHT, 0});
	ft_gui_elem_set_color(win->child, 0x151719);
	ft_gui_elem_set_block(win->child);
	ft_gui_elem_set_parent(head, win->child);
	ft_gui_init_win_menu(win->child);

	ft_gui_elem_init(&win->child, "win_setsector", (t_ui_coord){1620, 0, 0}, \
		(t_ui_coord){WIN_WIDTH, WIN_HEIGHT, 0});
	ft_gui_elem_set_color(win->child, 0xffd700);
	ft_gui_elem_set_block(win->child);
	ft_gui_elem_set_status(win->child, GUI_ELEM_HIDDEN);
	ft_gui_elem_set_parent(head, win->child);
	ft_gui_init_win_setsector(win->child);
}

/*
**	void ft_gui_init(t_wolf3d *w)
**	
**	Function that set gui.
*/
void	ft_gui_init(t_wolf3d *w)
{
	w->gui.redraw = 0;
	w->gui.redraw_elem = NULL;
	w->gui.search_elem = GUI_EVENT_OFF;
	w->gui.dom = NULL;
	w->gui.fonts = NULL;

	w->gui_map.grid_scale = 32;
	w->gui_map.v = (t_vector3){-2.5, -2.5, 0, 0};
	w->gui_map.check_vertex = 0;

	ft_gui_elem_init(&w->gui.dom, "win", (t_ui_coord){0, 0, 0}, \
		(t_ui_coord){WIN_WIDTH, WIN_HEIGHT, 0});
	ft_gui_elem_set_color(w->gui.dom, 0x000000);
	ft_gui_init_win(w->gui.dom);
}