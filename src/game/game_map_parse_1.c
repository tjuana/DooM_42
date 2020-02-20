/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_map_parse_1.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dorange- <dorange-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/26 13:15:15 by tjuana            #+#    #+#             */
/*   Updated: 2020/02/20 17:27:22 by dorange-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

	//win_game_hud_filename
void		ft_game_my_parse_map(t_new_player *pl, char *ag)
{
	t_list		*list; // hmm...
	t_gui_elem	*elem; // hmm...

	pl->file.count_sectors = -1;
	if (!ag)
		ag = "maps/button";
	pl->file.ag = ag;

	// hmm...
	pl->map_path = ag;
	list = ft_gui_search_elem_by_name(\
		((t_wolf3d*)pl->wolf3d)->gui.dom, \
		"win_game_hud_filename");
	elem = list->content;
	free(elem->str);
	elem->str = ft_strdup(pl->map_path);

	if ((pl->file.fd = open(ag, O_RDONLY)) < 0)
		ft_error("BAD FILE");
	pl->file.vertex_count = 0;
	while ((pl->file.res = get_next_line(pl->file.fd, &pl->file.line)) > 0)
	{
		pl->file.i = 1;
		if ((pl->file.ptr_my = ft_strchr(pl->file.line, (int)' ')) != NULL)
			ft_error("BAD FILE, ONLY TAB , MAN!");
		else if ((pl->file.ptr_my = ft_strchr(pl->file.line, (int)'v')) != NULL)
			ft_game_vertex_count(pl);
		else if ((pl->file.ptr_my = ft_strchr(pl->file.line, (int)'s')) != NULL)
			ft_game_sector_count(pl);
		ft_strdel(&pl->file.line);
		free(pl->file.line);
	}
	free(pl->file.line);
	close(pl->file.fd);
	ft_game_malloc_save_sectors(ag, pl);
}

void		ft_game_vertex_count(t_new_player *pl)
{
	int	i;

	i = 2;
	if (!(pl->file.split = ft_strsplit(pl->file.ptr_my, '\t')))
		ft_error("MALLOC_SPLIT");
	while (pl->file.split[i++] != NULL)
		pl->file.vertex_count++;
	if (pl->file.split)
		ft_2arrclean(&pl->file.split);
}

void		ft_game_sector_count(t_new_player *pl)
{
	int		count;

	pl->file.count_sector_vertex = 0;
	count = 3;
	if (!(pl->file.split = ft_strsplit(pl->file.ptr_my, '\t')))
		ft_error("MALLOC_SPLIT");
	while (pl->file.split[count] != NULL)
	{
		pl->file.count_sector_vertex++;
		count++;
	}
	pl->file.count_sector_vertex /= 2;
	pl->file.count_sectors++;
	if (pl->file.count_sectors > SECTORS)
		ft_error("Too many sectors");
	pl->file.tmp[pl->file.count_sectors] = pl->file.count_sector_vertex;
	if (&pl->file.split[0])
		ft_2arrclean(&pl->file.split);
}

t_vector3	*ft_game_malloc_sec_vertex(t_new_player *pl, char *v)
{
	t_vector3		*vertex;

	if ((pl->file.fd = open(v, O_RDONLY)) < 0)
		perror("Error: bad file");
	vertex = ft_my_malloc(sizeof(t_vector3) * (pl->file.vertex_count));
	pl->sectors = ft_my_malloc(sizeof(t_new_sector) * \
			(pl->file.count_sectors + 1));
	pl->sectors_nb = pl->file.count_sectors + 1;
	return (vertex);
}

void		ft_game_malloc_save_sectors(char *ag, t_new_player *pl)
{
	t_vector3		*vertex;

	vertex = ft_game_malloc_sec_vertex(pl, ag);
	pl->file.count_sectors2 = 0;
	pl->file.i = 0;
	while ((pl->file.res = get_next_line(pl->file.fd, &pl->file.line)) > 0)
	{
		if ((pl->file.ptr_my = ft_strchr(pl->file.line, (int)'v')) != NULL)
			vertex = ft_game_vertex_save(pl, vertex);
		else if ((pl->file.ptr_my = ft_strchr(pl->file.line, (int)'m')) != NULL)
			ft_game_level_save(pl);
		else if ((pl->file.ptr_my = ft_strchr(pl->file.line, (int)'s')) != NULL)
			ft_game_sector_save(pl, vertex);
		else if ((pl->file.ptr_my = ft_strchr(pl->file.line, (int)'p')) != NULL)
			ft_game_player_save(pl);
		ft_strdel(&pl->file.line);
		free(pl->file.line);
	}
	free(pl->file.line);
	free(vertex);
	close(pl->file.fd);
}
