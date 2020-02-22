/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gui_keydown.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dorange- <dorange-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/15 21:01:57 by dorange-          #+#    #+#             */
/*   Updated: 2020/02/21 17:27:27 by dorange-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

/*
** **************************************************************************
**	char ft_gui_get_keydown_letter(SDL_Event e)
**
**	Function that return keydown letter
** **************************************************************************
*/

char	ft_gui_get_keydown_letter(SDL_Event e)
{
	if (e.key.keysym.scancode >= SDL_SCANCODE_A && \
		e.key.keysym.scancode <= SDL_SCANCODE_Z)
		return ('a' + e.key.keysym.scancode - 4);
	if (e.key.keysym.scancode >= SDL_SCANCODE_1 && \
		e.key.keysym.scancode <= SDL_SCANCODE_9)
		return ('1' + e.key.keysym.scancode - SDL_SCANCODE_1);
	if (e.key.keysym.scancode == SDL_SCANCODE_0)
		return ('0');
	return ('\0');
}

/*
** **************************************************************************
**	void ft_gui_focus_add_letter(SDL_Event e, t_gui_elem *elem)
**
**	Function that add new letter for input.
** **************************************************************************
*/

void	ft_gui_focus_type_numb(SDL_Event e, t_gui_elem *elem)
{
	int	numb;

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

/*
** **************************************************************************
**	void ft_gui_focus_add_letter(SDL_Event e, t_gui_elem *elem)
**
**	Function that add new letter for input.
** **************************************************************************
*/

void	ft_gui_focus_add_letter(SDL_Event e, t_gui_elem *elem)
{
	char	c;
	char	*str;

	if (ft_strlen(elem->str) > 20)
		return ;
	c = ft_gui_get_keydown_letter(e);
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

/*
** **************************************************************************
**	void ft_gui_focus_delete_letter(t_gui_elem *elem)
**
**	Function that delete last letter.
** **************************************************************************
*/

void	ft_gui_focus_delete_letter(t_gui_elem *elem)
{
	char	*str;

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

/*
** **************************************************************************
**	void ft_gui_focus_keydown(t_wolf3d *w, SDL_Event e, t_list *dom)
**
**	Function that set map name.
** **************************************************************************
*/

void	ft_gui_focus_keydown(t_wolf3d *w, SDL_Event e, t_list *dom)
{
	t_gui_elem	*elem;

	w->gui.search_elem = GUI_EVENT_ON;
	elem = dom->content;
	if (e.key.keysym.scancode >= SDL_SCANCODE_A && \
		e.key.keysym.scancode <= SDL_SCANCODE_0)
		ft_gui_focus_add_letter(e, elem);
	else if (e.key.keysym.scancode == SDL_SCANCODE_BACKSPACE)
		ft_gui_focus_delete_letter(elem);
	if (elem->type == GUI_INPUT_NUMB)
		ft_gui_focus_type_numb(e, elem);
}
