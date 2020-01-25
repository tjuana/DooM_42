/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gui_keydown.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dorange- <dorange-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/15 21:01:57 by dorange-          #+#    #+#             */
/*   Updated: 2020/01/25 18:20:33 by dorange-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

/*
**	void ft_gui_focus_keydown(t_wolf3d *w, SDL_Event e, t_list *dom)
**	
**	Function that set map name.
*/
void	ft_gui_focus_keydown(t_wolf3d *w, SDL_Event e, t_list *dom)
{
	char	c;
	t_gui_elem	*elem;
	char	*str;
	int		numb;

	w->gui.search_elem = GUI_EVENT_ON;
	elem = dom->content;
	// if (elem)
		// return ;
	if (e.key.keysym.scancode >= SDL_SCANCODE_A && \
		e.key.keysym.scancode <= SDL_SCANCODE_0)
	{
		if (ft_strlen(elem->str) > 20)
			return ;
		// Выделить в отдельную функцию (набор текста в input)
		if (e.key.keysym.scancode >= SDL_SCANCODE_A && \
			e.key.keysym.scancode <= SDL_SCANCODE_Z)
			c = 'a' + e.key.keysym.scancode - 4;
		if (e.key.keysym.scancode >= SDL_SCANCODE_1 && \
			e.key.keysym.scancode <= SDL_SCANCODE_9)
			c = '1' + e.key.keysym.scancode - SDL_SCANCODE_1;
		if (e.key.keysym.scancode == SDL_SCANCODE_0)
			c = '0';
		if (ft_strlen(elem->str) == 1 && elem->str[0] == ' ')
		{
			str = ft_strnew(1);
			str[0] = c;
		}
		else
		{
			str = ft_strnew(ft_strlen(elem->str) + 1);
			str = ft_strncpy(str, elem->str, ft_strlen(elem->str));
			str[ft_strlen(elem->str)] = c;
		}

		free(elem->str);
		elem->str = str;
	}
	else if (e.key.keysym.scancode == SDL_SCANCODE_BACKSPACE)
	{
		if (ft_strlen(elem->str) == 1)
			str = ft_strdup(" ");
		else
		{
			str = ft_strnew(ft_strlen(elem->str) - 1);
			str = ft_strncpy(str, elem->str, ft_strlen(elem->str) - 1);
		}
		free(elem->str);
		elem->str = str;
	}
	if (elem->type == GUI_INPUT_NUMB)
	{
		numb = ft_atoi(elem->str);
		if (e.key.keysym.scancode == SDL_SCANCODE_UP)
			numb++;
		if (e.key.keysym.scancode == SDL_SCANCODE_DOWN)
			numb--;

		if (numb > 1000)
			numb = 1000;
		if (numb < 0)
			numb = 0;
		free(elem->str);
		elem->str = ft_itoa(numb);
	}
}