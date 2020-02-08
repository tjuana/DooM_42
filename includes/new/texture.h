/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dorange- <dorange-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/26 15:29:11 by drafe             #+#    #+#             */
/*   Updated: 2020/01/28 21:56:20 by dorange-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TEXTURE_H
# define TEXTURE_H
# include "wolf3d.h"

# define HEAD_SZ 18
# define BPP 16
# define IMG_H 7
# define IMG_W 6
# define IMG_TYPE 2
# define COLOR_MAP 1
# define ID_LENGTH 0
# define FLOOR  1
# define WALL_FULL 2
# define WALL_TOP  0
# define WALL_BOTT 1




typedef struct s_textures
{
	float hei;
	float mapx;
	float mapz;
	unsigned txtx1;
	unsigned txtz;
	int x;
	int y;
}               t_textures;


typedef struct		s_new_color
{
	u_int8_t		r;
	u_int8_t		g;
	u_int8_t		b;
	u_int8_t		a;
}					t_new_color;

typedef struct		s_new_texture
{
	t_new_color		*pixels;
	unsigned int	w;
	unsigned int	h;
}					t_new_texture;

typedef	struct			s_gun
{
	int					pistol_sprite[6][128][128];
	int					type;
	double				sprite_counter;
	int                 w;
	int                 h;
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
