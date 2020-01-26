/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   editor_gui_init.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dorange- <dorange-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/20 15:33:59 by dorange-          #+#    #+#             */
/*   Updated: 2020/01/26 14:30:54 by dorange-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"


/*
**	void ft_gui_elem_set_map(t_list *list, void *str)
**	
**	Function that set map type for gui element.
*/
void			ft_gui_elem_set_map(t_list *list)
{
	t_gui_elem	*elem;

	elem = list->content;
	elem->type = GUI_MAP;
	ft_gui_elem_set_event(list, ft_gui_mousemotion_win_map, SDL_MOUSEMOTION, 0);
	ft_gui_elem_set_event(list, ft_gui_mousebuttondown_win_map, SDL_MOUSEBUTTONDOWN, 0);
	ft_gui_elem_set_event(list, ft_gui_mousebuttonup_win_map, SDL_MOUSEBUTTONUP, 0);
	ft_gui_elem_set_event(list, ft_gui_mousewheel_win_map, SDL_MOUSEWHEEL, 0);
}

/*
	Рассмотреть возможность структуризации и типизации
	блоков меню, объектов и событий.
*/

void	ft_gui_init_win_menu(t_list *head)
{
	t_gui_elem	*elem;

	elem = head->content;
	ft_gui_elem_init(&elem->child, "win_menu_title", (t_gui_coord){WIN_WIDTH - 300 + 20, 5, 0}, \
		(t_gui_coord){WIN_WIDTH - 20, 45, 0});
	ft_gui_elem_set_color(elem->child, 0xffffff);
	ft_gui_elem_set_text(elem->child, "M A P   E D I T O R", 16);
	ft_gui_elem_set_parent(head, elem->child);

	ft_gui_elem_init(&elem->child, "win_menu_hr", (t_gui_coord){WIN_WIDTH - 300 + 20, 47, 0}, \
		(t_gui_coord){WIN_WIDTH - 20, 48, 0});
	ft_gui_elem_set_color(elem->child, 0xffffff);
	ft_gui_elem_set_block(elem->child);
	ft_gui_elem_set_parent(head, elem->child);

	ft_gui_elem_init(&elem->child, "win_menu_title", (t_gui_coord){WIN_WIDTH - 300 + 20, 60, 0}, \
		(t_gui_coord){WIN_WIDTH - 20, 110, 0});
	ft_gui_elem_set_color(elem->child, 0xcccccc);
	ft_gui_elem_set_text(elem->child, "Add:", 16);
	ft_gui_elem_set_parent(head, elem->child);

	ft_gui_elem_init(&elem->child, "win_menu_btnsector", (t_gui_coord){WIN_WIDTH - 300 + 20, 100, 0}, \
		(t_gui_coord){WIN_WIDTH - 150 - 5, 140, 0});
	ft_gui_elem_set_color(elem->child, GUI_CL_SECTOR);
	ft_gui_elem_set_button(elem->child, "Sector");
	ft_gui_elem_set_event(elem->child, ft_gui_mousebuttonup_win_menu_btnsector, SDL_MOUSEBUTTONUP, 0);
	ft_gui_elem_set_parent(head, elem->child);

	// ft_gui_elem_init(&elem->child, "win_menu_btnplayer", (t_gui_coord){WIN_WIDTH - 300 + 20, 100, 0}, \
	// 	(t_gui_coord){WIN_WIDTH - 20, 140, 0});
	ft_gui_elem_init(&elem->child, "win_menu_btnplayer", (t_gui_coord){WIN_WIDTH - 150 + 5, 100, 0}, \
		(t_gui_coord){WIN_WIDTH - 20, 140, 0});
	ft_gui_elem_set_color(elem->child, GUI_CL_PLAYER);
	ft_gui_elem_set_button(elem->child, "Player");
	ft_gui_elem_set_event(elem->child, ft_gui_mousebuttonup_win_menu_btnplayer, SDL_MOUSEBUTTONUP, 0);
	ft_gui_elem_set_parent(head, elem->child);

	ft_gui_elem_init(&elem->child, "win_menu_btndoor", (t_gui_coord){WIN_WIDTH - 300 + 20, 150, 0}, \
		(t_gui_coord){WIN_WIDTH - 150 - 5, 190, 0});
	ft_gui_elem_set_color(elem->child, GUI_CL_DOOR);
	ft_gui_elem_set_button(elem->child, "Door");
	ft_gui_elem_set_event(elem->child, ft_gui_mousebuttonup_win_menu_btndoor, SDL_MOUSEBUTTONUP, 0);
	ft_gui_elem_set_parent(head, elem->child);

	ft_gui_elem_init(&elem->child, "win_menu_btnsprite", (t_gui_coord){WIN_WIDTH - 150 + 5, 150, 0}, \
		(t_gui_coord){WIN_WIDTH - 20, 190, 0});
	ft_gui_elem_set_color(elem->child, GUI_CL_SPRITE);
	ft_gui_elem_set_button(elem->child, "Sprite");
	ft_gui_elem_set_event(elem->child, ft_gui_mousebuttonup_win_menu_btnsprite, SDL_MOUSEBUTTONUP, 0);
	ft_gui_elem_set_parent(head, elem->child);

	ft_gui_elem_init(&elem->child, "win_menu_btnenemy", (t_gui_coord){WIN_WIDTH - 300 + 20, 200, 0}, \
		(t_gui_coord){WIN_WIDTH - 150 - 5, 240, 0});
	ft_gui_elem_set_color(elem->child, GUI_CL_ENEMY);
	ft_gui_elem_set_button(elem->child, "Enemy");
	ft_gui_elem_set_event(elem->child, ft_gui_mousebuttonup_win_menu_btnenemy, SDL_MOUSEBUTTONUP, 0);
	ft_gui_elem_set_parent(head, elem->child);

	ft_gui_elem_init(&elem->child, "win_menu_title", (t_gui_coord){WIN_WIDTH - 300 + 20, 280, 0}, \
		(t_gui_coord){WIN_WIDTH - 20, 320, 0});
	ft_gui_elem_set_color(elem->child, 0xcccccc);
	ft_gui_elem_set_text(elem->child, "Set:", 16);
	ft_gui_elem_set_parent(head, elem->child);

	ft_gui_elem_init(&elem->child, "win_menu_btntxtr", (t_gui_coord){WIN_WIDTH - 300 + 20, 320, 0}, \
		(t_gui_coord){WIN_WIDTH - 150 - 5, 360, 0});
	ft_gui_elem_set_color(elem->child, 0xcccccc);
	ft_gui_elem_set_button(elem->child, "Textures");
	// ft_gui_elem_set_event(elem->child, ft_gui_mousebuttonup_win_menu_btnskybox, SDL_MOUSEBUTTONUP, 0);
	ft_gui_elem_set_parent(head, elem->child);

	ft_gui_elem_init(&elem->child, "win_menu_btnskybox", (t_gui_coord){WIN_WIDTH - 150 + 5, 320, 0}, \
		(t_gui_coord){WIN_WIDTH - 20, 360, 0});
	ft_gui_elem_set_color(elem->child, 0xcccccc);
	ft_gui_elem_set_button(elem->child, "Skybox");
	// ft_gui_elem_set_event(elem->child, ft_gui_mousebuttonup_win_menu_btnskybox, SDL_MOUSEBUTTONUP, 0);
	ft_gui_elem_set_parent(head, elem->child);

	ft_gui_elem_init(&elem->child, "win_menu_btnendplace", (t_gui_coord){WIN_WIDTH - 300 + 20, 370, 0}, \
		(t_gui_coord){WIN_WIDTH - 20, 410, 0});
	ft_gui_elem_set_color(elem->child, 0xcccccc);
	ft_gui_elem_set_button(elem->child, "Point to end game");
	// ft_gui_elem_set_event(elem->child, ft_gui_mousebuttonup_win_menu_btnendplace, SDL_MOUSEBUTTONUP, 0);
	ft_gui_elem_set_parent(head, elem->child);

	ft_gui_elem_init(&elem->child, "win_menu_titleinput", (t_gui_coord){WIN_WIDTH - 300 + 20, WIN_HEIGHT - 200, 0}, \
		(t_gui_coord){WIN_WIDTH - 20, WIN_HEIGHT - 160, 0});
	ft_gui_elem_set_color(elem->child, 0xffffff);
	ft_gui_elem_set_text(elem->child, "Save map as:", 16);
	ft_gui_elem_set_parent(head, elem->child);

	ft_gui_elem_init(&elem->child, "win_menu_inputmapname", (t_gui_coord){WIN_WIDTH - 300 + 20, WIN_HEIGHT - 160, 0}, \
		(t_gui_coord){WIN_WIDTH - 20, WIN_HEIGHT - 120, 0});
	ft_gui_elem_set_color(elem->child, 0xaaaaaa);
	ft_gui_elem_set_input(elem->child, " ", 0);
	ft_gui_elem_set_parent(head, elem->child);

	ft_gui_elem_init(&elem->child, "win_menu_btnsavemap", (t_gui_coord){WIN_WIDTH - 300 + 20, WIN_HEIGHT - 110, 0}, \
		(t_gui_coord){WIN_WIDTH - 20, WIN_HEIGHT - 70, 0});
	ft_gui_elem_set_color(elem->child, 0x50c878);
	ft_gui_elem_set_button(elem->child, "Save map");
	ft_gui_elem_set_event(elem->child, ft_gui_mousebuttonup_win_menu_btnsavemap, SDL_MOUSEBUTTONUP, 0);
	ft_gui_elem_set_parent(head, elem->child);

	ft_gui_elem_init(&elem->child, "win_menu_btnmenu", (t_gui_coord){WIN_WIDTH - 300 + 20, WIN_HEIGHT - 60, 0}, \
		(t_gui_coord){WIN_WIDTH - 20, WIN_HEIGHT - 20, 0});
	ft_gui_elem_set_color(elem->child, 0xcccccc);
	ft_gui_elem_set_button(elem->child, "Go to menu");
	// ft_gui_elem_set_event(elem->child, ft_gui_mousebuttonup_win_menu_btnsavemap, SDL_MOUSEBUTTONUP, 0);
	ft_gui_elem_set_parent(head, elem->child);
}

void	ft_gui_init_win_setsector(t_list *head)
{
	t_gui_elem	*elem;

	elem = head->content;
	ft_gui_elem_init(&elem->child, "win_setsector_title", (t_gui_coord){WIN_WIDTH - 300 + 20, 5, 0}, \
		(t_gui_coord){WIN_WIDTH - 20, 45, 0});
	ft_gui_elem_set_color(elem->child, 0x000000);
	ft_gui_elem_set_text(elem->child, "Set sector", 16);
	ft_gui_elem_set_parent(head, elem->child);

	// ft_gui_elem_init(&elem->child, "win_setsector_walltxtr", (t_gui_coord){WIN_WIDTH - 300 + 20, 50, 0}, \
	// 	(t_gui_coord){WIN_WIDTH - 20, 310, 0});
	// ft_gui_elem_set_color(elem->child, 0x000000);
	// ft_gui_elem_set_redraw(elem->child, ft_editor_redraw_txtr);
	// ft_gui_elem_set_event(elem->child, ft_gui_mousebuttonup_win_setsector_walltxtr, SDL_MOUSEBUTTONUP, 0);
	// // ft_gui_elem_set_block(elem->child);
	// ft_gui_elem_set_parent(head, elem->child);

	ft_gui_elem_init(&elem->child, "win_setsector_titleinputfloor", (t_gui_coord){WIN_WIDTH - 300 + 20, 400, 0}, \
		(t_gui_coord){WIN_WIDTH - 20, 440, 0});
	ft_gui_elem_set_color(elem->child, 0x000000);
	ft_gui_elem_set_text(elem->child, "Floor:", 16);
	ft_gui_elem_set_parent(head, elem->child);

	ft_gui_elem_init(&elem->child, "win_setsector_inputfloor", (t_gui_coord){WIN_WIDTH - 300 + 20, 440, 0}, \
		(t_gui_coord){WIN_WIDTH - 20, 480, 0});
	ft_gui_elem_set_color(elem->child, 0x333333);
	ft_gui_elem_set_input(elem->child, "0", 1);
	ft_gui_elem_set_parent(head, elem->child);

	ft_gui_elem_init(&elem->child, "win_setsector_titleinputheight", (t_gui_coord){WIN_WIDTH - 300 + 20, 500, 0}, \
		(t_gui_coord){WIN_WIDTH - 20, 540, 0});
	ft_gui_elem_set_color(elem->child, 0x000000);
	ft_gui_elem_set_text(elem->child, "Height:", 16);
	ft_gui_elem_set_parent(head, elem->child);

	ft_gui_elem_init(&elem->child, "win_setsector_inputheight", (t_gui_coord){WIN_WIDTH - 300 + 20, 540, 0}, \
		(t_gui_coord){WIN_WIDTH - 20, 580, 0});
	ft_gui_elem_set_color(elem->child, 0x333333);
	ft_gui_elem_set_input(elem->child, "0", 1);
	ft_gui_elem_set_parent(head, elem->child);

	ft_gui_elem_init(&elem->child, "win_setsector_btnsavemap", (t_gui_coord){WIN_WIDTH - 300 + 20, WIN_HEIGHT - 110, 0}, \
		(t_gui_coord){WIN_WIDTH - 20, WIN_HEIGHT - 70, 0});
	ft_gui_elem_set_color(elem->child, 0x50c878);
	ft_gui_elem_set_button(elem->child, "Save sector");
	ft_gui_elem_set_event(elem->child, ft_gui_mousebuttonup_win_setsector_btnsavemap, SDL_MOUSEBUTTONUP, 0);
	ft_gui_elem_set_parent(head, elem->child);

	ft_gui_elem_init(&elem->child, "win_setsector_btncancel", (t_gui_coord){WIN_WIDTH - 300 + 20, WIN_HEIGHT - 60, 0}, \
		(t_gui_coord){WIN_WIDTH - 20, WIN_HEIGHT - 20, 0});
	ft_gui_elem_set_color(elem->child, 0xcc0605);
	ft_gui_elem_set_button(elem->child, "Cancel");
	ft_gui_elem_set_event(elem->child, ft_gui_mousebuttonup_win_setsector_btncancel, SDL_MOUSEBUTTONUP, 0);
	ft_gui_elem_set_parent(head, elem->child);
}

void	ft_gui_init_win_setplayer(t_list *head)
{
	t_gui_elem	*elem;

	elem = head->content;
	ft_gui_elem_init(&elem->child, "win_setplayer_btntitle", (t_gui_coord){WIN_WIDTH - 300 + 20, 5, 0}, \
		(t_gui_coord){WIN_WIDTH - 20, 45, 0});
	ft_gui_elem_set_color(elem->child, 0x000000);
	ft_gui_elem_set_text(elem->child, "Set player", 16);
	ft_gui_elem_set_parent(head, elem->child);

	ft_gui_elem_init(&elem->child, "win_setplayer_playervec", (t_gui_coord){WIN_WIDTH - 300 + 20, 50, 0}, \
		(t_gui_coord){WIN_WIDTH - 20, 310, 0});
	ft_gui_elem_set_color(elem->child, 0x000000);
	ft_gui_elem_set_block(elem->child);
	ft_gui_elem_set_parent(head, elem->child);

	ft_gui_elem_init(&elem->child, "win_setplayer_btnsaveplayer", (t_gui_coord){WIN_WIDTH - 300 + 20, WIN_HEIGHT - 110, 0}, \
		(t_gui_coord){WIN_WIDTH - 20, WIN_HEIGHT - 70, 0});
	ft_gui_elem_set_color(elem->child, 0x50c878);
	ft_gui_elem_set_button(elem->child, "Save player");
	ft_gui_elem_set_event(elem->child, ft_gui_mousebuttonup_win_setplayer_btnsaveplayer, SDL_MOUSEBUTTONUP, 0);
	ft_gui_elem_set_parent(head, elem->child);

	ft_gui_elem_init(&elem->child, "win_setplayer_btncancel", (t_gui_coord){WIN_WIDTH - 300 + 20, WIN_HEIGHT - 60, 0}, \
		(t_gui_coord){WIN_WIDTH - 20, WIN_HEIGHT - 20, 0});
	ft_gui_elem_set_color(elem->child, 0xcc0605);
	ft_gui_elem_set_button(elem->child, "Cancel");
	ft_gui_elem_set_event(elem->child, ft_gui_mousebuttonup_win_setplayer_btncancel, SDL_MOUSEBUTTONUP, 0);
	ft_gui_elem_set_parent(head, elem->child);
}

void	ft_gui_init_win_setsprite(t_list *head)
{
	t_gui_elem	*elem;

	elem = head->content;
	ft_gui_elem_init(&elem->child, "win_setsprite_btntitle", (t_gui_coord){WIN_WIDTH - 300 + 20, 5, 0}, \
		(t_gui_coord){WIN_WIDTH - 20, 45, 0});
	ft_gui_elem_set_color(elem->child, 0x000000);
	ft_gui_elem_set_text(elem->child, "Set player", 16);
	ft_gui_elem_set_parent(head, elem->child);

	ft_gui_elem_init(&elem->child, "win_setsprite_playervec", (t_gui_coord){WIN_WIDTH - 300 + 20, 50, 0}, \
		(t_gui_coord){WIN_WIDTH - 20, 310, 0});
	ft_gui_elem_set_color(elem->child, 0x000000);
	ft_gui_elem_set_block(elem->child);
	ft_gui_elem_set_parent(head, elem->child);

	ft_gui_elem_init(&elem->child, "win_setsprite_btnsaveplayer", (t_gui_coord){WIN_WIDTH - 300 + 20, WIN_HEIGHT - 110, 0}, \
		(t_gui_coord){WIN_WIDTH - 20, WIN_HEIGHT - 70, 0});
	ft_gui_elem_set_color(elem->child, 0x50c878);
	ft_gui_elem_set_button(elem->child, "Save player");
	ft_gui_elem_set_event(elem->child, ft_gui_mousebuttonup_win_setsprite_btnsaveplayer, SDL_MOUSEBUTTONUP, 0);
	ft_gui_elem_set_parent(head, elem->child);

	ft_gui_elem_init(&elem->child, "win_setsprite_btncancel", (t_gui_coord){WIN_WIDTH - 300 + 20, WIN_HEIGHT - 60, 0}, \
		(t_gui_coord){WIN_WIDTH - 20, WIN_HEIGHT - 20, 0});
	ft_gui_elem_set_color(elem->child, 0xcc0605);
	ft_gui_elem_set_button(elem->child, "Cancel");
	ft_gui_elem_set_event(elem->child, ft_gui_mousebuttonup_win_setsprite_btncancel, SDL_MOUSEBUTTONUP, 0);
	ft_gui_elem_set_parent(head, elem->child);
}

void	ft_gui_init_win_setenemy(t_list *head)
{
	t_gui_elem	*elem;

	elem = head->content;
	ft_gui_elem_init(&elem->child, "win_setenemy_btntitle", (t_gui_coord){WIN_WIDTH - 300 + 20, 5, 0}, \
		(t_gui_coord){WIN_WIDTH - 20, 45, 0});
	ft_gui_elem_set_color(elem->child, 0x000000);
	ft_gui_elem_set_text(elem->child, "Set player", 16);
	ft_gui_elem_set_parent(head, elem->child);

	ft_gui_elem_init(&elem->child, "win_setenemy_playervec", (t_gui_coord){WIN_WIDTH - 300 + 20, 50, 0}, \
		(t_gui_coord){WIN_WIDTH - 20, 310, 0});
	ft_gui_elem_set_color(elem->child, 0x000000);
	ft_gui_elem_set_block(elem->child);
	ft_gui_elem_set_parent(head, elem->child);

	ft_gui_elem_init(&elem->child, "win_setenemy_btnsaveplayer", (t_gui_coord){WIN_WIDTH - 300 + 20, WIN_HEIGHT - 110, 0}, \
		(t_gui_coord){WIN_WIDTH - 20, WIN_HEIGHT - 70, 0});
	ft_gui_elem_set_color(elem->child, 0x50c878);
	ft_gui_elem_set_button(elem->child, "Save player");
	ft_gui_elem_set_event(elem->child, ft_gui_mousebuttonup_win_setenemy_btnsaveplayer, SDL_MOUSEBUTTONUP, 0);
	ft_gui_elem_set_parent(head, elem->child);

	ft_gui_elem_init(&elem->child, "win_setenemy_btncancel", (t_gui_coord){WIN_WIDTH - 300 + 20, WIN_HEIGHT - 60, 0}, \
		(t_gui_coord){WIN_WIDTH - 20, WIN_HEIGHT - 20, 0});
	ft_gui_elem_set_color(elem->child, 0xcc0605);
	ft_gui_elem_set_button(elem->child, "Cancel");
	ft_gui_elem_set_event(elem->child, ft_gui_mousebuttonup_win_setenemy_btncancel, SDL_MOUSEBUTTONUP, 0);
	ft_gui_elem_set_parent(head, elem->child);
}

void	ft_gui_init_win_setdoor(t_list *head)
{
	t_gui_elem	*elem;

	elem = head->content;
	ft_gui_elem_init(&elem->child, "win_setdoor_title", (t_gui_coord){WIN_WIDTH - 300 + 20, 5, 0}, \
		(t_gui_coord){WIN_WIDTH - 20, 45, 0});
	ft_gui_elem_set_color(elem->child, 0x000000);
	ft_gui_elem_set_text(elem->child, "Set door", 16);
	ft_gui_elem_set_parent(head, elem->child);

	ft_gui_elem_init(&elem->child, "win_setdoor_text", (t_gui_coord){WIN_WIDTH - 300 + 20, 45, 0}, \
		(t_gui_coord){WIN_WIDTH - 20, 45, 0});
	ft_gui_elem_set_color(elem->child, 0x000000);
	// Другой размер шрифта -> моментальная sega.
	ft_gui_elem_set_text(elem->child, "Draw line between two sector walls", 16);
	ft_gui_elem_set_parent(head, elem->child);

	ft_gui_elem_init(&elem->child, "win_setdoor_btnsave", (t_gui_coord){WIN_WIDTH - 300 + 20, WIN_HEIGHT - 110, 0}, \
		(t_gui_coord){WIN_WIDTH - 20, WIN_HEIGHT - 70, 0});
	ft_gui_elem_set_color(elem->child, 0x50c878);
	ft_gui_elem_set_button(elem->child, "Save door");
	ft_gui_elem_set_event(elem->child, ft_gui_mousebuttonup_win_setdoor_btnsave, SDL_MOUSEBUTTONUP, 0);
	ft_gui_elem_set_parent(head, elem->child);

	ft_gui_elem_init(&elem->child, "win_setdoor_btncancel", (t_gui_coord){WIN_WIDTH - 300 + 20, WIN_HEIGHT - 60, 0}, \
		(t_gui_coord){WIN_WIDTH - 20, WIN_HEIGHT - 20, 0});
	ft_gui_elem_set_color(elem->child, 0xcc0605);
	ft_gui_elem_set_button(elem->child, "Cancel");
	ft_gui_elem_set_event(elem->child, ft_gui_mousebuttonup_win_setdoor_btncancel, SDL_MOUSEBUTTONUP, 0);
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
		(t_gui_coord){WIN_WIDTH - 300, WIN_HEIGHT, 0});
	ft_gui_elem_set_color(win->child, 0x000000);
	ft_gui_elem_set_map(win->child);
	ft_gui_elem_set_parent(head, win->child);
	ft_gui_elem_set_redraw(win->child, ft_gui_draw_map);

	ft_gui_elem_init(&win->child, "win_menu", (t_gui_coord){WIN_WIDTH - 300, 0, 0}, \
		(t_gui_coord){WIN_WIDTH, WIN_HEIGHT, 0});
	ft_gui_elem_set_color(win->child, 0x151719);
	ft_gui_elem_set_block(win->child);
	ft_gui_elem_set_parent(head, win->child);
	ft_gui_init_win_menu(win->child);

	ft_gui_elem_init(&win->child, "win_setsector", (t_gui_coord){WIN_WIDTH - 300, 0, 0}, \
		(t_gui_coord){WIN_WIDTH, WIN_HEIGHT, 0});
	ft_gui_elem_set_color(win->child, GUI_CL_SECTOR);
	ft_gui_elem_set_block(win->child);
	ft_gui_elem_set_status(win->child, GUI_ELEM_HIDDEN);
	ft_gui_elem_set_parent(head, win->child);
	ft_gui_init_win_setsector(win->child);

	ft_gui_elem_init(&win->child, "win_setplayer", (t_gui_coord){WIN_WIDTH - 300, 0, 0}, \
		(t_gui_coord){WIN_WIDTH, WIN_HEIGHT, 0});
	ft_gui_elem_set_color(win->child, GUI_CL_PLAYER);
	ft_gui_elem_set_block(win->child);
	ft_gui_elem_set_status(win->child, GUI_ELEM_HIDDEN);
	ft_gui_elem_set_parent(head, win->child);
	ft_gui_init_win_setplayer(win->child);

	ft_gui_elem_init(&win->child, "win_setsprite", (t_gui_coord){WIN_WIDTH - 300, 0, 0}, \
		(t_gui_coord){WIN_WIDTH, WIN_HEIGHT, 0});
	ft_gui_elem_set_color(win->child, GUI_CL_SPRITE);
	ft_gui_elem_set_block(win->child);
	ft_gui_elem_set_status(win->child, GUI_ELEM_HIDDEN);
	ft_gui_elem_set_parent(head, win->child);
	ft_gui_init_win_setsprite(win->child);

	ft_gui_elem_init(&win->child, "win_setenemy", (t_gui_coord){WIN_WIDTH - 300, 0, 0}, \
		(t_gui_coord){WIN_WIDTH, WIN_HEIGHT, 0});
	ft_gui_elem_set_color(win->child, GUI_CL_ENEMY);
	ft_gui_elem_set_block(win->child);
	ft_gui_elem_set_status(win->child, GUI_ELEM_HIDDEN);
	ft_gui_elem_set_parent(head, win->child);
	ft_gui_init_win_setenemy(win->child);

	ft_gui_elem_init(&win->child, "win_setdoor", (t_gui_coord){WIN_WIDTH - 300, 0, 0}, \
		(t_gui_coord){WIN_WIDTH, WIN_HEIGHT, 0});
	ft_gui_elem_set_color(win->child, GUI_CL_DOOR);
	ft_gui_elem_set_block(win->child);
	ft_gui_elem_set_status(win->child, GUI_ELEM_HIDDEN);
	ft_gui_elem_set_parent(head, win->child);
	ft_gui_init_win_setdoor(win->child);
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