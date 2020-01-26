#ifndef WOLF3D_H
# define WOLF3D_H


// for save file
# define VER_HEIGHT (int)33
# define VER_WIDTH (int)54
# define FONT_PATH "fonts/RobotoMono-Medium.ttf"


# include "SDL2/SDL.h"
# include "SDL2/SDL_thread.h"
# include "SDL2/SDL_ttf.h"

# include "vetors.h"
# include <pthread.h>
# include <string.h>
# include <stdio.h>
# include <stdlib.h>
# include <fcntl.h>
# include <math.h>
# include <string.h>
# include <libft.h>
// matrix library
//# include "matrix/constants.h"
// # include "matrix/door.h"
// # include "matrix/player.h"
// # include "matrix/sprites.h"
//# include "matrix/sdl.h"
//# include "matrix/fdf.h"
# include "const.h"

# include "algebra.h" // math library for matrix transform
# include "file.h"
# include "gui_struct.h"
# include "func_struct.h"
# include "editor_struct.h"
# include "new/wolf3d.h"

typedef struct			s_font
{
	SDL_Surface			*surf[7];

	TTF_Font			*ptr_font_18_m;
	TTF_Font			*ptr_font_14_m;

	TTF_Font			*ptr;
	SDL_Color			color;
	int					f_sz;
	int					g_sz;
	int					w;
	int					h;
	int					half_menu;
}						t_font;

// DEPRECATED
typedef struct			s_rect		// (?)
{
	t_vector3			size;
	t_vector3			cd;
}						t_rect;


typedef struct			s_anime
{
	int					start_am;
	int					frame;
	t_rect				pframe;
	t_vector3			place;
	int					frames;
}						t_anime;

typedef struct			s_write			// Для чтения карты
{
	t_list				*lst;
	char				**s;
	int					x;
	int					y;
	int					s_count;
}						t_write;

typedef struct			s_sdl
{
	int					running;
	SDL_Window			*win;
	SDL_Renderer		*renderer;
	Uint32				*pixels;
	SDL_Texture			*text;
	SDL_Surface			**textures;
	SDL_AudioSpec		*wav_spect;
	Uint32				*wav_len;
	Uint8				**wav_buff;
	SDL_AudioDeviceID	*audio_device;
	t_font				font;
	unsigned char		i;
}						t_sdl;

typedef struct			s_const			// structure for constants
{
	double				camera_x_cnst;	// useful constant for camera offset
}						t_const;

typedef struct			s_time
{
	Uint32				time;
	Uint32				old_time;
	Uint32				frame_time;
	Uint32				sound_old_time;
	Uint32				sound_time;
	Uint32				change_of_time;
	Uint32				play_time;
	Uint32				sound_sum_time;
	unsigned char		flag;
}						t_time;

typedef struct			s_wolf3d
{
	// game objects
	t_list				*sector;
	t_player			pl;
	t_list				*sprite;
	t_list				*enemy;

	// game status (temp.)
	int					sector_status; // 0: nothing; 1: set new sector
	int					player_status; // 0: nothing; 1: player was set;
	int					sprite_status; // 0: nothing; 1: sprite was set;
	int					enemy_status; // 0: nothing; 1: enemy was set;
	int					door_status;	// door as sector

	// game objects count
	int					sector_count;
	int					sprite_count;
	int					enemy_count;

	// ?!
	t_list				*txtr;
	int					txtr_count;





	t_file				file;
	t_list				*vertex;
	// add list with sector
	// add temp list for map
	t_list				*map_sector; // (deprecated)
	// add temp list for map (top vertex)
	t_list				*map_sector_top; // (deprecated)
	// spec param
	double				fov;
	double				l_p;

	t_list				*sprites;

	t_sdl				*sdl; //structe for handle sdl  stuff
	// t_map				map;
	t_time				t;
	t_const				c;
	SDL_Surface			*weapon_texture;
	SDL_Surface			*map_texture;
	t_anime				anim;
	t_anime				view_map;
	int					temp;
	int					fd;
	int					x;
	int					y;
	int					hit;
	double				*z_buffer;
	double				ms;
	double				rs;
	unsigned char		arr[10];
	Uint8				*tex_col;
	Uint32				color;
	int					type;

	t_vector3			mouse_vertex;
	t_vector3			mouse_pos;



	int					status; // game status: 0: error; 1: map editor; 2: game

	t_gui_map			gui_map;
	t_gui				gui;

	// void				(*redraw)(void *data);
	// void				(*font_redraw)(void *data);

	void				*new_data;
}						t_wolf3d;

// typedef struct			s_thread_help
// {
// 	// add list with sector
// 	t_list				*sector;
// 	// spec param
// 	double				l;
// 	double				fov;
// 	double				l_p;
// 	t_vector3			fc_dir;
// 	t_vector3			ln_dir;
// 	double				ln_l;

// 	t_player			pl;
// 	// t_map				map;
// 	t_sdl				*sdl;
// 	void				*tex_col;
// 	double				*z_buffer;
// 	double				wall_hit;
// 	double				camera_x_cnst;
// 	Uint32				color;
// 	int					y;
// 	int					hit;
// 	int					line_height;
// 	int					draw_start;
// 	int					draw_end;
// 	int					texture_num;
// 	int					wall_color; // temp
// 	int					text_x;
// 	int					text_y;
// 	int					temp;
// 	int					half_height;


// 	// new for map
// 	t_vector3			mouse_pos;
// 	int					sector_status; // 0: nothing; 1: set new sector
// 	int					sector_count;
// 	int					status; // game status: 0: error; 1: map editor; 2: game

// }						t_threads_help;

// typedef struct			s_threads
// {
// 	t_threads_help		w;
// 	int					t1;
// 	int					t2;
// }						t_threads;



# include "func_func.h"
# include "gui_func.h"
# include "editor_func.h"



void					ft_clean_sdl(t_wolf3d *w);
int						ft_cleanmem(t_list **lst);
void					*ft_my_malloc(size_t s);
int						ft_error(char *code);
SDL_Surface				*ft_sdl_load_bmp(char *str);

t_sdl					*sdl_init(t_sdl *sdl);
void					ft_init_wolf(t_wolf3d *w);
void					ft_we_need_more_init(t_wolf3d *w);
// void					ft_init_multi_wolf(t_threads_help *w, t_wolf3d *head);
// int						ft_init_anim(t_wolf3d *wolf);

// ??!
void					ft_init_sound(t_wolf3d *w);
void					ft_load_sound(t_wolf3d *w);
void					ft_play_shot(t_wolf3d *w);
void					ft_play_music(t_wolf3d *w);

void					ft_read_file_nmp(int fd, t_wolf3d *w);
void					ft_draw_map_new_line(t_wolf3d *w);

// void					ft_debug_matrix(t_matrix_4x4 matrix);

int						ft_check_point_in_line_segment(t_vector3 p, t_vector3 p1, t_vector3 p2);
int						ft_check_div(double x1, double y1, double x2, double y2,double x3, double y3, double x4, double y4);
t_vector3				ft_find_intersect(double x1, double y1, double x2, double y2,double x3, double y3, double x4, double y4);
int						ft_get_player_sector(t_wolf3d *w);

int						ft_check_point(t_vector3 p, t_vector3 p1, t_vector3 p2, t_vector3 p1_pl, t_vector3 p2_pl);

// void					ft_sector_list_cast(t_threads *a);

void					ft_print_sectors(t_list *ptr_list);

/*
** **************************************************************************
**	Old parser functions [DELETE?]
** **************************************************************************
*/
int				ft_parser_get_vertexes_count(char *str);
t_vector3		ft_parser_nnmp_get_vertex(char **ptr, char *ptr_finish);
t_vector3		*ft_parser_nnmp_vertex(char **ptr);

void			ft_parser_nnmp_player(t_wolf3d *w, char **line);
void			ft_parser_nnmp_sprite(t_wolf3d *w, char **line);
void			ft_parser_nnmp_enemy(t_wolf3d *w, char **line);
void			ft_parser_nnmp(int fd, t_wolf3d *w);

void			ft_parser_nnmp_sector_neighborhood(t_wolf3d *w, char **line, \
					t_sector *sector);
void			ft_parser_nnmp_sector_vertexes(t_wolf3d *w, char **line, \
					t_sector *sector);
void			ft_parser_nnmp_sector_param(t_wolf3d *w, char **line, \
					t_sector *sector);
void			ft_parser_nnmp_sector(t_wolf3d *w, char **line);

char			*ft_parser_search_param(char *line, char *needly);
int				ft_parser_get_param(char *line, char *needly);


int				ft_editor_sector_compare_vertexes(t_vector3 v1, t_vector3 v2);
// void			ft_editor_threading(t_wolf3d *w);
SDL_Rect		*ft_create_rect(int w, int h, int x, int y);
int				ft_font_preset_sc(t_wolf3d *w, int size, int color);
void			ft_font_putstr_sdl(t_wolf3d *w, char *str, t_gui_coord c);

///just do it
void			ft_save_the_file(t_wolf3d *w);
void			ft_print_sectors_to_file(t_wolf3d *w, t_list *ptr_list);
void			ft_save_neighbour(t_sector *sector, int fd);

void			ft_create_list_of_vertexes(t_wolf3d *w);
void			ft_count_origin_vertexes(t_wolf3d *w);
void			ft_sector_num_vertex(t_list *ptr_list, t_vector3 *vertexes);
void			ft_print_to_file(t_wolf3d *w, int f);
void			ft_allocate_int2darr(t_wolf3d *w);


// MATH
int				ft_compare_vertexes(t_vector3 v1, t_vector3 v2);
double			ft_vxs_vector(t_vector3 v1, t_vector3 v2);
double			ft_vxs_double(double x1, double y1, double x2, double y2);
int				ft_check_div_vector(t_vector3 v1, t_vector3 v2, t_vector3 v3, t_vector3 v4);
t_vector3		ft_find_line_intersect(t_vector3 v1, t_vector3 v2, \
					t_vector3 v3, t_vector3 v4);
int				ft_check_line_segment_intersect_vector(t_vector3 v1, t_vector3 v2, \
					t_vector3 v3, t_vector3 v4);
int				ft_check_general_segment_line(t_vector3 v1, t_vector3 v2, \
					t_vector3 v3, t_vector3 v4);
int				ft_check_point_in_line_segment_diameter(t_vector3 p, t_vector3 p1, t_vector3 p2, double diameter);


double			ft_math_vxs(double x0, double y0, double x1, double y1);

// void			ft_game_render(t_wolf3d *w);
// void			ft_game_render_font(t_wolf3d *w);

#endif
