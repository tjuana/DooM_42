/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_load_sounds.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjuana <tjuana@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/08 12:08:45 by tjuana            #+#    #+#             */
/*   Updated: 2020/02/22 18:28:34 by tjuana           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

/*
** **************************************************************************
**	void ft_game_player_init_config(t_new_player *pl)
** **************************************************************************
*/

void	ft_load_sounds(t_new_player *pl)
{
	pl->sound_pistol = ft_load_sound("Sounds/pistol.wav");
	pl->sound_door = ft_load_sound("Sounds/door.wav");
	pl->sound_death = ft_load_sound("Sounds/Death 1.wav");
	pl->sound_fly = ft_load_sound("Sounds/Rocket Launcher.wav");
}
