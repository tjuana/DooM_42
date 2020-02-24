/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_engine_3.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjuana <tjuana@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/24 18:26:45 by dorange-          #+#    #+#             */
/*   Updated: 2020/02/24 18:36:25 by tjuana           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

void	ft_game_ceil_floor_move(t_new_player *pl)
{
	if (pl->flag_move_neighbors == 1)
	{
		if (pl->sect->ceil - pl->sect->floor < 20.0)
			pl->sect->ceil += 0.02;
	}
	if (pl->flag_move_neighbors == -1)
	{
		if (pl->sect->ceil - pl->sect->floor > 8.0)
			pl->sect->ceil -= 0.02;
	}
}
