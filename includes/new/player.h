#ifndef PLAYER_H
#define PLAYER_H
# include "wolf3d.h"



typedef struct	s_new_player
{
	SDL_Surface	*srf;
	SDL_Window	*win;
	SDL_Renderer	*rend;

	SDL_Texture	*texture;
	t_new_texture	*textures;
	int			textures_nb;

	char		*lvl;
	t_new_xy		t1;
	t_new_xy		t2;
	t_new_xy		scale_1;
	t_new_xy		scale_2;
    t_new_xyz		where;      // Current position
    t_new_xyz		velocity;   // Current motion vector
    float		angle;
    float		anglesin;//player view sin
    float		anglecos;//player view cos
    float		yaw;   // Looking towards (and sin() and cos() thereof)
    unsigned	sector;// Which sector the player is currently in
	int			sectors_nb;//Sectors number
    t_new_sector	*sectors;//store all sectors
	t_new_cycle		cycle;//one draw_screen cycle
	t_new_sector	*sect;//current sector
	int			door_all;//how much doors
	int			door_nb;//door near with player
	t_new_door		*doors;//array of doors
	int			but_all;//how much buttons
	int			but_nb;//buttons near with player
	t_new_but		*buttons;//array of buttons
	int			neib;
	t_new_ceil		ceil;
	t_new_floor		floor;
	float		nearz;
	float		farz;
	float		nearside;
	float		farside;
	float		x1;
	float		x2;
	int			y_top[WIN_W];
	int			y_bot[WIN_W];
	int			beginx;
	int			endx;
	int			contin;
	void		*pixels;
}				t_new_player;

#endif
