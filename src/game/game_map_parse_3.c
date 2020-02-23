/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_map_parse_3.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: drafe <drafe@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/28 14:16:26 by tjuana            #+#    #+#             */
/*   Updated: 2020/02/22 15:10:08 by drafe            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

void	ft_game_sector_save_bad_neib(int sec)
{
	ft_putstr_fd("sector:", 2);
	ft_putnbr_fd(sec, 2);
	ft_putstr_fd(" ", 2);
	ft_error("BAD NEIGHBOUR");
}
