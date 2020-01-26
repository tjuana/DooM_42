/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gui_func.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dorange- <dorange-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/21 13:58:04 by dorange-          #+#    #+#             */
/*   Updated: 2020/01/26 16:45:58 by dorange-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GUI_FUNC_H
# define GUI_FUNC_H

# include <libft.h>
# include "SDL2/SDL.h"
# include "SDL2/SDL_ttf.h"

/*
** **************************************************************************
**	gui/gui_debug.c
** **************************************************************************
*/
void				ft_gui_print_element_list(t_list *dom, int level);

/*
** **************************************************************************
**	gui/gui_destruct.c
** **************************************************************************
*/
void				ft_gui_desctuct(t_list *dom);
void				ft_gui_desctuct_fonts(t_list *fonts_list);

/*
** **************************************************************************
**	gui/gui_elem_button.c
** **************************************************************************
*/
void				ft_gui_mousemotion_button(void *data, SDL_Event e, \
						t_list *dom, int type);
void				ft_gui_mousebuttondown_button(void *data, SDL_Event e, \
						t_list *dom, int type);
void				ft_gui_mousebuttonup_button(void *data, SDL_Event e, \
						t_list *dom, int type);
void				ft_gui_mousebuttonup_block(void *data, SDL_Event e, \
						t_list *dom, int type);

/*
** **************************************************************************
**	gui/gui_elem_init.c
** **************************************************************************
*/
t_list				*ft_gui_search_elem_by_name(t_list *dom, char *name);
void				ft_gui_elem_init(t_list **dom, char *name, \
						t_gui_coord v1, t_gui_coord v2);
void				ft_gui_elem_set_color(t_list *list, int color);
void				ft_gui_elem_set_status(t_list *list, int status);
char				*ft_gui_elem_get_value(t_list *list);
void				ft_gui_elem_set_event(t_list *list, void *func, \
						int type, int code);
void				ft_gui_elem_set_redraw(t_list *list, void *func);
void				ft_gui_elem_set_redraw_font(t_list *list, void *func);
void				ft_gui_elem_set_image(t_list *list, char *path);
void				ft_gui_elem_set_block(t_list *list);
void				ft_gui_elem_set_button(t_list *list, void *str);
void				ft_gui_elem_set_input(t_list *list, void *str, \
						int flag_numb);
void				ft_gui_elem_set_text(t_list *list, void *str, \
						int font_size);
void				ft_gui_elem_set_parent(t_list *parent, t_list *child);
void				ft_gui_delete_status_focus(t_list *dom);
void				ft_gui_delete_status(t_list *dom);

/*
** **************************************************************************
**	gui/gui_elem_input.c
** **************************************************************************
*/
void				ft_gui_mousemotion_input(void *data, SDL_Event e, \
						t_list *dom, int type);
void				ft_gui_mousebuttondown_input(void *data, SDL_Event e, \
						t_list *dom, int type);
void				ft_gui_mousebuttonup_input(void *data, SDL_Event e, \
						t_list *dom, int type);

/*
** **************************************************************************
**	gui/events.c
** **************************************************************************
*/
void				ft_gui_events(t_wolf3d *w);

/*
** **************************************************************************
**	gui/gui_fonts.c
** **************************************************************************
*/
SDL_Rect			*ft_gui_create_sdl_rect(int w, int h, int x, int y);
void				ft_gui_set_font(t_wolf3d *w, char *font_path, int size);
int					ft_gui_font_preset_fsc(t_wolf3d *w, char *font_path, \
						int size, int color);
void				ft_gui_font_putstr_sdl(t_wolf3d *w, char *str, \
						t_gui_coord c);

/*
** **************************************************************************
**	gui/gui_keydown.c
** **************************************************************************
*/
void				ft_gui_focus_keydown(t_wolf3d *w, SDL_Event e, \
						t_list *dom);

/*
** **************************************************************************
**	gui/gui_mouse.c
** **************************************************************************
*/
int					ft_gui_check_event_area(t_gui_coord v, t_gui_coord v1, \
						t_gui_coord v2);
int					ft_gui_check_event_elem_area(t_gui_coord v, t_gui_elem *c);
void				ft_gui_init_mouse_pos(t_wolf3d *w);
int					ft_gui_event_call_func(t_wolf3d *w, SDL_Event e, \
						t_gui_event *event, int type);
int					ft_gui_event_action(t_wolf3d *w, SDL_Event e, \
						t_list *dom, int type);
int					ft_gui_event_search_elem(t_wolf3d *w, SDL_Event e, \
						t_list *dom, int type);
void				ft_gui_mousemotion(t_wolf3d *w, SDL_Event e, t_list *dom);
void				ft_gui_mousebuttondown(t_wolf3d *w, SDL_Event e, \
						t_list *dom);
void				ft_gui_mousebuttonup(t_wolf3d *w, SDL_Event e, \
						t_list *dom);
void				ft_gui_mousewheel(t_wolf3d *w, SDL_Event e, \
						t_list *dom);

/*
** **************************************************************************
**	gui/gui_redraw.c
** **************************************************************************
*/
void				ft_gui_draw_image_area(t_wolf3d *w, t_gui_rect rect, \
						SDL_Surface *surf);
void				ft_gui_draw_image(t_wolf3d *w, t_list *list);
void				ft_gui_fill_area(t_wolf3d *w, t_gui_coord v1, \
						t_gui_coord v2, int color);
void				ft_gui_draw_border(t_wolf3d *w, t_list *list, \
						int color, int border_width);
void				ft_gui_fill_elem(t_wolf3d *w, t_list *list, int color);
void				ft_gui_redraw_elem(t_wolf3d *w, t_list *dom);
int					ft_gui_redraw_frame(t_wolf3d *w);
void				ft_gui_putstr_elem_font(t_wolf3d *w, t_list *list, \
						int color);
void				ft_gui_redraw_elem_font(t_wolf3d *w, t_list *dom);
int					ft_gui_redraw(t_wolf3d *w);

/*
** **************************************************************************
**	gui/gui_init.c
** **************************************************************************
*/
void				ft_gui_init(t_wolf3d *w);

#endif