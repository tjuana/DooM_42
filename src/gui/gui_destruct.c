/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gui_destruct.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dorange- <dorange-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/14 17:07:32 by dorange-          #+#    #+#             */
/*   Updated: 2020/02/20 12:43:56 by dorange-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

/*
** **************************************************************************
**	void ft_gui_desctuct_events(t_list *events)
**
**	Function that destruct all element events.
** **************************************************************************
*/

void	ft_gui_desctuct_events(t_list *events)
{
	if (events != NULL)
	{
		ft_gui_desctuct_events(events->next);
		free(events->content);
		free(events);
	}
}

/*
** **************************************************************************
**	void ft_gui_desctuct(t_list *dom)
**
**	Function that destruct all gui values.
** **************************************************************************
*/

void	ft_gui_desctuct(t_list *dom)
{
	t_list		*list;
	t_gui_elem	*elem;

	list = dom;
	if (list != NULL)
	{
		ft_gui_desctuct(list->next);
		elem = list->content;
		ft_gui_desctuct(elem->child);
		ft_gui_desctuct_events(elem->events);
		free(elem->name);
		free(elem->str);
		free(elem->font_path);
		free(elem);
		free(list);
	}
	dom = NULL;
}

/*
** **************************************************************************
**	void ft_gui_desctuct_fonts(t_list *fonts_list)
**
**	Function that desctuct all fonts.
** **************************************************************************
*/

void	ft_gui_desctuct_fonts(t_list *fonts_list)
{
	t_list		*list;
	t_gui_font	*font;

	list = fonts_list;
	if (list != NULL)
	{
		font = list->content;
		TTF_CloseFont(font->ptr);
		font->ptr = NULL;
		free(font->path);
	}
}
