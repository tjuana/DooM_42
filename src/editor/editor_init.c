/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   editor_init.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dorange- <dorange-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/12 12:07:54 by dorange-          #+#    #+#             */
/*   Updated: 2020/02/16 19:47:02 by dorange-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

/*
** **************************************************************************
**	void ft_editor_init(t_wolf3d *w)
**
**	Function that set some editor parameters.
** **************************************************************************
*/

void		ft_editor_init(t_wolf3d *w)
{
	w->sector_count = 0;
	w->sector = NULL;
	w->txtr = NULL;
	w->txtr_count = 0;
	w->gui_map.r1 = (t_vector3){0, 0, 0, 0};
	w->gui_map.r2 = (t_vector3){VER_WIDTH, VER_HEIGHT, 0, 0};
}
