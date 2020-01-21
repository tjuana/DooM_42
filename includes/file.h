/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjuana <tjuana@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/17 15:07:53 by tjuana            #+#    #+#             */
/*   Updated: 2020/01/21 21:23:58 by tjuana           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FILE_H
# define FILE_H

#include "wolf3d.h"
# define VER_HEIGHT (int)33
# define VER_WIDTH (int)54


typedef struct			s_file
{
	int			**map;
	int			i;
	int			j;
	int			count;
	int			fd;
	char		*name;
}						t_file;

#endif