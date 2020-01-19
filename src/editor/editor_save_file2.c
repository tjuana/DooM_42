/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   editor_save_file2.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjuana <tjuana@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/18 20:20:51 by tjuana            #+#    #+#             */
/*   Updated: 2020/01/19 17:03:29 by tjuana           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

void	ft_save_neighbour(t_sector *sector, int fd)
{
	char	*str;
	int		j;

	if (sector->status == 1)
	{
		j = -1;
		while (++j < sector->vertex_count)
		{
			str = ft_strjoin(" ", ft_itoa(sector->neighbors[j]));
			ft_putstr_fd(str, fd);
		}
	}
}

t_list	*ft_print_sectors_to_file(t_wolf3d *w, t_list *list)
{
	char		*str;
	t_sector	*sector;
	t_list		*ptr_list;
	int			j;

	ptr_list = list;
	if (ptr_list == NULL)
		return (0);
	sector = (t_sector*)ptr_list->content;
	str = ft_strjoin(ft_strjoin(ft_strjoin(ft_strjoin("sector\t", \
			ft_itoa(sector->height)), " "), ft_itoa(sector->floor)), "\t");
	ft_putstr_fd(str, w->file.fd);
	j = -1;
	while (++j < sector->vertex_count)
	{
		str = ft_strjoin(" ", ft_itoa(sector->vertex[j]->w));
		ft_putstr_fd(str, w->file.fd);
	}
	ft_putstr_fd("    ", w->file.fd);
	ft_strdel(&str);///????????????????????!!!OKIDJSFOIDF
	ft_save_neighbour(sector, w->file.fd);
	ft_putstr_fd("\n", w->file.fd);
	ft_strdel(&str);
	return (ft_print_sectors_to_file(w, ptr_list->next));
}

void	ft_print_to_file(t_wolf3d *w, int f)
{
	char	*sy;
	char	*sx;
	char	*space_or_not;

	sy = ft_strjoin(ft_strjoin("vertex\t", ft_itoa(w->file.i)), "\t");
	space_or_not = ft_strdup(" ");
	if (!f && w->file.count == 0)
	{
		ft_putstr_fd(sy, w->file.fd);
		space_or_not = "";
	}
	else if (!f)
	{
		space_or_not = "";
		ft_putstr_fd(ft_strjoin("\n", sy), w->file.fd);
	}
	sx = ft_strjoin(space_or_not, ft_itoa(w->file.j));
	ft_putstr_fd(sx, w->file.fd);
	ft_strdel(&sx);
	ft_strdel(&sy);
}
