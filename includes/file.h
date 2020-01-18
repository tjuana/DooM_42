/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjuana <tjuana@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/17 15:07:53 by tjuana            #+#    #+#             */
/*   Updated: 2020/01/17 16:21:10 by tjuana           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"
# define VER_HEIGHT (int)33
# define VER_WIDTH (int)54


typedef struct			s_file
{
	int			sort[33][54];
	int			i;
	int			j;
	int			count;
}						t_file;