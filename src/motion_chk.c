/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   motion_chk.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: drafe <drafe@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/25 18:20:12 by drafe             #+#    #+#             */
/*   Updated: 2020/01/28 16:51:05 by drafe            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

int		ft_step_forward_check(t_wolf3d *w, unsigned char flag)
{
	if (flag == 1)
	{
		w->temp = w->map.map[(int)(w->pl.pos.x + w->pl.dir.x * w->ms * 5)
		+ (int)w->pl.pos.y * w->map.m_wid];
		if (!w->temp || w->temp == 20)
			return (1);
	}
	else if (flag == 0)
	{
		w->temp = w->map.map[(int)(w->pl.pos.y + w->pl.dir.y * w->ms * 5)
		* w->map.m_wid + (int)w->pl.pos.x];
		if (!w->temp || w->temp == 20)
			return (1);
	}
	return (0);
}
