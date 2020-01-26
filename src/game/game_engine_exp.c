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

#include "doom.h"

/*
** **************************************************************************
**	int engine_cross(t_new_player *pl, int sec_n, unsigned s)
**	Function to find intersections and set t1 & t2
**	t1.y was tz1 before recontruction
** **************************************************************************
*/

int			engine_cross(t_new_player *pl, int sec_n, unsigned s)
{
	t_new_xy	i1;
	t_new_xy	i2;
	t_new_xy	v_start;
	t_new_xy	v_end;

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
		if(pl->t1.y < pl->nearz)
		{
			if(i1.y > 0)
				pl->t1 = i1;
			else
				pl->t1 = i2;
		}
		if(pl->t2.y < pl->nearz)
		{
			if(i1.y > 0)
				pl->t2 = i1;
			else
				pl->t2 = i2;
		}
		
		/*(pl->t1.y < pl->nearz && i1.y > 0) ? pl->t1 = i1 : pl->t1;
		(pl->t1.y < pl->nearz && i1.y < 0) ? pl->t1 = i2 : pl->t1;
		(pl->t2.y < pl->nearz && i1.y > 0) ? pl->t2 = i1 : pl->t2;
		(pl->t2.y < pl->nearz && i1.y < 0) ? pl->t2 = i2 : pl->t2;*/
	}
	return (1);
}

/*
** **************************************************************************
**	static void engine_ceil_floor(t_new_player *pl, int x, int *z, int neib)
**	Function to draw ceil and floor lines and lines betwen them
** **************************************************************************
*/

static void	engine_ceil_floor(t_new_player *pl, int x, int *z, int neib)
{
	unsigned	col;

	*z = ((x - pl->x1) * (pl->t2.y - pl->t1.y) / (pl->x2 - pl->x1) + pl->t1.y) * 8;
	//Acquire the Y coordinates for our ceiling & floor for this X coordinate. Clamp them.
	pl->floor.ya = (x - pl->x1) * (pl->ceil.y2a - pl->ceil.y1a) / (pl->x2 - pl->x1) + pl->ceil.y1a;
	pl->ceil.cya = clamp(pl->floor.ya, pl->y_top[x], pl->y_bot[x]);// top
	pl->floor.yb = (x - pl->x1) * (pl->floor.y2b - pl->floor.y1b) / (pl->x2 - pl->x1) + pl->floor.y1b;
	pl->ceil.cyb = clamp(pl->floor.yb, pl->y_top[x], pl->y_bot[x]);// bottom
	//Render ceiling: everything above this sector's ceiling height.
	vline(x, pl->y_top[x], pl->ceil.cya - 1, 0xffffff, 0x222222 , 0xff0000, pl->srf);//ceiling colors
	//Render floor: everything below this sector's floor height.
	vline(x, pl->ceil.cyb + 1, pl->y_bot[x], 0x00ff00, 0x0000AA, 0x0000FF, pl->srf);
	if(neib >= 0)
	{
		pl->floor.nya = (x - pl->x1) * (pl->ceil.ny2a - pl->ceil.ny1a) / (pl->x2 - pl->x1) + pl->ceil.ny1a;
		pl->ceil.cnya = clamp(pl->floor.nya, pl->y_top[x], pl->y_bot[x]);
		pl->floor.nyb = (x - pl->x1) * (pl->floor.ny2b - pl->floor.ny1b) / (pl->x2 - pl->x1) + pl->floor.ny1b;
		pl->ceil.cnyb = clamp(pl->floor.nyb, pl->y_top[x], pl->y_bot[x]);
		//If our ceiling is higher than their ceiling, render upper wall
		col = 0xff0000 * (255 - *z);//color from floor to ceil(wall top)
		vline(x, pl->ceil.cya, pl->ceil.cnya - 1, 0, (x == pl->x1) || (x == pl->x2) ? 0 : col, 0, pl->srf); //Line Between our and their ceiling
		pl->y_top[x] = clamp(max(pl->ceil.cya, pl->ceil.cnya), pl->y_top[x], WIN_H-1);   // Shrink the remaining window below these ceilings
		//If our floor is lower than their floor, render bottom wall
		col = 0x00ff00 * (31 - *z / 8);//color from ceil to floor(wall bottom)
		vline(x, pl->ceil.cnyb+1, pl->ceil.cyb, 0, (x == pl->x1) || (x == pl->x2) ? 0 : col, 0, pl->srf); // Between their and our floor
		pl->y_bot[x] = clamp(min(pl->ceil.cyb, pl->ceil.cnyb), 0, pl->y_bot[x]); // Shrink the remaining window above these floors
	}

}

/*
** **************************************************************************
**	void engine_ceil_floor(t_new_player *pl, int neib)
**	Function to draw all needed lines
** **************************************************************************
*/

void		engine_put_lines(t_new_player *pl, int neib)
{
	int			z;
	int			x;
	unsigned	col;

	pl->beginx = (int)fmax((double)pl->x1, (double)pl->cycle.current->sx1);
	pl->endx = (int)fmin((double)pl->x2, (double)pl->cycle.current->sx2);
	x = pl->beginx;
	while (++x <= pl->endx)
	{
		engine_ceil_floor(pl, x, &z, neib);//ceil floor and some walls
		if(neib < 0)
		{
			//There's no neighbor. Render wall from top (cya = ceiling level) to bottom (cyb = floor level).
			col = 0x0000ff * (255 - z);
			vline(x, pl->ceil.cya, pl->ceil.cyb, 0, (x == pl->x1) || (x == pl->x2) ? 0 : col, 0, pl->srf);
		}	
	}
	//Schedule the neighboring sector for rendering within the window formed by this wall.
	if(neib >= 0 && pl->endx >= pl->beginx && (pl->cycle.head + MAX_QUEUE + 1 - pl->cycle.tail) % MAX_QUEUE)
	{
		pl->cycle.head->sec_nb = neib;
		pl->cycle.head->sx1 = pl->beginx;
		pl->cycle.head->sx2 = pl->endx;
		if(++pl->cycle.head == pl->cycle.queue + MAX_QUEUE)
			pl->cycle.head = pl->cycle.queue;
	}
}