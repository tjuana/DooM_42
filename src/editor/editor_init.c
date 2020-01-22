/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   editor_init.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dorange- <dorange-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/12 12:07:54 by dorange-          #+#    #+#             */
/*   Updated: 2020/01/22 17:48:35 by dorange-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

void		ft_editor_add_new_txtr(t_wolf3d *w, int color)
{
	t_txtr	txtr;
	t_list	*new_list;

	txtr.id = w->txtr_count + 1;
	txtr.color = color;
	new_list = ft_lstnew(&txtr, sizeof(txtr));
	if (w->txtr == NULL)
		w->txtr = new_list;
	else
		ft_lstadd(&w->txtr, new_list);
	w->txtr_count++;
}

void		ft_editor_init_txtr_list(t_wolf3d *w)
{
	ft_editor_add_new_txtr(w, 0xff0000);
	ft_editor_add_new_txtr(w, 0xffff00);
	ft_editor_add_new_txtr(w, 0x00ffff);
	ft_editor_add_new_txtr(w, 0x0000ff);
	ft_editor_add_new_txtr(w, 0xffcfab);
	ft_editor_add_new_txtr(w, 0x915f6d);
	ft_editor_add_new_txtr(w, 0xffa420);
	ft_editor_add_new_txtr(w, 0x8000ff);
	ft_editor_add_new_txtr(w, 0x00cccc);
	ft_editor_add_new_txtr(w, 0xf13a13);
	ft_editor_add_new_txtr(w, 0xca3767);
}



/*
**	void ft_editor_init(t_wolf3d *w)
**
**	Function that init. some values...
*/
void		ft_editor_init(t_wolf3d *w)
{
	// w->redraw = ft_editor_redraw;
	// w->sector_status = 0;
	// w->mouse_pos = (t_vector3){0, 0, 0, 0};
	// w->status = 1;
	w->sector_count = 0;
	w->sector = NULL;

	w->txtr = NULL;
	w->txtr_count = 0;
	
	ft_editor_init_txtr_list(w);

	w->gui_map.r1 = (t_vector3){0, 0, 0, 0};
	w->gui_map.r2 = (t_vector3){54, 33, 0, 0};
	// w->txtr_opt_type = 1;
	// w->act_s = NULL;
}