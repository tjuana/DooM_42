/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dorange- <dorange-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/26 15:29:11 by drafe             #+#    #+#             */
/*   Updated: 2020/01/27 15:59:46 by dorange-         ###   ########.fr       */
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
	unsigned int	edit;
}					t_new_texture;

#endif
