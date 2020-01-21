/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   editor_save_file.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjuana <tjuana@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/17 14:46:49 by tjuana            #+#    #+#             */
/*   Updated: 2020/01/21 18:46:39 by tjuana           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

void		ft_save_the_file(t_wolf3d *w)
{
	if ((w->file.fd = open("fuck_you.txt", O_CREAT | O_WRONLY | O_TRUNC, 0777)) \
			== -1)
		ft_error("open failed on output file");
	ft_editor_take_vertex(w);
	ft_count_origin_vertexes(w);
	ft_print_sectors_to_file(w, w->sector);
}

/*
**	void	ft_editor_take_vertex(t_wolf3d *w)
**	S
**	Function take vertex from sector list
**	and put it to int array of vertex were "y" is string
**	and column is "x"
**	D
*/

void		ft_editor_take_vertex(t_wolf3d *w)
{
	t_sector	*p_sec;
	t_list		*p_lst;
	int			j;
	int			tmp;
	int			b;

	p_lst = w->sector;
	while (p_lst != NULL)
	{
		p_sec = (t_sector*)p_lst->content;
		j = 0;
		b = 0;
		while (j < p_sec->vertex_count)
		{
			// ft_sort_list_vertex(p_sec->vertex[j]->y, p_sec->vertex[j]->x);
			
			tmp = p_sec->vertex[j]->y;
			b = p_sec->vertex[j]->x;
			w->file.sort[tmp][b] = 77;
			j++;
		}
		p_lst = p_lst->next;
	}
}

/*
**	void ft_clean_sdl(t_wolf3d *w)
**	A
**	D
**	заполнить лист с вершинами и порядковыми номерами
**	S
**	S
*/

void		ft_count_origin_vertexes(t_wolf3d *w)
{
	int	f;

	w->file.count = 0;
	w->file.i = -1;
	while (++w->file.i <= VER_HEIGHT)
	{
		w->file.j = -1;
		f = 0;
		while (++w->file.j <= VER_WIDTH)
		{
			if (w->file.sort[w->file.i][w->file.j] == 77)
			{
				ft_print_to_file(w, f);
				f = 1;
				ft_create_list_of_vertexes(w);\
				w->file.count++;
			}
		}
	}
	ft_putstr_fd("\n\n", w->file.fd);
}

/*
**	void ft_clean_sdl(t_wolf3d *w)
**	s
**	create list of vertexes
**	!!!!!7!!!!!
**	!!0!!!!!0!!
**	!!!!!7!!!!!
*/

void		ft_create_list_of_vertexes(t_wolf3d *w)
{
	t_vector3	*vertexes;
	t_list		*lst;
	t_sector	*ptr_sector;
	t_list		*ptr_list;
	int			f;

	ptr_list = w->sector;
	vertexes = ft_my_malloc(sizeof(t_vector3));
	vertexes->x = w->file.j;
	vertexes->y = w->file.i;
	vertexes->w = w->file.count;
	lst = ft_lstnew(vertexes, sizeof(vertexes));
	if (w->vertex == NULL)
		w->vertex = lst;
	else
		ft_lstadd(&(w->vertex), lst);
	ft_sector_num_vertex(ptr_list, vertexes);
}

/*
**	void ft_clean_sdl(t_wolf3d *w)
**	s
**	give order number to vertex in sector
**	!!!!!7!!!!!
**	!!0!!!!!0!!
**	!!!!!7!!!!!
*/

void		ft_sector_num_vertex(t_list *ptr_list, t_vector3 *vertexes)
{
	t_sector	*ptr_sector;
	int			j;

	while (ptr_list != NULL)
	{
		ptr_sector = (t_sector*)ptr_list->content;
		j = -1;
		while (++j < ptr_sector->vertex_count)
		{
			if (ptr_sector->vertex[j]->x == vertexes->x && \
			ptr_sector->vertex[j]->y == vertexes->y)
			{
				ptr_sector->vertex[j]->w = vertexes->w;
			}
		}
		ptr_list = ptr_list->next;
	}
}
