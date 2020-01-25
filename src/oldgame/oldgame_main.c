/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   oldgame_main.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dorange- <dorange-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/24 13:33:34 by tjuana            #+#    #+#             */
/*   Updated: 2020/01/25 16:39:55 by dorange-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"
# define DEG_30 0.52360

void	ft_game_gui_init_menu(t_list *head)
{
	t_gui_elem	*elem;

	elem = head->content;

	ft_gui_elem_init(&elem->child, "win_hud_live", (t_gui_coord){118, 18, 0}, \
	 	(t_gui_coord){144, 44, 0});
	// ft_gui_elem_init(&elem->child, "win_hud_live", (t_gui_coord){116, 16, 0}, \
	//  	(t_gui_coord){516, 416, 0});
	ft_gui_elem_set_color(elem->child, 0xffffff);
	ft_gui_elem_set_image(elem->child, "img/like.png");
	ft_gui_elem_set_parent(head, elem->child);

	ft_gui_elem_init(&elem->child, "win_hud_livescount", (t_gui_coord){150, 10, 0}, \
		(t_gui_coord){254, 50, 0});
	ft_gui_elem_set_color(elem->child, 0xffffff);
	ft_gui_elem_set_text(elem->child, "100", 16);
	ft_gui_elem_set_parent(head, elem->child);

	ft_gui_elem_init(&elem->child, "win_hud_pistol", (t_gui_coord){216, 16, 0}, \
	 	(t_gui_coord){248, 48, 0});
	// ft_gui_elem_init(&elem->child, "win_hud_live", (t_gui_coord){116, 16, 0}, \
	//  	(t_gui_coord){516, 416, 0});
	ft_gui_elem_set_color(elem->child, 0xffffff);
	ft_gui_elem_set_image(elem->child, "img/pistol.png");
	ft_gui_elem_set_parent(head, elem->child);

	ft_gui_elem_init(&elem->child, "win_hud_pistolcount", (t_gui_coord){250, 10, 0}, \
		(t_gui_coord){354, 50, 0});
	ft_gui_elem_set_color(elem->child, 0xffffff);
	ft_gui_elem_set_text(elem->child, "100", 16);
	ft_gui_elem_set_parent(head, elem->child);

	//pistol.png
}

void	ft_game_gui_init_hud(t_list *head)
{
	t_gui_elem	*elem;

	elem = head->content;
	ft_gui_elem_init(&elem->child, "win_hud", (t_gui_coord){100, 0, 0}, \
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

	ft_gui_elem_init(&w->gui.dom, "win", (t_gui_coord){0, 0, 0}, \
		(t_gui_coord){WIN_WIDTH, WIN_HEIGHT, 0});
	ft_gui_elem_set_color(w->gui.dom, 0x000000);
	ft_gui_elem_set_redraw(w->gui.dom, ft_game_render);
	ft_gui_elem_set_redraw_font(w->gui.dom, ft_game_render_font);
	ft_game_gui_init_hud(w->gui.dom);
}

int	main(int c, char **v)
{
	t_wolf3d	w;

	// Set map type
	w.type = 0;
	if (c == 2)
		w.type = 1;
	if (c == 3 && ft_strcmp(v[2], "nmap"))
		w.type = 2;

	// Check arguments and file
	if (w.type < 1)
		ft_error("Error: wrong parameters");
	if ((w.fd = open(v[1], O_RDONLY)) < 0)
		ft_error("Error: bad file");

	ft_parser_nnmp(w.fd, &w);
	ft_print_sectors(w.sector); // check sector
	w.sdl = sdl_init(w.sdl);
	ft_init_wolf(&w);

	w.status = 2;

	// gui init
	ft_game_gui_init(&w);
	ft_gui_print_element_list(w.gui.dom, 0);

	// ft_print_lines(&w); // Print the vertexes of lines
	// ft_print_sectors(w.sector);
	ft_load_textures(&w);
	ft_init_anim(&w);
	ft_init_view_map(&w);
	ft_init_sound(&w);
	fpsinit();
	while (w.sdl->running)
	{
		ft_gui_redraw(&w);
		// renderer(&w);
		ft_handle_events(&w);
		ft_use_events(&w);
	}
	ft_clean_sdl(&w);
	return (0);
}
