/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_gui_init.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjuana <tjuana@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/27 20:36:24 by dorange-          #+#    #+#             */
/*   Updated: 2020/02/08 13:33:26 by tjuana           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

void	ft_main_gui_init_win_menu(t_list *head)
{
	t_gui_elem	*elem;

	elem = head->content;

	ft_gui_elem_init(&elem->child, "win_menu_btngame", \
		(t_gui_coord){20, 100, 0}, \
		(t_gui_coord){140, 140, 0});
	ft_gui_elem_set_color(elem->child, 0xffa500);
	ft_gui_elem_set_button(elem->child, "Game");
	ft_gui_elem_set_event(elem->child, ft_gui_mousebuttonup_win_menu_btngame, SDL_MOUSEBUTTONUP, 0);
	ft_gui_elem_set_parent(head, elem->child);

	ft_gui_elem_init(&elem->child, "win_menu_btneditor", \
		(t_gui_coord){150, 100, 0}, \
		(t_gui_coord){280, 140, 0});
	ft_gui_elem_set_color(elem->child, 0xffa500);
	ft_gui_elem_set_button(elem->child, "Editor");
	ft_gui_elem_set_event(elem->child, ft_gui_mousebuttonup_win_menu_btneditor, SDL_MOUSEBUTTONUP, 0);
	ft_gui_elem_set_parent(head, elem->child);

	ft_gui_elem_init(&elem->child, "win_menu_btnexit", \
		(t_gui_coord){290, 100, 0}, \
		(t_gui_coord){420, 140, 0});
	ft_gui_elem_set_color(elem->child, 0xffa500);
	ft_gui_elem_set_button(elem->child, "Exit");
	ft_gui_elem_set_event(elem->child, ft_gui_mousebuttonup_win_menu_btnexit, SDL_MOUSEBUTTONUP, 0);
	ft_gui_elem_set_parent(head, elem->child);

	ft_gui_elem_init(&elem->child, "win_menu_image", \
		(t_gui_coord){0, 0, 0}, \
		(t_gui_coord){1400, 740, 0});
	ft_gui_elem_set_image(elem->child, "/Textures/bloody_game.jpg");
	ft_gui_elem_set_parent(head, elem->child);
}

void	ft_main_gui_init_win(t_list *head)
{
	t_gui_elem	*win;

	win = head->content;

	ft_gui_elem_init(&win->child, "win_menu", (t_gui_coord){0, 0, 0}, \
		(t_gui_coord){WIN_WIDTH, WIN_HEIGHT, 0});
	ft_gui_elem_set_color(win->child, 0x000000);
	// ft_gui_elem_set_map(win->child);
	ft_gui_elem_set_parent(head, win->child);
	ft_main_gui_init_win_menu(win->child);

	ft_gui_elem_init(&win->child, "win_editor", (t_gui_coord){0, 0, 0}, \
		(t_gui_coord){WIN_WIDTH, WIN_HEIGHT, 0});
	ft_gui_elem_set_color(win->child, 0x000000);
	ft_gui_elem_set_parent(head, win->child);
	ft_gui_elem_set_redraw(win->child, ft_gui_draw_map);
	ft_gui_elem_set_status(win->child, GUI_ELEM_HIDDEN);
	ft_editor_gui_init_win_editor(win->child);

	ft_gui_elem_init(&win->child, "win_game", (t_gui_coord){0, 0, 0}, \
		(t_gui_coord){WIN_WIDTH , WIN_HEIGHT, 0});
	ft_gui_elem_set_color(win->child, 0x000000);
	ft_gui_elem_set_parent(head, win->child);
	ft_gui_elem_set_redraw(win->child, ft_game_redraw);
	ft_gui_elem_set_status(win->child, GUI_ELEM_HIDDEN);
	ft_game_gui_init_hud(win->child);

}

void	ft_main_gui_init(t_wolf3d *w)
{
	w->gui.redraw = 0;
	w->gui.redraw_elem = NULL;
	w->gui.search_elem = GUI_EVENT_OFF;
	w->gui.dom = NULL;
	w->gui.fonts = NULL;
	w->gui.mode = GUI_MD_ME;
	ft_editor_gui_init(w);

	ft_gui_elem_init(&w->gui.dom, "win", (t_gui_coord){0, 0, 0}, \
		(t_gui_coord){WIN_WIDTH, WIN_HEIGHT, 0});
	ft_gui_elem_set_color(w->gui.dom, 0x000000);
	ft_main_gui_init_win(w->gui.dom);
}
