# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tjuana <tjuana@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/08/08 11:40:58 by tjuana            #+#    #+#              #
#    Updated: 2020/01/28 14:29:50 by tjuana           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# Project structure:
# src/
#		func/		General functions
#		algebra/	Functions for use linear algebra
#		math/		Mathematic functions for calculations (temp.?)
#		editor/		Map editor (with main file)
#
#		gui/		Functions for create interface
#		game/		Game (with main file)
#
#

# Project name
NAME = DooM_nuKem

# File name
GAME_NAME = doom_nukem
EDITOR_NAME = map_editor
GUI_NAME = gui_test

# Сompiler settings
CC = gcc
FLAGS = -g -O3 -O0

# SDL2 settings
USERNAME = $(shell whoami)
LIBRARIES = \
-lft -L$(LIBFT_DIRECTORY)\
-lSDL2 -lSDL2main -L/Users/$(USERNAME)/.brew/Cellar/sdl2/2.0.10/lib \
-lSDL2_ttf -L/Users/$(USERNAME)/.brew/Cellar/sdl2_ttf/2.0.15/lib \
-lSDL2_image -L/Users/$(USERNAME)/.brew/Cellar/sdl2_image/2.0.5/lib

INCLUDES = -I$(HEADERS_DIRECTORY) -I$(LIBFT_HEADERS) -I$(SDL_HEADERS)

LIBFT = $(addprefix $(LIBFT_DIRECTORY),libft.a)
LIBFT_DIRECTORY = ./libft/
LIBFT_HEADERS = ./libft/includes
SDL_HEADERS = include/

HEADERS_DIRECTORY = ./includes/
HEADERS_LIST = wolf3d.h
HEADERS = $(addprefix $(HEADERS_DIRECTORY), $(HEADERS_LIST))

DIRECTORY =  $(shell pwd)

SRCS_PATH = ./src/
OBJS_PATH = ./objects/

# ALGEBRA FUNCTIONS
ALGEBRA_SRCS_DIRECTORY = $(SRCS_PATH)algebra/
ALGEBRA_LIST = \
algebra_matrix.c \
algebra_vectors_1.c \
algebra_vectors_2.c

ALGEBRA_OBJS_DIRECTORY = $(OBJS_PATH)
ALGEBRA_OBJS_LIST = $(patsubst %.c, %.o, $(ALGEBRA_LIST))
ALGEBRA_OBJS = $(addprefix $(ALGEBRA_OBJS_DIRECTORY), $(ALGEBRA_OBJS_LIST))

# MATH FUNCTIONS
MATH_SRCS_DIRECTORY = $(SRCS_PATH)math/
MATH_LIST = \
math_intersect.c \
math_vectors.c

MATH_OBJS_DIRECTORY = $(OBJS_PATH)
MATH_OBJS_LIST = $(patsubst %.c, %.o, $(MATH_LIST))
MATH_OBJS = $(addprefix $(MATH_OBJS_DIRECTORY), $(MATH_OBJS_LIST))

# PARSER
PARSER_DIRECTORY = $(SRCS_PATH)parser/
PARSER_LIST = \
parser_func.c \
parser_nnmp_sector.c \
parser_nnmp.c \
parser_vertex.c

PARSER_OBJS_DIRECTORY = $(OBJS_PATH)
PARSER_OBJS_LIST = $(patsubst %.c, %.o, $(PARSER_LIST))
PARSER_OBJS = $(addprefix $(PARSER_OBJS_DIRECTORY), $(PARSER_OBJS_LIST))



# OBJECTS
GENERAL_SRCS_DIRECTORY = $(SRCS_PATH)
GENERAL_SRCS_LIST = \
sdl.c \
debug.c \
sector.c \
sound.c	\
textures.c

GENERAL_OBJS_DIRECTORY = $(OBJS_PATH)
GENERAL_OBJS_LIST = $(patsubst %.c, %.o, $(GENERAL_SRCS_LIST))
GENERAL_OBJS = $(addprefix $(GENERAL_OBJS_DIRECTORY), $(GENERAL_OBJS_LIST))

# FUNC FUNCTIONS
FUNC_SRCS_DIRECTORY = $(SRCS_PATH)func/
FUNC_LIST = \
func_fpc.c \
func_help.c \
func_sdl.c \
func_wu_color.c \
func_wu_draw.c \
func_wu.c

FUNC_OBJS_DIRECTORY = $(OBJS_PATH)
FUNC_OBJS_LIST = $(patsubst %.c, %.o, $(FUNC_LIST))
FUNC_OBJS = $(addprefix $(FUNC_OBJS_DIRECTORY), $(FUNC_OBJS_LIST))



# EDITOR WITH MAIN FILE
EDITOR_SRCS_DIRECTORY = $(SRCS_PATH)editor/
EDITOR_SRCS_LIST = \
editor_main.c \
editor_init.c \
editor_neighbors.c \
editor_debug.c \
editor_save_file.c \
editor_save_file2.c \
editor_save_file3.c\
editor_gui_init.c \
editor_map_draw_objects.c \
editor_gui_draw_map.c \
editor_gui_elem_event_list.c \
editor_gui_events_win_map.c \
editor_gui_map_check.c \
editor_gui_map_enemy.c \
editor_map_func.c \
editor_gui_map_sprite.c \
\
editor_redraw.c \
editor_sector.c \
editor_gui_txtr.c \
editor_desctuct.c \
editor_door.c

EDITOR_OBJS_DIRECTORY = $(OBJS_PATH)
EDITOR_OBJS_LIST = $(patsubst %.c, %.o, $(EDITOR_SRCS_LIST))
EDITOR_OBJS = $(addprefix $(EDITOR_OBJS_DIRECTORY), $(EDITOR_OBJS_LIST))



# GUI WITH MAIN FILE
GUI_SRCS_DIRECTORY = $(SRCS_PATH)gui/
GUI_SRCS_LIST = \
gui_events.c \
gui_redraw.c \
gui_elem_init.c \
gui_destruct.c \
gui_debug.c \
gui_mouse.c \
gui_elem_button.c \
gui_fonts.c \
gui_elem_input.c \
gui_keydown.c \
gui_init.c



GUI_OBJS_DIRECTORY = $(OBJS_PATH)
GUI_OBJS_LIST = $(patsubst %.c, %.o, $(GUI_SRCS_LIST))
GUI_OBJS = $(addprefix $(GUI_OBJS_DIRECTORY), $(GUI_OBJS_LIST))



# GAME WITH MAIN FILE
GAME_SRCS_DIRECTORY = $(SRCS_PATH)game/
GAME_SRCS_LIST = \
game_engine.c \
game_engine_exp.c \
game_functions_main.c \
game_gun.c \
game_main.c \
game_math_functions.c \
game_sdl_addons.c \
game_textures.c \
game_vectors_1.c \
game_vectors_2.c \
game_walls.c \
game_map_parse.c \
game_map_parse2.c

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
$(GAME_OBJS) \
$(GENERAL_OBJS) \
$(ALGEBRA_OBJS) \
$(MATH_OBJS) \
$(PARSER_OBJS) \
$(EDITOR_OBJS) \
$(GUI_OBJS) \
$(FUNC_OBJS) \

# file for game
GAME_OBJS_COMPILE = \
$(GENERAL_OBJS) \
$(MATH_OBJS) \
$(PARSER_OBJS) \
$(ALGEBRA_OBJS) \
$(FUNC_OBJS) \
$(GUI_OBJS) \
$(GAME_OBJS)

# file for editor
EDITOR_OBJS_COMPILE = \
$(EDITOR_OBJS) \
$(GUI_OBJS) \
$(MATH_OBJS) \
$(GENERAL_OBJS) \
$(PARSER_OBJS) \
$(FUNC_OBJS) \
$(ALGEBRA_OBJS)

$(NAME): $(LIBFT) $(OBJS_COMPILE)
	@echo "\n$(NAME): $(GREEN)object files were created$(RESET)"
	@$(CC) $(FLAGS) $(LIBRARIES) $(INCLUDES) $(GAME_OBJS_COMPILE) -o $(GAME_NAME)
	@echo "$(NAME): $(GREEN)$(NAME) was created$(RESET)"
	@$(CC) $(FLAGS) $(LIBRARIES) $(INCLUDES) $(EDITOR_OBJS_COMPILE) -o $(EDITOR_NAME)
	@echo "$(EDITOR_NAME): $(GREEN)$(EDITOR_NAME) was created$(RESET)"



# Object files
$(GENERAL_OBJS_DIRECTORY)%.o : $(GENERAL_SRCS_DIRECTORY)%.c $(HEADERS)
	@mkdir -p $(GENERAL_OBJS_DIRECTORY) 2>/dev/null || echo "" > /dev/null
	@$(CC) $(FLAGS) -c $(INCLUDES) $< -o $@
	@echo "$(C_TX_RED).$(RESET)\c"

$(PARSER_OBJS_DIRECTORY)%.o : $(PARSER_DIRECTORY)%.c $(HEADERS)
	@mkdir -p $(PARSER_OBJS_DIRECTORY) 2>/dev/null || echo "" > /dev/null
	@$(CC) $(FLAGS) -c $(INCLUDES) $< -o $@
	@echo "$(C_TX_GREY).$(RESET)\c"

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

$(MATH_OBJS_DIRECTORY)%.o : $(MATH_SRCS_DIRECTORY)%.c $(HEADERS)
	@mkdir -p $(MATH_OBJS_DIRECTORY) 2>/dev/null || echo "" > /dev/null
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
	@rm -rf $(GENERAL_OBJS_DIRECTORY)
	@echo "$(NAME): $(RED)$(GENERAL_OBJS_DIRECTORY) was deleted$(RESET)"
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
