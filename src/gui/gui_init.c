/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gui_init.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dorange- <dorange-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/14 17:00:08 by dorange-          #+#    #+#             */
/*   Updated: 2020/01/15 15:00:41 by dorange-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

/*
**	void ft_gui_init(t_wolf3d *w)
**	
**	Function that set dom.
*/
void	ft_gui_init_dom(t_list *head)
{
	t_gui_elem	*win;
	// t_list		child;

	win = head->content;
	ft_gui_elem_init(&win->child, "elem1", (t_ui_coord){20, 20, 0}, \
		(t_ui_coord){100, 100, 0});
	ft_gui_elem_set_color(win->child, 0x00ff00);
	ft_gui_elem_set_event(win->child, ft_gui_mousemotion_elem1, SDL_MOUSEMOTION, 0);
	ft_gui_elem_set_parent(head, win->child);

	ft_gui_elem_init(&win->child, "elem2", (t_ui_coord){1000, 20, 0}, \
		(t_ui_coord){1100, 100, 0});
	ft_gui_elem_set_color(win->child, 0x0000ff);
	ft_gui_elem_set_parent(head, win->child);

	ft_gui_elem_init(&win->child, "win_btn", (t_ui_coord){500, 100, 0}, \
		(t_ui_coord){600, 200, 0});
	ft_gui_elem_set_color(win->child, 0x00ffff);
	ft_gui_elem_set_button(win->child, "Hello!");
	ft_gui_elem_set_parent(head, win->child);
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
	ft_gui_elem_init(&w->gui.dom, "win", (t_ui_coord){0, 0, 0}, \
		(t_ui_coord){WIN_WIDTH, WIN_HEIGHT, 0});
	ft_gui_elem_set_color(w->gui.dom, 0xff0000);
	ft_gui_init_dom(w->gui.dom);
}