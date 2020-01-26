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



//static unsigned NumSectors = 0;

typedef struct	s_new_wolf3d
{	
	SDL_Surface	*weapon_texture;
	t_new_anime		anim;
	int			*tex_col;
	int			color;
}				t_new_wolf3d;

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
int			engine_cross(t_new_player *pl, int sec_n, unsigned s);
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
void		player_init(t_new_player *pl, t_new_xy *v, float *angle, int *n);
void		line(int x, int y1,int y2, int top,int middle,int bottom, t_new_player *pl);

/*			math_functions.c			*/
float		min(float a, float b);
float		max(float a, float b);
float		clamp(float a, float mi, float ma);
float		vxs(float x0, float y0, float x1, float y1);
int			Overlap(float a0, float a1, float b0, float b1);
int			IntersectBox(float x0, float y0, float x1, float y1,float x2, float y2, float x3, float y3);
float		PointSide(float px, float py, float x0, float y0,float x1, float y1);
t_new_xy		Intersect(float x1, float y1, float x2, float y2,float x3, float y3, float x4, float y4);
void		UnloadData();
void		MovePlayer(float dx, float dy, t_new_player *player);
float		Yaw(float y, float z, t_new_player *player);
double		to_deg(double radians);

/*			motion.c			*/
void		motion_chk(t_new_sect_ops *op, t_new_player *player, t_new_others *ot, t_new_sub_ev *se);
void		motion_move_pl(float dx, float dy, t_new_player *pl);

/*			sdl_addons.c			*/
SDL_Rect	*ft_create_rect(int w, int h, int x, int y);
void		ft_sdl_error();



/*			texture_parser.c			*/
t_new_texture	texture_parse(const char *fp, unsigned edit);




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



#endif
