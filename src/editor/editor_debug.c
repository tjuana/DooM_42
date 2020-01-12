/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   editor_debug.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dorange- <dorange-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/12 14:08:59 by dorange-          #+#    #+#             */
/*   Updated: 2020/01/12 14:48:41 by dorange-         ###   ########.fr       */
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

		if (ptr_sector->status == 1)
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