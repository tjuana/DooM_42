/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gui_destruct.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjuana <tjuana@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/14 17:07:32 by dorange-          #+#    #+#             */
/*   Updated: 2020/01/29 14:54:27 by tjuana           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

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
**	void ft_gui_desctuct(t_list *dom)
**	
**	Function that destruct all gui values.
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
		// free(elem->surf); // How to close?
		free(elem->name);
		free(elem->str);
		free(elem);
		// ft_lstdel(list, ft_bzero);
		free(list);
	}
}

/*
**	void ft_gui_desctuct_fonts(t_list *fonts_list)
**	
**	Function that desctuct all fonts.
*/
void	ft_gui_desctuct_fonts(t_list *fonts_list)
{
	t_list		*list;
	t_gui_font	*font;

	list = fonts_list;
	if (list != NULL)
	{
		ft_gui_desctuct(list->next);
		font = list->content;
		TTF_CloseFont(font->ptr);
		free(font->path);
	}
}