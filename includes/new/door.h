/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   door.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dorange- <dorange-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/21 21:15:08 by dorange-          #+#    #+#             */
/*   Updated: 2020/02/21 21:15:09 by dorange-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DOOR_H
# define DOOR_H

/*
** **************************************************************************
**	t_new_tmp_trio
**
**	Structure for game sector.
**
**	Arguments:
**	int s_nb		| door sector nb
**	float spd		| speed of lift door up or down
**	int max_d		| lift up while max_d
**	int min_d		| lift down while min_d
**	int state		| 0-close 1-open
**	int key			| key id
** **************************************************************************
*/
typedef struct	s_new_door
{
	int			s_nb;
	float		spd;
	int			max_d;
	int			min_d;
	int			state;
	int			key;
}				t_new_door;

/*
** **************************************************************************
**	t_new_tmp_trio
**
**	Structure for game sector.
**
**	Arguments:
**	int s_nb		| button sector nb
**	int state		|
** **************************************************************************
*/
typedef struct	s_new_but
{
	int			s_nb;
	int			state;
}				t_new_but;

#endif
