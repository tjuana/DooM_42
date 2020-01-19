/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   editor_save_file2.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjuana <tjuana@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/18 20:20:51 by tjuana            #+#    #+#             */
/*   Updated: 2020/01/19 14:49:17 by tjuana           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"
void	ft_save_to_file(t_wolf3d *w)
{

}

void	ft_print_to_file(t_wolf3d *w, int f)
{
	char	*sy;
	char	*sx;
	char	*space_or_not;

	sy = ft_strjoin(ft_strjoin("vertex\t", ft_itoa(w->file.i)), "\t");
	space_or_not =ft_strdup(" ");
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