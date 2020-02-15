/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   const.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: drafe <drafe@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/26 16:47:07 by dorange-          #+#    #+#             */
/*   Updated: 2020/02/15 21:21:13 by drafe            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CONST_H
# define CONST_H

/*
** **************************************************************************
**	General
** **************************************************************************
*/
# define WIN_WIDTH				1280
# define WIN_HEIGHT				720
# define VER_WIDTH				54
# define VER_HEIGHT				33

/*
** **************************************************************************
**	Mode
** **************************************************************************
*/
# define GUI_MD_GAME			0x0000A001
# define GUI_MD_ME				0x0000F001
# define GUI_MD_ME_SET_SECTOR	0x0000F100
# define GUI_MD_ME_SET_PLAYER	0x0000F200
# define GUI_MD_ME_SET_SPRITE	0x0000F300
# define GUI_MD_ME_SET_ENEMY	0x0000F400
# define GUI_MD_ME_SET_DOOR		0x0000F500

/*
** **************************************************************************
**	Color mask
** **************************************************************************
*/
# define C_A					0xFF000000
# define C_R					0x00FF0000
# define C_G					0x0000FF00
# define C_B					0x000000FF

/*
** **************************************************************************
**	Define for editor
** **************************************************************************
*/
# define GUI_MAP_GRID_LIMIT_TL	0x1
# define GUI_MAP_GRID_LIMIT_TR	0x2
# define GUI_MAP_GRID_LIMIT_BL	0x3
# define GUI_MAP_GRID_LIMIT_BR	0x4

# define H_FOV					(1.0 * 0.73f * WIN_H / WIN_W)
# define V_FOV					(1.0 * .2f)

/*
 *
 * TEXTURES
 */

# define	LEAF 0
# define	GREEN 1
# define	MARBLE 2
# define 	ROCK1	3
# define 	ROCK2	4
# define 	SKY		5
# define 	FENCE	7

#endif
