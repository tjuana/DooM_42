//
// Created by Nymphadora Shelly on 13/01/2020.
//
#include "doom.h"

static void		draw_gun(t_new_player *pl, int width, int height, int n)
{
	t_draw_gun g;

	g.y_num = 0;
	g.y = 0;
	(void)((g.y *= 0 | (int)(g.y_num *= 0)));
	while (g.y < pl->tex[n].h && height < WIN_H)
	{
		g.x = 0;
		g.x_num = 0;
		g.x_img = width - 200;
		while (g.x < pl->tex[n].w - 1 && g.x_img < WIN_W)
		{
			g.x_num += 0.8;//width of the gun and hand
			g.x = (int)g.x_num;
			g.p = (g.y % pl->tex[n].h) * pl->tex[n].w + g.x % pl->tex[n].w ;//formula = y*w + x
			g.hex = hexcolor(pl->tex[n].pixels[g.p].r, pl->tex[n].pixels[g.p].g, pl->tex[n].pixels[g.p].b);
			if (pl->tex[n].pixels[g.p].a != 0)
				pl->pix[height * WIN_W + g.x_img] =
						color_transoform(g.hex, pl->light);
			g.x_img++;
		}
		g.y_num += 1;
		g.y = (int)g.y_num;
		height++;
	}
}

void			draw_pistol(t_gun *wpn, t_new_player *pl)
{
	int n;
	n = GUN;
    if (wpn->sprite_counter == 1)
		draw_gun(pl,WIN_W - 400, WIN_H - 310, n);
    else if (wpn->sprite_counter > 1)
    {
            draw_gun(pl,WIN_W - 430 ,WIN_H - 340, n + 1);
        wpn->sprite_counter += 1;
    }
    if (wpn->sprite_counter > 3)
        wpn->sprite_counter = 1;
}

