/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_map_parse_3.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dorange- <dorange-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/16 15:44:06 by tjuana            #+#    #+#             */
/*   Updated: 2020/02/19 18:31:10 by dorange-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

// [deprecated function]
void	ft_game_check_ver_nei(int v_c, t_file_read file)
{
	if ((v_c / 2) != file.tmp[file.count_sectors2])
		ft_error("BAD NEIGHBOUR");
}
