# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: dorange- <dorange-@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/08/08 11:40:58 by tjuana            #+#    #+#              #
#    Updated: 2020/01/19 19:47:31 by dorange-         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = DooM_nuKem
EDITOR_NAME = map_editor

# temp for testing
GUI_NAME = gui_test

USERNAME = dorange-

FLAGS = -g -O3 -O0
CC = gcc
LIBRARIES = -lft -L$(LIBFT_DIRECTORY)\
	-lSDL2 -lSDL2main -L/Users/$(USERNAME)/.brew/Cellar/sdl2/2.0.10/lib\
	-lSDL2_ttf -L/Users/$(USERNAME)/.brew/Cellar/sdl2_ttf/2.0.15/lib\
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

PARSER_DIRECTORY = ./src/parser/
PARSER_LIST = parser_func.c parser_nnmp_sector.c parser_nnmp.c parser_vertex.c

PARSER_OBJS_DIRECTORY = ./obj_parser/
PARSER_OBJS_LIST = $(patsubst %.c, %.o, $(PARSER_LIST))
PARSER_OBJS = $(addprefix $(PARSER_OBJS_DIRECTORY), $(PARSER_OBJS_LIST))

SRCS_DIRECTORY = ./src/
SRCS_LIST = \
			help.c\
			read_map.c\
			sdl.c\
			textures.c\
			events.c\
			threads.c\
			sdl_render.c\
			move.c\
			fpc.c\
			animation.c\
			sound.c	\
			map.c \
			alg_wu_color.c \
			alg_wu_draw.c \
			alg_wu.c \
			map_arrow.c \
			vectors_1.c \
			vectors_2.c \
			matrix.c \
			debug.c \
			sector.c

OBJS_DIRECTORY = ./objects/
OBJS_LIST = $(patsubst %.c, %.o, $(SRCS_LIST))
OBJS = $(addprefix $(OBJS_DIRECTORY), $(OBJS_LIST))



MAIN_SRCS_DIRECTORY = ./src/
MAIN_SRCS_LIST = main.c

MAIN_OBJS_DIRECTORY = ./obj_main/
MAIN_OBJS_LIST = $(patsubst %.c, %.o, $(MAIN_SRCS_LIST))
MAIN_OBJS = $(addprefix $(MAIN_OBJS_DIRECTORY), $(MAIN_OBJS_LIST))



EDITOR_SRCS_DIRECTORY = ./src/editor/
EDITOR_SRCS_LIST = editor.c render.c map.c events.c mouse.c \
draw.c init.c neighbors.c editor_debug.c editor_threads.c fonts.c\
editor_save_file.c editor_save_file2.c

EDITOR_OBJS_DIRECTORY = ./obj_editor/
EDITOR_OBJS_LIST = $(patsubst %.c, %.o, $(EDITOR_SRCS_LIST))
EDITOR_OBJS = $(addprefix $(EDITOR_OBJS_DIRECTORY), $(EDITOR_OBJS_LIST))



GUI_SRCS_DIRECTORY = ./src/gui/
GUI_SRCS_LIST = gui_main.c gui_events.c gui_redraw.c gui_init.c \
	gui_elem_init.c gui_destruct.c gui_debug.c gui_mouse.c \
	gui_elem_button.c gui_fonts.c gui_elem_input.c \
	gui_keydown.c gui_elem_block.c gui_elem_event_list.c \
	gui_events_win_map.c gui_draw_map.c \
	\
	gui_temp.c gui_map_func.c gui_draw_map_objects.c \
	gui_map_sprite.c gui_map_enemy.c gui_map_sector.c



GUI_OBJS_DIRECTORY = ./obj_gui/
GUI_OBJS_LIST = $(patsubst %.c, %.o, $(GUI_SRCS_LIST))
GUI_OBJS = $(addprefix $(GUI_OBJS_DIRECTORY), $(GUI_OBJS_LIST))



SDL_LIBS = $(addprefix $(DIRECTORY)/lib/, $(LIB_LIST))

LIBFT = libft/libft.a
LIBSDL_EXIST = 0
err = no

GREEN = \033[0;32m
RED = \033[0;31m
RESET = \033[0m

.PHONY: all clean fclean re

all: $(NAME) $(EDITOR_NAME) $(GUI_NAME)


$(NAME): $(LIBFT) $(OBJS_DIRECTORY) $(PARSER_OBJS_DIRECTORY) $(MAIN_OBJS_DIRECTORY) $(OBJS) $(PARSER_OBJS) $(MAIN_OBJS)
	@$(CC) $(FLAGS) $(LIBRARIES) $(INCLUDES) $(OBJS) $(MAIN_OBJS) $(PARSER_OBJS) -o $(NAME)
	@echo "\n$(NAME): $(GREEN)object files were created$(RESET)"
	@echo "$(NAME): $(GREEN)$(NAME) was created$(RESET)"

$(OBJS_DIRECTORY):
	@mkdir -p $(OBJS_DIRECTORY) 2>/dev/null || echo "" > /dev/null
	@echo "$(NAME): $(GREEN)$(OBJS_DIRECTORY) was created$(RESET)"

$(OBJS_DIRECTORY)%.o : $(SRCS_DIRECTORY)%.c $(HEADERS)
	@$(CC) $(FLAGS) -c $(INCLUDES) $< -o $@
	@echo "$(GREEN).$(RESET)\c"

$(PARSER_OBJS_DIRECTORY):
	@mkdir -p $(PARSER_OBJS_DIRECTORY) 2>/dev/null || echo "" > /dev/null
	@echo "$(NAME): $(GREEN)$(PARSER_OBJS_DIRECTORY) was created$(RESET)"

$(PARSER_OBJS_DIRECTORY)%.o : $(PARSER_DIRECTORY)%.c $(HEADERS)
	@$(CC) $(FLAGS) -c $(INCLUDES) $< -o $@
	@echo "$(GREEN).$(RESET)\c"

$(MAIN_OBJS_DIRECTORY):
	@mkdir -p $(MAIN_OBJS_DIRECTORY) 2>/dev/null || echo "" > /dev/null
	@echo "$(NAME): $(GREEN)$(MAIN_OBJS_DIRECTORY) was created$(RESET)"

$(MAIN_OBJS_DIRECTORY)%.o : $(MAIN_SRCS_DIRECTORY)%.c $(HEADERS)
	@$(CC) $(FLAGS) -c $(INCLUDES) $< -o $@
	@echo "$(GREEN).$(RESET)\c"



$(EDITOR_NAME): $(LIBFT) $(EDITOR_OBJS_DIRECTORY) $(EDITOR_OBJS) $(OBJS)
	#@echo $(EDITOR_OBJS) $(OBJS)
	@$(CC) $(FLAGS) $(LIBRARIES) $(INCLUDES) $(EDITOR_OBJS) $(OBJS) $(PARSER_OBJS) -o $(EDITOR_NAME)
	@echo "\n$(EDITOR_NAME): $(GREEN)object files were created$(RESET)"
	@echo "$(EDITOR_NAME): $(GREEN)$(EDITOR_NAME) was created$(RESET)"

$(EDITOR_OBJS_DIRECTORY):
	@mkdir -p $(EDITOR_OBJS_DIRECTORY) 2>/dev/null || echo "" > /dev/null
	@echo "$(EDITOR_NAME): $(GREEN)$(EDITOR_OBJS_DIRECTORY) was created$(RESET)"

$(EDITOR_OBJS_DIRECTORY)%.o : $(EDITOR_SRCS_DIRECTORY)%.c $(HEADERS)
	@$(CC) $(FLAGS) -c $(INCLUDES) $< -o $@
	@echo "$(GREEN).$(RESET)\c"



$(GUI_NAME): $(LIBFT) $(GUI_OBJS_DIRECTORY) $(GUI_OBJS) $(OBJS)
	#@echo $(GUI_OBJS) $(OBJS)
	@$(CC) $(FLAGS) $(LIBRARIES) $(INCLUDES) $(GUI_OBJS) $(OBJS) $(PARSER_OBJS) -o $(GUI_NAME)
	@echo "\n$(GUI_NAME): $(GREEN)object files were created$(RESET)"
	@echo "$(GUI_NAME): $(GREEN)$(GUI_NAME) was created$(RESET)"

$(GUI_OBJS_DIRECTORY):
	@mkdir -p $(GUI_OBJS_DIRECTORY) 2>/dev/null || echo "" > /dev/null
	@echo "$(GUI_NAME): $(GREEN)$(GUI_OBJS_DIRECTORY) was created$(RESET)"

$(GUI_OBJS_DIRECTORY)%.o : $(GUI_SRCS_DIRECTORY)%.c $(HEADERS)
	@$(CC) $(FLAGS) -c $(INCLUDES) $< -o $@
	@echo "$(GREEN).$(RESET)\c"



$(LIBFT):
	@echo "$(NAME): $(GREEN)Creating $(LIBFT)...$(RESET)"
	@$(MAKE) -sC $(LIBFT_DIRECTORY)

clean:
	@$(MAKE) -sC $(LIBFT_DIRECTORY) clean
	@rm -rf $(OBJS_DIRECTORY)
	@echo "$(NAME): $(RED)$(OBJS_DIRECTORY) was deleted$(RESET)"
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
