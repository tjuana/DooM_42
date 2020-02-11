/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gui_elem_set_style.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dorange- <dorange-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/06 17:23:59 by dorange-          #+#    #+#             */
/*   Updated: 2020/02/06 17:58:57 by dorange-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

/*
** **************************************************************************
**	[TEMPORARY]
**	void ft_gui_elem_set_color(t_gui_elem *elem, int color)
**
**	Function that set gui element color.
** **************************************************************************
*/

void	ft_gui_elem_set_color(t_list *list, int color)
{
	t_gui_elem *elem;

	if (list == NULL)
		ft_error("ERROR (N2)");
	elem = list->content;
	elem->color = color;
}

/*
** **************************************************************************
**	void ft_gui_elem_set_text(t_list *list, void *str, int font_size)
**
**	Function that set text type for gui element.
** **************************************************************************
*/

void	ft_gui_elem_set_text(t_list *list, \
			void *str, int font_size)
{
	t_gui_elem	*elem;

	elem = list->content;
	elem->type = GUI_TEXT;
	elem->str = ft_strdup(str);
	elem->fs = font_size;
	elem->fs == 0 ? elem->fs = 16 : 0;
}

/*
** **************************************************************************
**	void ft_gui_elem_set_text(t_list *list, void *str, int font_size)
**
**	Function that set text type for gui element.
** **************************************************************************
*/

char	*ft_gui_elem_get_value(t_list *list)
{
	t_gui_elem	*elem;

	if (list == NULL)
		return (NULL);
	elem = list->content;
	return (elem->str);
}
