/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   help.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dorange- <dorange-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/16 16:34:17 by tjuana            #+#    #+#             */
/*   Updated: 2020/02/19 20:00:26 by dorange-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HELP_H
# define HELP_H

typedef struct	s_new_tmp_trio //sectorno, sx1, sx2;
{
    int	sec_nb;
    int	sx1;
    int	sx2;
}				t_new_tmp_trio;

typedef struct	s_new_rect
{
    t_vector3	size;
    t_vector3	crd;
}				t_new_rect;

#endif
