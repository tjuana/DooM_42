//
// Created by danny on 26.01.2020.
//
#include "doom.h"

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
	// hex = 0xff0000;
    pix[t->y * WIN_W + t->x] = hex;//pl->sky_pix[t->y][t->x];
}