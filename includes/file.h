/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjuana <tjuana@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/17 15:07:53 by tjuana            #+#    #+#             */
/*   Updated: 2020/01/20 19:40:01 by tjuana           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"
#include <sys/types.h>
#include <sys/stat.h>
# define VER_HEIGHT 33
# define VER_WIDTH 54


typedef struct			s_file
{
	int			sort[33][54];
	int			i;
	int			j;
	int			count;
	int			fd;
	char		*name;
}						t_file;