/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gui_init.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dorange- <dorange-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/14 17:00:08 by dorange-          #+#    #+#             */
/*   Updated: 2020/01/14 19:04:57 by dorange-         ###   ########.fr       */
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

	win = head->content;
	ft_gui_elem_init(&win->child, (t_ui_coord){20, 20, 0}, \
		(t_ui_coord){100, 100, 0}, 2);
	ft_gui_elem_set_color(win->child, 0x00ff00);
	ft_gui_elem_set_parent(head, win->child);

	ft_gui_elem_init(&win->child, (t_ui_coord){1000, 20, 0}, \
		(t_ui_coord){1100, 100, 0}, 2);
	ft_gui_elem_set_color(win->child, 0x0000ff);
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
	ft_gui_elem_init(&w->gui.dom, (t_ui_coord){0, 0, 0}, \
		(t_ui_coord){WIN_WIDTH, WIN_HEIGHT, 0}, 2);
	ft_gui_elem_set_color(w->gui.dom, 0xff0000);
	ft_gui_init_dom(w->gui.dom);
}