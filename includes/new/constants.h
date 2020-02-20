/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   constants.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dorange- <dorange-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/16 16:30:37 by tjuana            #+#    #+#             */
/*   Updated: 2020/02/20 13:43:41 by dorange-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CONSTANTS_H
# define CONSTANTS_H

/*
** **************************************************************************
**	Define window size
** **************************************************************************
*/

# define WIN_W WIN_WIDTH
# define WIN_H WIN_HEIGHT

/*
** **************************************************************************
**	Define various vision related constants
** **************************************************************************
*/

# define EYE_H  6    //Camera height from floor when standing
# define CROUCH_H 2.5  //And when crouching
# define HEAD_H 1    //How much room there is above camera before the head hits the ceiling
# define NOT_JUMP_H 2    //How tall obstacles the player can simply walk over without jumping

# define MAX_QUEUE 64 //maximum number of pending portal renders (engine)
# define MAX_DOORS 100 //maximum number of doors
# define MAX_BUT 100 //maximum number of buttons


#endif
