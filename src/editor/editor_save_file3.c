/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   editor_save_file3.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjuana <tjuana@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/19 19:45:00 by tjuana            #+#    #+#             */
/*   Updated: 2020/01/25 22:22:01 by tjuana           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

static char		*ft_space_only_join(int j)
{
	char	*itoa;
	char	*join;

	itoa = ft_itoa(j);
	join = ft_strjoin(" ", itoa);
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
	join = ft_strjoin(tmp, " ");
	ft_strdel(&tmp);
	tmp = ft_strdup(join);
	ft_strdel(&join);
	itoa = ft_itoa(w->pl.pos.y);
	join = ft_strjoin(tmp, itoa);
	ft_strdel(&itoa);
	ft_strdel(&tmp);
	tmp = ft_strdup(join);
	ft_strdel(&join);
	join = ft_strjoin(tmp, "\t0\t0");
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
		j = -1;
		while (++j < sector->vertex_count)
		{
			str = ft_space_only_join(sector->neighbors[j]);
			ft_putstr_fd(str, fd);
			ft_strdel(&str);
		}
	}
}
