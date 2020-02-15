/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_math_functions3.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nshelly <nshelly@student.21school.>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/15 17:32:04 by nshelly           #+#    #+#             */
/*   Updated: 2020/02/15 17:32:04 by nshelly          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

t_new_xy	sum_vectors_xy(t_new_xy v0, t_new_xy v1)
{
	t_new_xy result;

	result.x = v0.x + v1.x;
	result.y = v0.y + v1.y;
	return (result);
}

int			hexcolor(int r, int g, int b)
{
	return ((r << 16) | (g << 8) | b);
}
