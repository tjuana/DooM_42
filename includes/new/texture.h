/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dorange- <dorange-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/26 15:29:11 by drafe             #+#    #+#             */
/*   Updated: 2020/02/19 20:06:50 by dorange-         ###   ########.fr       */
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

# define WALL_FULL	2
# define WALL_TOP	0
# define WALL_BOTT	1

typedef struct			s_draw_gun
{
	unsigned int		x;
	unsigned int		y;
	int					x_img;
	float				x_num;
	float				y_num;
	unsigned int		p;
	unsigned int		hex;
}						t_draw_gun;

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


typedef struct			s_new_texture
{
	t_color				*pixels;
	unsigned int		w;
	unsigned int		h;
}						t_new_texture;

typedef	struct			s_gun
{
	int					pistol_sprite[6][128][128];
	int					type;
	double				sprite_counter;
	int					w;
	int					h;
}						t_gun;

typedef struct			s_scaler
{
	int					result;
	int					bop;
	int					fd;
	int					ca;
	int					cache;
}						t_scaler;

#endif
