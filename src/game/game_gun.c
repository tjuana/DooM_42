//
// Created by Nymphadora Shelly on 13/01/2020.
//
#include "wolf3d.h"



void		draw_cur_pistol_sprite(t_new_weapons *wpn, int width,
                                   int height, int cur_sprite, SDL_Surface *surface)
{
    int		x;
    int		y;
    int		x_img;
    float	x_num;
    float	y_num;
    unsigned int *pix = surface->pixels;

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

            if ((wpn->pistol_sprite[cur_sprite][y][x] >> 24 & 0XFF) != 0)
                pix[height * WIN_W + x_img] =
                        wpn->pistol_sprite[cur_sprite][y][x];
            x_img++;
        }
        y_num += 0.5;
        y = (int)y_num;
        height++;
    }
}

void		load_weapons(t_new_weapons *wpn)
{
    wpn->sprite_counter = 1;
    load_pistol(wpn);
}

void		load_pistol(t_new_weapons *wpn)
{
    int sprite;
    int max_sprites;

    max_sprites = 6;//number of images
    sprite = 0;
    while  (sprite < max_sprites)
    {
        load_pistol_sprite(wpn, sprite);
        sprite++;
    }
}

int			load_pistol_sprite(t_new_weapons *wpn, int sprite_count)
{
    SDL_Surface		*cur_sprite;
    unsigned int	*pixels;
    int				x;
    int				y;

    if (!(IMG_Init(IMG_INIT_PNG) & IMG_INIT_PNG))
        ft_putendl(IMG_GetError());
    cur_sprite = load_pistol_part(sprite_count);
    y = -1;
    pixels = (unsigned int *)cur_sprite->pixels;
    while (++y < 128)
    {
        x = -1;
        while (++x < 128)
            wpn->pistol_sprite[sprite_count][y][x] = pixels[(y * cur_sprite->w) + x];
    }
    SDL_FreeSurface(cur_sprite);
    return (1);
}

SDL_Surface		*load_pistol_part(int sprite)
{
    SDL_Surface *cur_sprite;
    SDL_Surface *tmp;
     cur_sprite = NULL;

    if (sprite == 0)
        cur_sprite = IMG_Load("sprites/pistol1.png");
    else if (sprite == 1)
        cur_sprite = IMG_Load("sprites/pistol2.png");
    else if (sprite == 2)
        cur_sprite = IMG_Load("sprites/pistol3.png");
    else if (sprite == 3)
        cur_sprite = IMG_Load("sprites/pistol4.png");
    else if (sprite == 4)
        cur_sprite = IMG_Load("sprites/pistol5.png");
    else if (sprite == 5)
        cur_sprite = IMG_Load("sprites/pistol6.png");
    tmp = SDL_ConvertSurfaceFormat(cur_sprite,
                                   SDL_PIXELFORMAT_ARGB8888, 0);//SDL_PIXELFORMAT_ARGB32, 0);
    SDL_FreeSurface(cur_sprite);
    cur_sprite = tmp;
    return (cur_sprite);
}

void			draw_pistol(t_new_weapons *wpn, SDL_Surface *surface)
{
    static float velocity;//how fast are we going to see the animation of the gun
    if (wpn->sprite_counter == 1)
        draw_cur_pistol_sprite(wpn, WIN_W - 600, WIN_H - 250, 0, surface);
    else if (wpn->sprite_counter > 1)
    {
        //velocity = 0;
        if(velocity < 3)
        {
            draw_cur_pistol_sprite(wpn, WIN_W - 600, WIN_H - 250, wpn->sprite_counter - 1, surface);
            velocity += 0.05f;
        } else
            velocity = 0;
        wpn->sprite_counter += 1;
    }
    if (wpn->sprite_counter >= 6)
        wpn->sprite_counter = 1;
}

