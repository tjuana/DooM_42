/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_map_parse3.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjuana <tjuana@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/16 15:44:06 by tjuana            #+#    #+#             */
/*   Updated: 2020/02/16 15:46:13 by tjuana           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

void	ft_check_ver_nei(int v_c, t_file_read file)
{
	if ((v_c / 2) != file.tmp[file.count_sectors2])
		ft_error("BAD NEIGHBOUR");
}
