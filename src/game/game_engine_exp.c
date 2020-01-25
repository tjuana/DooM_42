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

#define TEMP_WIN_W_FOR_SURFACE 1400

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
	int		c;

	//Acquire the x,y coordinates of the two endpoints (vertices) of this edge of the sector
	v_start.x = pl->sectors[sec_n].vertex[s + 0].x - pl->where.x;
	v_start.y = pl->sectors[sec_n].vertex[s + 0].y - pl->where.y;
	v_end.x = pl->sectors[sec_n].vertex[s + 1].x - pl->where.x;
	v_end.y = pl->sectors[sec_n].vertex[s + 1].y - pl->where.y;

	// Определяем длину отрезка
	// c = (int)(sqrt(pow(v_end.x - v_start.x, 2) + pow(v_end.y - v_start.y, 2)) * WIN_W);

	pl->cl = sqrt(pow(v_end.x - v_start.x, 2) + pow(v_end.y - v_start.y, 2));
	c = pl->cl * 200;

	//Rotate them around the player's view
	pl->t1.x = v_start.x * pl->anglesin - v_start.y * pl->anglecos;
	pl->t1.y = v_start.x * pl->anglecos + v_start.y * pl->anglesin;
	pl->t2.x = v_end.x * pl->anglesin - v_end.y * pl->anglecos;
	pl->t2.y = v_end.x * pl->anglecos + v_end.y * pl->anglesin;
	//Is the wall at least partially in front of the player?
	if((pl->t1.y <= 0) && (pl->t2.y <= 0))
		return (0); //continue
	//If it's partially behind the player, cut it against player's view
	pl->u0 = 0;
	pl->u1 = c;
	pl->wall_height_c = pl->sect->ceil;
	// Вопрос смещения
	if((pl->t1.y <= 0) || (pl->t2.y <= 0))
	{
		// Find an intersection between the wall and the approximate edges of player's view
		i1 = Intersect(pl->t1.x, pl->t1.y, pl->t2.x, pl->t2.y, -pl->nearside, pl->nearz, -pl->farside, pl->farz);
		i2 = Intersect(pl->t1.x, pl->t1.y, pl->t2.x, pl->t2.y, pl->nearside, pl->nearz, pl->farside, pl->farz);
        pl->org1x = pl->t1.x;
        pl->org1y = pl->t1.y;
        pl->org2x = pl->t2.x;
        pl->org2y = pl->t2.y;
		(pl->t1.y < pl->nearz && i1.y > 0) ? pl->t1 = i1 : pl->t1;
		(pl->t1.y < pl->nearz && i1.y < 0) ? pl->t1 = i2 : pl->t1;
		(pl->t2.y < pl->nearz && i1.y > 0) ? pl->t2 = i1 : pl->t2;
		(pl->t2.y < pl->nearz && i1.y < 0) ? pl->t2 = i2 : pl->t2;
        /*EXTRA CALCS FOR WALLS*/
		// Соотношения
        if (fabsf(pl->t2.x - pl->t1.x) > fabsf(pl->t2.y - pl->t1.y)) {
            pl->u0 = (int) ((pl->t1.x - pl->org1x) * c / (pl->org2x - pl->org1x));
            pl->u1 = (int) ((pl->t2.x - pl->org1x) * c / (pl->org2x - pl->org1x));
        } else {
            pl->u0 = (int) ((pl->t1.y - pl->org1y) * c /
                        (pl->org2y - pl->org1y));
            pl->u1 = (int) ((pl->t2.y - pl->org1y) * c /
                        (pl->org2y - pl->org1y));
        }
        /*END EXTRA CALCAS FOR WALLS*/
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
	col = 0;

	*z = ((x - pl->x1) * (pl->t2.y - pl->t1.y) / (pl->x2 - pl->x1) + pl->t1.y) * 8;
	//Acquire the Y coordinates for our ceiling & floor for this X coordinate. Clamp them.
	pl->floor.ya = (x - pl->x1) * (pl->ceil.y2a - pl->ceil.y1a) / (pl->x2 - pl->x1) + pl->ceil.y1a;
	pl->floor.yb = (x - pl->x1) * (pl->floor.y2b - pl->floor.y1b) / (pl->x2 - pl->x1) + pl->floor.y1b;
	pl->ceil.cya = clamp(pl->floor.ya, pl->y_top[x], pl->y_bot[x]);// top
	pl->ceil.cyb = clamp(pl->floor.yb, pl->y_top[x], pl->y_bot[x]);// bottom
	//Render ceiling: everything above this sector's ceiling height.
	//vline(x, pl->y_top[x], pl->ceil.cya - 1, 0xffffff, 0x222222 , 0xff0000, pl->srf);//ceiling colors
	//Render floor: everything below this sector's floor height.
	//vline(x, pl->ceil.cyb + 1, pl->y_bot[x], 0x00ff00, 0x0000AA, 0x0000FF, pl->srf);
    /*  NEW CODOE FOR TEXTURES CEIL AND FLOOR*/

    t_new_textures t;

    t.y = pl->y_top[x];
    t.x = x;
    while (++t.y <= pl->y_bot[x])//HERE we draw ceil and floor
    {
        if (t.y >= pl->ceil.cya && t.y <= pl->ceil.cyb)
        {
            t.y = pl->ceil.cyb;
            continue;
        }
        t.hei = t.y < pl->ceil.cya ? pl->ceil.yceil : pl->floor.yfloor;
        t.mapz = t.hei * WIN_H * V_FOV / ((WIN_H / 2 - (float)t.y) - pl->yaw * WIN_H * V_FOV);
        //printf("%f\n", player->yaw);
        t.mapx = t.mapz * (WIN_W/2 - (float)t.x) / (WIN_W * (H_FOV));
        t.txtx1 = (unsigned int)(((t.mapz * pl->anglecos + t.mapx * pl->anglesin) + pl->where.x) * 256);
        t.txtz = (unsigned int)(((t.mapz * pl->anglesin - t.mapx * pl->anglecos) + pl->where.y) * 256);
        if (t.y < pl->ceil.cya)
            pix1(&t, pl, CEIL);
        else
            pix1(&t, pl, FLOOR);

    }
    /* END OF CODE FOR TEXTURES CEIL AND FLOOR*/
	if(neib >= 0)
	{
		pl->floor.nya = (x - pl->x1) * (pl->ceil.ny2a - pl->ceil.ny1a) / (pl->x2 - pl->x1) + pl->ceil.ny1a;
		pl->ceil.cnya = clamp(pl->floor.nya, pl->y_top[x], pl->y_bot[x]);
		pl->floor.nyb = (x - pl->x1) * (pl->floor.ny2b - pl->floor.ny1b) / (pl->x2 - pl->x1) + pl->floor.ny1b;
		pl->ceil.cnyb = clamp(pl->floor.nyb, pl->y_top[x], pl->y_bot[x]);
		//If our ceiling is higher than their ceiling, render upper wall
        int a,b,c,d,f;
        a = pl->floor.ya;
        b = pl->ceil.cya;
        c = pl->floor.yb;
        d = 0;
        f = TEMP_WIN_W_FOR_SURFACE - 1;
        pl->y1 = pl->ceil.cya;
        pl->y2 = pl->ceil.cnya;
        vline_walls(x, pl, scalar_create(a,b,c,d,f), WALL1);
		//col = 0xff0000 * (255 - *z);//color from floor to ceil(wall top)
		//vline(x, pl->ceil.cya, pl->ceil.cnya - 1, 0xff0000, (x == pl->x1) || (x == pl->x2) ? 0 : col, 0x00ff00, pl->srf); //Line Between our and their ceiling
		pl->y_top[x] = clamp(max(pl->ceil.cya, pl->ceil.cnya), pl->y_top[x], WIN_H-1);   // Shrink the remaining window below these ceilings
		//If our floor is lower than their floor, render bottom wall
		//col = 0x00ff00 * (31 - *z / 8);//color from ceil to floor(wall bottom)
		//vline(x, pl->ceil.cnyb+1, pl->ceil.cyb, 0, (x == pl->x1) || (x == pl->x2) ? 0 : col, 0, pl->srf); // Between their and our floor
		pl->y_bot[x] = clamp(min(pl->ceil.cyb, pl->ceil.cnyb), 0, pl->y_bot[x]); // Shrink the remaining window above these floors
        a = pl->floor.ya;
        b = pl->ceil.cnyb + 1;
        c = pl->floor.yb;
        d = 0;
        f = TEMP_WIN_W_FOR_SURFACE - 1;
        pl->y1 = pl->ceil.cnyb + 1;
        pl->y2 = pl->ceil.cyb;
        vline_walls(x, pl, scalar_create(a,b,c,d,f), WALL1);
        //vline(x, pl->ceil.cnyb+1, pl->ceil.cyb, 0xff0000, (x == pl->x1) || (x == pl->x2) ? 0 : col, 0x00ff00, pl->srf);
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
	// int			x;
	// unsigned	col;

	pl->beginx = (int)fmax((double)pl->x1, (double)pl->cycle.current->sx1);
	pl->endx = (int)fmin((double)pl->x2, (double)pl->cycle.current->sx2);
	pl->interx = pl->beginx;
	while (++pl->interx <= pl->endx)
	{
        pl->txtx = (int)((pl->u0 * ((pl->x2 - pl->interx) * pl->t2.y) + pl->u1 * ((pl->interx - pl->x1) * pl->t1.y)) / ((pl->x2 - pl->interx) * pl->t2.y + (pl->interx - pl->x1) * pl->t1.y));
		engine_ceil_floor(pl, pl->interx, &z, neib);//ceil floor and some walls
		if(neib < 0)
		{
			//There's no neighbor. Render wall from top (cya = ceiling level) to bottom (cyb = floor level).
			// col = 0x0000ff * (255 - z);

            int a,b,c,d,f;
			a = pl->floor.ya ;
            b = pl->ceil.cya;
            c = pl->floor.yb ;
            d = 0;
            f = TEMP_WIN_W_FOR_SURFACE - 1;
            pl->y1 = pl->ceil.cya;
            pl->y2 = pl->ceil.cyb;
            vline_walls(pl->interx, pl, scalar_create(a,b,c,d,f), WALL1);
            //vline(x, pl->ceil.cya, pl->ceil.cyb, 0xff0000, 0, 0x00ff00, pl->srf);
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