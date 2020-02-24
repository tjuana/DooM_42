/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_gui_init_author.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dorange- <dorange-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/21 18:38:46 by dorange-          #+#    #+#             */
/*   Updated: 2020/02/21 18:38:55 by dorange-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

void	ft_main_gui_init_win_author_1(t_list *head)
{
	t_gui_elem	*elem;

	elem = head->content;
	ft_gui_elem_init_grid(head, "win_author_title", 1, \
		(t_gui_coord){1, 5, 0});
	ft_gui_elem_set_color(elem->child, 0xffffff);
	ft_gui_elem_set_text(elem->child, "DOOM", 72, "fonts/Raleway-Black.ttf");
	ft_gui_elem_init_grid(head, "win_author_title2", 11, \
		(t_gui_coord){1, 5, 0});
	ft_gui_elem_set_color(elem->child, 0xffffff);
	ft_gui_elem_set_text(elem->child, "NUKEM", 72, "fonts/Raleway-Black.ttf");
	ft_gui_elem_init_grid(head, "win_author_title2", 31, \
		(t_gui_coord){1, 5, 0});
	ft_gui_elem_set_color(elem->child, 0xffffff);
	ft_gui_elem_set_text(elem->child, "Author", 48, "fonts/Raleway-Black.ttf");
}

void	ft_main_gui_init_win_author_2(t_list *head)
{
	t_gui_elem	*elem;

	elem = head->content;
	ft_gui_elem_init_grid(head, "win_author_drafe", 41, \
		(t_gui_coord){1, 5, 0});
	ft_gui_elem_set_color(elem->child, 0xffffff);
	ft_gui_elem_set_text(elem->child, "drafe", 36, \
		"fonts/Raleway-ExtraBold.ttf");
	ft_gui_elem_init_grid(head, "win_author_dorange-", 51, \
		(t_gui_coord){1, 5, 0});
	ft_gui_elem_set_color(elem->child, 0xffffff);
	ft_gui_elem_set_text(elem->child, "dorange-", 36, \
		"fonts/Raleway-ExtraBold.ttf");
	ft_gui_elem_init_grid(head, "win_author_nshelly", 61, \
		(t_gui_coord){1, 5, 0});
	ft_gui_elem_set_color(elem->child, 0xffffff);
	ft_gui_elem_set_text(elem->child, "nshelly", 36, \
		"fonts/Raleway-ExtraBold.ttf");
	ft_gui_elem_init_grid(head, "win_author_tjuana", 71, \
		(t_gui_coord){1, 5, 0});
	ft_gui_elem_set_color(elem->child, 0xffffff);
	ft_gui_elem_set_text(elem->child, "tjuana", 36, \
		"fonts/Raleway-ExtraBold.ttf");
}

void	ft_main_gui_init_win_author_3(t_list *head)
{
	t_gui_elem	*elem;

	elem = head->content;
	ft_gui_elem_init_grid(head, "win_author_btnmenu", 91, \
		(t_gui_coord){2, 1, 0});
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

void	ft_main_gui_init_win_author(t_list *head)
{
	t_gui_elem	*elem;

	elem = head->content;
	ft_main_gui_init_win_author_1(head);
	ft_main_gui_init_win_author_2(head);
	ft_main_gui_init_win_author_3(head);
}
