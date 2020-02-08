//
// Created by danny on 26.01.2020.
//
#include "doom.h"

void		pix_sky(t_textures *t, t_new_player *pl)//guarda la textura gun
{
    int hex;
    unsigned int p;

    pl->pix = (int *)pl->srf->pixels;
	p = (t->y%pl->tex[SKY].h) * pl->tex[SKY].w + t->x%pl->tex[SKY].w ;//formula = y*w + x
	hex = hexcolor(pl->tex[SKY].pixels[p].r, pl->tex[SKY].pixels[p].g, pl->tex[SKY].pixels[p].b);
    pl->pix[t->y * WIN_W + t->x] = hex;//pl->sky_pix[t->y][t->x];
}