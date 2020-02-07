/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   editor_save_file3.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjuana <tjuana@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/19 19:45:00 by tjuana            #+#    #+#             */
/*   Updated: 2020/02/07 15:15:57 by tjuana           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

static char		*ft_space_only_join(int j)
{
	char	*itoa;
	char	*join;

	itoa = ft_itoa(j - 1);
	join = ft_strjoin("\t", itoa);
	ft_strdel(&itoa);
	return (join);
}

void			ft_player_string(t_wolf3d *w)
{
	char	*itoa;
	char	*join;
	char	*tmp;

	itoa = ft_itoa(w->pl.pos.x);
	join = ft_strjoin("player\t", itoa);
	tmp = ft_strdup(join);
	ft_strdel(&itoa);
	ft_strdel(&join);
	join = ft_strjoin(tmp, "\t");
	ft_strdel(&tmp);
	tmp = ft_strdup(join);
	ft_strdel(&join);
	itoa = ft_itoa(w->pl.pos.y);
	join = ft_strjoin(tmp, itoa);
	ft_strdel(&itoa);
	ft_strdel(&tmp);
	tmp = ft_strdup(join);
	ft_strdel(&join);
	join = ft_strjoin(tmp, "\t1\t0");
	ft_strdel(&tmp);
	ft_putstr_fd(join, w->file.fd);
	ft_strdel(&join);
}

void			ft_save_neighbour(t_sector *sector, int fd)
{
	char	*str;
	int		j;

	if (sector->status == 1)
	{
		str = ft_space_only_join(sector->neighbors[sector->vertex_count - 1]);
		ft_putstr_fd(str, fd);
		ft_strdel(&str);
		j = -1;
		while (++j < (sector->vertex_count - 1))
		{
			str = ft_space_only_join(sector->neighbors[j]);
			ft_putstr_fd(str, fd);
			ft_strdel(&str);
		}
	}
}

void			ft_free_mf(t_wolf3d *w)
{
	t_list	*lst;
	int		i;

	lst = NULL;
	i = -1;
	lst = w->vertex;
	while (lst != NULL)
	{
		free(lst->content);
		free(lst);
		lst = lst->next;
	}
	while (++i < VER_HEIGHT)
		free(w->file.map[i]);
	free(w->file.map);
	w->file.map = NULL;
}

void			ft_allocate_int2darr(t_wolf3d *w)
{
	int	i;
	int count;
	int j;

	i = -1;
	j = 0;
	count = 0;
	w->file.map = NULL;
	w->file.map = ft_my_malloc(VER_HEIGHT * sizeof(int *));
	while (++i < VER_HEIGHT)
		w->file.map[i] = ft_my_malloc(sizeof(int) * VER_WIDTH);
	i = -1;
	j = -1;
	while (++i < VER_HEIGHT)
		while (++j < VER_HEIGHT)
			w->file.map[i][j] = 0;
}
