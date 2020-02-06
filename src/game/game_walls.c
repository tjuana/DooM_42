/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_walls.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dorange- <dorange-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/28 21:41:49 by dorange-          #+#    #+#             */
/*   Updated: 2020/02/04 13:17:29 by dorange-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//
// Created by Nymphadora Shelly on 20/01/2020.
//

#include "doom.h"

// delete
void load_imgs(SDL_Surface *img[10])
{
    img[0]= IMG_Load("Textures/wall1.png");
    img[0]= SDL_ConvertSurfaceFormat(img[0], SDL_PIXELFORMAT_ARGB8888, 0);
    img[1]= IMG_Load("Textures/wood.png");
    img[1]= SDL_ConvertSurfaceFormat(img[1], SDL_PIXELFORMAT_ARGB8888, 0);
    img[2]= IMG_Load("Textures/wall2.png");
    img[2]= SDL_ConvertSurfaceFormat(img[2], SDL_PIXELFORMAT_ARGB8888, 0);
    img[3]= IMG_Load("Textures/cosmos.png");
    img[3]= SDL_ConvertSurfaceFormat(img[3], SDL_PIXELFORMAT_ARGB8888, 0);
    img[4]= IMG_Load("Textures/bloody_game.jpg");
    img[4]= SDL_ConvertSurfaceFormat(img[4], SDL_PIXELFORMAT_ARGB8888, 0);
    img[5]= IMG_Load("Textures/graffiti.png");
    img[5]= SDL_ConvertSurfaceFormat(img[5], SDL_PIXELFORMAT_ARGB8888, 0);
    img[6]= IMG_Load("Textures/green.png");
    img[6]= SDL_ConvertSurfaceFormat(img[6], SDL_PIXELFORMAT_ARGB8888, 0);
    img[7]= IMG_Load("Textures/red.png");
    img[7]= SDL_ConvertSurfaceFormat(img[7], SDL_PIXELFORMAT_ARGB8888, 0);
    img[8]= IMG_Load("Textures/met.png");
    img[8]= SDL_ConvertSurfaceFormat(img[8], SDL_PIXELFORMAT_ARGB8888, 0);
    img[9]= IMG_Load("Textures/wood.png");
}

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
	int		*pix;
	int 		hex;
	unsigned int 		p;
	t_scaler	ty;

	if(wall == 0)
	{
		pl->y1 = pl->ceil.cya;
		pl->y2 = pl->ceil.cnya;
	}
	if(wall == 1)
	{
		pl->y1 = pl->ceil.cnyb;
		pl->y2 = pl->ceil.cyb;
	}
	if(wall == 2)
	{
		pl->y1 = pl->ceil.cya;
		pl->y2 = pl->ceil.cyb;
	}
	ty = scalar_create(pl->floor.ya, pl->y1, pl->floor.yb, 0, pl->tex[0].w - 1);
	y = pl->y1;
	pix = (int *)pl->srf->pixels;
	// pix = (int*)pl->srf->pixels;
	pl->y1 = clamp(pl->y1, 0, WIN_H-1);//??
	pl->y2 = clamp(pl->y2, 0, WIN_H-1);//??
	if(pl->y2 >= pl->y1 && wall)
	{
		// if(pl->y2 == pl->y1)
			// pix[pl->y1*WIN_W+x] = pl->sky_pix[pl->y1][x];
		while (y < pl->y2)
		{
			++y;
			txty = scr_nxt(&ty);
			// p = ((txty % pl->srf->h) * pl->tex[n].w + (pl->txtx % pl->srf->w)% pl->tex[n].w);//formula = y*w + x
			// hex = hexcolor(pl->tex[n].pixels[p].r, pl->tex[n].pixels[p].g, pl->tex[n].pixels[p].b);
			// if (pl->tex[n].pixels[p].a == 0)//hex == 0x000000)
			// {
				// p = (y%pl->tex[5].h) * pl->tex[5].w + x%pl->tex[5].w ;//formula = y*w + x
				// hex = hexcolor(pl->tex[5].pixels[p].r, pl->tex[5].pixels[p].g, pl->tex[5].pixels[p].b);
			// }
			// // hex = 0xff0000;
			// pix[y * WIN_W + x] = hex;//color;

			pix[y * WIN_W + x] = 0x4b0082;
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
