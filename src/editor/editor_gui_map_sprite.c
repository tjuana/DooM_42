/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   editor_gui_map_sprite.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dorange- <dorange-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/19 17:05:37 by dorange-          #+#    #+#             */
/*   Updated: 2020/01/21 14:33:55 by dorange-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

void	ft_set_sprite(t_wolf3d *w, t_vector3 pos, int type)
{
	t_list		*list;
	t_sprite	*sprite;

	sprite = ft_my_malloc(sizeof(t_sprite));
	ft_bzero_char(sprite, sizeof(t_sprite));

	sprite->id = w->sprite_count + 1;
	sprite->pos = pos;
	sprite->texture = type;

	list = ft_lstnew(sprite, sizeof(t_sprite));
	if (w->sprite == NULL)
		w->sprite = list;
	else
		ft_lstadd(&w->sprite, list);
	w->sprite_count++;
	w->sprite_status = 0;
}

void	ft_delete_sprite(t_wolf3d *w)
{
	t_list	*list;

	if (w->sprite == NULL)
		return ;
	list = w->sprite;
	w->sprite = w->sprite->next;
	free(list->content);
	free(list);
}

/*
**	void ft_gui_elem_set_map(t_list *list, void *str)
**	
**	Function that set map type for gui element.
*/
void			ft_gui_elem_set_map(t_list *list)
{
	t_gui_elem	*elem;

	elem = list->content;
	elem->type = GUI_MAP;
	ft_gui_elem_set_event(list, ft_gui_mousemotion_win_map, SDL_MOUSEMOTION, 0);
	ft_gui_elem_set_event(list, ft_gui_mousebuttondown_win_map, SDL_MOUSEBUTTONDOWN, 0);
	ft_gui_elem_set_event(list, ft_gui_mousebuttonup_win_map, SDL_MOUSEBUTTONUP, 0);
	ft_gui_elem_set_event(list, ft_gui_mousewheel_win_map, SDL_MOUSEWHEEL, 0);
}