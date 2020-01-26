/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   jhony.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dorange- <dorange-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/22 15:10:15 by tjuana            #+#    #+#             */
/*   Updated: 2020/01/26 22:32:59 by dorange-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>


int		ft_2darrclean(int ***dst)
{
	size_t i;

	i = 0;
	while ((*dst)[i])
	{
		free((*dst)[i]);
		(*dst)[i] = NULL;
		i++;
	}
	free(*dst);
	*dst = NULL;
	dst = NULL;
	return (1);
}

int main() 
{ 
    int r = 33, c = 54, i, j, count; 
  
    int **arr = (int **)malloc(r * sizeof(int *)); 
    for (i=0; i<r; i++) 
         arr[i] = (int *)malloc(c * sizeof(int)); 
  
    // Note that arr[i][j] is same as *(*(arr+i)+j) 
    count = 0; 
    for (i = 0; i <  r; i++) 
      for (j = 0; j < c; j++) 
         arr[i][j] = ++count;  // OR *(*(arr+i)+j) = ++count 
  
    for (i = 0; i <  r; i++) 
      for (j = 0; j < c; j++) 
         // printf(">>%d ", arr[i][j]); 
	ft_2darrclean(&arr);
   /* Code for further processing and free the  
      dynamically allocated memory */
  
   return 0; 
} 