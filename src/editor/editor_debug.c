/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   editor_debug.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dorange- <dorange-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/12 14:08:59 by dorange-          #+#    #+#             */
/*   Updated: 2020/01/26 18:22:02 by dorange-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

void	ft_editor_sector_special_debug(t_list *ptr_list)
{
	t_sector	*ptr_sector;
	int			i;
	int			j;

	i = 0;
	while (ptr_list != NULL)
	{
		// Get sector values
		ptr_sector = (t_sector*)ptr_list->content;

		printf("SECTOR #%d   VERTEX_COUNT %d   STATUS: %d\n", ptr_sector->id, \
			ptr_sector->vertex_count, (int)ptr_sector->status);

		printf("vertexes:   ");

		j = 0;
		while (j < ptr_sector->vertex_count)
		{
			if (j > 0)
				printf(" | ");
			printf(
				"[%02.0f, %02.0f]",
				ptr_sector->vertex[j]->x,
				ptr_sector->vertex[j]->y
			);
			j++;
		}

		printf("\n");

		if (ptr_sector->status == SECTOR_STATUS_POLYGON ||
			ptr_sector->status == SECTOR_STATUS_SET)
		{
			printf ("neighbors:  ");

			j = 0;
			while (j < ptr_sector->vertex_count)
			{
				if (j > 0)
					printf(" ");
				printf(
					"%d",
					ptr_sector->neighbors[j]
				);
				
				j++;
			}

			printf ("\n");
		}
		
		// Get next sector
		ptr_list = ptr_list->next;
		i++;
	}
}

/*
	void ft_print_sectors(t_list *ptr_list)
	
	Function that print the map sectors.
*/
void	ft_print_sectors(t_list *ptr_list)
{
	t_sector	*ptr_sector;
	int			i;
	int			j;

	i = 0;
	while (ptr_list != NULL)
	{
		// Get sector values
		ptr_sector = (t_sector*)ptr_list->content;

		j = 0;
		while (j < ptr_sector->vertex_count)
		{
			// Print the vertexes of sector
			printf(
				"SECTOR #%.2d   VERTEX #%.2d   x: %6.2f   y: %6.2f   status: %d\n",
				i,
				j,
				ptr_sector->vertex[j]->x,
				ptr_sector->vertex[j]->y,
				(int)ptr_sector->status
			);
			j++;
		}

		// Get next sector
		ptr_list = ptr_list->next;
		i++;
	}
}