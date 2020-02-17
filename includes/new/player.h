/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dorange- <dorange-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/16 15:09:12 by tjuana            #+#    #+#             */
/*   Updated: 2020/02/17 16:29:18 by dorange-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PLAYER_H
#define PLAYER_H
# include "wolf3d.h"

typedef struct	s_file_read
{
	int			fd;
	int			res;
	char		*line;
	int			tmp[SECTORS];
	char		**split;
	char		*ptr_my;
	int			i;
	int			count_sectors;
	int			count_sectors2;
	int			count_sector_vertex;
	int			vertex_count;
}				t_file_read;

typedef struct	s_new_player
{
	SDL_Surface *img[10];
	SDL_Window	*win;
	SDL_Renderer	*rend;

	// SDL_Texture	*texture;
	t_new_texture	*textures;
	int			textures_nb;

	t_new_xy		t1;
	t_new_xy		t2;
	t_new_xy		scale_1;
	t_new_xy		scale_2;
    t_new_xyz		pos;      // Current position
    t_new_xyz		velo;   // Current motion vector
	t_new_xyz		hole;
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

	t_new_xy	near_point;
	t_new_xy 	far_point;
	float		nearz;
	float		farz;
	float		nearside;
	float		farside;

	float		x1;
	float		x2;
	int			*y_top;
	int			*y_bot;
	int			beginx;
	int			endx;
	int			contin;
	void		*pixels;

	char		*lvl;
	t_file_read	file;	//open map

	int         count_sprite;//for start animation
	float       light;

	int         **sky_pix;
	t_textures	t;
	t_new_texture   *tex;
	int         f;
	int         y1;
	int         y2;
	int         n;
	int         s;
	t_new_xy 		org1;
	t_new_xy 		org2;
	float         u0;// "
	float         u1;
	int			txtx;
	int			*pix;
	int 		y;
	t_scaler    ty;
	int 		fly;


	// camera vertex
	t_vector3	fov_vec1;
	t_vector3	fov_vec2;
}				t_new_player;

#endif
