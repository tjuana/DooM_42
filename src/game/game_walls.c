/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_walls.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjuana <tjuana@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/28 21:41:49 by dorange-          #+#    #+#             */
/*   Updated: 2020/01/29 15:21:51 by tjuana           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//
// Created by Nymphadora Shelly on 20/01/2020.
//

#include "doom.h"

t_scaler	scalar_create(int a, int b, int c, int d, int f)
{
    t_scaler	s;
    if (c - a == 0)
        c += 1;
    s.result = d + (b - 1 - a) * (f - d) / (c - a);
    s.bop = ((f < d) ^ (c < a)) ? -1 : 1;
    s.fd = abs(f - d);
    s.ca = abs(c - a);
    s.cache = (int)((b - 1 - a) * abs(f - d)) % abs(c - a);
    return (s);
}

int			scr_nxt(t_scaler *i)
{
    i->cache += i->fd;
    while (i->cache >= i->ca)
    {
        i->result += i->bop;
        i->cache -= i->ca;
    }
    return (i->result);
}

int hexcolor( int r, int g, int b)
{
	return ((r<<16) | (g<<8) | b);
}

void draw_walls(int x, t_new_player *pl, int wall, int n)
{
    unsigned	txty;
    int			y;
    int        *pix;
    int 		hex;
    unsigned int 		p;
    t_scaler    ty;

    if(wall == 0)
    {
        pl->y1 = pl->ceil.cya;
        pl->y2 = pl->ceil.cnya - 1;
    }
    else if(wall == 1)
    {
        pl->y1 = pl->ceil.cnyb + 1;
        pl->y2 = pl->ceil.cyb;
    }
    else if(wall == 2)
    {
        pl->y1 = pl->ceil.cya;
        pl->y2 = pl->ceil.cyb;
    }
    ty = scalar_create(pl->floor.ya, pl->y1, pl->floor.yb, 0, pl->tex[n].w - 1);
    y = pl->y1;
    pix = (int *)pl->srf->pixels;
    pl->y1 = clamp(pl->y1, 0, WIN_H-1);//??
    pl->y2 = clamp(pl->y2, 0, WIN_H-1);//??
    if(pl->y2 >= pl->y1)
    {
        // if(pl->y2 == pl->y1)
            // pix[pl->y1*WIN_W+x] = pl->sky_pix[pl->y1][x];
        while (y < pl->y2)
        {
        	++y;
            txty = scr_nxt(&ty);
			p = ((txty % pl->srf->h) * pl->tex[n].w + (pl->txtx % pl->srf->w)% pl->tex[n].w);//formula = y*w + x
            hex = color_transoform(hexcolor(pl->tex[n].pixels[p].r, pl->tex[n].pixels[p].g, pl->tex[n].pixels[p].b),pl->light);
            if (pl->tex[n].pixels[p].a == 0)//this is for transparent wall
			{
				p = (y%pl->tex[SKY].h) * pl->tex[SKY].w + x%pl->tex[SKY].w ;//formula = y*w + x
				hex = hexcolor(pl->tex[5].pixels[p].r, pl->tex[SKY].pixels[p].g, pl->tex[SKY].pixels[p].b);
			}
            pix[y * WIN_W + x] = hex;
        }
    }

}

void vline_graffiti(int x, t_new_player *pl, t_scaler ty, int n)
{
    unsigned	txty;
    int			y;
    int         *pix;
    int         color;

    y = pl->y1;
    pix = (int*)pl->srf->pixels;
    pl->y1 = clamp(pl->y1, 0, WIN_H);
    pl->y2 = clamp(pl->y2 , 0, WIN_H);
    pix += pl->y1  * WIN_W + x ;
    while (y <= pl->y2)
    {
        ++y;
        txty = scr_nxt(&ty);
        color = ft_get_pixel(pl->img[n], pl->txtx % (pl->img[n]->w + 200), txty % pl->img[n]->h);
        if (color != 0x000000)
         *pix = color_transoform(color, pl->light);
        pix += WIN_W ;
    }
}
