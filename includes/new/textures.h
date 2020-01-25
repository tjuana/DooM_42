//
// Created by Nymphadora Shelly on 17/01/2020.
//

#ifndef UNTITLED2_TEXTURES_H
#define UNTITLED2_TEXTURES_H
# define H_FOV					(1.0 * 0.73f * WIN_H / WIN_W)
# define V_FOV					(1.0 * .2f)
# define CEIL   0
# define FLOOR  1
# define WALL1   2
# define WALL2   3

#include "wolf3d.h"

typedef struct s_new_textures
{
    float hei;
    float mapx;
    float mapz;
    unsigned txtx1;
    unsigned txtz;
    int x;
    int y;
}               t_new_textures;

typedef struct			s_new_scaler
{
    int					result;
    int					bop;
    int					fd;
    int					ca;
    int					cache;

    int                 a;
    int                 b;
    int                 c;
    int                 d;
    int                 f;
}						t_new_scaler;

typedef	struct			s_new_weapons
{
    unsigned int					pistol_sprite[6][128][128];
    int					***lighter_sprite;
    int					type;
    double				sprite_counter;
}						t_new_weapons;

void		draw_cur_pistol_sprite(t_new_weapons *wpn, int width, int height, int cur_sprite, SDL_Surface *surface);
void		load_weapons(t_new_weapons *wpn);
void		load_pistol(t_new_weapons *wpn);
int			load_pistol_sprite(t_new_weapons *wpn, int sprite_count);
SDL_Surface		*load_pistol_part(int sprite);
void			draw_pistol(t_new_weapons *wpn, SDL_Surface *surface);

void vline_walls(int x, t_new_player *pl, t_new_scaler ty, int n);
t_new_scaler	scalar_create(int a, int b, int c, int d, int f);
int			scr_nxt(t_new_scaler *i);

int			color_transoform(int color, float percent);
int			ft_get_pixel(SDL_Surface *sur, int x, int y);
//void		draw_ceil_floor(t_draw_screen_calc *ds, t_new_player *p, t_tex_i tex_i, t_game *g);
void		pix1(t_new_textures *t, t_new_player *pl, int n);
void        load_imgs(SDL_Surface *img[10]);//load images
#endif //UNTITLED2_TEXTURES_H
