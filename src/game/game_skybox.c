//
// Created by danny on 26.01.2020.
//
#include "doom.h"

int			load_sky(t_new_player * pl)
{
    SDL_Surface *sky;
    unsigned int *pixels;
    int x;
    int y;

    sky = pl->img[3];
    pl->sky_pix = (int **)malloc(sizeof(int *) * sky->h);
    y = 0;
    while (y < sky->h)
    {
        pl->sky_pix[y] = (int *)malloc(sizeof(int) * sky->w);
        y++;
    }
    y = -1;
    pixels = (unsigned int *) sky->pixels;
    while (++y < sky->h) {
        x = -1;
        while (++x < sky->h)
            pl->sky_pix[y][x] = pixels[(y * sky->w) + x];
    }
    SDL_FreeSurface(sky);
    return (1);
}

void		pix_sky(t_textures *t, t_new_player *pl)//guarda la textura gun
{
    int *pix;
    int hex;
    unsigned int p;
    int n;

	n = 5;
    pix = (int *)pl->srf->pixels;
	p = (t->y%pl->tex[n].h) * pl->tex[n].w + t->x%pl->tex[n].w ;//formula = y*w + x
	hex = hexcolor(pl->tex[n].pixels[p].r, pl->tex[n].pixels[p].g, pl->tex[n].pixels[p].b);
    pix[t->y * WIN_W + t->x] = hex;//pl->sky_pix[t->y][t->x];
}