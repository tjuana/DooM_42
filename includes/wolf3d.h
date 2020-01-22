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
# include "constants.h"
# include "help.h"
# include "animations.h"
# include "engine.h"
# include "events.h"
# include "door.h"
# include "player.h"


//static unsigned NumSectors = 0;

typedef struct	s_w
{	
	SDL_Surface	*weapon_texture;
	t_anime		anim;
	int			*tex_col;
	int			color;
}				t_wolf3d;


/*			math_functions.c			*/
float		min(float a, float b);
float		max(float a, float b);
float		clamp(float a, float mi, float ma);
float		vxs(float x0, float y0, float x1, float y1);
int			Overlap(float a0, float a1, float b0, float b1);
int			IntersectBox(float x0, float y0, float x1, float y1,float x2, float y2, float x3, float y3);
float		PointSide(float px, float py, float x0, float y0,float x1, float y1);
t_xy		Intersect(float x1, float y1, float x2, float y2,float x3, float y3, float x4, float y4);
void		UnloadData();
void		MovePlayer(float dx, float dy, t_player *player);
float		Yaw(float y, float z, t_player *player);
double		to_degrees(double radians);

/*			main.c			*/
void		vline(int x, int y1,int y2, int top,int middle,int bottom, SDL_Surface* surface);

/*			engine.c			*/
void		engine_begin(t_player *pl);
int			engine_scale(t_player *pl, int sx1, int sx2);

/*			engine_exp.c			*/
int			engine_cross(t_player *pl, int sec_n, unsigned s);
void		engine_put_lines(t_player *pl, int neib);

/*			functions_main.c			*/
int			sub_events(t_subevents *se, t_player *player);
int			events(t_subevents *se, t_player *player);
void		mouse_movement(t_mouse *ms, t_player *player);
void		vectors_vel_dir(t_player *player, t_subevents *se, t_others *ot);
void		sectors_ops(t_sector_ops *op, t_player *player, t_others *ot, t_subevents *se);
void		jumps(t_subevents *se, t_player *player, t_sector_ops *op, t_others *ot);

/*			animations.c			*/
int			ft_init_anim(t_wolf3d *wolf);
void		ft_draw_animation(t_wolf3d *w);
void		ft_animation_play(t_wolf3d *w);

/*			door.c			*/
void		door_but_сlick(t_player *pl, t_subevents *se);//when you press button
void		door(t_player *pl, t_subevents *se);//cycle for open door

/*			door_detect.c			*/
int			door_detect(t_player *pl);//return sec_nb of door

/*			but.c			*/
void		but_total(t_player *pl);//create buttons array

/*			but_detect.c			*/
int			but_detect(t_player *pl);//return sec_nb of button

/*			vector_1.c			*/
t_vector3	ft_vec3_create(t_vector3 *orig, t_vector3 *dest);
double		ft_vec3_magnitude(t_vector3 this);
t_vector3	ft_vec3_add(t_vector3 this, t_vector3 rhs);
t_vector3	ft_vec3_sub(t_vector3 this, t_vector3 rhs);
t_vector3	ft_vec3_cross_product(t_vector3 this, t_vector3 rhs);

/*			vector_2.c			*/
double		ft_vec3_dot_product(t_vector3 this, t_vector3 rhs);
double		ft_vec3_cosinus(t_vector3 this, t_vector3 rhs);
t_vector3	ft_vec3_opposite(t_vector3 this);
t_vector3	ft_vec3_scalar_product(t_vector3 this, double k);
t_vector3	ft_vec3_normalize(t_vector3 vtc);

/*			sdl_addons.c			*/
SDL_Rect	*ft_create_rect(int w, int h, int x, int y);

#endif
