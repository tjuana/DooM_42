/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   editor_save_file2.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjuana <tjuana@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/18 20:20:51 by tjuana            #+#    #+#             */
/*   Updated: 2020/01/18 20:50:29 by tjuana           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"
void	ft_save_to_file(t_wolf3d *w)
{
	if ((w->file.fd = open(w->file.name, O_CREAT | O_WRONLY | O_TRUNC, \
	S_IWRITE)) == -1)
		ft_error("open failed on output file");
}

// void	ft_print_to_file(t_wolf3d *w, int flag)
// {

// }