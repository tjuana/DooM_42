/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_texture_parser.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dorange- <dorange-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/25 16:38:34 by tjuana            #+#    #+#             */
/*   Updated: 2020/01/28 21:36:05 by dorange-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

/*
** **************************************************************************
**	static t_new_color *texture_parse_2(unsigned char *src, \
**	unsigned w, unsigned h, unsigned bpp)
**	Function to store raw_pixels to pixels we need
** **************************************************************************
*/

static t_new_color	*texture_parse_3(unsigned char *src, size_t i, unsigned bpp)
{
	t_new_color	*res;
	size_t	j;

	j = 0;
	if (!(res = (t_new_color *)malloc(sizeof(t_new_color) * i + 1)))
	{
		free(src);
		ft_putstr_fd("Can't allocate memory for pixels.\n", 2);
		exit(EXIT_FAILURE);
	}
	while (i > 0)
	{
		res[i].b = src[j];
		res[i].g = src[j + 1];
		res[i].r = src[j + 2];
		if (bpp == 32)
			res[i].a = src[j + 3];
		else
			res[i].a = 255;
		j += 3;
		bpp == 32 ? j++ : j;
		i--;
	}
	free(src);
	return (res);
}

/*
** **************************************************************************
**	t_new_texture texture_parse(const char *fp, unsigned int edit)
**	Function to store pixels from file into structure t_new_texture
** **************************************************************************
*/

t_new_texture		texture_parse_2(size_t f_size, int fd, unsigned char *head)
{
	t_new_texture		res;
	unsigned char	*pix_raw;
	size_t			i;

	i = ((short *)head)[IMG_W] * ((short *)head)[IMG_H] - 1;
	if (!(pix_raw = (unsigned char *)malloc(sizeof(unsigned char) \
	* (f_size - HEAD_SZ))))
	{
		ft_putstr_fd("Can't allocate memory for pix_raw.\n", 2);
		exit(EXIT_FAILURE);
	}
	if (read(fd, pix_raw, f_size - HEAD_SZ) < (ssize_t)(f_size - HEAD_SZ))
	{
		free(pix_raw);
		ft_putstr_fd("Cant read texture header. Wrong HEAD_SZ\n", 2);
		exit(EXIT_FAILURE);
	}
	res.pixels = texture_parse_3(pix_raw, i, head[BPP]);
	return (res);
}

/*
** **************************************************************************
**	static void texture_header_chk(const char *fp, int fd, \
**	unsigned char *head)
**	Function to check img header
** **************************************************************************
*/

static void		texture_header_chk(const char *fp, int fd, unsigned char *head)
{
	if (!fp || (fd < 0) || (fd > 10240) || (access(fp, F_OK) == -1))
	{
		ft_putstr_fd("Error cant open texture file.\n", 2);
		exit(EXIT_FAILURE);
	}
	if (head[BPP] != 32 && head[BPP] != 24)
	{
		ft_putstr_fd("Cant read texture header. Wrong BPP.\n", 2);
		exit(EXIT_FAILURE);
	}
	if (head[IMG_TYPE] != 2)
	{
		ft_putstr_fd("Cant read texture header. Wrong IMG_TYPE.\n", 2);
		exit(EXIT_FAILURE);
	}
	if (head[COLOR_MAP] != 0)
	{
		ft_putstr_fd("Cant read texture header. Wrong COLOR_MAP.\n", 2);
		exit(EXIT_FAILURE);
	}
}

/*
** **************************************************************************
**	t_new_texture texture_parse(const char *fp, unsigned int edit)
**	Function to store pixels from file into structure t_new_texture
** **************************************************************************
*/

t_new_texture		texture_parse(const char *fp)
{
	t_new_texture		res;
	struct stat		st_inf;
	int				fd;
	unsigned char	head[18];

	fd = 0;
	fd = open(fp, O_RDONLY);
	if (read(fd, &head, HEAD_SZ) < HEAD_SZ)
	{
		ft_putstr_fd("Cant read texture header. Wrong HEAD_SZ\n", 2);
		exit(EXIT_FAILURE);
	}
	texture_header_chk(fp, fd, head);
	stat(fp, &st_inf);
	res = texture_parse_2(st_inf.st_size, fd, head);
	return (res);
}
