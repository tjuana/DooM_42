#ifndef PLAYER_H
#define PLAYER_H
# include "wolf3d.h"

typedef struct	s_player
{
	SDL_Surface	*srf;
	t_xy		t1;
	t_xy		t2;
	t_xy		scale_1;
	t_xy		scale_2;
    t_xyz		where;      // Current position
    t_xyz		velocity;   // Current motion vector
    float		angle;
    float		anglesin;//player view sin
    float		anglecos;//player view cos
    float		yaw;   // Looking towards (and sin() and cos() thereof)
    unsigned	sector;// Which sector the player is currently in
	int			sectors_nb;//Sectors number
    t_sector	*sectors;//store all sectors
	t_cycle		cycle;//one draw_screen cycle
	t_sector	*sect;//current sector
	int			door_all;//how much doors
	int			door_nb;//door near with player
	t_door		*doors;//array of doors
	int			but_all;//how much buttons
	int			but_nb;//buttons near with player
	t_but		*buttons;//array of buttons
	int			neib;
	t_ceil		ceil;
	t_floor		floor;
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
}				t_player;

#endif
