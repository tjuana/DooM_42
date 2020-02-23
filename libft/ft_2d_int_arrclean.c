/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_2d_int_arrclean.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjuana <tjuana@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/22 19:37:34 by tjuana            #+#    #+#             */
/*   Updated: 2020/02/05 13:33:31 by tjuana           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_2d_int_arrclean(int ***dst)
{
	size_t i;

	i = 1;
	while ((*dst)[i - 1])
	{
		free((*dst)[i]);
		(*dst)[i] = NULL;
		i++;
	}
	free(*dst);
	*dst = NULL;
	dst = NULL;
	return (0);
}