/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_main_1.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjuana <tjuana@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/08 12:08:45 by tjuana            #+#    #+#             */
/*   Updated: 2020/02/24 18:33:10 by tjuana           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

/*
** **************************************************************************
**	void ft_game_player_init_config(t_new_player *pl)
** **************************************************************************
*/

void		ft_game_player_init_config(t_new_player *pl)
{
	t_list		*list;
	t_gui_elem	*elem;

	pl->light = 1;
	pl->live_count = 100;
	pl->bullet_count = 10;
	pl->status = PL_STATUS_LIVE;
	pl->died_timer = 0;
	pl->f = GREEN;
	pl->n = ROCK1;
	pl->ch = 0;
	list = ft_gui_search_elem_by_name(\
		((t_wolf3d*)pl->wolf3d)->gui.dom, \
		"win_game_hud_pistolcount");
	elem = list->content;
	free(elem->str);
	elem->str = ft_itoa(pl->bullet_count);
	list = ft_gui_search_elem_by_name(\
		((t_wolf3d*)pl->wolf3d)->gui.dom, \
		"win_game_hud_livescount");
	elem = list->content;
	free(elem->str);
	elem->str = ft_itoa(pl->live_count);
}

/*
** **************************************************************************
**	void ft_game_player_init(t_new_player *pl, t_vector3 *v, int *n)
** **************************************************************************
*/

void		ft_game_player_init(t_new_player *pl, t_vector3 *v, int *n)
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
	pl->near_point.y = 0.001;
	pl->far_point.y = 5;
	pl->near_point.x = 0.00001;
	pl->far_point.x = 1000;
	pl->door_all = -1;
	pl->door_nb = -1;
	pl->but_all = -1;
	pl->but_nb = -1;
	pl->lvl = NULL;
	pl->pix = pl->pixels;
	ft_game_player_init_config(pl);
}

/*
** **************************************************************************
**	void ft_gui_dead(t_wolf3d *w)
** **************************************************************************
*/

static void	ft_gui_dead(t_wolf3d *w)
{
	t_new_player	*pl;

	pl = ((t_new_temp*)w->new_data)->pl;
	if (w->gui.mode != GUI_MD_GAME)
		return ;
	if (pl->status == PL_STATUS_DEAD)
	{
		sleep(3);
		ft_gui_elem_set_status(\
			ft_gui_search_elem_by_name(w->gui.dom, \
			"win_game_doortext"), GUI_ELEM_HIDDEN);
		ft_gui_elem_set_status(\
			ft_gui_search_elem_by_name(w->gui.dom, \
			"win_game_diedtext"), GUI_ELEM_HIDDEN);
		ft_gui_elem_set_status(ft_gui_search_elem_by_name(w->gui.dom, \
			"win_game_diedbg"), GUI_ELEM_HIDDEN);
		w->player_status = 0;
		ft_game_end_game(pl, pl->file.ag);
		return ;
	}
}

static void	ft_game_gui_exit(t_wolf3d *w)
{
	t_new_player	*pl;

	pl = ((t_new_temp*)w->new_data)->pl;
	if (w->gui.mode != GUI_MD_GAME)
		return ;
	if (pl->status == PL_STATUS_EXIT_GAME)
	{
		sleep(3);
		ft_gui_elem_set_status(\
			ft_gui_search_elem_by_name(w->gui.dom, \
			"win_game_doortext"), GUI_ELEM_HIDDEN);
		w->player_status = 0;
		w->sdl->running = 0;
		return ;
	}
}

static void	ft_game_redraw_help(t_new_temp *data)
{
	t_gun		wpn;

	wpn.sprite_counter = 1;
	ft_game_engine_begin(data->pl);
	if (data->pl->count_sprite == 10)
	{
		wpn.sprite_counter = 2;
		data->pl->count_sprite = 1;
		data->pl->bullet_status = 1;
		data->pl->bullet_frame = 0;
		// wpn.scale = 100;
	}
	// ft_game_draw_sprite(data->pl);
	ft_game_draw_pistol(&wpn, data->pl);
	ft_game_draw_bullet(&wpn, data->pl);
}

/*
** **************************************************************************
**	void ft_game_redraw(t_wolf3d *w, t_list *dom)
** **************************************************************************
*/

void		ft_game_redraw(t_wolf3d *w, t_list *dom)
{
	t_new_temp	*data;

	(void)dom;
	if (((t_new_temp*)w->new_data)->pl->status == PL_STATUS_DEAD)
		ft_gui_dead(w);
	else if (((t_new_temp*)w->new_data)->pl->status == PL_STATUS_EXIT_GAME)
		ft_game_gui_exit(w);
	else
	{
		data = w->new_data;
		ft_game_redraw_help(data);
		data->pl->hole.z = data->se.ducking ? CROUCH_H + 1.5 : EYE_H;
		data->se.ground = !data->se.falling;
		ft_game_events_jumps(&data->se, data->pl, &data->ot);
		ft_game_motion_chk(data->pl, &data->ot, &data->se);
		ft_game_events_new_mouse_move(&data->ms, data->pl);
		ft_game_events_vel(data->pl, &data->se, &data->ot);
		if (!events(&data->se, data->pl))
			return ;
		door(data->pl, &data->se);
	}
}
