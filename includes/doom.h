/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   doom.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dorange- <dorange-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/26 19:02:58 by dorange-          #+#    #+#             */
/*   Updated: 2020/02/22 13:40:28 by dorange-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DOOM_H
# define DOOM_H

# include "SDL2/SDL.h"
# include "SDL2/SDL_thread.h"
# include "SDL2/SDL_ttf.h"

# include <pthread.h>
# include <string.h>
# include <stdio.h>
# include <stdlib.h>
# include <fcntl.h>
# include <math.h>
# include <string.h>
# include <libft.h>

# include "const.h"

# include "algebra.h"
# include "file.h"

# include "general_struct.h"
# include "gui_struct.h"
# include "func_struct.h"
# include "editor_struct.h"

# include "new/wolf3d.h"

# include "func_func.h"
# include "gui_func.h"
# include "editor_func.h"

/*
** **************************************************************************
**	src/main/main.c
** **************************************************************************
*/
void	ft_main(int c, char **v);

/*
** **************************************************************************
**	src/main/main_btn_action.c
** **************************************************************************
*/
void	ft_gui_mousebuttonup_win_menu_btnauthor(void *data, SDL_Event e, \
			t_list *dom, int type);
void	ft_gui_mousebuttonup_win_author_btnmenu(void *data, SDL_Event e, \
			t_list *dom, int type);
void	ft_gui_mousebuttonup_win_menu_btngame(void *data, SDL_Event e, \
			t_list *dom, int type);
void	ft_gui_mousebuttonup_win_menu_btneditor(void *data, SDL_Event e, \
			t_list *dom, int type);
void	ft_gui_mousebuttonup_win_menu_btnexit(void *data, SDL_Event e, \
			t_list *dom, int type);

/*
** **************************************************************************
**	src/main/main_events.c
** **************************************************************************
*/
void	ft_main_events(t_wolf3d *w);

/*
** **************************************************************************
**	src/main/main_gui_init.c
** **************************************************************************
*/
void	ft_main_gui_init_win_1(t_list *head);
void	ft_main_gui_init_win_2(t_list *head);
void	ft_main_gui_init_win(t_list *head);
void	ft_main_gui_init(t_wolf3d *w);

/*
** **************************************************************************
**	src/main/main_gui_init_author.c
** **************************************************************************
*/
void	ft_main_gui_init_win_author_1(t_list *head);
void	ft_main_gui_init_win_author_2(t_list *head);
void	ft_main_gui_init_win_author_3(t_list *head);
void	ft_main_gui_init_win_author(t_list *head);

/*
** **************************************************************************
**	src/main/main_gui_init_menu.c
** **************************************************************************
*/
void	ft_main_gui_init_win_menu_btn_2(t_list *head);
void	ft_main_gui_init_win_menu_btn(t_list *head);
void	ft_main_gui_init_win_menu(t_list *head);

#endif
