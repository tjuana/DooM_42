/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_main.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: drafe <drafe@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/08 12:08:45 by tjuana            #+#    #+#             */
/*   Updated: 2020/02/16 16:40:21 by drafe            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

void	player_init(t_new_player *pl, t_new_xy *v, int *n)
{
	pl->pos.x = v->x;
	pl->pos.y = v->y;
	pl->pos.z = 0;
	pl->velo.x = 0;
	pl->velo.y = 0;
	pl->velo.z = 0;
	pl->angle = 0;
	pl->anglesin = 0;
	pl->anglecos = 0;
	pl->yaw = 0;
	pl->sector = *n;
	pl->ceil.nyceil = 0;
	pl->floor.nyfloor = 0;
	pl->near_point.y = 0.0001;
	pl->far_point.y = 5;
	pl->near_point.x = 0.00001;
	pl->far_point.x = 1000;
	pl->door_all = -1;
	pl->door_nb = -1;
	pl->but_all = -1;
	pl->but_nb = -1;
	pl->lvl = NULL;
	pl->light = 1;
	pl->pix = (int *)pl->srf->pixels;
}

void	ft_game_redraw(void *d, t_list *dom)
{
	t_wolf3d	*w;
	t_new_temp	*data;
	t_gun		wpn;

	w = (t_wolf3d*)d;
	data = w->new_data;
	wpn.sprite_counter = 1;
	engine_begin(data->pl);
	if (data->pl->count_sprite == 10)
	{
		wpn.sprite_counter = 2;
		data->pl->count_sprite = 1;
	}
	draw_pistol(&wpn, data->pl);
	data->pl->hole.z = data->se.ducking ? CROUCH_H : EYE_H;
	data->se.ground = !data->se.falling;
	events_jumps(&data->se, data->pl, &data->ot);
	motion_chk(data->pl, &data->ot, &data->se);
//	motion_move_pl(&(t_new_xy){0, 0}, data->pl);
	events_new_mouse_move(&data->ms, data->pl);
	events_vel(data->pl, &data->se, &data->ot);
	if (!events(&data->se, data->pl))
		return ;
	door(data->pl, &data->se);
}

void	ft_game_init(t_wolf3d *w, char *path)
{
	t_new_temp	*data;

	data = (t_new_temp*)w->new_data;
	data->pl->sectors_nb = 0;
	data->se.quit = 0;
	data->pl->srf = w->sdl->srf;
	ft_my_parse_map(data->pl, path);
	SDL_ShowCursor(SDL_ENABLE);
	data->se.wsad[0] = 0;
	data->se.wsad[1] = 0;
	data->se.wsad[2] = 0;
	data->se.wsad[3] = 0;
	data->se.falling = 1;
	data->se.ground = 0;
	data->ot.moving = 0;
	data->se.ducking = 0;
	data->ms.yaw = 0;
}

/*
** **************************************************************************
**	void ft_game_gui_init_menu(t_list *head)
**	Function that init gui elements for hud.
** **************************************************************************
*/

void	ft_game_gui_init_menu(t_list *head)
{
	t_gui_elem	*elem;

	elem = head->content;
	ft_gui_elem_init(&elem->child, "win_game_hud_live", (t_gui_coord)\
	{118, 18, 0}, (t_gui_coord){144, 44, 0});
	ft_gui_elem_set_color(elem->child, 0xffffff);
	ft_gui_elem_set_image(elem->child, "img/like.png");
	ft_gui_elem_set_parent(head, elem->child);
	ft_gui_elem_init(&elem->child, "win_game_hud_livescount", \
		(t_gui_coord){150, 10, 0}, (t_gui_coord){254, 50, 0});
	ft_gui_elem_set_color(elem->child, 0xffffff);
	ft_gui_elem_set_text(elem->child, "100", 16);
	ft_gui_elem_set_parent(head, elem->child);
	ft_gui_elem_init(&elem->child, "win_game_hud_pistol", \
		(t_gui_coord){216, 16, 0}, \
		(t_gui_coord){248, 48, 0});
	ft_gui_elem_set_color(elem->child, 0xffffff);
	ft_gui_elem_set_image(elem->child, "img/pistol.png");
	ft_gui_elem_set_parent(head, elem->child);
	ft_gui_elem_init(&elem->child, "win_game_hud_pistolcount", (t_gui_coord)\
	{250, 10, 0}, (t_gui_coord){354, 50, 0});
	ft_gui_elem_set_color(elem->child, 0xffffff);
	ft_gui_elem_set_text(elem->child, "100", 16);
	ft_gui_elem_set_parent(head, elem->child);
}

void	ft_game_gui_init_hud(t_list *head)
{
	t_gui_elem	*elem;

	elem = head->content;
	ft_gui_elem_init(&elem->child, "win_game_hud", (t_gui_coord){100, 0, 0}, \
		(t_gui_coord){WIN_WIDTH - 100, 60, 0});
	ft_gui_elem_set_color(elem->child, 0xbf000000);
	ft_gui_elem_set_parent(head, elem->child);
	ft_game_gui_init_menu(elem->child);
}
