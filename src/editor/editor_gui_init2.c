/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   editor_gui_init2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dorange- <dorange-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/13 19:01:58 by dorange-          #+#    #+#             */
/*   Updated: 2020/02/15 13:59:37 by dorange-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

void	ft_gui_init_win_menu_add_1(t_list *head)
{
	t_gui_elem	*elem;

	elem = head->content;
	ft_gui_elem_init_grid(head, "win_me_menu_title", 3, (t_gui_coord){1, 2});
	ft_gui_elem_set_color(elem->child, 0xcccccc);
	ft_gui_elem_set_text(elem->child, "Add:", 16);
	ft_gui_elem_init_grid(head, "win_me_menu_sctr", 5, (t_gui_coord){1, 1});
	ft_gui_elem_set_color(elem->child, GUI_CL_SECTOR);
	ft_gui_elem_set_button(elem->child, "Sector");
	ft_gui_elem_set_event(elem->child, \
		ft_gui_mousebuttonup_win_menu_btnsector, SDL_MOUSEBUTTONUP, 0);
	ft_gui_elem_init_grid(head, "win_me_menu_pl", 6, (t_gui_coord){1, 1});
	ft_gui_elem_set_color(elem->child, GUI_CL_PLAYER);
	ft_gui_elem_set_button(elem->child, "Player");
	ft_gui_elem_set_event(elem->child, \
		ft_gui_mousebuttonup_win_menu_btnplayer, SDL_MOUSEBUTTONUP, 0);
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
	ft_gui_init_win_menu_add_1(head);
	ft_gui_elem_init_grid(head, "win_me_menu_door", 7, (t_gui_coord){1, 1});
	ft_gui_elem_set_color(elem->child, GUI_CL_DOOR);
	ft_gui_elem_set_button(elem->child, "Door");
	ft_gui_elem_set_event(elem->child, \
		ft_gui_mousebuttonup_win_menu_btndoor, SDL_MOUSEBUTTONUP, 0);
	ft_gui_elem_init_grid(head, "win_me_menu_sprt", 8, (t_gui_coord){1, 1});
	ft_gui_elem_set_color(elem->child, GUI_CL_SPRITE);
	ft_gui_elem_set_button(elem->child, "Sprite");
	ft_gui_elem_set_event(elem->child, \
		ft_gui_mousebuttonup_win_menu_btnsprite, SDL_MOUSEBUTTONUP, 0);
	ft_gui_elem_init_grid(head, "win_me_menu_enemy", 9, (t_gui_coord){1, 1});
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
	ft_gui_elem_init_grid(head, "win_me_menu_title", 11, (t_gui_coord){1, 2});
	ft_gui_elem_set_color(elem->child, 0xcccccc);
	ft_gui_elem_set_text(elem->child, "Set:", 16);
	ft_gui_elem_init_grid(head, "win_me_menu_txtr", 13, (t_gui_coord){1, 1});
	ft_gui_elem_set_color(elem->child, 0xcccccc);
	ft_gui_elem_set_status(elem->child, GUI_ELEM_DISABLE);
	ft_gui_elem_set_button(elem->child, "Textures");
	ft_gui_elem_init_grid(head, "win_me_menu_sky", 14, (t_gui_coord){1, 1});
	ft_gui_elem_set_color(elem->child, 0xcccccc);
	ft_gui_elem_set_status(elem->child, GUI_ELEM_DISABLE);
	ft_gui_elem_set_button(elem->child, "Skybox");
	ft_gui_elem_init_grid(head, "win_me_menu_savep", 15, (t_gui_coord){2, 1});
	ft_gui_elem_set_color(elem->child, 0xcccccc);
	ft_gui_elem_set_status(elem->child, GUI_ELEM_DISABLE);
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
	ft_gui_elem_init_grid(head, "win_me_menu_titlen", 21, (t_gui_coord){2, 1});
	ft_gui_elem_set_color(elem->child, 0xffffff);
	ft_gui_elem_set_text(elem->child, "Save map as:", 16);
	ft_gui_elem_init_grid(head, "win_me_menu_name", 23, (t_gui_coord){2, 1});
	ft_gui_elem_set_color(elem->child, 0xaaaaaa);
	ft_gui_elem_set_input(elem->child, " ", 0);
	ft_gui_elem_init_grid(head, "win_me_menu_save", 25, (t_gui_coord){2, 1});
	ft_gui_elem_set_color(elem->child, 0x50c878);
	ft_gui_elem_set_button(elem->child, "Save map");
	ft_gui_elem_set_event(elem->child, \
		ft_gui_mousebuttonup_win_menu_btnsavemap, SDL_MOUSEBUTTONUP, 0);
	ft_gui_elem_init_grid(head, "win_me_menu_exit", 27, (t_gui_coord){2, 1});
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
