#ifndef WOLF3D_H
# define WOLF3D_H
# define WIN_HEIGHT 1080
# define WIN_WIDTH 1920
# define TEXTURES_NUMBER 23
# define THREADS 10
# define TEX_W 64
# define TEX_H 64
# define ONE_ANIM 20
# define FULL_ANIM ONE_ANIM * 4 - 4
# define T_CAM_HR_ANGLE 0.02 // transform angle for camera
# define T_CAM_Z_ANGLE 0.01 // transform angle for camera

# define DEG_30 0.52360

# define C_R 0x00FF0000
# define C_G 0x0000FF00
# define C_B 0x000000FF

# define E_GRID_L 32 // GRID LENGTH (SCALE)
# define E_GRID_V_D 6 // VERTEX DIAMETER
# define E_GRID_V_D_D 4 // VERTEX DRAW DIAMETER

# define FONT_PATH "fonts/RobotoMono-Medium.ttf"

# include "SDL2/SDL.h"
# include "SDL2/SDL_thread.h"
# include "SDL2/SDL_ttf.h"

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
#include "file.h"
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

typedef	struct			s_ui_pos		// позиционирование
{
	int					top;
	int					bottom;
	int					left;
	int					right;
}						t_ui_pos;

typedef struct			s_ui_coord
{
	int					x;
	int					y;
	int					w; // element diameter
}						t_ui_coord;

typedef struct			s_ui_elem
{
	t_ui_coord			v1;				// left top point
	t_ui_coord			v2;				// right bottom point
	// t_ui_coord			r1;				// restriction
	// t_ui_coord			r2;				// ...
	int					w;				// frame width
	int					h;				// frame height
	int					status;			// element status: 0: disable, 1: block
	int					trigger;		// element trigger: 0: static, 1: hover, 2: click, 3: active, 4: disabled
	struct s_ui_elem	*parent;		// parent element
	t_ui_pos			pos;			// position: top, bottom, left, right
}						t_ui_elem;

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
	int					status;			// 0: broken line; 1: polygon

	t_ui_elem			elem_2d;		// Сектор как элемент ui (устаревшее)

	t_vector3			vtx_center;		// Центр сектора
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
	int					texture;
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

typedef struct			s_gui_rect
{
	t_ui_coord			v1;
	t_ui_coord			v2;
	int					w;
	int					h;
}						t_gui_rect;

typedef struct			s_gui_event
{
	int					type;
	int					code;
	void				(*func)(void *data, SDL_Event e, t_list *dom, int type);
	t_list				*elem;
}						t_gui_event;

typedef struct			s_gui_font
{
	char				*path;
	SDL_Surface			*surf[7];
	TTF_Font			*ptr;
	SDL_Color			color;
	int					f_sz;
	int					g_sz;
	int					w;
	int					h;
	int					half_menu;
}						t_gui_font;

/*
**	Special struct for map element parameters.
*/
typedef struct			s_gui_map
{
	t_list				*ptr;		// Указатель на gui-элемент
	int					grid_scale;
	unsigned char		check_vertex;
	t_vector3			v;
}						t_gui_map;

# define GUI_ELEM_HIDDEN		0x00000001
# define GUI_ELEM_VISIBLE		0x00000002
# define GUI_ELEM_STATIC		0x00000004
# define GUI_ELEM_DYNAMIC		0x00000008

# define GUI_ELEM_NORMAL		0x00000010
# define GUI_ELEM_HOVER			0x00000020
# define GUI_ELEM_CLICK			0x00000040
# define GUI_ELEM_ACTIVE		0x00000080
# define GUI_ELEM_FOCUS			0x00000100
# define GUI_ELEM_DISABLE		0x00000200

# define GUI_ELEM_ACT_MASK		0x0000000F

# define GUI_ELEM_TYPE_BLOCK	0x01
# define GUI_ELEM_TYPE_TEXT		0x02
# define GUI_ELEM_TYPE_BUTTON	0x03
# define GUI_ELEM_TYPE_INPUT	0x04
# define GUI_ELEM_TYPE_MAP		0xF1

typedef struct			s_gui_elem
{
	char				*name;			// name
	t_ui_coord			v1;				// left top point
	t_ui_coord			v2;				// right bottom point
	t_ui_coord			r1;				// absolute area
	t_ui_coord			r2;				// ...
	int					w;				// frame width
	int					h;				// frame height
	int					status;			// element status
	t_list				*parent;		// parent element
	t_ui_pos			pos;			// position: top, bottom, left, right

	t_list				*child;			// child elements
	int					color;			// element color
	t_list				*events;		// element events
	int					type;			// element type
	char				*str;			// element string
}						t_gui_elem;

# define GUI_NOT_REDRAW			0x00
# define GUI_REDRAW				0x01
# define GUI_REDRAW_FRAME		0x02

// по логике дублирует redraw
# define GUI_EVENT_OFF			0x00
# define GUI_EVENT_ON			0x01
# define GUI_EVENT_SEARCH		0x02

// Режимы
# define GUI_MD_ME				0x0000F001
# define GUI_MD_ME_SET_SECTOR	0x0000F100
# define GUI_MD_ME_SET_PLAYER	0x0000F200
# define GUI_MD_ME_SET_SPRITE	0x0000F300
# define GUI_MD_ME_SET_ENEMY	0x0000F400

// Цвета
# define GUI_CL_STANDART		0x00ff0000
# define GUI_CL_SECTOR			0x00ffd700
# define GUI_CL_PLAYER			0x00a496f2
# define GUI_CL_SPRITE			0x00df73ff
# define GUI_CL_ENEMY			0x00fb607f

typedef struct			s_gui
{
	t_list				*fonts;
	t_list				*dom;
	unsigned char		redraw;
	t_gui_elem			*redraw_elem;
	t_ui_coord			mouse_pos;
	int					search_elem;
	t_list				*focus_elem;
	int					mode;	// режим
}						t_gui;

typedef struct			s_wolf3d
{
	t_file				file;
	t_list				*vertex;
	// add list with sector
	t_list				*sector;
	// add temp list for map
	t_list				*map_sector;
	// add temp list for map (top vertex)
	t_list				*map_sector_top;
	// spec param
	double				fov;
	double				l_p;

	t_list				*sprites;

	t_sdl				*sdl; //structe for handle sdl  stuff
	t_map				map;
	t_time				t;
	t_const				c;
	t_player			pl;
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
	int					sector_status; // 0: nothing; 1: set new sector
	int					sector_count;

	int					player_status; // 0: nothing; 1: player was set;

	int					status; // game status: 0: error; 1: map editor; 2: game

	t_gui_map			gui_map;
	t_gui				gui;



	t_ui_elem			ui_map; // (deprecated)
	t_ui_elem			ui_act_s; // (deprecated)
	t_ui_elem			ui_act_s_floor; // (deprecated)
	t_ui_elem			ui_act_s_wall; // (deprecated)
	t_ui_elem			ui_act_s_ceil; // (deprecated)
	t_sector			*act_s;		// Просматриваемый сектор: если нет, то NULL

	t_ui_elem			ui_txtr_opt; // (deprecated)
	t_ui_elem			ui_txtr_opt_close; // (deprecated)
	int					txtr_opt_type;	// 0: floor, 1: wall, 2: ceil  // (deprecated)

	t_ui_elem			ui_me_menu;	// Меню map_editor: основная информация о карте,  // (deprecated)
									// выбор помещаемого объекта, сохранение карты. // (deprecated)
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

	t_ui_elem			ui_map;
}						t_threads_help;

typedef struct			s_threads
{
	t_threads_help		w;
	int					t1;
	int					t2;
}						t_threads;

typedef struct			s_fdf_wu
{
	double				x1;
	double				y1;
	double				x2;
	double				y2;
	double				p;
	double				dx;
	double				dy;
	double				gradient;
	double				xend;
	double				yend;
	double				xgap;
	double				xpxl1;
	double				ypxl1;
	double				xpxl2;
	double				ypxl2;
	double				intery;
	int					steep;
	int					steps;
	int					step;
	int					color1;
	int					color2;
	int					check_color_rev;
	double				temp_f;
}						t_fdf_wu;

typedef struct			s_fdf_get_color
{
	int					color1;	// Первый цвет
	int					color2;	// Второй цвет
	double				f1;		// Полупрозрачность первого цвета
	int					r1;
	int					g1;
	int					b1;
	int					r2;
	int					g2;
	int					b2;
	int					r_rez;
	int					g_rez;
	int					b_rez;
}						t_fdf_get_color;


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
void			ft_font_putstr_sdl(t_wolf3d *w, char *str, t_ui_coord c);

t_sector		*ft_editor_search_sector_by_id(t_wolf3d *w, t_list *list, int i);

void			ft_editor_mouse_move_act_s_mark(t_wolf3d *w);

void			ft_editor_fill_elem(t_wolf3d *w, t_ui_elem elem, int color);

int				ft_editor_check_event_area(t_vector3 v, t_ui_elem c);

void			ft_editor_mouse_btn_up(t_wolf3d *w, SDL_Event e);

void			ft_editor_init_ui_child_elem(t_ui_elem *child, t_ui_elem *parent);
void			ft_editor_init_ui_elem_reset(t_ui_elem *child, t_ui_elem *parent);





/*
**	gui functions
*/
int				ft_gui_redraw(t_wolf3d *w);
void			ft_gui_events(t_wolf3d *w);
void			ft_gui_init(t_wolf3d *w);
void			ft_gui_elem_init(t_list **dom, char *name, t_ui_coord v1, t_ui_coord v2);
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
void			ft_gui_font_putstr_sdl(t_wolf3d *w, char *str, t_ui_coord c);
SDL_Rect		*ft_gui_create_sdl_rect(int w, int h, int x, int y);
void			ft_gui_desctuct_fonts(t_list *fonts_list);
void			ft_gui_elem_set_button(t_list *list, void *str);

void			ft_gui_elem_set_text(t_list *list, void *str);

void			ft_gui_mousemotion_input(void *data, SDL_Event e, t_list *dom, int type);
void			ft_gui_mousebuttondown_input(void *data, SDL_Event e, t_list *dom, int type);
void			ft_gui_mousebuttonup_input(void *data, SDL_Event e, t_list *dom, int type);

void			ft_gui_elem_set_input(t_list *list, void *str);
void			ft_gui_delete_status_focus(t_list *dom);
void			ft_gui_delete_status(t_list *dom);

void			ft_gui_mousebuttonup_block(void *data, SDL_Event e, t_list *dom, int type);
void			ft_gui_elem_set_block(t_list *list);
void			ft_gui_focus_keydown(t_wolf3d *w, SDL_Event e, t_list *dom);

void			ft_gui_mousebuttonup_win_menu_btn_sector(void *data, SDL_Event e, t_list *dom, int type);
void			ft_gui_mousebuttonup_win_setsector_btn_cancel(void *data, SDL_Event e, t_list *dom, int type);

t_list			*ft_gui_search_elem_by_name(t_list *dom, char *name);

void			ft_gui_mousemotion_win_map(void *data, SDL_Event e, t_list *dom, int type);
void			ft_gui_mousebuttondown_win_map(void *data, SDL_Event e, t_list *dom, int type);
void			ft_gui_mousebuttonup_win_map(void *data, SDL_Event e, t_list *dom, int type);
void			ft_gui_mousewheel_win_map(void *data, SDL_Event e, t_list *dom, int type);

void			ft_gui_elem_set_map(t_list *list);
void			ft_gui_draw_map(t_wolf3d *w, t_list *list);

void			ft_gui_mousewheel(t_wolf3d *w, SDL_Event e, t_list *dom);

void			ft_gui_fill_area(t_wolf3d *w, t_ui_coord v1, t_ui_coord v2, int color);

t_vector3		ft_gui_map_coord_to_vertex(t_wolf3d *w, t_gui_rect rect, t_ui_coord c);
t_ui_coord		ft_gui_map_vertex_to_coord(t_wolf3d *w, t_gui_rect rect, t_vector3 v);

void			ft_gui_mousebuttonup_win_menu_btn_player(void *data, SDL_Event e, t_list *dom, int type);
void			ft_gui_mousebuttonup_win_menu_btn_sprite(void *data, SDL_Event e, t_list *dom, int type);
void			ft_gui_mousebuttonup_in_menu_btn_enemy(void *data, SDL_Event e, t_list *dom, int type);


///just do it
///editor_save_file.c
void			ft_editor_take_vertex(t_wolf3d *w);
void			ft_save_the_file(t_wolf3d *w);

void			ft_save_neighbour(t_sector *sector, int fd);
void			ft_sector_num_vertex(t_list *ptr_list, t_vector3 *vertexes);
///editor_save_file2.c
void			ft_print_sectors_to_file(t_wolf3d *w, t_list *ptr_list);
void			ft_create_list_of_vertexes(t_wolf3d *w);
void			ft_count_origin_vertexes(t_wolf3d *w);
void			ft_print_to_file(t_wolf3d *w, int f);
///editor_save_file3.c
void			ft_save_neighbour(t_sector *sector, int fd);

// TEMP.
void			ft_editor_sector_create(t_wolf3d *w);
void			ft_editor_sector_set_vertex(t_wolf3d *w, t_sector *sector, t_vector3 v);

t_ui_coord		ft_gui_map_check_mouse_vertex_pos(t_wolf3d *w, t_ui_coord c, \
					t_gui_elem *elem);

// for test
int				ft_new_editor_map_check_area(t_wolf3d *w);

void			ft_gui_mousebuttonup_win_setplayer_btncancel(void *data, SDL_Event e, t_list *dom, int type);

void			ft_gui_mousebuttonup_win_setsprite_btncancel(void *data, SDL_Event e, t_list *dom, int type);
void			ft_gui_mousebuttonup_win_setenemy_btncancel(void *data, SDL_Event e, t_list *dom, int type);

int				ft_search_point_in_sector(void *a, t_vector3 v);
void			ft_gui_draw_point(t_wolf3d *w, t_ui_coord c, int color);

void			ft_gui_draw_player(t_wolf3d *w);

#endif
