/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gui.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dorange- <dorange-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/20 19:54:12 by dorange-          #+#    #+#             */
/*   Updated: 2020/01/20 20:25:09 by dorange-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GUI_H
# define GUI_H

# include <libft.h>
# include "SDL2/SDL.h"
# include "SDL2/SDL_ttf.h"

/*
** **************************************************************************
**	Element status
** **************************************************************************
*/
# define GUI_ELEM_HIDDEN		0x00000001
# define GUI_ELEM_VISIBLE		0x00000002
# define GUI_ELEM_STATIC		0x00000004
# define GUI_ELEM_DYNAMIC		0x00000008

# define GUI_ELEM_NORMAL		0x00000010
# define GUI_ELEM_HOVER			0x00000020
# define GUI_ELEM_CLICK			0x00000040
# define GUI_ELEM_ACTIVE		0x00000080
# define GUI_ELEM_FOCUS			0x00000100
# define GUI_ELEM_DISABLE		0x00000200

# define GUI_ELEM_ACT_MASK		0x0000000F

/*
** **************************************************************************
**	Element type
** **************************************************************************
*/
# define GUI_BLOCK				0x01
# define GUI_TEXT				0x02
# define GUI_BUTTON				0x03
# define GUI_INPUT				0x04
# define GUI_INPUT_NUMB			0x05
# define GUI_MAP				0xF1

/*
** **************************************************************************
**	Redraw status
** **************************************************************************
*/
# define GUI_NOT_REDRAW			0x00
# define GUI_REDRAW				0x01
# define GUI_REDRAW_FRAME		0x02

/*
** **************************************************************************
**	Event status
** **************************************************************************
*/
# define GUI_EVENT_OFF			0x00
# define GUI_EVENT_ON			0x01
# define GUI_EVENT_SEARCH		0x02

/*
** **************************************************************************
**	Mode
** **************************************************************************
*/
# define GUI_MD_ME				0x0000F001
# define GUI_MD_ME_SET_SECTOR	0x0000F100
# define GUI_MD_ME_SET_PLAYER	0x0000F200
# define GUI_MD_ME_SET_SPRITE	0x0000F300
# define GUI_MD_ME_SET_ENEMY	0x0000F400

/*
** **************************************************************************
**	Color
** **************************************************************************
*/
# define GUI_CL_STANDART		0x00ff0000
# define GUI_CL_SECTOR			0x00ffd700
# define GUI_CL_PLAYER			0x00a496f2
# define GUI_CL_SPRITE			0x005499a1
# define GUI_CL_ENEMY			0x00fb607f

/*
** **************************************************************************
**	t_gui_coord
**
**	Structure for interface coordinates.
**
**	Arguments:
**	int x		| x coordinates
**	int y		| y coordinates
**	int w		| point width
** **************************************************************************
*/
typedef struct		s_gui_coord
{
	int				x;
	int				y;
	int				w;
}					t_gui_coord;

/*
** **************************************************************************
**	t_gui_rect
**
**	Structure for interface area.
**
**	Arguments:
**	t_gui_coord v1	| left top vertex coordinate
**	t_gui_coord v2	| right bottom vertex coordinate
**	int w			| area width
**	int h			| area height
** **************************************************************************
*/
typedef struct		s_gui_rect
{
	t_gui_coord		v1;
	t_gui_coord		v2;
	int				w;
	int				h;
}					t_gui_rect;

/*
** **************************************************************************
**	t_gui_event
**
**	Structure for gui-element event.
**
**	Arguments:
**	int type		| type of event
**	int code		| right bottom vertex coordinate
**	void (*func)	| function that will be to call if event happened
**	t_list *elem	| pointer of gui-element
** **************************************************************************
*/
typedef struct		s_gui_event
{
	int				type;
	int				code;
	void			(*func)(void *data, SDL_Event e, t_list *dom, int type);
	t_list			*elem;
}					t_gui_event;

typedef struct		s_gui_font
{
	char			*path;
	SDL_Surface		*surf[7];
	TTF_Font		*ptr;
	SDL_Color		color;
	int				f_sz;
	int				g_sz;
	int				w;
	int				h;
	int				half_menu;
}					t_gui_font;

/*
** **************************************************************************
**	t_gui_elem
**
**	Structure for gui-element.
**
**	Arguments:
**	char *name		| element name
**	t_gui_coord v1	| left top vertex element coordinate
**	t_gui_coord v2	| right bottom vertex element coordinate
**	int w			| element width
**	int h			| element height
**	int status		| element status
**	t_list *parent	| pointer to parent element
**	t_list *child	| pointer to child elements
**	int color		| background color (or text color)
**	t_list *events	| pointer to event list
**	int type		| type
**	char *str		| element values
**	void (*redraw)	| function that redraw element
** **************************************************************************
*/
typedef struct		s_gui_elem
{
	char			*name;
	t_gui_coord		v1;
	t_gui_coord		v2;
	int				w;
	int				h;
	int				status;
	t_list			*parent;
	t_list			*child;
	int				color;
	t_list			*events;
	int				type;
	char			*str;
	void			(*redraw)(void *data, t_list *dom);
}					t_gui_elem;

/*
** **************************************************************************
**	t_gui
**
**	Special structure with general gui configuration.
**
**	Arguments:
**	t_list *fonts			| pointer to font list
**	t_list *dom				| pointer to element list
**	unsigned char redraw	| redraw status
**	t_gui_elem *redraw_elem	| pointer to redraw element
**	t_gui_coord mouse_pos	| mouse coordinates
**	int search_elem			| search element status
**	t_list *focus_elem		| pointer to focus element
**	int mode				| interface mode
** **************************************************************************
*/
typedef struct		s_gui
{
	t_list			*fonts;
	t_list			*dom;
	unsigned char	redraw;
	t_gui_elem		*redraw_elem;
	t_gui_coord		mouse_pos;
	int				search_elem;
	t_list			*focus_elem;
	int				mode;
}					t_gui;

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
void				ft_gui_elem_set_block(t_list *list);
void				ft_gui_elem_set_map(t_list *list);
void				ft_gui_elem_set_button(t_list *list, void *str);
void				ft_gui_elem_set_input(t_list *list, void *str, \
						int flag_numb);
void				ft_gui_elem_set_text(t_list *list, void *str);
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
int					ft_gui_check_event_area(t_gui_coord v, t_gui_elem *c);
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

#endif
