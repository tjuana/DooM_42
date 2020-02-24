/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dorange- <dorange-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/16 15:09:12 by tjuana            #+#    #+#             */
/*   Updated: 2020/02/24 19:01:23 by dorange-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PLAYER_H
# define PLAYER_H
# include "wolf3d.h"

/*
** **************************************************************************
**	Player status constant
** **************************************************************************
*/
# define PL_STATUS_LIVE			0x01
# define PL_STATUS_DEAD			0x02
# define PL_STATUS_EXIT_GAME	0x03

/*
** **************************************************************************
**	t_file_read
**
**	Structure for file read.
**
**	Arguments:
**	int fd					|
**	int res					|
**	char *line				|
**	char *ag				|
**	int tmp[SECTORS]		|
**	char **split			|
**	char *ptr_my			|
**	int i					|
**	int count_sectors		|
**	int count_sectors2		|
**	int count_sector_vertex	|
**	int vertex_count		|
** **************************************************************************
*/
typedef struct		s_file_read
{
	int				fd;
	int				res;
	char			*line;
	char			*ag;
	int				tmp[SECTORS];
	char			**split;
	char			*ptr_my;
	int				i;
	int				count_sectors;
	int				count_sectors2;
	int				count_sector_vertex;
	int				vertex_count;
}					t_file_read;

/*
** **************************************************************************
**	t_new_player
**
**	Structure for player.
**
**	Arguments:
**	SDL_Surface *img[10]	|
**	t_new_texture *textures	|
**	int textures_nb			|
**	t_vector3 t1			|
**	t_vector3 t2			|
**	t_vector3 scale_1		|
**	t_vector3 scale_2		|
**	t_vector3 pos			| Current position
**	t_vector3 velo			| Current motion vector
**	t_vector3 hole			|
**	float angle				|
**	float anglesin			| player view sin
**	float anglecos			| player view cos
**	float yaw				| Looking towards (and sin() and cos() thereof)
**	unsigned sector			| Which sector the player is currently in
**	int sectors_nb			| Sectors number
**	t_new_sector *sectors	| store all sectors
**	t_new_cycle cycle		| one draw_screen cycle
**	t_new_sector *sect		| current sector
**	int door_all			| how much doors
**	int door_nb				| door near with player
**	t_new_door *doors		| array of doors
**	int but_all				| how much buttons
**	int but_nb				| buttons near with player
**	t_new_but *buttons		| array of buttons
**	int neib				|
**	t_new_ceil ceil			|
**	t_new_floor floor		|
**	t_vector3 near_point	|
**	t_vector3  far_point	|
**	float x1				|
**	float x2				|
**	int *y_top				|
**	int *y_bot				|
**	int beginx				|
**	int endx				|
**	int contin				|
**	Uint32 *pixels			|
**	char *lvl				|
**	t_file_read file		| open map
**	int count_sprite		| for start animation
**	float light				|
**	int **sky_pix			|
**	t_textures t			|
**	t_new_texture *tex		|
**	int f					|
**	int y1					|
**	int y2					|
**	int n					|
**	int s					|
**	t_vector3 org1			|
**	t_vector3 org2			|
**	float u0				|
**	float u1				|
**	int txtx				|
**	Uint32 *pix				|
**	int y					|
**	t_scaler ty				|
**	int fly					|
**	void *wolf3d			| pointer to wolf3d!
**	int live_count			|
**	int bullet_count		|
**	Mix_Chunk *sound		|
**	int status				| Player status
**	int died_timer			| Died timer
**	double const_hfov		|
**	double const_vfov		|
**	double const_hfov_spec	|
**	double const_vfov_spec	|
** **************************************************************************
*/
typedef struct		s_new_player
{
	SDL_Surface		*img[10];
	t_new_texture	*textures;
	int				textures_nb;
	t_vector3		t1;
	t_vector3		t2;
	t_vector3		scale_1;
	t_vector3		scale_2;
	t_vector3		pos;
	t_vector3		velo;
	t_vector3		hole;
	float			angle;
	float			anglesin;
	float			anglecos;
	float			yaw;
	unsigned		sector;
	int				sectors_nb;
	t_new_sector	*sectors;
	t_new_cycle		cycle;
	t_new_sector	*sect;
	int				door_all;
	int				door_nb;
	t_new_door		*doors;
	int				but_all;
	int				but_nb;
	t_new_but		*buttons;
	int				neib;
	t_new_ceil		ceil;
	t_new_floor		floor;
	t_vector3		near_point;
	t_vector3		far_point;
	float			x1;
	float			x2;
	int				*y_top;
	int				*y_bot;
	int				beginx;
	int				endx;
	int				contin;
	Uint32			*pixels;
	char			*lvl;
	t_file_read		file;
	int				count_sprite;
	float			light;
	int				**sky_pix;
	t_textures		t;
	t_new_texture	*tex;
	int				f;
	int				y1;
	int				y2;
	int				n;
	int				s;
	t_vector3		org1;
	t_vector3		org2;
	float			u0;
	float			u1;
	int				txtx;
	Uint32			*pix;
	int				y;
	t_scaler		ty;
	int				fly;
	void			*wolf3d;
	int				live_count;
	int				bullet_count;
	int				armors_count;
	Mix_Chunk		*sound_pistol;
	Mix_Chunk		*sound_door;
	Mix_Chunk		*sound_death;
	Mix_Chunk		*sound_fly;
	int				status;
	int				died_timer;
	char			*map_path;
	t_vector3		fov_vec1;
	t_vector3		fov_vec2;
	int				lunar;
	double			const_hfov;
	double			const_vfov;
	double			const_hfov_spec;
	double			const_vfov_spec;
	int				ch;
	int				bullet_status;
	int				bullet_frame;
	int				flag_move_neighbors;
	int				m_over;
}					t_new_player;

#endif
