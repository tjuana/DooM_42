#ifndef WOLF3D_H
# define WOLF3D_H

# include "SDL2/SDL.h"
# include "SDL2/SDL_thread.h"
# include "SDL2/SDL_ttf.h"
# include "SDL2/SDL_image.h"
# include <pthread.h>
# include <string.h>
# include <stdio.h>
# include <stdlib.h>
# include <fcntl.h>
# include <math.h>
# include <string.h>
# include <libft.h>
# include <sys/stat.h>
# include "constants.h"
# include "help.h"
# include "animations.h"
# include "engine.h"
# include "events.h"
# include "door.h"
# include "texture.h"
# include "player.h"
# include "sky.h"



//static unsigned NumSectors = 0;

typedef struct	s_new_wolf3d
{	
	SDL_Surface	*weapon_texture;
	t_new_anime		anim;
	int			*tex_col;
	int			color;
}				t_new_wolf3d;

typedef	struct		s_new_temp
{
    t_new_sub_ev		se;
    t_new_mouse			ms;
    t_new_player		pl;
    t_new_others		ot;
    t_new_sect_ops		op;
	t_new_wolf3d		w;
}					t_new_temp;

/*			animations.c			*/
int			ft_init_anim(t_new_wolf3d *wolf);
void		ft_draw_animation(t_new_wolf3d *w);
void		ft_animation_play(t_new_wolf3d *w);

/*			but_detect.c			*/
int			but_detect(t_new_player *pl);//return sec_nb of button

/*			but.c			*/
void		but_total(t_new_player *pl);//create buttons array
int			but_script(t_new_player *pl, int but_nb, t_new_sub_ev *se);//choose but task

/*			door_detect.c			*/
int			door_detect(t_new_player *pl);//return sec_nb of door

/*			door.c			*/
void		door_but_сlick(t_new_player *pl, t_new_sub_ev *se);//when you press E key or button
void		door(t_new_player *pl, t_new_sub_ev *se);//cycle for open door

/*			engine_exp.c			*/
// int			engine_cross(t_new_player *pl, int sec_n, unsigned s);
int			engine_cross(t_new_player *pl);
void		engine_put_lines(t_new_player *pl, int neib);

/*			engine.c			*/
void		engine_begin(t_new_player *pl);
int			engine_scale(t_new_player *pl, int sx1, int sx2);

/*			events_1.c			*/
int			events(t_new_sub_ev *se, t_new_player *player);

/*			events_2.c			*/
void		events_new_mouse_move(t_new_mouse *ms, t_new_player *pl);
void		events_vel(t_new_player *pl, t_new_sub_ev *se, t_new_others *ot);
void		events_jumps(t_new_sub_ev *se, t_new_player *pl, t_new_sect_ops *op, t_new_others *ot);

/*			load_file.c			*/
t_new_player	*load_next(t_new_player *pl);
void		load_file(char *ag, t_new_player *pl);

/*			load_textures.c			*/
t_new_texture	*load_textures(t_new_player *pl);
void		texture_init(t_new_player *pl);
SDL_Texture	*texture_new(t_new_player *pl);

/*			main.c			*/
int			main(int ac, char **ag);
// void		player_init(t_new_player *pl, t_new_xy *v, float *angle, int *n);
void		line(int x, int y1,int y2, int top,int middle,int bottom, t_new_player *pl);

/*			math_functions.c			*/
float		min(float a, float b);
float		max(float a, float b);
float		clamp(float a, float mi, float ma);
float		vxs(float x0, float y0, float x1, float y1);
int			Overlap(float a0, float a1, float b0, float b1);
int			IntersectBox(float x0, float y0, float x1, float y1,float x2, float y2, float x3, float y3);
float		PointSide(float px, float py, float x0, float y0,float x1, float y1);
t_new_xy	Intersect(float x1, float y1, float x2, float y2,float x3, float y3, float x4, float y4);
void		UnloadData();
float		Yaw(float y, float z, t_new_player *player);
double		to_deg(double radians);

/*			motion.c			*/
void		motion_chk(t_new_sect_ops *op, t_new_player *player, t_new_others *ot, t_new_sub_ev *se);
void		motion_move_pl(t_new_xy *delt, t_new_player *pl);

/*			sdl_addons.c			*/
SDL_Rect	*ft_create_rect(int w, int h, int x, int y);
void		ft_sdl_error();



/*			texture_parser.c			*/
t_new_texture	texture_parse(const char *fp);




/*			vector_1.c			*/
t_new_vector3	ft_new_vec3_create(t_new_vector3 *orig, t_new_vector3 *dest);
double		ft_new_vec3_magnitude(t_new_vector3 this);
t_new_vector3	ft_new_vec3_add(t_new_vector3 this, t_new_vector3 rhs);
t_new_vector3	ft_new_vec3_sub(t_new_vector3 this, t_new_vector3 rhs);
t_new_vector3	ft_new_vec3_cross_product(t_new_vector3 this, t_new_vector3 rhs);

/*			vector_2.c			*/
double		ft_new_vec3_dot_product(t_new_vector3 this, t_new_vector3 rhs);
double		ft_new_vec3_cosinus(t_new_vector3 this, t_new_vector3 rhs);
t_new_vector3	ft_new_vec3_opposite(t_new_vector3 this);
t_new_vector3	ft_new_vec3_scalar_product(t_new_vector3 this, double k);
t_new_vector3	ft_new_vec3_normalize(t_new_vector3 vtc);

/*			vector_3.c			*/
float		vec2_cos(t_new_vector3 vec1, t_new_vector3 vec2);

// void vline(int x, int y1,int y2, int top,int middle,int bottom, t_new_player *pl);
void vline(int x, int y1,int y2, int top,int middle,int bottom, SDL_Surface* surface);

static void	nearz_change(t_new_player *pl);
static void	nearside_change(t_new_player *pl);
static void	farz_change(t_new_player *pl);
static void	farside_change(t_new_player *pl);
static void	sub_events_2(t_new_sub_ev *se, t_new_player *pl);
static int	sub_events(t_new_sub_ev *se, t_new_player *pl);
int			events(t_new_sub_ev *se, t_new_player *pl);
void		ft_game_events(t_new_temp *data);

void		ft_game_init(t_wolf3d *w, char *path);

///parse map for game
void			ft_my_parse_map(t_new_player *pl, char *ag);
void			ft_alloc_save_sectors(char *ag, t_new_player *pl);
t_new_xy		*ft_vertex_save(t_new_player *pl, t_new_xy *vertex);
void			ft_sector_save(t_new_player *pl, t_new_xy *vertex);
void			ft_sector_count(t_new_player *pl);
void				ft_vertex_count(t_new_player *pl);
t_new_xy		*ft_malloc_sec_vertex(t_new_player *pl, char *v);
void			ft_fill_the_sector(t_new_sector *sector, int number, \
					t_file_read file, t_new_xy *vertex);
void			ft_player_save(t_new_player *pl);
void			player_init(t_new_player *pl, t_new_xy *v, int *angle, int *n);
void			ft_level_save(t_new_player *pl);

// texture.h
void		draw_cur_pistol_sprite(t_gun *wpn, int width, int height, int cur_sprite, SDL_Surface *surface);
void		load_pistol(t_gun *wpn);
int			load_pistol_sprite(t_gun *wpn, int sprite_count);
SDL_Surface		*load_pistol_part(int sprite);
void			draw_pistol(t_gun *wpn, t_new_player *pl);

void draw_walls(int x, t_new_player *pl, int wall, int n);
t_scaler	scalar_create(int a, int b, int c, int d, int f);
int			scr_nxt(t_scaler *i);
int			color_transoform(int color, float percent);
int			ft_get_pixel(SDL_Surface *sur, int x, int y);
void		pix1(t_new_player *pl);
void        load_imgs(SDL_Surface *img[10]);//load images
void vline_graffiti(int x, t_new_player *pl, t_scaler ty, int n);
void    draw_ceil_floor(int x, t_new_player *pl);

// sky
int			load_sky(t_new_player * pl);
void		pix_sky(t_textures *t, t_new_player *pl);

// new file
int				hexcolor( int r, int g, int b);

#endif
