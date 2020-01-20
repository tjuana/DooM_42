/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   editor_redraw.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dorange- <dorange-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/20 16:06:28 by dorange-          #+#    #+#             */
/*   Updated: 2020/01/20 16:07:43 by dorange-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

void	ft_editor_redraw(void *ptr)
{
	t_wolf3d	*w;

	w = (t_wolf3d*)w;
	ft_gui_draw_sprites(w);
	ft_gui_draw_enemies(w);
}