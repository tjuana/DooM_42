#ifndef WOLF3D_NEW_H
# define WOLF3D_NEW_H

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
# include "engine.h"
# include "events.h"
//# include "door.h"
# include "help.h"
# include "player.h"
# include "textures.h"



//static unsigned NumSectors = 0;

typedef struct	s_w
{	
	SDL_Surface	*weapon_texture;
	int			color;
}				t_new_wolf3d;


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
double		to_degrees(double radians);

/*			main.c			*/
void		vline(int x, int y1,int y2, int top,int middle,int bottom, SDL_Surface* surface);

/*			engine.c			*/
void		engine_begin(t_new_player *pl);
int			engine_scale(t_new_player *pl, int sx1, int sx2);

/*			engine_exp.c			*/
int			engine_cross(t_new_player *pl, int sec_n, unsigned s);
void		engine_put_lines(t_new_player *pl, int neib);

/*			functions_main.c			*/
int			sub_events(t_subevents *se, t_new_player *player);
int			events(t_subevents *se, t_new_player *player);
void		mouse_movement(t_new_mouse *ms, t_new_player *player);
void		vectors_vel_dir(t_new_player *player, t_subevents *se, t_new_others *ot);
void		sectors_ops(t_new_sector_ops *op, t_new_player *player, t_new_others *ot, t_subevents *se);
void		jumps(t_subevents *se, t_new_player *player, t_new_sector_ops *op, t_new_others *ot);

/*			door.c			*/
void		door_button(t_new_player *pl, t_subevents *se);
void		door(t_new_player *pl, t_subevents *se);

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

/*			sdl_addons.c			*/
SDL_Rect	*ft_create_rect(int w, int h, int x, int y);

#endif
