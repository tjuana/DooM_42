//**************************************************************************
//                                                                          
//                                                       :::      ::::::::  
//  engine_exp.c                                       :+:      :+:    :+:  
//                                                   +:+ +:+         +:+    
//  By: drafe <drafe@student.42.fr>                +#+  +:+       +#+       
//                                               +#+#+#+#+#+   +#+          
//  Created: 2020/01/10 21:27:28 by drafe             #+#    #+#            
//  Updated: 2020/01/12 19:03:44 by drafe            ###   ########.fr      
//                                                                          
//**************************************************************************

#include "wolf3d.h"

/*
** **************************************************************************
**	void engine_preset(t_player *pl)
**	Function to set up some arrays & lists for engine
** **************************************************************************
*/

void		engine_preset(t_player *pl)
{
	int	i;

	i = -1;
	while(++i < WIN_W)
		pl->y_top[i] = 0;
	i = -1;
	while(++i < WIN_W)
		pl->y_bot[i] = WIN_H - 1;
}

/*
** **************************************************************************
**	int engine_cross(t_player *pl, t_sector *sect, unsigned s)
**	Function to find intersections and set t1 & t2
**	t1.y was tz1 before recontruction
** **************************************************************************
*/

int			engine_cross(t_player *pl, int sec_n, unsigned s)
{
	t_xy	i1;
	t_xy	i2;
	t_xy	v_start;
	t_xy	v_end;

	//Acquire the x,y coordinates of the two endpoints (vertices) of this edge of the sector
	v_start.x = pl->sectors[sec_n].vertex[s + 0].x - pl->where.x;
	v_start.y = pl->sectors[sec_n].vertex[s + 0].y - pl->where.y;
	v_end.x = pl->sectors[sec_n].vertex[s + 1].x - pl->where.x;
	v_end.y = pl->sectors[sec_n].vertex[s + 1].y - pl->where.y;
	//Rotate them around the player's view
	pl->t1.x = v_start.x * pl->anglesin - v_start.y * pl->anglecos;
	pl->t1.y = v_start.x * pl->anglecos + v_start.y * pl->anglesin;
	pl->t2.x = v_end.x * pl->anglesin - v_end.y * pl->anglecos;
	pl->t2.y = v_end.x * pl->anglecos + v_end.y * pl->anglesin;
	//Is the wall at least partially in front of the player?
	if((pl->t1.y <= 0) && (pl->t2.y <= 0))
		return (0);//continue
	//If it's partially behind the player, cut it against player's view
	if((pl->t1.y <= 0) || (pl->t2.y <= 0))
	{
		// Find an intersection between the wall and the approximate edges of player's view
		i1 = Intersect(pl->t1.x, pl->t1.y, pl->t2.x, pl->t2.y, -pl->nearside, pl->nearz, -pl->farside, pl->farz);
		i2 = Intersect(pl->t1.x, pl->t1.y, pl->t2.x, pl->t2.y, pl->nearside, pl->nearz, pl->farside, pl->farz);
		(pl->t1.y < pl->nearz && i1.y > 0) ? pl->t1 = i1 : pl->t1;
		(pl->t1.y < pl->nearz && i1.y < 0) ? pl->t1 = i2 : pl->t1;
		(pl->t2.y < pl->nearz && i1.y > 0) ? pl->t2 = i1 : pl->t2;
		(pl->t2.y < pl->nearz && i1.y < 0) ? pl->t2 = i2 : pl->t2;
	}
	return (1);
}

/*
** **************************************************************************
**	void engine_scale(t_player *pl, float tz1, float tz2)
**	Function to scale floor & ceil
** **************************************************************************
*/

void		engine_scale(t_player *pl, float tz1, float tz2)
{
	pl->scale_1.x = hfov / tz1;
	pl->scale_1.y = vfov / tz1;
	pl->scale_2.x = hfov / tz2;
	pl->scale_2.y = vfov / tz2;
	//Do perspective transformation
	pl->x1 = WIN_W / 2 - (int)(pl->t1.x * pl->scale_1.x);
	pl->x2 = WIN_W / 2 - (int)(pl->t2.x * pl->scale_2.x);
	//Project our ceiling & floor heights into screen coordinates (Y coordinate)
	pl->ceil.y1a = WIN_H / 2 - (int)(Yaw(pl->ceil.yceil, tz1, pl) * pl->scale_1.y);
	pl->floor.y1b = WIN_H / 2 - (int)(Yaw(pl->floor.yfloor, tz1, pl) * pl->scale_1.y);
	pl->ceil.y2a = WIN_H / 2 - (int)(Yaw(pl->ceil.yceil, tz2, pl) * pl->scale_2.y);
	pl->floor.y2b = WIN_H / 2 - (int)(Yaw(pl->floor.yfloor, tz2, pl) * pl->scale_2.y);
	//The same for the neighboring sector
	pl->ceil.ny1a = WIN_H / 2 - (int)(Yaw(pl->ceil.nyceil, tz1, pl) * pl->scale_1.y);
	pl->floor.ny1b = WIN_H / 2 - (int)(Yaw(pl->floor.nyfloor, tz1, pl) * pl->scale_1.y);
	pl->ceil.ny2a = WIN_H / 2 - (int)(Yaw(pl->ceil.nyceil, tz2, pl) * pl->scale_2.y);
	pl->floor.ny2b = WIN_H / 2 - (int)(Yaw(pl->floor.nyfloor, tz2, pl) * pl->scale_2.y);
}

/*
** **************************************************************************
**	void engine_ceil_floor(t_player *pl, int x)
**	Function to draw ceil and floor lines and lines betwen them
** **************************************************************************
*/

static void	engine_ceil_floor(t_player *pl, int x, int z)
{
	unsigned	col;

	pl->floor.nya = (x - pl->x1) * (pl->ceil.ny2a - pl->ceil.ny1a) / (pl->x2 - pl->x1) + pl->ceil.ny1a;
	pl->ceil.cnya = clamp(pl->floor.nya, pl->y_top[x], pl->y_bot[x]);
	pl->floor.nyb = (x - pl->x1) * (pl->floor.ny2b - pl->floor.ny1b) / (pl->x2 - pl->x1) + pl->floor.ny1b;
	pl->ceil.cnyb = clamp(pl->floor.nyb, pl->y_top[x], pl->y_bot[x]);
	//If our ceiling is higher than their ceiling, render upper wall
	col = 0xff0000 * (255 - z );//color from floor to ceil(wall top)
	vline(x, pl->ceil.cya, pl->ceil.cnya - 1, 0, (x == pl->x1) || (x == pl->x2) ? 0 : col, 0, pl->srf); //Line Between our and their ceiling
	pl->y_top[x] = clamp(max(pl->ceil.cya, pl->ceil.cnya), pl->y_top[x], WIN_H-1);   // Shrink the remaining window below these ceilings
	//If our floor is lower than their floor, render bottom wall
	col = 0x00ff00 * (31 - z / 8);//color from ceil to floor(wall bottom)
	vline(x, pl->ceil.cnyb+1, pl->ceil.cyb, 0, (x == pl->x1) || (x == pl->x2) ? 0 : col, 0, pl->srf); // Between their and our floor
	pl->y_bot[x] = clamp(min(pl->ceil.cyb, pl->ceil.cnyb), 0, pl->y_bot[x]); // Shrink the remaining window above these floors
}

/*
** **************************************************************************
**	void engine_ceil_floor(t_player *pl, int x)
**	Function to draw all needed lines
** **************************************************************************
*/

void		engine_put_lines(t_player *pl, int neib)
{
	int			z;
	int			x;
	unsigned	col;

	x = pl->beginx;
	while (++x <= pl->endx)
	{
		z = ((x - pl->x1) * (pl->t2.y - pl->t1.y) / (pl->x2 - pl->x1) + pl->t1.y) * 8;
		//Acquire the Y coordinates for our ceiling & floor for this X coordinate. Clamp them.
		pl->floor.ya = (x - pl->x1) * (pl->ceil.y2a - pl->ceil.y1a) / (pl->x2 - pl->x1) + pl->ceil.y1a;
		pl->ceil.cya = clamp(pl->floor.ya, pl->y_top[x], pl->y_bot[x]);// top
		pl->floor.yb = (x - pl->x1) * (pl->floor.y2b - pl->floor.y1b) / (pl->x2 - pl->x1) + pl->floor.y1b;
		pl->ceil.cyb = clamp(pl->floor.yb, pl->y_top[x], pl->y_bot[x]);// bottom
		//Render ceiling: everything above this sector's ceiling height.
		vline(x, pl->y_top[x], pl->ceil.cya - 1, 0xffffff, 0x222222 , 0xff0000, pl->srf);//ceiling colors
		//Render floor: everything below this sector's floor height.
		vline(x, pl->ceil.cyb + 1, pl->y_bot[x], 0x00ff00, 0x0000AA, 0x0000FF, pl->srf);
		if(neib >= 0)//ceil floor and some walls
			engine_ceil_floor(pl, x, z);
		else
		{
			//There's no neighbor. Render wall from top (cya = ceiling level) to bottom (cyb = floor level).
			col = 0x0000ff * (255 - z);
			vline(x, pl->ceil.cya, pl->ceil.cyb, 0, (x == pl->x1) || (x == pl->x2) ? 0 : col, 0, pl->srf);
		}	
	}
}