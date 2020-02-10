/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   editor_map_sector.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dorange- <dorange-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/10 19:06:08 by dorange-          #+#    #+#             */
/*   Updated: 2020/02/10 15:01:08 by dorange-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

/*
** **************************************************************************
**	void ft_editor_turn_vertexes(t_sector *s, int numb)
** **************************************************************************
*/

void	ft_editor_turn_vertexes(t_sector *s, int numb)
{
	t_vector3	**vertex;
	int			i;

	vertex = ft_my_malloc(sizeof(void*) * (s->vertex_count));
	i = 0;
	while (numb < s->vertex_count)
	{
		vertex[i] = s->vertex[numb];
		printf("%d -> %d: [%.0f, %.0f]\n", numb, i, vertex[i]->x, vertex[i]->y);
		i++;
		numb++;
	}
	numb = 0;
	while (i < s->vertex_count)
	{
		vertex[i] = s->vertex[numb];
		printf("%d -> %d: [%.0f, %.0f]\n", numb, i, vertex[i]->x, vertex[i]->y);
		i++;
		numb++;
	}
	free(s->vertex);
	s->vertex = vertex;
}

/*
** **************************************************************************
**	void ft_editor_check_turn_vertexes(t_wolf3d *w)
** **************************************************************************
*/

void	ft_editor_check_turn_vertexes(t_wolf3d *w)
{
	t_sector	*s;
	int			numb;
	int			i;

	s = w->sector->content;
	numb = 0;
	i = 1;
	while (i < s->vertex_count)
	{
		if (s->vertex[numb]->x > s->vertex[i]->x && \
			s->vertex[numb]->y > s->vertex[i]->y)
		{
			numb = i;
			i = 0;
		}
		else
			i++;
	}
	if (numb != 0)
		ft_editor_turn_vertexes(s, numb);
}

/*
** **************************************************************************
**	void ft_editor_sector_create(t_wolf3d *w)
**
**	Function that create sector.
** **************************************************************************
*/

void		ft_editor_sector_create(t_wolf3d *w)
{
	t_sector	sector;
	t_list		*list_item;

	sector.id = w->sector_count + 1;
	sector.vertex = NULL;
	sector.neighbors = NULL;
	sector.vertex_count = 0;
	sector.status = SECTOR_STATUS_NOTHING;
	sector.type = SECTOR_TYPE_SECTOR;
	sector.floor = 0;
	sector.height = 10;
	list_item = ft_lstnew(&sector, sizeof(t_sector));
	if (w->sector == NULL)
		w->sector = list_item;
	else
		ft_lstadd(&(w->sector), list_item);
}

/*
** **************************************************************************
**	void ft_delete_sector(t_wolf3d *w)
**
**	Function that delete sector.
** **************************************************************************
*/

void		ft_delete_sector(t_wolf3d *w)
{
	t_list		*list;
	t_sector	*s;
	int			i;

	if (w->sector == NULL)
		return ;
	list = w->sector;
	w->sector = w->sector->next;
	s = list->content;
	i = 0;
	while (i < s->vertex_count)
	{
		free(s->vertex[i]);
		i++;
	}
	free(s->vertex);
	if (s->neighbors != NULL)
		free(s->neighbors);
	free(list->content);
	free(list);
}

/*
** **************************************************************************
**	t_sector *ft_editor_search_sector_by_id(t_wolf3d *w, t_list *list, int i)
**
**	Function that search sector by id.
** **************************************************************************
*/

t_sector	*ft_editor_search_sector_by_id(t_wolf3d *w, t_list *list, int i)
{
	t_sector	*sector;

	while (list)
	{
		sector = list->content;
		if (sector->id == i)
			return ((t_sector*)(list->content));
		list = list->next;
	}
	return (NULL);
}
