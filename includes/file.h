/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dorange- <dorange-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/17 15:07:53 by tjuana            #+#    #+#             */
/*   Updated: 2020/01/26 19:17:20 by dorange-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FILE_H
# define FILE_H

# include "wolf3d.h"

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
