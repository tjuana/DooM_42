/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wolf3d.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjuana <tjuana@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/16 16:34:44 by tjuana            #+#    #+#             */
/*   Updated: 2020/02/23 19:54:24 by tjuana           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WOLF3D_H
# define WOLF3D_H

# include "SDL2/SDL.h"
# include "SDL2/SDL_thread.h"
# include "SDL2/SDL_ttf.h"
# include "SDL2/SDL_image.h"
# include "SDL2/SDL_mixer.h"

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
# include "engine.h"
# include "events.h"
# include "door.h"
# include "texture.h"
# include "player.h"

typedef	struct		s_new_temp
{
	t_new_sub_ev	se;
	t_new_mouse		ms;
	t_new_player	*pl;
	t_new_others	ot;
}					t_new_temp;

/*
** **************************************************************************
**	src/game/game_bullet.c
** **************************************************************************
*/
void				ft_game_draw_bullet(t_gun *wpn, t_new_player *pl);

/*
** **************************************************************************
**	src/game/game_but.c
** **************************************************************************
*/
int					ft_game_but_script(t_new_player *pl, int sec_nb, \
						t_new_sub_ev *se);
void				ft_game_but_total(t_new_player *pl);

/*
** **************************************************************************
**	src/game/game_but_detect.c
** **************************************************************************
*/
int					ft_game_but_detect(t_new_player *pl);

/*
** **************************************************************************
**	src/game/game_door.c
** **************************************************************************
*/
void				ft_game_door_total(t_new_player *pl);
void				ft_game_door_but_сlick(t_new_player *pl, \
						t_new_sub_ev *se);
void				door(t_new_player *pl, t_new_sub_ev *se);

/*
** **************************************************************************
**	src/game/game_door_detect.c
** **************************************************************************
*/
int					ft_game_door_detect(t_new_player *pl);

/*
** **************************************************************************
**	src/game/game_engine_1.c
** **************************************************************************
*/
int					ft_game_engine_scale(t_new_player *pl, int sx1, int sx2);
void				ft_game_engine_begin(t_new_player *pl);

/*
** **************************************************************************
**	src/game/game_engine_2.c
** **************************************************************************
*/
void				ft_game_engine_calcs(int x, t_new_player *pl, \
						int operation);
void				ft_game_draw_ceil_floor(int x, t_new_player *pl);
void				ft_game_engine_put_lines(t_new_player *pl, int neib);

/*
** **************************************************************************
**	src/game/game_engine_cross.c
** **************************************************************************
*/
void				ft_game_xy_vertex_of_sectors(t_vector3 *v_start, \
						t_vector3 *v_end, t_new_player *pl);
int					ft_game_engine_cross(t_new_player *pl);

/*
** **************************************************************************
**	src/game/game_events_1.c
** **************************************************************************
*/
void				ft_game_sub_events_moving(t_new_sub_ev *se, \
						t_new_player *pl);
void				ft_game_sub_events_player(t_new_sub_ev *se, \
						t_new_player *pl);
void				ft_game_mouse_events(t_new_sub_ev *se, \
						t_new_player *pl);
int					events(t_new_sub_ev *se, t_new_player *pl);
void				ft_game_events(t_new_temp *data);

/*
** **************************************************************************
**	src/game/game_events_2.c
** **************************************************************************
*/
void				ft_game_events_vel(t_new_player *pl, \
						t_new_sub_ev *se, t_new_others *ot);
void				ft_game_events_jumps(t_new_sub_ev *se, \
						t_new_player *pl, t_new_others *ot);
void				ft_game_events_new_mouse_move(t_new_mouse *ms, \
						t_new_player *pl);

/*
** **************************************************************************
**	src/game/game_events_3.c
** **************************************************************************
*/
int					ft_game_events_exit(t_new_player *pl);
void				ft_game_hidden_message(t_list *dom);
void				ft_game_set_dead(t_new_player *pl, t_list *dom);
int					ft_game_sub_events(t_new_sub_ev *se, t_new_player *pl);
void				ft_game_mouse_events_click(t_new_player *pl);

/*
** **************************************************************************
**	src/game/game_gun.c
** **************************************************************************
*/
void				ft_game_draw_pistol(t_gun *wpn, t_new_player *pl);

/*
** **************************************************************************
**	src/game/game_load_file.c
** **************************************************************************
*/
void				ft_game_end_game(t_new_player *pl, char *map);
t_new_player		*ft_game_end_game2(t_new_player *pl, char *map);
t_new_player		*load_next(t_new_player *pl, char *map);

/*
** **************************************************************************
**	src/game/game_load_textures.c
** **************************************************************************
*/
t_new_texture		*ft_game_load_textures(t_new_player *pl);

/*
** **************************************************************************
**	src/game/game_main_1.c
** **************************************************************************
*/
void				ft_game_player_init_config(t_new_player *pl);
void				ft_game_player_init(t_new_player *pl, t_vector3 *v, int *n);
void				ft_game_redraw(t_wolf3d *w, t_list *dom);

/*
** **************************************************************************
**	src/game/game_main_2.c
** **************************************************************************
*/
void				ft_game_init(t_wolf3d *w, char *path);
void				ft_game_gui_init_menu(t_list *head);
void				ft_game_gui_init_hud(t_list *head);

/*
** **************************************************************************
**	src/game/game_map_parse_1.c
** **************************************************************************
*/
void				ft_game_my_parse_map(t_new_player *pl, char *ag);
void				ft_game_vertex_count(t_new_player *pl);
void				ft_game_sector_count(t_new_player *pl);
t_vector3			*ft_game_malloc_sec_vertex(t_new_player *pl, char *v);
void				ft_game_malloc_save_sectors(char *ag, t_new_player *pl);

/*
** **************************************************************************
**	src/game/game_map_parse_2.c
** **************************************************************************
*/
t_vector3			*ft_game_vertex_save(t_new_player *pl, t_vector3 *vertex);
void				ft_game_sector_save(t_new_player *pl, t_vector3 *vertex);
void				ft_game_fill_the_sector(t_new_sector *sector, int number, \
						t_file_read file, t_vector3 *vertex);
void				ft_game_player_save(t_new_player *pl);
void				ft_game_level_save(t_new_player *pl);

/*
** **************************************************************************
**	src/game/game_motion_1.c
** **************************************************************************
*/
void				ft_game_motion_move_pl(t_vector3 *delt, t_new_player *pl);
void				ft_game_motion_chk(t_new_player *pl, \
						t_new_others *ot, t_new_sub_ev *se);

/*
** **************************************************************************
**	src/game/game_motion_2.c
** **************************************************************************
*/
int					ft_game_motion_chk_sec(t_new_sector *sect, \
						t_vector3 *delt, int i, t_new_player *pl);

/*
** **************************************************************************
**	src/game/game_sdl_addons.c
** **************************************************************************
*/
void				ft_sdl_error(t_sdl *sdl);

/*
** **************************************************************************
**	src/game/game_texture_parser.c
** **************************************************************************
*/
t_new_texture		ft_game_texture_parse_2(size_t f_size, int fd, \
						unsigned char *head);
t_new_texture		ft_game_texture_parse(char *fp);

/*
** **************************************************************************
**	src/game/game_textures.c
** **************************************************************************
*/
void				ft_game_pix1(t_new_player *pl, int img);
void				ft_game_pix_sky(t_textures *t, t_new_player *pl);
void				ft_draw_walls_put_pixel_to_surface(int x, \
						t_new_player *pl, int img);
void				ft_game_draw_graffiti_put_pixel_to_surface(int x, \
						t_new_player *pl, int img);

/*
** **************************************************************************
**	src/game/game_walls.c
** **************************************************************************
*/
t_scaler			ft_game_scalar_create(int a, int b, int c, int f);
int					ft_game_scr_nxt(t_scaler *i);
void				ft_game_draw_walls(int x, t_new_player *pl, \
						int wall_type, int img);
void				ft_game_draw_graffiti(int x, t_new_player *pl, \
						int wall_type, int img);
/*
** **************************************************************************
**	src/game/game_load_sounds.c
** **************************************************************************
*/
void				ft_load_sounds(t_new_player *pl);
#endif
