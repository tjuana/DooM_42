/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   const.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dorange- <dorange-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/26 16:47:07 by dorange-          #+#    #+#             */
/*   Updated: 2020/01/26 17:32:12 by dorange-         ###   ########.fr       */
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

/*
** **************************************************************************
**	Mode
** **************************************************************************
*/
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
# define C_A 0xFF000000
# define C_R 0x00FF0000
# define C_G 0x0000FF00
# define C_B 0x000000FF

/*
** **************************************************************************
**	Define for editor
** **************************************************************************
*/
# define GUI_MAP_GRID_LIMIT_TL	0x1
# define GUI_MAP_GRID_LIMIT_TR	0x2
# define GUI_MAP_GRID_LIMIT_BL	0x3
# define GUI_MAP_GRID_LIMIT_BR	0x4


/*
** **************************************************************************
**	DEPRECATED
** **************************************************************************
*/
# define TEXTURES_NUMBER 23
# define THREADS 10
# define TEX_W 64
# define TEX_H 64
# define ONE_ANIM 20
# define FULL_ANIM ONE_ANIM * 4 - 4
# define T_CAM_HR_ANGLE 0.02 // transform angle for camera
# define T_CAM_Z_ANGLE 0.01 // transform angle for camera
# define E_GRID_L 32 // GRID LENGTH (SCALE)
# define E_GRID_V_D 6 // VERTEX DIAMETER
# define E_GRID_V_D_D 4 // VERTEX DRAW DIAMETER
# define DEG_30 0.52360


#endif
