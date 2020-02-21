/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_main_2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dorange- <dorange-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/21 19:28:15 by tjuana            #+#    #+#             */
/*   Updated: 2020/02/21 21:45:02 by dorange-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

/*
** **************************************************************************
**	void ft_game_init(t_wolf3d *w, char *path)
** **************************************************************************
*/
void		ft_game_init(t_wolf3d *w, char *path)
{
	t_new_temp	*data;

	data = w->new_data;
	data->pl->const_hfov = (0.73f * WIN_H);
	data->pl->const_vfov = (0.2f * WIN_H);
	data->pl->const_hfov_spec = (1.0 * 0.73f * WIN_H / WIN_W);
	data->pl->const_vfov_spec = (1.0 * .2f);
	data->pl->wolf3d = w;
	data->pl->sectors_nb = 0;
	data->se.quit = 0;
	data->pl->pixels = w->sdl->pixels;
	ft_game_my_parse_map(data->pl, path);
	data->pl->y_top = ft_my_malloc(sizeof(int) * WIN_WIDTH);
	data->pl->y_bot = ft_my_malloc(sizeof(int) * WIN_WIDTH);
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
**	void ft_game_gui_init_menu2(t_gui_elem *elem, t_list *head)
**	Function that init gui elements for hud.
** **************************************************************************
*/

static void	ft_gui_init_menu_2(t_gui_elem *elem, t_list *head)
{
	ft_gui_elem_init(&elem->child, "win_game_hud_pistolcount", \
		(t_gui_coord){250, 10, 0}, (t_gui_coord){354, 50, 0});
	ft_gui_elem_set_color(elem->child, 0xffffff);
	ft_gui_elem_set_text(elem->child, "10", 16, "fonts/Raleway-Bold.ttf");
	ft_gui_elem_set_parent(head, elem->child);
	ft_gui_elem_init(&elem->child, "win_game_hud_armors", \
		(t_gui_coord){316, 16, 0}, \
		(t_gui_coord){348, 48, 0});
	ft_gui_elem_set_color(elem->child, 0xffffff);
	ft_gui_elem_set_image(elem->child, "img/armors.png");
	ft_gui_elem_set_parent(head, elem->child);
	ft_gui_elem_init(&elem->child, "win_game_hud_armorscount", \
		(t_gui_coord){350, 10, 0}, (t_gui_coord){454, 50, 0});
	ft_gui_elem_set_color(elem->child, 0xffffff);
	ft_gui_elem_set_text(elem->child, "10", 16, "fonts/Raleway-Bold.ttf");
	ft_gui_elem_set_parent(head, elem->child);
	ft_gui_elem_init(&elem->child, "win_game_hud_filename", \
		(t_gui_coord){500, 10, 0}, (t_gui_coord){700, 50, 0});
	ft_gui_elem_set_color(elem->child, 0xffffff);
	ft_gui_elem_set_text(elem->child, "file", 16, "fonts/Raleway-Bold.ttf");
	ft_gui_elem_set_parent(head, elem->child);
}

/*
** **************************************************************************
**	void ft_game_gui_init_menu(t_list *head)
**	Function that init gui elements for hud.
** **************************************************************************
*/

void		ft_game_gui_init_menu(t_list *head)
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
	ft_gui_elem_set_text(elem->child, "100", 16, "fonts/Raleway-Bold.ttf");
	ft_gui_elem_set_parent(head, elem->child);
	ft_gui_elem_init(&elem->child, "win_game_hud_pistol", \
		(t_gui_coord){216, 16, 0}, \
		(t_gui_coord){248, 48, 0});
	ft_gui_elem_set_color(elem->child, 0xffffff);
	ft_gui_elem_set_image(elem->child, "img/pistol.png");
	ft_gui_elem_set_parent(head, elem->child);
	ft_gui_init_menu_2(elem, head);
}

/*
** **************************************************************************
**	void ft_game_gui_init_hud_help(t_list *head)
** **************************************************************************
*/

static void	ft_game_gui_init_hud_help(t_list *head, t_gui_elem *elem)
{
	ft_gui_elem_init(&elem->child, "win_game_diedtext", \
		(t_gui_coord){300, 300, 0}, (t_gui_coord){WIN_WIDTH, WIN_HEIGHT, 0});
	ft_gui_elem_set_color(elem->child, 0xfff0000);
	ft_gui_elem_set_text(elem->child, "VI UMERLI! HAH!", 72, \
									"fonts/Raleway-ExtraBold.ttf");
	ft_gui_elem_set_status(elem->child, GUI_ELEM_HIDDEN);
	ft_gui_elem_set_parent(head, elem->child);
}

/*
** **************************************************************************
**	void ft_game_gui_init_hud(t_list *head)
** **************************************************************************
*/

void		ft_game_gui_init_hud(t_list *head)
{
	t_gui_elem	*elem;

	elem = head->content;
	ft_gui_elem_init(&elem->child, "win_game_hud", \
		(t_gui_coord){100, 0, 0}, (t_gui_coord){WIN_WIDTH - 100, 60, 0});
	ft_gui_elem_set_color(elem->child, 0xbf000000);
	ft_gui_elem_set_parent(head, elem->child);
	ft_game_gui_init_menu(elem->child);
	ft_gui_elem_init(&elem->child, "win_game_doortext", \
		(t_gui_coord){300, 300, 0}, (t_gui_coord){WIN_WIDTH, WIN_HEIGHT, 0});
	ft_gui_elem_set_color(elem->child, 0xbfffff00);
	ft_gui_elem_set_text(elem->child, "DVER' MNE ZAPILI!", 72, \
										"fonts/Raleway-ExtraBold.ttf");
	ft_gui_elem_set_status(elem->child, GUI_ELEM_HIDDEN);
	ft_gui_elem_set_parent(head, elem->child);
	ft_gui_elem_init(&elem->child, "win_game_diedbg", (t_gui_coord){0, 0, 0}, \
		(t_gui_coord){WIN_WIDTH, WIN_HEIGHT, 0});
	ft_gui_elem_set_color(elem->child, 0xbfff0000);
	ft_gui_elem_set_status(elem->child, GUI_ELEM_HIDDEN);
	ft_gui_elem_set_parent(head, elem->child);
	ft_game_gui_init_hud_help(head, elem);
}
