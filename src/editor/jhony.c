/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   jhony.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjuana <tjuana@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/22 15:10:15 by tjuana            #+#    #+#             */
/*   Updated: 2020/01/26 14:58:11 by tjuana           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <fcntl.h>

static t_gnl	*gnl_find_or_create(const int fd, t_list **my_list)
{
	t_list	*file;
	t_gnl	file_data;

	file = *my_list;
	while (file)
	{
		if (((t_gnl *)(file->content))->fd == fd)
			return (file->content);
		file = file->next;
	}
	file_data.fd = fd;
	if ((file_data.buff = ft_strnew(BUFF_SIZE)) == NULL)
		return (NULL);
	if ((file = ft_lstnew(&file_data, sizeof(file_data))) == NULL)
		return (NULL);
	ft_lstadd(my_list, file);
	return ((*my_list)->content);
}

static ssize_t	gnl_read_line(t_gnl *file)
{
	char		buff[BUFF_SIZE + 1];
	ssize_t		r;
	char		*temp;

	r = 1;
	while (ft_strstr(file->buff, "\n") == NULL && \
	(r = read(file->fd, &buff, BUFF_SIZE)) > 0)
	{
		buff[r] = '\0';
		temp = file->buff;
		file->buff = ft_strjoin(file->buff, buff);
		ft_strdel(&temp);
	}
	return (r);
}

int				get_next_line(const int fd, char **line)
{
	static t_list	*my_list;
	t_gnl			*file;
	ssize_t			r;
	char			*temp;
	int				endl;

	if (fd < 0 || !line)
		return (-1);
	file = gnl_find_or_create(fd, &my_list);
	if ((r = gnl_read_line(file)) == -1)
		return (-1);
	temp = file->buff;
	if ((endl = (ft_strchr(file->buff, '\n') > 0)))
		*line = ft_strsub(file->buff, 0, ft_strchr(file->buff, '\n') \
		- file->buff);
	else
		*line = ft_strdup(file->buff);
	file->buff = ft_strsub(file->buff, (unsigned int)(ft_strlen(*line) + endl),
			(size_t)(ft_strlen(file->buff) - (ft_strlen(*line) + endl)));
	ft_strdel(&temp);
	return (!(!(**line) && !r));
}

void	main(int c, char **v)
{
	/*
    take vertex
    
    */
	int fd;
	int res;
	char	*line;
	char	*ptr_my;
	//char	**split_ver;
	int		count_vertex = -1;
	int		count_sectors = -1;
	int count_sector_vertex = -1;
	char **split;
	// t_xy *vert_new = NULL;

	int i;
	// int j;
	if ((fd = open(v, O_RDONLY)) < 0)
		perror("Error: bad file");
	while ((res = get_next_line(fd, &line)) > 0)
	{
		i = -1;
		if ((ptr_my = ft_strchr(line, (int)'#')) != NULL)
			continue ;
		else if ((ptr_my = ft_strchr(line, (int)'v')) != NULL)
		{
			count_vertex++;
			while (ptr_my != NULL)
			{
				ptr_my++;
				if ((ptr_my = ft_strstr(ptr_my, " ")) != NULL)
					count_vertex++;
			}
		}
		else if ((ptr_my = ft_strchr(line, (int)'s')) != NULL)
		{
			ptr_my += 7;
			split = ft_strsplit(ptr_my, ' ');
			while (split[i++] != NULL)
				printf("%s\n", split[i]);
			count_sectors++;
		}
		ft_strdel(&line);
		free(line);
	}
	free(line);
	
}