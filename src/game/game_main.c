/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_main.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dorange- <dorange-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/08 12:08:45 by tjuana            #+#    #+#             */
/*   Updated: 2020/02/14 15:52:55 by dorange-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

void player_init(t_new_player *pl, t_new_xy *v, int *n)//init data for LoadData function
{
    //player = (struct player) { {v->x, v->y, 0}, {0,0,0}, *angle,0,0,0, n };
    pl->where.x = v->x;
    pl->where.y = v->y;
    pl->where.z = 0;
    pl->velocity.x = 0;
    pl->velocity.y = 0;
    pl->velocity.z = 0;
    pl->angle = 0;
    pl->anglesin = 0;
    pl->anglecos = 0;
    pl->yaw = 0;
    pl->sector = *n;
	pl->ceil.nyceil = 0;
	pl->floor.nyfloor = 0;
	//If it's partially behind the player, clip it against player's view frustrum
	pl->nearz = 0.0001;
	pl->farz = 5;
	pl->nearside = 0.00001;
	pl->farside = 1000;
	pl->door_all = -1;
	pl->door_nb = -1;
	pl->but_all = -1;
	pl->but_nb = -1;
	pl->lvl = NULL;
	pl->light = 1.0f;
	pl->pix = (int *)pl->srf->pixels;
}

void vline(int x, int y1,int y2, int top,int middle,int bottom, SDL_Surface* surface)
{
    int	*pix;

	pix = (int*)surface->pixels;
    y1 = clamp(y1, 0, WIN_H - 1);
    y2 = clamp(y2, 0, WIN_H - 1);
    if(y2 == y1)
        pix[y1* WIN_W + x] = middle;
    else if(y2 > y1)
    {
        pix[y1 * WIN_W + x] = top;
        for(int y= y1 + 1; y < y2; ++y)
            pix[y * WIN_W + x] = middle;
        pix[y2 * WIN_W + x] = bottom;
    }
}

void	ft_game_redraw(void *d, t_list *dom)
{
	t_wolf3d	*w;
	t_new_temp	*data;
	t_gun	wpn;

	w = (t_wolf3d*)d;
	data = w->new_data;
	wpn.sprite_counter = 1;
	engine_begin(&data->pl);
	if (data->pl.count_sprite == 10)// this for the event shoot
 	{
 		wpn.sprite_counter = 2;
		data->pl.count_sprite = 1;
	}

	draw_pistol(&wpn, &data->pl);
	data->op.eye_h = data->se.ducking ? CROUCH_H : EYE_H;
	data->se.ground = !data->se.falling;
	events_jumps(&data->se, &data->pl, &data->op, &data->ot);
	motion_chk(&data->op, &data->pl, &data->ot, &data->se);
	//motion_move_pl(0, 0, &data->pl);
	events_new_mouse_move(&data->ms, &data->pl);//mouse aiming
	events_vel(&data->pl, &data->se, &data->ot);
	if (!events(&data->se, &data->pl))
		return ;
	door(&data->pl, &data->se);
}

void	ft_game_init(t_wolf3d *w, char *path)
{
	t_new_temp	*data;

	data = (t_new_temp*)w->new_data;
	data->pl.sectors_nb = 0;
	data->se.quit = 0;
	data->pl.srf = w->sdl->srf;
	ft_my_parse_map(&data->pl, path);
	SDL_ShowCursor(SDL_ENABLE);//NOT SHOW MOUSE CURSOR
	data->se.wsad[0] = 0;
	data->se.wsad[1] = 0;
	data->se.wsad[2] = 0;
	data->se.wsad[3] = 0;
	data->se.falling = 1;
	data->se.ground = 0;
	data->ot.moving = 0;
	data->se.ducking = 0;
	data->ms.yaw = 0;
	//data->pl.srf = w->sdl->srf;??
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
	ft_gui_elem_init(&elem->child, "win_game_hud_live", \
		(t_gui_coord){118, 18, 0}, (t_gui_coord){144, 44, 0});
	ft_gui_elem_set_color(elem->child, 0xffffff);
	ft_gui_elem_set_image(elem->child, "img/like.png");
	ft_gui_elem_set_parent(head, elem->child);
	ft_gui_elem_init(&elem->child, "win_game_hud_livescount", \
		(t_gui_coord){150, 10, 0}, (t_gui_coord){254, 50, 0});
	ft_gui_elem_set_color(elem->child, 0xffffff);
	ft_gui_elem_set_text(elem->child, "100", 16);
	ft_gui_elem_set_parent(head, elem->child);
	ft_gui_elem_init(&elem->child, "win_game_hud_pistol", \
		(t_gui_coord){216, 16, 0}, (t_gui_coord){248, 48, 0});
	ft_gui_elem_set_color(elem->child, 0xffffff);
	ft_gui_elem_set_image(elem->child, "img/pistol.png");
	ft_gui_elem_set_parent(head, elem->child);
	ft_gui_elem_init(&elem->child, "win_game_hud_pistolcount", \
		(t_gui_coord){250, 10, 0}, (t_gui_coord){354, 50, 0});
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
	// ft_gui_elem_set_color(elem->child, 0xbffd7c6e);
	ft_gui_elem_set_color(elem->child, 0xbf000000);
	ft_gui_elem_set_parent(head, elem->child);
	ft_game_gui_init_menu(elem->child);
}

void	ft_game_gui_init(t_wolf3d *w)
{
	// gui init element
	w->gui.redraw = 0;
	w->gui.redraw_elem = NULL;
	w->gui.search_elem = GUI_EVENT_OFF;
	w->gui.dom = NULL;
	w->gui.fonts = NULL;
	w->gui.mode = GUI_MD_ME;

	ft_gui_elem_init(&w->gui.dom, "win_game", (t_gui_coord){0, 0, 0}, \
		(t_gui_coord){WIN_WIDTH, WIN_HEIGHT, 0});
	ft_gui_elem_set_color(w->gui.dom, 0x0000FF);
	ft_gui_elem_set_redraw(w->gui.dom, ft_game_redraw);
	// ft_gui_elem_set_redraw_font(w->gui.dom, ft_game_render_font);
	ft_game_gui_init_hud(w->gui.dom);
}
