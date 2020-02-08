//
// Created by Nymphadora Shelly on 13/01/2020.
//
#include "doom.h"



void		draw_cur_pistol_sprite(t_gun *wpn, int width, int height, int cur_sprite, SDL_Surface *surface)
{
    int		x;
    int		y;
    int		x_img;
    float	x_num;
    float	y_num;
    int *pix = (int*)surface->pixels;

    y_num = 0;
    y = 0;
    (void)((y *= 0 | (int)(y_num *= 0)));
    while (y < 128 && height < WIN_H)
    {
        x = 0;
        x_num = 0;
        x_img = width - 200;
        while (x < 128 - 1 && x_img < WIN_W)
        {
            x_num += 0.3;//width of the gun and hand
            x = (int)x_num;
            if (wpn->pistol_sprite[cur_sprite][y][x] != 0x000000)
                    pix[height * WIN_W + x_img] =
                            color_transoform(wpn->pistol_sprite[cur_sprite][y][x], 1);
            x_img++;
        }
        y_num += 0.5;
        y = (int)y_num;
        height++;
    }
}

static void		draw_gun(t_new_player *pl, int width, int height, SDL_Surface *surface, int n)
{
	unsigned int		x;
	unsigned int		y;
	int		x_img;
	float	x_num;
	float	y_num;
	int *pix = (int*)surface->pixels;
	unsigned int p;
	int hex;

	y_num = 0;
	y = 0;
	(void)((y *= 0 | (int)(y_num *= 0)));
	while (y < pl->tex[n].h && height < WIN_H)
	{
		x = 0;
		x_num = 0;
		x_img = width - 200;
		while (x < pl->tex[n].w - 1 && x_img < WIN_W)
		{
			x_num += 0.8;//width of the gun and hand
			x = (int)x_num;
			p = (y%pl->tex[n].h) * pl->tex[n].w + x % pl->tex[n].w ;//formula = y*w + x
			hex = hexcolor(pl->tex[n].pixels[p].r, pl->tex[n].pixels[p].g, pl->tex[n].pixels[p].b);
			if (pl->tex[n].pixels[p].a != 0)
				pix[height * WIN_W + x_img] =
						color_transoform(hex, pl->light);
			x_img++;
		}
		y_num += 1;
		y = (int)y_num;
		height++;
	}
}

void			draw_pistol(t_gun *wpn, t_new_player *pl)
{
	int n;
	n = 9;
    if (wpn->sprite_counter == 1)
		draw_gun(pl,WIN_W - 400, WIN_H - 310, pl->srf, n);
    else if (wpn->sprite_counter > 1)
    {
            draw_gun(pl,WIN_W - 430 ,WIN_H - 340, pl->srf, n + 1);
        wpn->sprite_counter += 1;
    }
    if (wpn->sprite_counter > 3)
        wpn->sprite_counter = 1;
}

