# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: dorange- <dorange-@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/08/08 11:40:58 by tjuana            #+#    #+#              #
#    Updated: 2020/02/21 20:59:51 by dorange-         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# Project structure:
# src/
#		albegra/	Functions for use linear algebra
#		editor/		Functions for map editor
#		func/		?
#		game/		Function for game
#		gui/		Function for gui-interface

# Project name
NAME = DooM_nuKem

# File name
GAME_NAME = doom_nukem
EDITOR_NAME = map_editor
GUI_NAME = gui_test

# Сompiler settings
CC = gcc
FLAGS_NORME = -Wall -Wextra -Werror
#FLAGS_O = -O0 -O3
#FLAGS_OPT = -march=native -m64 -flto -funroll-loops -Ofast
FLAGS = -g $(FLAGS_NORME) #$(FLAGS_O) #$(FLAGS_NORME) $(FLAGS_OPT)

# SDL2 settings
USERNAME = $(shell whoami)
LIBRARIES = \
-lft -L$(LIBFT_DIRECTORY)\
-lSDL2 -lSDL2main -L/Users/$(USERNAME)/.brew/Cellar/sdl2/2.0.10/lib \
-lSDL2_ttf -L/Users/$(USERNAME)/.brew/Cellar/sdl2_ttf/2.0.15/lib \
-lSDL2_image -L/Users/$(USERNAME)/.brew/Cellar/sdl2_image/2.0.5/lib \
-lSDL2_mixer -L/Users/$(USERNAME)/.brew/Cellar/sdl2_mixer/2.0.4/lib 

INCLUDES = -I$(HEADERS_DIRECTORY) -I$(LIBFT_HEADERS) -I$(SDL_HEADERS)

LIBFT = $(addprefix $(LIBFT_DIRECTORY),libft.a)
LIBFT_DIRECTORY = ./libft/
LIBFT_HEADERS = ./libft/includes
SDL_HEADERS = include/

HEADERS_DIRECTORY = ./includes/
HEADERS_LIST = doom.h
HEADERS = $(addprefix $(HEADERS_DIRECTORY), $(HEADERS_LIST))

DIRECTORY =  $(shell pwd)

SRCS_PATH = ./src/
OBJS_PATH = ./obj/

# MAIN FUNCTIONS
MAIN_SRCS_DIRECTORY = $(SRCS_PATH)main/
MAIN_LIST = \
main_gui_init.c \
main_gui_init_author.c \
main_gui_init_menu.c \
main.c \
main_btn_action.c \
main_events.c

MAIN_OBJS_DIRECTORY = $(OBJS_PATH)
MAIN_OBJS_LIST = $(patsubst %.c, %.o, $(MAIN_LIST))
MAIN_OBJS = $(addprefix $(MAIN_OBJS_DIRECTORY), $(MAIN_OBJS_LIST))

# ALGEBRA FUNCTIONS
ALGEBRA_SRCS_DIRECTORY = $(SRCS_PATH)algebra/
ALGEBRA_LIST = \
algebra_intersect.c \
algebra_intersect2.c \
algebra_matrix_transform.c \
algebra_matrix.c \
algebra_matrix_2.c \
algebra_vectors_1.c \
algebra_vectors_2.c \
algebra_vectors_3.c \
algebra_vectors_func.c \
algebra_math_1.c \
algebra_math_2.c \
algebra_math_3.c

ALGEBRA_OBJS_DIRECTORY = $(OBJS_PATH)
ALGEBRA_OBJS_LIST = $(patsubst %.c, %.o, $(ALGEBRA_LIST))
ALGEBRA_OBJS = $(addprefix $(ALGEBRA_OBJS_DIRECTORY), $(ALGEBRA_OBJS_LIST))






# FUNC FUNCTIONS
FUNC_SRCS_DIRECTORY = $(SRCS_PATH)func/
FUNC_LIST = \
func_help.c \
func_sdl.c \
func_wu_color.c \
func_wu_draw.c \
func_wu_init.c \
func_wu_line.c \
func_wu.c \
func_color.c

FUNC_OBJS_DIRECTORY = $(OBJS_PATH)
FUNC_OBJS_LIST = $(patsubst %.c, %.o, $(FUNC_LIST))
FUNC_OBJS = $(addprefix $(FUNC_OBJS_DIRECTORY), $(FUNC_OBJS_LIST))



# EDITOR WITH MAIN FILE
EDITOR_SRCS_DIRECTORY = $(SRCS_PATH)editor/
EDITOR_SRCS_LIST = \
editor_desctuct.c \
editor_draw_map.c \
editor_draw_map_grid.c \
editor_draw_map_objects.c \
editor_draw_map_sector.c \
editor_draw_map_vertex.c \
editor_event_win_map_click.c \
editor_event_win_map_move.c \
editor_event_win_map_set.c \
editor_event_win_map_zoom.c \
editor_event_win_menu.c \
editor_event_win_menu2.c \
editor_event_win_setdoor.c \
editor_event_win_setenemy.c \
editor_event_win_setplayer.c \
editor_event_win_setsector.c \
editor_event_win_setsprite.c \
editor_gui_init.c \
editor_gui_init2.c \
editor_gui_init3.c \
editor_init.c \
editor_map_check.c \
editor_map_door.c \
editor_map_enemy.c \
editor_map_func.c \
editor_map_sector.c \
editor_map_sector_neighbors.c \
editor_map_sector_vertex.c \
editor_map_sprite.c \
editor_save_file.c \
editor_save_file2.c \
editor_save_file3.c \
editor_map_check_line.c \
editor_map_check2.c

EDITOR_OBJS_DIRECTORY = $(OBJS_PATH)
EDITOR_OBJS_LIST = $(patsubst %.c, %.o, $(EDITOR_SRCS_LIST))
EDITOR_OBJS = $(addprefix $(EDITOR_OBJS_DIRECTORY), $(EDITOR_OBJS_LIST))



# GUI WITH MAIN FILE
GUI_SRCS_DIRECTORY = $(SRCS_PATH)gui/
GUI_SRCS_LIST = \
gui_events.c \
gui_events_mouse.c \
gui_redraw.c \
gui_elem_init.c \
gui_destruct.c \
gui_mouse.c \
gui_mouse_event.c \
gui_elem_button.c \
gui_fonts.c \
gui_elem_input.c \
gui_keydown.c \
gui_init.c \
gui_elem_set_func.c \
gui_elem_set_status.c \
gui_elem_set_style.c \
gui_elem_set_type.c \
gui_redraw_fill.c \
gui_redraw_font.c \
gui_redraw_image.c \
gui_mouse_actions.c \
gui_sdl_func.c

GUI_OBJS_DIRECTORY = $(OBJS_PATH)
GUI_OBJS_LIST = $(patsubst %.c, %.o, $(GUI_SRCS_LIST))
GUI_OBJS = $(addprefix $(GUI_OBJS_DIRECTORY), $(GUI_OBJS_LIST))

# GAME WITH MAIN FILE
GAME_SRCS_DIRECTORY = $(SRCS_PATH)game/
GAME_SRCS_LIST = \
game_but.c \
game_but_detect.c \
game_door.c \
game_door_detect.c \
game_engine_1.c \
game_engine_2.c \
game_engine_cross.c \
game_events_1.c \
game_events_2.c \
game_events_3.c \
game_gun.c \
game_load_file.c \
game_load_textures.c \
game_main.c \
game_map_parse_1.c \
game_map_parse_2.c \
game_motion_1.c \
game_motion_2.c \
game_sdl_addons.c \
game_texture_parser.c \
game_textures.c \
game_walls.c

GAME_OBJS_DIRECTORY = $(OBJS_PATH)
GAME_OBJS_LIST = $(patsubst %.c, %.o, $(GAME_SRCS_LIST))
GAME_OBJS = $(addprefix $(GAME_OBJS_DIRECTORY), $(GAME_OBJS_LIST))

SDL_LIBS = $(addprefix $(DIRECTORY)/lib/, $(LIB_LIST))

LIBFT = libft/libft.a
LIBSDL_EXIST = 0
err = no

GREEN = \033[0;32m
RED = \033[0;31m
RESET = \033[0m

C_TX_BLACK = \033[30m
C_TX_RED = \033[31m
C_TX_GREEN = \033[32m
C_TX_YELLOW = \033[33m
C_TX_BLUE = \033[34m
C_TX_MAGENTA = \033[35m
C_TX_CYAN = \033[36m
C_TX_GREY = \033[37m

C_BG_BLACK = \033[40m
C_BG_RED = \033[41m
C_BG_GREEN = \033[42m
C_BG_YELLOW = \033[43m
C_BG_BLUE = \033[44m
C_BG_MAGENTA = \033[45m
C_BG_CYAN = \033[46m
C_BG_GREY = \033[47m

C_RESET = \033[0m

.PHONY: all clean fclean re

all: $(NAME)

# all objs file
OBJS_COMPILE = \
$(MAIN_OBJS) \
$(GAME_OBJS) \
$(EDITOR_OBJS) \
$(ALGEBRA_OBJS) \
$(GUI_OBJS) \
$(FUNC_OBJS) \

$(NAME): $(LIBFT) $(OBJS_COMPILE)
	@echo "\n$(NAME): $(GREEN)object files were created$(RESET)"
	@$(CC) $(FLAGS) $(LIBRARIES) $(INCLUDES) $(OBJS_COMPILE) -o $(GAME_NAME)
	@echo "$(NAME): $(GREEN)$(NAME) was created$(RESET)"



$(MAIN_OBJS_DIRECTORY)%.o : $(MAIN_SRCS_DIRECTORY)%.c $(HEADERS)
	@mkdir -p $(MAIN_OBJS_DIRECTORY) 2>/dev/null || echo "" > /dev/null
	@$(CC) $(FLAGS) -c $(INCLUDES) $< -o $@
	@echo "$(C_TX_YELLOW).$(RESET)\c"

$(EDITOR_OBJS_DIRECTORY)%.o : $(EDITOR_SRCS_DIRECTORY)%.c $(HEADERS)
	@mkdir -p $(EDITOR_OBJS_DIRECTORY) 2>/dev/null || echo "" > /dev/null
	@$(CC) $(FLAGS) -c $(INCLUDES) $< -o $@
	@echo "$(C_TX_MAGENTA).$(RESET)\c"

$(GUI_OBJS_DIRECTORY)%.o : $(GUI_SRCS_DIRECTORY)%.c $(HEADERS)
	@mkdir -p $(GUI_OBJS_DIRECTORY) 2>/dev/null || echo "" > /dev/null
	@$(CC) $(FLAGS) -c $(INCLUDES) $< -o $@
	@echo "$(C_TX_GREY).$(RESET)\c"

$(ALGEBRA_OBJS_DIRECTORY)%.o : $(ALGEBRA_SRCS_DIRECTORY)%.c $(HEADERS)
	@mkdir -p $(ALGEBRA_OBJS_DIRECTORY) 2>/dev/null || echo "" > /dev/null
	@$(CC) $(FLAGS) -c $(INCLUDES) $< -o $@
	@echo "$(C_TX_GREY).$(RESET)\c"

$(FUNC_OBJS_DIRECTORY)%.o : $(FUNC_SRCS_DIRECTORY)%.c $(HEADERS)
	@mkdir -p $(FUNC_OBJS_DIRECTORY) 2>/dev/null || echo "" > /dev/null
	@$(CC) $(FLAGS) -c $(INCLUDES) $< -o $@
	@echo "$(C_TX_GREY).$(RESET)\c"

$(GAME_OBJS_DIRECTORY)%.o : $(GAME_SRCS_DIRECTORY)%.c $(HEADERS)
	@mkdir -p $(GAME_OBJS_DIRECTORY) 2>/dev/null || echo "" > /dev/null
	@$(CC) $(FLAGS) -c $(INCLUDES) $< -o $@
	@echo "$(C_TX_YELLOW).$(RESET)\c"

$(LIBFT):
	@echo "$(NAME): $(GREEN)Creating $(LIBFT)...$(RESET)"
	@$(MAKE) -sC $(LIBFT_DIRECTORY)



clean:
	@$(MAKE) -sC $(LIBFT_DIRECTORY) clean
	@rm -rf $(OBJS_PATH)
	@echo "$(NAME): $(RED)$(OBJS_PATH) was deleted$(RESET)"
	@rm -rf $(PARSER_OBJS_DIRECTORY)
	@echo "$(NAME): $(RED)$(PARSER_OBJS_DIRECTORY) was deleted$(RESET)"
	@echo "$(NAME): $(RED)object files were deleted$(RESET)"

dd:
	rm $(NAME)

fclean: clean
	@rm -r $(LIBFT)
	@echo "$(NAME): $(RED)$(LIBFT) was deleted$(RESET)"
	@rm -f $(NAME)
	@echo "$(NAME): $(RED)$(NAME) was deleted$(RESET)"
re:
	@$(MAKE) fclean
	@$(MAKE) all