/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   editor_struct.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dorange- <dorange-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/26 17:32:56 by dorange-          #+#    #+#             */
/*   Updated: 2020/02/24 19:47:37 by dorange-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EDITOR_STRUCT_H
# define EDITOR_STRUCT_H

# include "doom.h"

/*
** **************************************************************************
**	Sector type
** **************************************************************************
*/
# define SECTOR_TYPE_SECTOR			0x00
# define SECTOR_TYPE_DOOR			0x01

/*
** **************************************************************************
**	Sector status
** **************************************************************************
*/
# define SECTOR_STATUS_NOTHING		0x00
# define SECTOR_STATUS_BROKEN_LINE	0x00
# define SECTOR_STATUS_POLYGON		0x01
# define SECTOR_STATUS_READY		0x02
# define SECTOR_STATUS_PRESET		0x03
# define SECTOR_STATUS_SET			0x04

/*
** **************************************************************************
**	t_sector
**
**	Structure for sector (map editor).
**
**	Arguments:
**	int id;					| id
**	t_vector3 **vertex;		| Указатель на массив вершин
**	int vertex_count;		| Кол-во вершин в секторе
**	int *neighbors;			| Номера соседних секторов
**	double height;			| Высота стены
**	double floor;			| Высота <<от пола>>
**	int txtr_floor;			| Номер текстуры сектора (?)
**	int txtr_walls;			| Номер текстуры сектора (?)
**	int txtr_ceil;			| Номер текстуры сектора (?)
**	int color;				| Цвет сектора (for map editor)
**	int type;				| sector type
**	int status;				| sector status
** **************************************************************************
*/
typedef struct			s_sector
{
	int					id;
	t_vector3			**vertex;
	int					vertex_count;
	int					*neighbors;
	double				height;
	double				floor;
	int					txtr_floor;
	int					txtr_walls;
	int					txtr_ceil;
	int					color;
	int					type;
	int					status;
}						t_sector;

/*
** **************************************************************************
**	t_gui_map
**
**	Structure for sector (map editor).
**
**	Arguments:
**	t_list *ptr				| pointer to gui-element
**	t_vector3 r1			| left top vertex
**	t_vector3 r2			| right bottom vertex
**	int grid_scale			| grid scale coeff.
**	char check_vertex		| flag (?)
**	t_vector3 v				| mouse vertes (?)
** **************************************************************************
*/
typedef struct			s_gui_map
{
	t_list				*ptr;
	t_vector3			r1;
	t_vector3			r2;
	int					grid_scale;
	char				check_vertex;
	t_vector3			v;
}						t_gui_map;

/*
** **************************************************************************
**	t_txtr
**
**	Structure for textures.
**
**	Arguments:
**	int id					| texture number
**	int color;				| basic color
**	SDL_Surface *surf;		| pointer to surface
** **************************************************************************
*/
typedef struct			s_txtr
{
	int					id;
	int					color;
	SDL_Surface			*surf;
}						t_txtr;

/*
** **************************************************************************
**	t_sprite
**
**	Structure for sprites.
**
**	Arguments:
**	int id					| sprite number
**	t_vector3 pos			| sprite position
**	double x				| x coord. (deprecated)
**	double y				| y coord. (deprecated)
**	double distance			| distance between sprite and player
**	int texture				| texture number (?)
**	int status				| sprite status
** **************************************************************************
*/
typedef struct			s_sprite
{
	int					id;
	t_vector3			pos;
	double				x;
	double				y;
	double				distance;
	int					texture;
	int					status;
}						t_sprite;

/*
** **************************************************************************
**	t_player
**
**	Structure for player.
**
**	Arguments:
**	t_vector3 camera_vector	| Основной вектор камеры
**	t_vector3 pos;			| Позиция игрока
**	double wall_dist;		| temp: Дистанция до стены с коррекцией fish eyes
**	int side;				| flag: сторона (например, подкрашивает стены)
** **************************************************************************
*/
typedef struct			s_player
{
	t_vector3			camera_vector;
	t_vector3			pos;
	double				wall_dist;
	int					side;
	int					sector;
}						t_player;

#endif
