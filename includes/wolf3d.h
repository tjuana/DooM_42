#ifndef WOLF3D_H
# define WOLF3D_H
// # define WIN_HEIGHT 1080
// # define WIN_WIDTH 1920
# define WIN_HEIGHT 720
# define WIN_WIDTH 1280
# define TEXTURES_NUMBER 23
# define THREADS 10
# define TEX_W 64
# define TEX_H 64
# define ONE_ANIM 20
# define FULL_ANIM ONE_ANIM * 4 - 4
# define T_CAM_HR_ANGLE 0.02 // transform angle for camera
# define T_CAM_Z_ANGLE 0.01 // transform angle for camera

# define DEG_30 0.52360

# define C_A 0xFF000000
# define C_R 0x00FF0000
# define C_G 0x0000FF00
# define C_B 0x000000FF

# define E_GRID_L 32 // GRID LENGTH (SCALE)
# define E_GRID_V_D 6 // VERTEX DIAMETER
# define E_GRID_V_D_D 4 // VERTEX DRAW DIAMETER

# define VER_HEIGHT (int)33
# define VER_WIDTH (int)54
# define FONT_PATH "fonts/RobotoMono-Medium.ttf"

/*
** **************************************************************************
**	Mode
** **************************************************************************
*/
# define GUI_MD_ME				0x0000F001
# define GUI_MD_ME_SET_SECTOR	0x0000F100
# define GUI_MD_ME_SET_PLAYER	0x0000F200
# define GUI_MD_ME_SET_SPRITE	0x0000F300
# define GUI_MD_ME_SET_ENEMY	0x0000F400
# define GUI_MD_ME_SET_DOOR		0x0000F500

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
# include "algebra.h" // math library for matrix transform
# include "file.h"
# include "gui_struct.h"
# include "func_struct.h"
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

#define SECTOR_STATUS_NOTHING		0x00
#define SECTOR_STATUS_BROKEN_LINE	0x00
#define SECTOR_STATUS_POLYGON		0x01
#define SECTOR_STATUS_READY			0x02 //.
#define SECTOR_STATUS_PRESET		0x03 //.
#define SECTOR_STATUS_SET			0x04 //.

#define SECTOR_TYPE_SECTOR			0x00
#define SECTOR_TYPE_DOOR			0x01

// new struct for sector
typedef struct			s_sector
{
	int					id;
	t_vector3			**vertex;		// Указатель на массив вершин
	int					vertex_count;	// Кол-во вершин в секторе
	int					*neighbors;		// Номера соседних секторов
	double				height;			// Высота стены
	double				floor;			// Высота ~ от z = 0
	int					txtr_floor;		// Номер текстуры сектора (?)
	int					txtr_walls;		// Номер текстуры сектора (?)
	int					txtr_ceil;		// Номер текстуры сектора (?)
	int					color;			// Цвет сектора (for map editor)
	int					type;			// type
	int					status;			// 0: broken line; 1: polygon

	t_vector3			vtx_center;		// Центр сектора (?)
}						t_sector;

typedef struct			s_sort_util	// Структура для спрайтов (?)
{
	int					i;
	int					j;
	int					count;
	char				swap;
}						t_sort_util;

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

typedef struct			s_player
{
	t_vector3			camera_vector;	// Основной вектор камеры
	t_vector3			pos;			// Позиция игрока
	double				cameraX;		// temp: Смещение луча от центра камеры (-1.0 ... 1.0)
	double				cameraH;		// Высота камеры (-1.0 ... 1.0)
	double				wall_dist;		// temp: Дистанция до стены с коррекцией fish eyes
	int					side;			// flag: сторона (например, подкрашивает стены)
}						t_player;

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

/*
	Old sprite struct
*/
typedef struct			s_sprite
{
	int					id;
	t_vector3			pos;
	double				x; // (deprecated)
	double				y; // (deprecated)
	double				distance;
	int					texture; // (as type?)
	int					status;	// 0: no set, 1: set (?)
}						t_sprite;

/*
	New sprite struct (example)
*/
typedef struct			s_sprite_new
{
	int					type;			// 0: static, 1: dynamic (enemy?)
	t_vector3			pos;			// xyz-w coord.
	double				distance;
	int					texture;
}						t_sprite_new;

typedef struct			s_map
{
	int					m_wid;
	int					m_hei;
	int					*map;
	int					x;
	int					y;
	int					s_count;
	t_sprite			**sprite;
	int					*s_ord;
	double				*s_dst;
}						t_map;

/*
	Some point about crs, src, mcrs and msrs constants.
	These constants are helpers for rotations. If we will use them,
	our calculations will be simpler. But we don't have
	matrix functions for constant parameters.
*/
typedef struct			s_const			// structure for constants
{
	double				crs;			// [now not use]
	double				srs;			// [now not use]
	double				mcrs;			// [now not use]
	double				msrs;			// [now not use]
	double				camera_x_cnst;	// useful constant for camera offset
	int					half_height;	// [not use]
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

/*
**	Special struct for map element parameters.
*/
typedef struct			s_gui_map
{
	t_list				*ptr;		// Указатель на gui-элемент
	t_vector3			r1;			// left top vertex ограничение (для координат карты)
	t_vector3			r2;			// right bottom vertex ограничение
	int					grid_scale;
	unsigned char		check_vertex;
	t_vector3			v;
}						t_gui_map;

// Test texture struct
typedef struct			s_txtr
{
	int					id;		// texture number
	int					color;	// basic color
	SDL_Surface			*surf;	// pointer to surface
}						t_txtr;

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
	t_map				map;
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

typedef struct			s_thread_help
{
	// add list with sector
	t_list				*sector;
	// spec param
	double				l;
	double				fov;
	double				l_p;
	t_vector3			fc_dir;
	t_vector3			ln_dir;
	double				ln_l;

	t_player			pl;
	t_map				map;
	t_sdl				*sdl;
	void				*tex_col;
	double				*z_buffer;
	double				wall_hit;
	double				camera_x_cnst;
	Uint32				color;
	int					y;
	int					hit;
	int					line_height;
	int					draw_start;
	int					draw_end;
	int					texture_num;
	int					wall_color; // temp
	int					text_x;
	int					text_y;
	int					temp;
	int					half_height;


	// new for map
	t_vector3			mouse_pos;
	int					sector_status; // 0: nothing; 1: set new sector
	int					sector_count;
	int					status; // game status: 0: error; 1: map editor; 2: game

}						t_threads_help;

typedef struct			s_threads
{
	t_threads_help		w;
	int					t1;
	int					t2;
}						t_threads;

// # include "gui.h"
// # include "func.h"

# include "func_func.h"
# include "gui_func.h"


void					ft_clean_sdl(t_wolf3d *w);
int						ft_cleanmem(t_list **lst);
void					*ft_my_malloc(size_t s);
int						ft_error(char *code);
SDL_Surface				*ft_sdl_load_bmp(char *str);

t_sdl					*sdl_init(t_sdl *sdl);
void					ft_init_wolf(t_wolf3d *w);
void					ft_we_need_more_init(t_wolf3d *w);
void					ft_init_multi_wolf(t_threads_help *w, t_wolf3d *head);
int						ft_init_anim(t_wolf3d *wolf);

void					ft_load_textures(t_wolf3d *w);
void					renderer(t_wolf3d *wolf);

void					ft_handle_events(t_wolf3d *w);
void					ft_use_events(t_wolf3d *w);
int						ft_step_back_check(t_wolf3d *w, unsigned char flag);
int						ft_step_forward_check(t_wolf3d *w, unsigned char flag);

void					threading(t_wolf3d *w);

void					*begin_game(void *w);
int						ft_step_back_check(t_wolf3d *w, unsigned char flag);
int						ft_step_forward_check(t_wolf3d *w, unsigned char flag);

// fps
void					fpsthink(void);
void					fpsinit(void);

void					ft_draw_animation(t_wolf3d *w);
void					ft_animation_play(t_wolf3d *w);

void					ft_init_sound(t_wolf3d *w);
void					ft_load_sound(t_wolf3d *w);
void					ft_play_shot(t_wolf3d *w);
void					ft_play_music(t_wolf3d *w);

int						ft_init_view_map(t_wolf3d *wolf);
void					ft_draw_map(t_wolf3d *w);

void					ft_sort(t_wolf3d *w);
void					write_sprites(t_map *m);

void					ft_fdf_init_wu(t_fdf_wu **wu, t_vector3 *dot_1, \
							t_vector3 *dot_2);
void					ft_fdf_swap_double(double *n1, double *n2);
void					ft_fdf_draw_line_swap(t_fdf_wu **wu);
void					ft_fdf_draw_line_param(t_wolf3d *data, t_fdf_wu **wu);
void					ft_fdf_wu(t_vector3 *dot_1, t_vector3 *dot_2, \
							t_wolf3d *data);

void					ft_fdf_wu_color(t_vector3 *dot_1, t_vector3 *dot_2, \
							t_wolf3d *data, int color);
void					ft_fdf_init_wu_color(t_fdf_wu **wu, t_vector3 *dot_1, \
							t_vector3 *dot_2, int color);

void					ft_fdf_wu_rect_color(t_wolf3d *data, t_gui_rect coord, \
							t_gui_rect area, int color);

void					ft_fdf_draw_line_first_pixels(t_wolf3d *data, \
							t_fdf_wu **wu);
void					ft_fdf_draw_line_last_pixels(t_wolf3d *data, \
							t_fdf_wu **wu);
void					ft_fdf_wu_cycle_x(t_wolf3d *data, t_fdf_wu *wu, \
							double x);
void					ft_fdf_wu_cycle_y(t_wolf3d *data, t_fdf_wu *wu, \
							double x);

int						ft_fdf_ipart(double x);
double					ft_fdf_round(double x);
double					ft_fdf_fpart(double x);
int						ft_fdf_get_color(int color1, int color2, double f1);

void					ft_draw_compass(t_wolf3d *w);
void					ft_draw_compass_static(t_wolf3d *w);

void					ft_read_file_nmp(int fd, t_wolf3d *w);
void					ft_draw_map_new_line(t_wolf3d *w);
void					ft_draw_map_new_sector(t_wolf3d *w);
void					ft_draw_map_new_sector_iso(t_wolf3d *w);

void					ft_debug_matrix(t_matrix_4x4 matrix);

int						ft_check_point_in_line_segment(t_vector3 p, t_vector3 p1, t_vector3 p2);
int						ft_check_div(double x1, double y1, double x2, double y2,double x3, double y3, double x4, double y4);
t_vector3				ft_find_intersect(double x1, double y1, double x2, double y2,double x3, double y3, double x4, double y4);
int						ft_get_player_sector(t_wolf3d *w);

int						ft_check_point(t_vector3 p, t_vector3 p1, t_vector3 p2, t_vector3 p1_pl, t_vector3 p2_pl);

void					ft_sector_list_cast(t_threads *a);
int						ft_check_point_fov(t_vector3 p, t_vector3 p1, t_vector3 p2, t_vector3 p1_pl, t_vector3 p2_pl);

void					ft_print_sectors(t_list *ptr_list);

/*
**	Parser functions
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

/*
**	Editor functions
*/

void			ft_editor_renderer(t_wolf3d *wolf);

// void			ft_editor_fill_frame(t_wolf3d *w);
int				ft_editor_check_line_for_map(t_vector3 p1, t_vector3 p2);
double			ft_editor_get_angle(double sin, double cos);
void			ft_editor_map_transform_vertexes(t_wolf3d *w, t_sector *ptr_sector, t_sector *ptr_sector_origin, double diff);
void			ft_editor_map_draw_walls(t_wolf3d *w, t_sector *ptr_sector);
void			ft_editor_map_draw_walls_height(t_wolf3d *w, t_sector *ptr_sector, t_sector *ptr_sector_top);
void			ft_editor_draw_map_2d(t_wolf3d *w, t_list *sector);

void			ft_editor_handle_events(t_wolf3d *w);
void			ft_editor_use_events(t_wolf3d *w);

void			ft_editor_mouse_move(t_wolf3d *w, SDL_Event e);

void			ft_editor_draw_point(t_wolf3d *data, t_vector3 v, int color);
void			ft_editor_draw_mouse_vertex(t_wolf3d *w);

int				ft_editor_check_mouse_vertex_pos(t_wolf3d *w, int x, int y);
void			ft_editor_mouse_click(t_wolf3d *w, SDL_Event e);

void			ft_editor_sector_draw_line_to_vertex(t_wolf3d *w);

t_vector3		ft_editor_map_get_xy_vertex_pos(t_wolf3d *w, t_vector3 v);

void			ft_editor_delete_last_vertex(t_wolf3d *w);

int				ft_editor_map_check_area(t_wolf3d *w);

int				ft_sector_check_sector(void *a, t_vector3 v);
int				ft_sector_check_cross(t_wolf3d *w, t_sector *ptr_sector, t_vector3 v);

int				ft_editor_sector_compare_vertexes(t_vector3 v1, t_vector3 v2);

// editor/init.c
void			ft_editor_init(t_wolf3d *w);
void			ft_editor_init_fonts(t_wolf3d *w);
void			ft_editor_close_fonts(t_wolf3d *w);
void			ft_editor_init_sectors_areas(t_wolf3d *w, t_list *sector);
void			ft_editor_init_sectors_item_area(t_wolf3d *w, t_sector *s);

// editor/neighbors.c
int				ft_editor_sector_search_neighbors(t_wolf3d *w, t_sector *sector);

// editor/editor_debug.c
void			ft_editor_sector_special_debug(t_list *ptr_list);

int				ft_editor_check_event_area_map(t_wolf3d *w, t_vector3 v);

void			ft_editor_threading(t_wolf3d *w);

// editor/fonts.c
SDL_Rect		*ft_create_rect(int w, int h, int x, int y);
int				ft_font_preset_sc(t_wolf3d *w, int size, int color);
void			ft_font_putstr_sdl(t_wolf3d *w, char *str, t_gui_coord c);

t_sector		*ft_editor_search_sector_by_id(t_wolf3d *w, t_list *list, int i);

void			ft_editor_mouse_move_act_s_mark(t_wolf3d *w);

// void			ft_editor_fill_elem(t_wolf3d *w, t_ui_elem elem, int color);

// int				ft_editor_check_event_area(t_vector3 v, t_ui_elem c);

// void			ft_editor_mouse_btn_up(t_wolf3d *w, SDL_Event e);

// void			ft_editor_init_ui_child_elem(t_ui_elem *child, t_ui_elem *parent);
// void			ft_editor_init_ui_elem_reset(t_ui_elem *child, t_ui_elem *parent);





/*
**	gui functions
*/
int				ft_gui_redraw(t_wolf3d *w);
void			ft_gui_events(t_wolf3d *w);
void			ft_gui_init(t_wolf3d *w);
void			ft_gui_elem_init(t_list **dom, char *name, t_gui_coord v1, t_gui_coord v2);
void			ft_gui_elem_set_color(t_list *list, int color);
void			ft_gui_elem_set_event(t_list *list, void *func, int type, int code);
void			ft_gui_elem_set_parent(t_list *parent, t_list *child);
void			ft_gui_print_element_list(t_list *dom, int level);
void			ft_gui_desctuct(t_list *dom);

void			ft_gui_mousebuttondown(t_wolf3d *w, SDL_Event e, t_list *dom);
void			ft_gui_mousebuttonup(t_wolf3d *w, SDL_Event e, t_list *dom);
void			ft_gui_mousemotion(t_wolf3d *w, SDL_Event e, t_list *dom);
void			ft_gui_elem_set_status(t_list *list, int status);

void			ft_gui_mousemotion_button(void *data, SDL_Event e, t_list *dom, int type);
void			ft_gui_mousebuttondown_button(void *data, SDL_Event e, t_list *dom, int type);
void			ft_gui_mousebuttonup_button(void *data, SDL_Event e, t_list *dom, int type);

int				ft_gui_font_preset_fsc(t_wolf3d *w, char *font_path, int size, int color);
void			ft_gui_font_putstr_sdl(t_wolf3d *w, char *str, t_gui_coord c);
SDL_Rect		*ft_gui_create_sdl_rect(int w, int h, int x, int y);
void			ft_gui_desctuct_fonts(t_list *fonts_list);
void			ft_gui_elem_set_button(t_list *list, void *str);

void			ft_gui_elem_set_text(t_list *list, void *str, int font_size);

void			ft_gui_mousemotion_input(void *data, SDL_Event e, t_list *dom, int type);
void			ft_gui_mousebuttondown_input(void *data, SDL_Event e, t_list *dom, int type);
void			ft_gui_mousebuttonup_input(void *data, SDL_Event e, t_list *dom, int type);

void			ft_gui_elem_set_input(t_list *list, void *str, int flag_numb);
void			ft_gui_delete_status_focus(t_list *dom);
void			ft_gui_delete_status(t_list *dom);

void			ft_gui_mousebuttonup_block(void *data, SDL_Event e, t_list *dom, int type);
void			ft_gui_elem_set_block(t_list *list);
void			ft_gui_focus_keydown(t_wolf3d *w, SDL_Event e, t_list *dom);

void			ft_gui_mousebuttonup_win_menu_btnsector(void *data, SDL_Event e, t_list *dom, int type);
void			ft_gui_mousebuttonup_win_setsector_btncancel(void *data, SDL_Event e, t_list *dom, int type);

t_list			*ft_gui_search_elem_by_name(t_list *dom, char *name);

void			ft_gui_mousemotion_win_map(void *data, SDL_Event e, t_list *dom, int type);
void			ft_gui_mousebuttondown_win_map(void *data, SDL_Event e, t_list *dom, int type);
void			ft_gui_mousebuttonup_win_map(void *data, SDL_Event e, t_list *dom, int type);
void			ft_gui_mousewheel_win_map(void *data, SDL_Event e, t_list *dom, int type);

void			ft_gui_elem_set_map(t_list *list);
void			ft_gui_draw_map(t_wolf3d *w, t_list *list);

void			ft_gui_mousewheel(t_wolf3d *w, SDL_Event e, t_list *dom);

void			ft_gui_fill_area(t_wolf3d *w, t_gui_coord v1, t_gui_coord v2, int color);

t_vector3		ft_gui_map_coord_to_vertex(t_wolf3d *w, t_gui_rect rect, t_gui_coord c);
t_gui_coord		ft_gui_map_vertex_to_coord(t_wolf3d *w, t_gui_rect rect, t_vector3 v);

void			ft_gui_mousebuttonup_win_menu_btnplayer(void *data, SDL_Event e, t_list *dom, int type);
void			ft_gui_mousebuttonup_win_menu_btnsprite(void *data, SDL_Event e, t_list *dom, int type);
void			ft_gui_mousebuttonup_win_menu_btnenemy(void *data, SDL_Event e, t_list *dom, int type);


///just do it
void			ft_editor_take_vertex(t_wolf3d *w);
void			ft_save_the_file(t_wolf3d *w);
void			ft_print_sectors_to_file(t_wolf3d *w, t_list *ptr_list);
void			ft_save_neighbour(t_sector *sector, int fd);

void			ft_create_list_of_vertexes(t_wolf3d *w);
void			ft_count_origin_vertexes(t_wolf3d *w);
void			ft_sector_num_vertex(t_list *ptr_list, t_vector3 *vertexes);
void			ft_print_to_file(t_wolf3d *w, int f);
void			ft_allocate_int2darr(t_wolf3d *w);
void			ft_player_string(t_wolf3d *w);
// TEMP.
void			ft_editor_sector_create(t_wolf3d *w);
void			ft_editor_sector_set_vertex(t_wolf3d *w, t_sector *sector, t_vector3 v, int pos);

t_gui_coord		ft_gui_map_check_mouse_vertex_pos(t_wolf3d *w, t_gui_coord c, \
					t_gui_elem *elem);

// for test
int				ft_new_editor_map_check_area(t_wolf3d *w);

void			ft_gui_mousebuttonup_win_setplayer_btncancel(void *data, SDL_Event e, t_list *dom, int type);

void			ft_gui_mousebuttonup_win_setsprite_btncancel(void *data, SDL_Event e, t_list *dom, int type);
void			ft_gui_mousebuttonup_win_setenemy_btncancel(void *data, SDL_Event e, t_list *dom, int type);

int				ft_search_point_in_sector(void *a, t_vector3 v);
void			ft_gui_draw_point(t_wolf3d *w, t_gui_coord c, int color);

void			ft_gui_draw_player(t_wolf3d *w);

void			ft_set_sprite(t_wolf3d *w, t_vector3 pos, int type);
void			ft_delete_sprite(t_wolf3d *w);

void			ft_gui_draw_sprites(t_wolf3d *w);

void			ft_set_enemy(t_wolf3d *w, t_vector3 pos, int type);
void			ft_delete_enemy(t_wolf3d *w);
void			ft_gui_draw_enemies(t_wolf3d *w);

void			ft_gui_mousebuttonup_win_setsector_btnsavemap(void *data, SDL_Event e, t_list *dom, int type);
void			ft_gui_mousebuttonup_win_setplayer_btnsaveplayer(void *data, SDL_Event e, t_list *dom, int type);
void			ft_gui_mousebuttonup_win_setsprite_btnsaveplayer(void *data, SDL_Event e, t_list *dom, int type);
void			ft_gui_mousebuttonup_win_setenemy_btnsaveplayer(void *data, SDL_Event e, t_list *dom, int type);

void			ft_delete_sector(t_wolf3d *w);

int				ft_compare_vertexes(t_vector3 v1, t_vector3 v2);
double			ft_vxs_vector(t_vector3 v1, t_vector3 v2);
double			ft_vxs_double(double x1, double y1, double x2, double y2);
int				ft_check_div_vector(t_vector3 v1, t_vector3 v2, t_vector3 v3, t_vector3 v4);
t_vector3		ft_find_line_intersect(t_vector3 v1, t_vector3 v2, \
					t_vector3 v3, t_vector3 v4);
int				ft_check_line_segment_intersect_vector(t_vector3 v1, t_vector3 v2, \
					t_vector3 v3, t_vector3 v4);

int				ft_check_point_in_sector(t_wolf3d *w, t_sector *s, t_vector3 v);
int				ft_search_point_in_sector(void *a, t_vector3 v);
int				ft_new_editor_map_check_area(t_wolf3d *w);

// MATH
int				ft_compare_vertexes(t_vector3 v1, t_vector3 v2);
double			ft_vxs_vector(t_vector3 v1, t_vector3 v2);
double			ft_vxs_double(double x1, double y1, double x2, double y2);
int				ft_check_div_vector(t_vector3 v1, t_vector3 v2, t_vector3 v3, t_vector3 v4);
t_vector3		ft_find_line_intersect(t_vector3 v1, t_vector3 v2, \
					t_vector3 v3, t_vector3 v4);
int				ft_check_line_segment_intersect_vector(t_vector3 v1, t_vector3 v2, \
					t_vector3 v3, t_vector3 v4);


void			ft_editor_init(t_wolf3d *w);
void			ft_editor_gui_init(t_wolf3d *w);
void			ft_editor_redraw(void *ptr);

void			ft_gui_elem_set_redraw(t_list *list, void *func);
int				ft_check_general_segment_line(t_vector3 v1, t_vector3 v2, \
					t_vector3 v3, t_vector3 v4);

char			*ft_gui_elem_get_value(t_list *list);
void			ft_gui_mousebuttonup_win_menu_btnsavemap(void *data, SDL_Event e, t_list *dom, int type);

void			ft_game_render(t_wolf3d *w);
void			ft_gui_elem_set_map(t_list *list);

void			ft_game_render_font(t_wolf3d *w);

// ?!?!?!?!?
void			ft_gui_elem_set_redraw_font(t_list *list, void *func);
void			ft_gui_elem_set_image(t_list *list, char *path);

void			*ft_editor_redraw_txtr(void *data, t_list *dom);

void			ft_gui_mousebuttonup_win_setsector_walltxtr(void *data, SDL_Event e, t_list *dom, int type);

void			ft_editor_desctuct(t_wolf3d *w);

void	ft_gui_mousebuttonup_win_menu_btndoor(void *data, SDL_Event e, t_list *dom, int type);
void	ft_gui_mousebuttonup_win_setdoor_btncancel(void *data, SDL_Event e, t_list *dom, int type);
int		ft_map_check_straight_line(t_vector3 v1, t_vector3 v2);
int		ft_check_point_in_line_segment_diameter(t_vector3 p, t_vector3 p1, t_vector3 p2, double diameter);
int		ft_search_point_in_sector_line_diameter(void *a, t_vector3 v, double d);
int		ft_check_point_in_sector_line_diameter(t_sector *s, t_vector3 v, double d);

void	ft_create_sector_door(t_wolf3d *w);

void	ft_change_door_vertex(t_wolf3d *w, t_vector3 v1, t_vector3 v2, t_vector3 pos);

void	ft_gui_mousebuttonup_win_setdoor_btnsave(void *data, SDL_Event e, t_list *dom, int type);

void	ft_map_set_new_sector(t_wolf3d *w, t_sector *s);

void	ft_editor_sectors_reset_neighbors(t_wolf3d *w);

int		ft_sectors_set_all_neighbors(t_wolf3d *w);

double		ft_math_vxs(double x0, double y0, double x1, double y1);

void			ft_new_clean_sdl(t_wolf3d *w);

void	ft_game_redraw(void *d, t_list *dom);

void	ft_gui_draw_image_area(t_wolf3d *w, t_gui_rect rect, SDL_Surface *surf);

///parse map for game
void			ft_my_parse_map(t_new_player *pl, char *ag);
void			ft_alloc_save_sectors(char *ag, t_new_player *pl);
t_new_xy		*ft_vertex_save(t_new_player *pl, t_new_xy *vertex);
void			ft_sector_save(t_new_player *pl, t_new_xy *vertex);
void			ft_sector_count(t_new_player *pl);
void				ft_vertex_count(t_new_player *pl);
t_new_xy		*ft_malloc_sec_vertex(t_new_player *pl, char *v);
void			ft_fill_the_sector(t_new_sector *sector, int number, \
					t_file_read file, t_new_xy *vertex);
void			ft_player_save(t_new_player *pl);
void			player_init(t_new_player *pl, t_new_xy *v, int *angle, int *n);
void			ft_level_save(t_new_player *pl);
#endif
