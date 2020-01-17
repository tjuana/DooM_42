/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   editor_save_file.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjuana <tjuana@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/17 14:46:49 by tjuana            #+#    #+#             */
/*   Updated: 2020/01/17 15:22:56 by tjuana           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

void	ft_sort_vertex(t_wolf3d *w)
{
	int			i;
	int 		j;
	int			or_mum;

	or_mum = 0;
	i = -1;
	while (++i <= VER_WIDTH)
	{
		j = -1;
		while (j++ <= VER_HEIGHT)
		{
			if (w->sort[i][j] == 77)
			{
				y = i;
				x = j;
				w = or_mum;
				or_mum++;
			}
			
		}
	}
}

void	ft_editor_take_vertex(t_wolf3d *w)
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
			tmp = p_sec->vertex[j]->y;
			b = p_sec->vertex[j]->x;
			w->sort[tmp][b] = 77;
			j++;
		}
		p_lst = p_lst->next;
	}
}

void	ft_save_the_file(t_wolf3d *w)
{
	ft_bzero(&w->sort, sizeof(int)*VER_HEIGHT*VER_WIDTH);
	ft_editor_take_vertex(w);//take & sort vertex
	//создать список вершин
	// ft_sort_vertex(w);заполнить лист с вершинами и порядковыми номерами
	///проставить порядковые номера в секторах
}