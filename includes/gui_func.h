/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gui_func.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dorange- <dorange-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/21 13:58:04 by dorange-          #+#    #+#             */
/*   Updated: 2020/02/24 19:07:44 by dorange-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GUI_FUNC_H
# define GUI_FUNC_H

# include <libft.h>
# include "SDL2/SDL.h"
# include "SDL2/SDL_ttf.h"
# include "general_struct.h"

/*
** **************************************************************************
**	src/gui/gui_destruct.c
** **************************************************************************
*/
void		ft_gui_desctuct_events(t_list *events);
void		ft_gui_desctuct(t_list *dom);
void		ft_gui_desctuct_fonts(t_list *fonts_list);

/*
** **************************************************************************
**	src/gui/gui_elem_button.c
** **************************************************************************
*/
void		ft_gui_mousemotion_button(void *data, SDL_Event e, \
				t_list *dom, int type);
void		ft_gui_mousebuttondown_button(void *data, SDL_Event e, \
				t_list *dom, int type);
void		ft_gui_mousebuttonup_button(void *data, SDL_Event e, \
				t_list *dom, int type);
void		ft_gui_mousebuttonup_block(void *data, SDL_Event e, \
				t_list *dom, int type);

/*
** **************************************************************************
**	src/gui/gui_elem_init.c
** **************************************************************************
*/
void		ft_gui_elem_init(t_list **dom, char *name, \
				t_gui_coord v1, t_gui_coord v2);
void		ft_gui_elem_init_grid(t_list *parent, char *name, \
				int pos, t_gui_coord count);
void		ft_gui_elem_set_grid(t_list *dom, t_gui_coord count, \
				int margin);
void		ft_gui_elem_set_parent(t_list *parent, t_list *child);
t_list		*ft_gui_search_elem_by_name(t_list *dom, char *name);

/*
** **************************************************************************
**	src/gui/gui_elem_input.c
** **************************************************************************
*/
void		ft_gui_mousemotion_input(void *data, SDL_Event e, \
				t_list *dom, int type);
void		ft_gui_mousebuttondown_input(void *data, SDL_Event e, \
				t_list *dom, int type);
void		ft_gui_mousebuttonup_input(void *data, SDL_Event e, \
				t_list *dom, int type);

/*
** **************************************************************************
**	src/gui/gui_elem_set_func.c
** **************************************************************************
*/
void		ft_gui_elem_set_event(t_list *list, void *func, int type, \
				int code);
void		ft_gui_elem_set_redraw(t_list *list, void *func);
void		ft_gui_elem_set_redraw_font(t_list *list, void *func);

/*
** **************************************************************************
**	src/gui/gui_elem_set_status.c
** **************************************************************************
*/
void		ft_gui_elem_set_status(t_list *list, int status);
void		ft_gui_delete_status_focus(t_list *dom);
void		ft_gui_delete_status(t_list *dom);

/*
** **************************************************************************
**	src/gui/gui_elem_set_style.c
** **************************************************************************
*/
void		ft_gui_elem_set_color(t_list *list, int color);
void		ft_gui_elem_set_text(t_list *list, \
				void *str, int font_size, char *font_path);
void		ft_gui_elem_change_text(t_list *list, void *ptr_str);
char		*ft_gui_elem_get_value(t_list *list);

/*
** **************************************************************************
**	src/gui/gui_elem_set_type.c
** **************************************************************************
*/
void		ft_gui_elem_set_image(t_list *list, char *path);
void		ft_gui_elem_set_block(t_list *list);
void		ft_gui_elem_set_button(t_list *list, void *str, int font_size);
void		ft_gui_elem_set_input(t_list *list, void *str, int flag_numb);

/*
** **************************************************************************
**	src/gui/gui_events.c
** **************************************************************************
*/
void		ft_gui_events_keydown_set_sector(t_wolf3d *w, SDL_Event *e);
void		ft_gui_events_keydown_me(t_wolf3d *w, SDL_Event *e);
void		ft_gui_events_keydowm_map(t_wolf3d *w, SDL_Event *e);
void		ft_gui_events_keydown(t_wolf3d *w, SDL_Event *e);
void		ft_gui_events(t_wolf3d *w);

/*
** **************************************************************************
**	src/gui/gui_events_mouse.c
** **************************************************************************
*/
void		ft_gui_events_mouse(t_wolf3d *w, SDL_Event *e);

/*
** **************************************************************************
**	src/gui/gui_fonts.c
** **************************************************************************
*/
void		ft_gui_set_font(t_wolf3d *w, char *font_path, int size);
void		ft_gui_check_glyph_metrics(t_font *f);
int			ft_gui_font_preset_fsc(t_wolf3d *w, char *font_path, \
				int size, int color);
void		ft_gui_font_rect(t_wolf3d *w, SDL_Texture *txtr, \
				t_font *f, t_gui_coord c);
void		ft_gui_font_putstr_sdl(t_wolf3d *w, \
				char *str, t_gui_coord c);

/*
** **************************************************************************
**	src/gui/gui_init.c
** **************************************************************************
*/
void		ft_gui_init(t_wolf3d *w);

/*
** **************************************************************************
**	src/gui/gui_keydown.c
** **************************************************************************
*/
char		ft_gui_get_keydown_letter(SDL_Event e);
void		ft_gui_focus_type_numb(SDL_Event e, t_gui_elem *elem);
void		ft_gui_focus_add_letter(SDL_Event e, t_gui_elem *elem);
void		ft_gui_focus_delete_letter(t_gui_elem *elem);
void		ft_gui_focus_keydown(t_wolf3d *w, SDL_Event e, t_list *dom);

/*
** **************************************************************************
**	src/gui/gui_mouse.c
** **************************************************************************
*/
int			ft_gui_check_event_area(t_gui_coord v, t_gui_coord v1, \
				t_gui_coord v2);
int			ft_gui_check_event_elem_area(t_gui_coord v, t_gui_elem *c);
void		ft_gui_init_mouse_pos(t_wolf3d *w);

/*
** **************************************************************************
**	src/gui/gui_mouse_actions.c
** **************************************************************************
*/
void		ft_gui_mousemotion(t_wolf3d *w, SDL_Event e, t_list *dom);
void		ft_gui_mousebuttondown(t_wolf3d *w, SDL_Event e, t_list *dom);
void		ft_gui_mousebuttonup(t_wolf3d *w, SDL_Event e, t_list *dom);
void		ft_gui_mousewheel(t_wolf3d *w, SDL_Event e, t_list *dom);

/*
** **************************************************************************
**	src/gui/gui_mouse_event.c
** **************************************************************************
*/
int			ft_gui_event_call_func(t_wolf3d *w, SDL_Event e, \
				t_gui_event *event, int type);
int			ft_gui_event_action(t_wolf3d *w, SDL_Event e, t_list *dom, \
				int type);
int			ft_gui_event_search_elem(t_wolf3d *w, SDL_Event e, \
				t_list *dom, int type);

/*
** **************************************************************************
**	src/gui/gui_redraw.c
** **************************************************************************
*/
void		ft_gui_redraw_elem(t_wolf3d *w, t_list *dom);
int			ft_gui_redraw(t_wolf3d *w);

/*
** **************************************************************************
**	src/gui/gui_redraw_fill.c
** **************************************************************************
*/
void		ft_gui_fill_area_rect(t_wolf3d *w, t_gui_rect coord, \
					t_gui_rect area, int color);
void		ft_gui_fill_area(t_wolf3d *w, t_gui_coord v1, \
				t_gui_coord v2, int color);
void		ft_gui_draw_border(t_wolf3d *w, t_list *list, \
				int color, int border_width);
void		ft_gui_fill_elem(t_wolf3d *w, t_list *list, int color);

/*
** **************************************************************************
**	src/gui/gui_redraw_font.c
** **************************************************************************
*/
int			ft_gui_check_special_lightness(int color);
void		ft_gui_putstr_elem_font(t_wolf3d *w, t_list *list, \
				int color);
void		ft_gui_redraw_elem_font(t_wolf3d *w, t_list *dom);

/*
** **************************************************************************
**	src/gui/gui_redraw_image.c
** **************************************************************************
*/
int			ft_gui_get_image_pixel_pos_elem(int x, int y, \
				t_gui_elem *elem);
int			ft_gui_get_image_pixel_pos(int x, int y, \
				t_gui_rect rect, SDL_Surface *surf);
void		ft_gui_draw_image_put_pixel(t_wolf3d *w, int x, int y, \
				int color);
void		ft_gui_draw_image_area(t_wolf3d *w, t_gui_rect rect, \
				SDL_Surface *surf);
void		ft_gui_draw_image(t_wolf3d *w, t_list *list);

/*
** **************************************************************************
**	src/gui/gui_sdl_func.c
** **************************************************************************
*/
SDL_Rect	*ft_gui_create_sdl_rect(int w, int h, int x, int y);
void		ft_gui_set_sdl_color(SDL_Color *sdl_color, int color);

#endif
