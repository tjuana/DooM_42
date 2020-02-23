/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_gui_init_menu.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dorange- <dorange-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/21 18:39:34 by dorange-          #+#    #+#             */
/*   Updated: 2020/02/21 18:39:57 by dorange-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

void	ft_main_gui_init_win_menu_btn_2(t_list *head)
{
	t_gui_elem	*elem;

	elem = head->content;
	ft_gui_elem_init_grid(head, "win_menu_btnabout", 51, \
		(t_gui_coord){2, 2, 0});
	ft_gui_elem_set_color(elem->child, 0x30444444);
	ft_gui_elem_set_button(elem->child, "About", 30);
	ft_gui_elem_init_grid(head, "win_menu_btnauthor", 53, \
		(t_gui_coord){2, 2, 0});
	ft_gui_elem_set_color(elem->child, 0x30444444);
	ft_gui_elem_set_button(elem->child, "Author", 30);
	ft_gui_elem_set_event(elem->child, \
		ft_gui_mousebuttonup_win_menu_btnauthor, \
		SDL_MOUSEBUTTONUP, 0);
	ft_gui_elem_init_grid(head, "win_menu_btnexit", 71, \
		(t_gui_coord){2, 2, 0});
	ft_gui_elem_set_color(elem->child, 0x30ff0000);
	ft_gui_elem_set_button(elem->child, "Exit", 30);
	ft_gui_elem_set_event(elem->child, \
		ft_gui_mousebuttonup_win_menu_btnexit, \
		SDL_MOUSEBUTTONUP, 0);
}

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
	ft_gui_elem_init_grid(head, "win_menu_btneditor", 33, \
		(t_gui_coord){2, 2, 0});
	ft_gui_elem_set_color(elem->child, 0x30444444);
	ft_gui_elem_set_button(elem->child, "Editor", 30);
	ft_gui_elem_set_event(elem->child, \
		ft_gui_mousebuttonup_win_menu_btneditor, \
		SDL_MOUSEBUTTONUP, 0);
}

void	ft_main_gui_init_win_menu(t_list *head)
{
	t_gui_elem	*elem;

	elem = head->content;
	ft_main_gui_init_win_menu_btn(head);
	ft_main_gui_init_win_menu_btn_2(head);
	ft_gui_elem_init(&elem->child, "win_menu_image", \
		(t_gui_coord){0, 0, 0}, \
		(t_gui_coord){WIN_W, WIN_H, 0});
	ft_gui_elem_set_image(elem->child, "./Textures/bloody_game.jpg");
	ft_gui_elem_set_parent(head, elem->child);
}
