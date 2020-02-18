/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   general_struct.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjuana <tjuana@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/26 18:55:40 by dorange-          #+#    #+#             */
/*   Updated: 2020/02/17 12:37:02 by tjuana           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GENERAL_STRUCT_H
# define GENERAL_STRUCT_H

# include "doom.h"

# include <libft.h>
# include "editor_struct.h"
# include "file.h"
# include "gui_struct.h"

typedef struct			s_font
{
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

typedef struct			s_sdl
{
	SDL_Surface			*srf;
	
	int					running;
	SDL_Window			*win;
	SDL_Renderer		*renderer;
	Uint32				*pixels;
	SDL_Texture			*text;
	// SDL_Surface			**textures;
	// SDL_AudioSpec		*wav_spect;
	// Uint32				*wav_len;
	// Uint8				**wav_buff;
	// SDL_AudioDeviceID	*audio_device;
	t_font				font;
	unsigned char		i;
}						t_sdl;

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

	// texture
	t_list				*txtr;
	int					txtr_count;

	t_file				file;
	t_list				*vertex;

	t_list				*sprites;

	t_sdl				*sdl; //structe for handle sdl  stuff
	t_time				t;
	int					fd;

	t_vector3			pos;
	t_gui_coord			pos_start;
	t_gui_coord			offset;
	int					v_d;

	t_gui_map			gui_map;
	t_gui				gui;

	void				*new_data;	// pointer to game data
}						t_wolf3d;

#endif
