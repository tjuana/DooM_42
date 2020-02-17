/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjuana <tjuana@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/05 15:56:10 by tjuana            #+#    #+#             */
/*   Updated: 2020/02/17 12:30:13 by tjuana           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_bzero(void *s, size_t n)
{
	int delta;

	delta = 1;
	while (n)
	{
		if (n >= 8)
		{
			*(__uint64_t *)s = 0;
			delta = 8;
		}
		else if (n >= 1)
		{
			*(char *)s = 0;
			delta = 1;
		}
		n = n - delta;
		s = ((char *)s) + delta;
	}
}
