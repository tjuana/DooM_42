/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gui_map_enemy.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dorange- <dorange-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/19 18:54:05 by dorange-          #+#    #+#             */
/*   Updated: 2020/01/19 19:34:25 by dorange-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

void	ft_set_enemy(t_wolf3d *w, t_vector3 pos, int type)
{
	t_list		*list;
	t_sprite	*sprite;

	sprite = ft_my_malloc(sizeof(t_sprite));
	ft_bzero_char(sprite, sizeof(t_sprite));

	sprite->id = w->enemy_count + 1;
	sprite->pos = pos;
	sprite->texture = type;

	list = ft_lstnew(sprite, sizeof(t_sprite));
	if (w->enemy == NULL)
		w->enemy = list;
	else
		ft_lstadd(&w->enemy, list);
	w->enemy_count++;
	w->enemy_status = 0;
}

void	ft_delete_enemy(t_wolf3d *w)
{
	t_list	*list;

	if (w->enemy == NULL)
		return ;
	list = w->enemy;
	w->enemy = w->enemy->next;
	free(list->content);
	free(list);
}