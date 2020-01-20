/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   editor_init.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dorange- <dorange-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/12 12:07:54 by dorange-          #+#    #+#             */
/*   Updated: 2020/01/20 18:22:11 by dorange-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

/*
**	void ft_editor_init(t_wolf3d *w)
**
**	Function that init. some values...
*/
void		ft_editor_init(t_wolf3d *w)
{
	w->redraw = ft_editor_redraw;
	// w->sector_status = 0;
	// w->mouse_pos = (t_vector3){0, 0, 0, 0};
	// w->status = 1;
	w->sector_count = 0;
	w->sector = NULL;
	// w->txtr_opt_type = 1;
	// w->act_s = NULL;
}