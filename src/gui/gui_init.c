/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gui_init.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dorange- <dorange-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/25 17:57:51 by dorange-          #+#    #+#             */
/*   Updated: 2020/01/26 15:08:18 by dorange-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

void	ft_gui_init(t_wolf3d *w)
{
	w->gui.win_w = WIN_WIDTH;
	w->gui.win_h = WIN_HEIGHT;
	w->gui.focus_elem = NULL;
}