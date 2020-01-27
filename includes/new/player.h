#ifndef PLAYER_H
#define PLAYER_H
# include "wolf3d.h"

typedef struct	s_file_read
{
	int			fd;
	int			res;
	char		*line;
	int			tmp[40];
	char		**split;
	char		*ptr_my;
	int			i;
	int			count_sectors;
	int			count_sector_vertex;
	int			vertex_count;
}				t_file_read;

typedef struct	s_new_player
{
	// SDL_Surface	*srf;
	SDL_Surface *img[10];
	t_new_xy		t1;	// смещение
	t_new_xy		t2; // смещение
	t_new_xy		scale_1;
	t_new_xy		scale_2;
    t_new_xyz		where;      // Current position
    t_new_xyz		velocity;   // Current motion vector
    float		angle;
    float		anglesin;
    float		anglecos;
    float		yaw;   // Looking towards (and sin() and cos() thereof)
    unsigned	sector;// Which sector the player is currently in
	int			sectors_nb;//Sectors number
    t_new_sector	*sectors;
	t_new_cycle		cycle;//one draw_screen cycle
	t_new_sector	*sect;//current sector
	int			door_all;//how much doors
	int			door_nb;//door near with player
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
	int			interx;			// intermediate x coordinate
	int         count_sprite;	//for start animation
    int         txtx;			//need for walls
	int         u0;				// 0
	int         u1;				// Сейчас -- то, на сколько частей де-факто делится стена
								// Коэффициент, где u0 + u1 = 1023
	float       org1x;			// Хранение предыдущих координат
	float       org1y;			// -//-
	float       org2x;			// -//-
	float       org2y;			// -//-
	float       light;
	int       y1;
	int       y2;
	int			origin_y1_coord;
	int		intery;	// intermediate y coordinate

	double		wall_height_c;	// wall height coeff.
	int			wall_height;	// for coordinates
	double		cl;				// Дистанция до стены?
	void		*pixels;
	t_file_read	file;	//open map
}				t_new_player;

#endif
