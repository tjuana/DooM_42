/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_gui_init.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjuana <tjuana@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/27 20:36:24 by dorange-          #+#    #+#             */
/*   Updated: 2020/02/21 13:46:21 by tjuana           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

void	ft_main_gui_init_win_menu_btn(t_list *head)
{
	t_gui_elem	*elem;

	elem = head->content;
	ft_gui_elem_init_grid(head, "win_menu_title", 1, (t_gui_coord){1, 5, 0});
	ft_gui_elem_set_color(elem->child, 0xffffff);
	ft_gui_elem_set_text(elem->child, "DOOM", 72, "fonts/Raleway-Black.ttf");

	ft_gui_elem_init_grid(head, "win_menu_title2", 11, (t_gui_coord){1, 5, 0});
	ft_gui_elem_set_color(elem->child, 0xffffff);
	ft_gui_elem_set_text(elem->child, "NUKEM", 72, "fonts/Raleway-Black.ttf");

	ft_gui_elem_init_grid(head, "win_menu_btngame", 31, (t_gui_coord){2, 2, 0});
	ft_gui_elem_set_color(elem->child, 0x30444444);
	ft_gui_elem_set_button(elem->child, "Game", 30);
	ft_gui_elem_set_event(elem->child, \
		ft_gui_mousebuttonup_win_menu_btngame, \
		SDL_MOUSEBUTTONUP, 0);
	ft_gui_elem_init_grid(head, "win_menu_btneditor", 33, (t_gui_coord){2, 2, 0});
	ft_gui_elem_set_color(elem->child, 0x30444444);
	ft_gui_elem_set_button(elem->child, "Editor", 30);
	ft_gui_elem_set_event(elem->child, \
		ft_gui_mousebuttonup_win_menu_btneditor, \
		SDL_MOUSEBUTTONUP, 0);
	ft_gui_elem_init_grid(head, "win_menu_btnabout", 51, (t_gui_coord){2, 2, 0});
	ft_gui_elem_set_color(elem->child, 0x30444444);
	ft_gui_elem_set_button(elem->child, "About", 30);
	ft_gui_elem_init_grid(head, "win_menu_btnauthor", 53, (t_gui_coord){2, 2, 0});
	ft_gui_elem_set_color(elem->child, 0x30444444);
	ft_gui_elem_set_button(elem->child, "Author", 30);
	ft_gui_elem_set_event(elem->child, \
		ft_gui_mousebuttonup_win_menu_btnauthor, \
		SDL_MOUSEBUTTONUP, 0);
	ft_gui_elem_init_grid(head, "win_menu_btnexit", 71, (t_gui_coord){2, 2, 0});
	ft_gui_elem_set_color(elem->child, 0x30ff0000);
	ft_gui_elem_set_button(elem->child, "Exit", 30);
	ft_gui_elem_set_event(elem->child, \
		ft_gui_mousebuttonup_win_menu_btnexit, \
		SDL_MOUSEBUTTONUP, 0);
}

void	ft_main_gui_init_win_menu(t_list *head)
{
	t_gui_elem	*elem;

	elem = head->content;
	ft_main_gui_init_win_menu_btn(head);
	ft_gui_elem_init(&elem->child, "win_menu_image", \
		(t_gui_coord){0, 0, 0}, \
		(t_gui_coord){WIN_W, WIN_H, 0});
	ft_gui_elem_set_image(elem->child, "./Textures/bloody_game.jpg");
	ft_gui_elem_set_parent(head, elem->child);
}

void	ft_main_gui_init_win_author(t_list *head)
{
	t_gui_elem	*elem;

	elem = head->content;
	ft_gui_elem_init_grid(head, "win_author_title", 1, (t_gui_coord){1, 5, 0});
	ft_gui_elem_set_color(elem->child, 0xffffff);
	ft_gui_elem_set_text(elem->child, "DOOM", 72, "fonts/Raleway-Black.ttf");

	ft_gui_elem_init_grid(head, "win_author_title2", 11, (t_gui_coord){1, 5, 0});
	ft_gui_elem_set_color(elem->child, 0xffffff);
	ft_gui_elem_set_text(elem->child, "NUKEM", 72, "fonts/Raleway-Black.ttf");

	ft_gui_elem_init_grid(head, "win_author_title2", 31, (t_gui_coord){1, 5, 0});
	ft_gui_elem_set_color(elem->child, 0xffffff);
	ft_gui_elem_set_text(elem->child, "Author", 48, "fonts/Raleway-Black.ttf");

	ft_gui_elem_init_grid(head, "win_author_drafe", 41, (t_gui_coord){1, 5, 0});
	ft_gui_elem_set_color(elem->child, 0xffffff);
	ft_gui_elem_set_text(elem->child, "drafe", 36, "fonts/Raleway-ExtraBold.ttf");

	ft_gui_elem_init_grid(head, "win_author_dorange-", 51, (t_gui_coord){1, 5, 0});
	ft_gui_elem_set_color(elem->child, 0xffffff);
	ft_gui_elem_set_text(elem->child, "dorange-", 36, "fonts/Raleway-ExtraBold.ttf");

	ft_gui_elem_init_grid(head, "win_author_nshelly", 61, (t_gui_coord){1, 5, 0});
	ft_gui_elem_set_color(elem->child, 0xffffff);
	ft_gui_elem_set_text(elem->child, "nshelly", 36, "fonts/Raleway-ExtraBold.ttf");

	ft_gui_elem_init_grid(head, "win_author_tjuana", 71, (t_gui_coord){1, 5, 0});
	ft_gui_elem_set_color(elem->child, 0xffffff);
	ft_gui_elem_set_text(elem->child, "tjuana", 36, "fonts/Raleway-ExtraBold.ttf");

	ft_gui_elem_init_grid(head, "win_author_btnmenu", 91, (t_gui_coord){2, 1, 0});
	ft_gui_elem_set_color(elem->child, 0x30444444);
	ft_gui_elem_set_button(elem->child, "Go to menu", 30);
	ft_gui_elem_set_event(elem->child, \
		ft_gui_mousebuttonup_win_author_btnmenu, \
		SDL_MOUSEBUTTONUP, 0);

	ft_gui_elem_init(&elem->child, "win_author_image", \
		(t_gui_coord){0, 0, 0}, \
		(t_gui_coord){WIN_W, WIN_H, 0});
	ft_gui_elem_set_image(elem->child, "./Textures/bloody_game.jpg");
	ft_gui_elem_set_parent(head, elem->child);

}

void	ft_main_gui_init_win(t_list *head)
{
	t_gui_elem	*win;

	win = head->content;

	ft_gui_elem_init(&win->child, "win_menu", (t_gui_coord){0, 0, 0}, \
		(t_gui_coord){WIN_WIDTH, WIN_HEIGHT, 0});
	ft_gui_elem_set_color(win->child, 0x000000);
	ft_gui_elem_set_grid(win->child, (t_gui_coord){10, 10, 0}, 10);
	ft_gui_elem_set_parent(head, win->child);
	ft_main_gui_init_win_menu(win->child);

	ft_gui_elem_init(&win->child, "win_author", (t_gui_coord){0, 0, 0}, \
		(t_gui_coord){WIN_WIDTH, WIN_HEIGHT, 0});
	ft_gui_elem_set_color(win->child, 0x000000);
	ft_gui_elem_set_grid(win->child, (t_gui_coord){10, 10, 0}, 10);
	ft_gui_elem_set_parent(head, win->child);
	ft_gui_elem_set_status(win->child, GUI_ELEM_HIDDEN);
	ft_main_gui_init_win_author(win->child);

	ft_gui_elem_init(&win->child, "win_me", (t_gui_coord){0, 0, 0}, \
		(t_gui_coord){WIN_WIDTH, WIN_HEIGHT, 0});
	ft_gui_elem_set_grid(win->child, (t_gui_coord){4, 1, 0}, 0);
	ft_gui_elem_set_color(win->child, 0x000000);
	ft_gui_elem_set_parent(head, win->child);
	ft_gui_elem_set_redraw(win->child, ft_gui_draw_map);
	ft_gui_elem_set_status(win->child, GUI_ELEM_HIDDEN);
	ft_editor_gui_init_win_me(win->child);

	ft_gui_elem_init(&win->child, "win_game", (t_gui_coord){0, 0, 0}, \
		(t_gui_coord){WIN_WIDTH, WIN_HEIGHT, 0});
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
	w->gui.mode = GUI_MD_MENU;
	ft_editor_gui_init(w);
	ft_gui_elem_init(&w->gui.dom, "win", (t_gui_coord){0, 0, 0}, \
		(t_gui_coord){WIN_WIDTH, WIN_HEIGHT, 0});
	ft_gui_elem_set_color(w->gui.dom, 0x000000);
	ft_main_gui_init_win(w->gui.dom);
}
