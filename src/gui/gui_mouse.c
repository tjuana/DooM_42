/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gui_mouse.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dorange- <dorange-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/14 19:58:53 by dorange-          #+#    #+#             */
/*   Updated: 2020/02/07 15:30:30 by dorange-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

/*
** **************************************************************************
**	int ft_gui_check_event_elem_area(t_gui_coord v, t_gui_elem *c)
**
**	Function that check event area.
** **************************************************************************
*/

int		ft_gui_check_event_area(t_gui_coord v, t_gui_coord v1, t_gui_coord v2)
{
	return (v.x >= v1.x && v.x < v2.x \
		&& v.y >= v1.y && v.y < v2.y);
}

/*
** **************************************************************************
**	int ft_gui_check_event_elem_area(t_gui_coord v, t_gui_elem *c)
**
**	Function that check event area.
** **************************************************************************
*/

int		ft_gui_check_event_elem_area(t_gui_coord v, t_gui_elem *c)
{
	return (v.x >= c->v1.x && v.x < c->v2.x \
		&& v.y >= c->v1.y && v.y < c->v2.y && c->status);
}

/*
** **************************************************************************
**	void ft_gui_init_mouse_pos(t_wolf3d *w)
**
**	Function that initialize mouse position.
** **************************************************************************
*/

void	ft_gui_init_mouse_pos(t_wolf3d *w)
{
	int			x;
	int			y;

	x = 0;
	y = 0;
	SDL_GetMouseState(&x, &y);
	w->gui.mouse_pos = (t_gui_coord){x, y, 0};
}
