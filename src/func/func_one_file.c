/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   func_one_file.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjuana <tjuana@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/22 17:06:01 by tjuana            #+#    #+#             */
/*   Updated: 2020/02/23 14:30:42 by tjuana           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

void	ft_unpack(void)
{
	if (system("test -d music/ ") != 0 && system("test -d Textures/") != 0 && \
		system("test -d Sounds/") != 0 && system("test -d img/") != 0 && \
		system("test -d maps/") != 0 && system("test -d sprites/") != 0 && \
		system("test -d Img_tga/") != 0 && system("test -d fonts/") != 0)
	{
		if (system("test -f pack.doom") == 0)
			system("tar -xf pack.doom");
		else
			ft_error("file mne verni gad\n");
	}
}

void	ft_check_folders(void)
{
	if (system("test -d music/ ") == 0 && system("test -d Textures/") == 0 && \
		system("test -d Sounds/") == 0 && system("test -d img/") == 0 && \
		system("test -d maps/") == 0 && system("test -d sprites/") == 0 && \
		system("test -d Img_tga/") == 0 && system("test -d fonts/") == 0)
	{
		if (system("test -f ""pack.doom") == 0)
			system("rm -rf pack.doom");
		if (system("tar -cf pack.doom music/ Textures/ Sounds/ img/\
			maps/ Img_tga/ fonts/ sprites/") == 0)
		{
			ft_putstr_fd("bomb has been planted\n", 2);
			system("rm -rf music/ Textures/ Sounds/ img/ maps/ sprites/ \
			Img_tga/ fonts/");
		}
	}
}
