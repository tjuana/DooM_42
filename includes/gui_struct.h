/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gui_struct.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dorange- <dorange-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/20 19:54:12 by dorange-          #+#    #+#             */
/*   Updated: 2020/02/21 20:47:24 by dorange-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GUI_STRUCT_H
# define GUI_STRUCT_H

# include <libft.h>

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
# define GUI_IMAGE				0x06
# define GUI_MAP				0xF1

/*
** **************************************************************************
**	Redraw status
** **************************************************************************
*/
# define GUI_NOT_REDRAW			0x00
# define GUI_REDRAW				0x01

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
**	Color
** **************************************************************************
*/
# define GUI_CL_STANDART		0x00ff0000
# define GUI_CL_SECTOR			0x00ffd700
# define GUI_CL_PLAYER			0x00a496f2
# define GUI_CL_SPRITE			0x005499a1
# define GUI_CL_ENEMY			0x00fb607f
# define GUI_CL_DOOR			0x00ff7538

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

typedef struct		s_gui_grid
{
	t_gui_rect		area;
	int				margin;
	t_gui_coord		count;
	int				elem_w;
	int				elem_h;
}					t_gui_grid;

/*
** **************************************************************************
**	t_gui_elem
**
**	Structure for gui-element.
**
**	Arguments:
**	char *name			| element name
**	t_gui_coord v1		| left top vertex element coordinate
**	t_gui_coord v2		| right bottom vertex element coordinate
**	int w				| element width
**	int h				| element height
**	int fs				| font size
**	int status			| element status
**	t_list *parent		| pointer to parent element
**	t_list *child		| pointer to child elements
**	int color			| background color (or text color)
**	t_list *events		| pointer to event list
**	int type			| type
**	char *str			| element values
**	void (*redraw)		| function that redraw element
**	void (*redraw)		| function that redraw element font
**	SDL_Surface *surf	| pointer to element surface (image)
**	t_gui_grid grid		| element grid
**	char *font_path		| Font path
** **************************************************************************
*/
typedef struct		s_gui_elem
{
	char			*name;
	t_gui_coord		v1;
	t_gui_coord		v2;
	int				w;
	int				h;
	int				fs;
	int				status;
	t_list			*parent;
	t_list			*child;
	int				color;
	t_list			*events;
	int				type;
	char			*str;
	void			(*redraw)(void *data, t_list *dom);
	void			(*redraw_font)(void *data, t_list *dom);
	SDL_Surface		*surf;
	t_gui_grid		grid;
	char			*font_path;
}					t_gui_elem;

/*
** **************************************************************************
**	t_gui
**
**	Special structure with general gui configuration.
**
**	Arguments:
**	int win_w				| window width
**	int win_h				| window height
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
	int				win_w;
	int				win_h;
	t_list			*fonts;
	t_list			*dom;
	unsigned char	redraw;
	t_gui_elem		*redraw_elem;
	t_gui_coord		mouse_pos;
	int				search_elem;
	t_list			*focus_elem;
	int				mode;
}					t_gui;

#endif
