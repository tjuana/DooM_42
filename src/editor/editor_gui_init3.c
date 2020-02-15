/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   editor_gui_init3.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dorange- <dorange-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/13 19:02:34 by dorange-          #+#    #+#             */
/*   Updated: 2020/02/15 14:04:41 by dorange-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

/*
** **************************************************************************
**	void ft_gui_init_win_setsector(t_list *head)
** **************************************************************************
*/

void	ft_gui_init_win_setsector(t_list *head)
{
	t_gui_elem	*elem;

	elem = head->content;
	ft_gui_init_win_setsector_1(head);
	ft_gui_elem_init_grid(head, "win_me_sctr_titleh", 21, (t_gui_coord){2, 1});
	ft_gui_elem_set_color(elem->child, 0x000000);
	ft_gui_elem_set_text(elem->child, "Height:", 16);
	ft_gui_elem_init_grid(head, "win_me_sctr_inputh", 23, (t_gui_coord){2, 1});
	ft_gui_elem_set_color(elem->child, 0x333333);
	ft_gui_elem_set_input(elem->child, "0", 1);
	ft_gui_elem_init_grid(head, "win_me_sctr_save", 25, (t_gui_coord){2, 1});
	ft_gui_elem_set_color(elem->child, 0x50c878);
	ft_gui_elem_set_button(elem->child, "Save sector");
	ft_gui_elem_set_event(elem->child, \
		ft_gui_mousebuttonup_win_setsector_btnsavemap, SDL_MOUSEBUTTONUP, 0);
	ft_gui_elem_init_grid(head, "win_me_sctr_cncl", 27, (t_gui_coord){2, 1});
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
	ft_gui_elem_init_grid(head, "win_me_pl_title", 1, (t_gui_coord){2, 1});
	ft_gui_elem_set_color(elem->child, 0x000000);
	ft_gui_elem_set_text(elem->child, "Set player", 16);
	ft_gui_elem_init_grid(head, "win_me_pl_save", 25, (t_gui_coord){2, 1});
	ft_gui_elem_set_color(elem->child, 0x50c878);
	ft_gui_elem_set_button(elem->child, "Save player");
	ft_gui_elem_set_event(elem->child, \
		ft_gui_mousebuttonup_win_setplayer_btnsaveplayer, SDL_MOUSEBUTTONUP, 0);
	ft_gui_elem_init_grid(head, "win_me_pl_cncl", 27, (t_gui_coord){2, 1});
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
	ft_gui_elem_init_grid(head, "win_me_sprt_title", 1, (t_gui_coord){2, 1});
	ft_gui_elem_set_color(elem->child, 0x000000);
	ft_gui_elem_set_text(elem->child, "Set player", 16);
	ft_gui_elem_init_grid(head, "win_me_sprt_save", 25, (t_gui_coord){2, 1});
	ft_gui_elem_set_color(elem->child, 0x50c878);
	ft_gui_elem_set_button(elem->child, "Save sprite");
	ft_gui_elem_set_event(elem->child, \
		ft_gui_mousebuttonup_win_setsprite_btnsaveplayer, SDL_MOUSEBUTTONUP, 0);
	ft_gui_elem_init_grid(head, "win_me_sprt_cncl", 27, (t_gui_coord){2, 1});
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
	ft_gui_elem_init_grid(head, "win_me_enemy_title", 1, (t_gui_coord){2, 1});
	ft_gui_elem_set_color(elem->child, 0x000000);
	ft_gui_elem_set_text(elem->child, "Set player", 16);
	ft_gui_elem_set_parent(head, elem->child);
	ft_gui_elem_init_grid(head, "win_me_enemy_save", 25, (t_gui_coord){2, 1});
	ft_gui_elem_set_color(elem->child, 0x50c878);
	ft_gui_elem_set_button(elem->child, "Save enemy");
	ft_gui_elem_set_event(elem->child, \
		ft_gui_mousebuttonup_win_setenemy_btnsaveplayer, SDL_MOUSEBUTTONUP, 0);
	ft_gui_elem_set_parent(head, elem->child);
	ft_gui_elem_init_grid(head, "win_me_enemy_cncl", 27, (t_gui_coord){2, 1});
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
	ft_gui_elem_init_grid(head, "win_me_door_title", 1, (t_gui_coord){2, 1});
	ft_gui_elem_set_color(elem->child, 0x000000);
	ft_gui_elem_set_text(elem->child, "Set door", 16);
	ft_gui_elem_init_grid(head, "win_me_door_text", 3, (t_gui_coord){2, 1});
	ft_gui_elem_set_color(elem->child, 0x000000);
	ft_gui_elem_set_text(elem->child, "Draw line between two sector", 16);
	ft_gui_elem_init_grid(head, "win_me_door_save", 25, (t_gui_coord){2, 1});
	ft_gui_elem_set_color(elem->child, 0x50c878);
	ft_gui_elem_set_button(elem->child, "Save door");
	ft_gui_elem_set_event(elem->child, \
		ft_gui_mousebuttonup_win_setdoor_btnsave, SDL_MOUSEBUTTONUP, 0);
	ft_gui_elem_init_grid(head, "win_me_door_cncl", 27, (t_gui_coord){2, 1});
	ft_gui_elem_set_color(elem->child, 0xcc0605);
	ft_gui_elem_set_button(elem->child, "Cancel");
	ft_gui_elem_set_event(elem->child, \
		ft_gui_mousebuttonup_win_setdoor_btncancel, SDL_MOUSEBUTTONUP, 0);
}
