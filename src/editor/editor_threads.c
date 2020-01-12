/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   editor_threads.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dorange- <dorange-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/12 19:07:04 by dorange-          #+#    #+#             */
/*   Updated: 2020/01/12 19:51:40 by dorange-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

void		*ft_editor_begin_game(void *w);

void		ft_editor_threading(t_wolf3d *w)
{
	int			x;
	int			xx;
	pthread_t	threads[THREADS];
	t_threads	args[THREADS];

	x = -1;
	xx = 0;
	while (++x < THREADS)
	{
		args[x].t1 = xx;
		args[x].t2 = xx + ((WIN_WIDTH / THREADS));
		// printf("%d   %d\n", args[x].t1, args[x].t2);
		ft_init_multi_wolf(&args[x].w, w);
		pthread_create(&threads[x], NULL, ft_editor_begin_game, (void*)&args[x]);
		xx += (WIN_WIDTH / THREADS);
	}
	x = -1;
	while (++x < THREADS)
		pthread_join(threads[x], NULL);
}

void	ft_editor_map_fill_sectors_for_threads(t_threads *a)
{
	int	y;
	int	x;
	int	color;
	int	pos;

	x = a->t1;
	y = a->w.ui_map.v1.y;
	while (y < a->w.ui_map.v2.y)
	{
		if (ft_sector_check_sector(&a->w, (t_vector3){x, y, 0, 0}))
		{
			pos = x + (y * WIN_WIDTH);
			color = ft_fdf_get_color(0xffff00, (int)a->w.sdl->pixels[pos], 0.7);
			a->w.sdl->pixels[pos] = color;
		}
		y++;
	}
}

void		*ft_editor_begin_game(void *w)
{
	t_threads *p;

	p = (t_threads *)w;
	while (p->t1 < p->t2)
	{
		ft_editor_map_fill_sectors_for_threads(p);
		p->t1++;
	}
	return (NULL);
}
