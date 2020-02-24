/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjuana <tjuana@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/26 15:29:11 by drafe             #+#    #+#             */
/*   Updated: 2020/02/23 18:15:30 by tjuana           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TEXTURE_H
# define TEXTURE_H
# include "wolf3d.h"

# define HEAD_SZ	18
# define BPP		16
# define IMG_H		7
# define IMG_W		6
# define IMG_TYPE	2
# define COLOR_MAP	1
# define ID_LENGTH	0
# define FLOOR		1
# define WALL_TOP	0
# define WALL_BOTT	1
# define WALL_FULL	2

# define LEAF		0
# define GREEN		1
# define MARBLE		2
# define ROCK1		3
# define ROCK2		4
# define SKY		5
# define FENCE		7
# define GUN		9
# define BULLET		14

# define WALL_FULL	2
# define WALL_TOP	0
# define WALL_BOTT	1

/*
** **************************************************************************
**	t_draw_gun
**
**	Structure for draw gun.
**
**	Arguments:
**	unsigned int x		|
**	unsigned int y		|
**	int x_img			|
**	float x_num			|
**	float y_num			|
**	unsigned int p		|
**	unsigned int hex	|
**	int widht			| position x
**	int height			| position h
**	int n				| number of texture
**	double scale		| bullet scale
** **************************************************************************
*/
typedef struct			s_draw_gun
{
	unsigned int		x;
	unsigned int		y;
	int					x_img;
	float				x_num;
	float				y_num;
	int					p;
	unsigned int		hex;
	double				scale;
	int					width;
	int					height;
	int					n;
}						t_draw_gun;

/*
** **************************************************************************
**	t_new_texture
**
**	Structure for texture.
**
**	Arguments:
**	float hei			|
**	float mapx			|
**	float mapz			|
**	unsigned int txtx1	|
**	unsigned int txtz	|
**	int x				|
**	int y				|
** **************************************************************************
*/
typedef struct			s_textures
{
	float				hei;
	float				mapx;
	float				mapz;
	unsigned int		txtx1;
	unsigned int		txtz;
	int					x;
	int					y;
}						t_textures;

/*
** **************************************************************************
**	t_new_texture
**
**	Structure for texture.
**
**	Arguments:
**	t_color *pixels		|
**	unsigned int w		|
**	unsigned int h		|
** **************************************************************************
*/
typedef struct			s_new_texture
{
	t_color				*pixels;
	unsigned int		w;
	unsigned int		h;
}						t_new_texture;

/*
** **************************************************************************
**	t_gun
**
**	Structure for gun.
**
**	Arguments:
**	int type						|
**	double sprite_counter			|
**	int w							|
**	int h							|
** **************************************************************************
*/
typedef	struct			s_gun
{
	int					type;
	double				sprite_counter;
	int					w;
	int					h;
}						t_gun;

/*
** **************************************************************************
**	t_scaler
**
**	Structure for scaler.
**
**	Arguments:
**	int result	|
**	int bop		|
**	int fd		|
**	int ca		|
**	int cache	|
** **************************************************************************
*/
typedef struct			s_scaler
{
	int					result;
	int					bop;
	int					fd;
	int					ca;
	int					cache;
}						t_scaler;

#endif
