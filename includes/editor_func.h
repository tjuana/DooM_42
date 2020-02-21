/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   editor_func.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dorange- <dorange-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/26 16:22:17 by dorange-          #+#    #+#             */
/*   Updated: 2020/02/21 15:55:06 by dorange-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EDITOR_FUNC_H
# define EDITOR_FUNC_H

# include "doom.h"

/*
** **************************************************************************
**	editor/editor_debug.c
** **************************************************************************
*/
void				ft_print_sectors(t_list *ptr_list);

/*
** **************************************************************************
**	editor/editor_desctuct.c
** **************************************************************************
*/
void				ft_editor_desctuct_objects(t_wolf3d *w);
void				ft_editor_desctuct_vertexes(t_vector3 **vrtx, int count);
void				ft_editor_desctuct_sectors(t_wolf3d *w);
void				ft_editor_desctuct(t_wolf3d *w);

/*
** **************************************************************************
**	editor/editor_draw_map.c
** **************************************************************************
*/
void				ft_gui_draw_map_sectors(t_wolf3d *w, t_list *list);
void				ft_gui_draw_map(t_wolf3d *w, t_list *list);

/*
** **************************************************************************
**	editor/editor_draw_map_grid.c
** **************************************************************************
*/
void				ft_gui_draw_map_grid_limit_sector(t_wolf3d *w, \
						t_gui_elem *elem, t_vector3 v, int type);
void				ft_gui_draw_map_grid_limit_line(t_wolf3d *w, \
						t_gui_elem *elem, t_vector3 v);
void				ft_gui_draw_map_grid(t_wolf3d *w, \
						t_gui_elem *elem, int scale);

/*
** **************************************************************************
**	editor/editor_draw_map_objects.c
** **************************************************************************
*/
void				ft_gui_draw_player(t_wolf3d *w);
void				ft_gui_draw_sprites(t_wolf3d *w);
void				ft_gui_draw_enemies(t_wolf3d *w);

/*
** **************************************************************************
**	editor/editor_draw_map_sector.c
** **************************************************************************
*/
void				ft_gui_draw_map_sector_walls(t_wolf3d *w, t_sector *s);

/*
** **************************************************************************
**	editor/editor_draw_map_vertex.c
** **************************************************************************
*/
void				ft_gui_draw_point(t_wolf3d *w, t_gui_coord c, \
						int color);
int					ft_gui_draw_map_vertex(t_wolf3d *w, t_gui_coord c, \
						int status, int mode);
int					ft_gui_draw_map_vertex_line(t_wolf3d *w, \
						t_gui_coord c1);

/*
** **************************************************************************
**	editor/editor_event_win_map_click.c
** **************************************************************************
*/
void				ft_gui_mouse_click_map(t_wolf3d *w, \
						SDL_Event e, t_list *elem);
void				ft_gui_mousebuttondown_win_map(void *data, \
						SDL_Event e, t_list *dom, int type);
void				ft_gui_mousebuttonup_win_map(void *data, \
						SDL_Event e, t_list *dom, int type);

/*
** **************************************************************************
**	editor/editor_event_win_map_door.c
** **************************************************************************
*/
void				ft_gui_mousemotion_win_map_door(t_wolf3d *w, \
						SDL_Event e, t_list *dom);
void				ft_map_click_door(t_wolf3d *w, \
						SDL_Event e, t_list *elem);

/*
** **************************************************************************
**	editor/editor_event_win_map_move.c
** **************************************************************************
*/
void				ft_gui_mousemotion_win_map(void *data, SDL_Event e, \
						t_list *dom, int type);

/*
** **************************************************************************
**	editor/editor_event_win_map_set.c
** **************************************************************************
*/
void				ft_gui_event_set_sector(t_wolf3d *w, \
						SDL_Event e, t_list *elem);
void				ft_gui_event_set_player(t_wolf3d *w, \
						SDL_Event e, t_list *elem);
void				ft_gui_event_set_sprite(t_wolf3d *w, \
						SDL_Event e, t_list *elem);
void				ft_gui_event_set_enemy(t_wolf3d *w, \
						SDL_Event e, t_list *elem);

/*
** **************************************************************************
**	editor/editor_event_win_map_zoom.c
** **************************************************************************
*/
void				ft_gui_mousewheel_win_map(\
						void *data, SDL_Event e, t_list *dom, int type);

/*
** **************************************************************************
**	editor/editor_event_win_menu.c
** **************************************************************************
*/
void				ft_gui_mousebuttonup_win_menu_btnsector(\
						void *data, SDL_Event e, t_list *dom, int type);
void				ft_gui_mousebuttonup_win_menu_btnplayer(\
						void *data, SDL_Event e, t_list *dom, int type);
void				ft_gui_mousebuttonup_win_menu_btnsprite(\
						void *data, SDL_Event e, t_list *dom, int type);
void				ft_gui_mousebuttonup_win_menu_btnenemy(\
						void *data, SDL_Event e, t_list *dom, int type);
void				ft_gui_mousebuttonup_win_menu_btndoor(\
						void *data, SDL_Event e, t_list *dom, int type);

/*
** **************************************************************************
**	editor/editor_event_win_menu_save_map.c
** **************************************************************************
*/
void				ft_gui_mousebuttonup_win_menu_btnsavemap(void *data, \
						SDL_Event e, t_list *dom, int type);

/*
** **************************************************************************
**	editor/editor_event_win_setdoor.c
** **************************************************************************
*/
void				ft_gui_mousebuttonup_win_setdoor_btnsave(\
						void *data, SDL_Event e, t_list *dom, int type);
void				ft_gui_mousebuttonup_win_setdoor_btncancel(\
						void *data, SDL_Event e, t_list *dom, int type);

/*
** **************************************************************************
**	editor/editor_event_win_setenemy.c
** **************************************************************************
*/
void				ft_gui_mousebuttonup_win_setenemy_btnsaveplayer(\
						void *data, SDL_Event e, t_list *dom, int type);
void				ft_gui_mousebuttonup_win_setenemy_btncancel(\
						void *data, SDL_Event e, t_list *dom, int type);

/*
** **************************************************************************
**	editor/editor_event_win_setplayer.c
** **************************************************************************
*/
void				ft_gui_mousebuttonup_win_setplayer_btnsaveplayer(\
						void *data, SDL_Event e, t_list *dom, int type);
void				ft_gui_mousebuttonup_win_setplayer_btncancel(\
						void *data, SDL_Event e, t_list *dom, int type);

/*
** **************************************************************************
**	editor/editor_event_win_setsector.c
** **************************************************************************
*/
void				ft_gui_mousebuttonup_win_setsector_btnsavemap(\
						void *data, SDL_Event e, t_list *dom, int type);
void				ft_gui_mousebuttonup_win_setsector_btncancel(\
						void *data, SDL_Event e, t_list *dom, int type);

/*
** **************************************************************************
**	editor/editor_event_win_setsprite.c
** **************************************************************************
*/
void				ft_gui_mousebuttonup_win_setsprite_btnsaveplayer(\
						void *data, SDL_Event e, t_list *dom, int type);
void				ft_gui_mousebuttonup_win_setsprite_btncancel(\
						void *data, SDL_Event e, t_list *dom, int type);

/*
** **************************************************************************
**	editor/editor_gui_init.c
** **************************************************************************
*/
void				ft_gui_elem_set_map(t_list *list);
void				ft_gui_init_win_menu(t_list *head);
void				ft_gui_init_win_setsector(t_list *head);
void				ft_gui_init_win_setplayer(t_list *head);
void				ft_gui_init_win_setsprite(t_list *head);
void				ft_gui_init_win_setenemy(t_list *head);
void				ft_gui_init_win_setdoor(t_list *head);
void				ft_editor_gui_init_win_me(t_list *head);
void				ft_editor_gui_init(t_wolf3d *w);

/*
** **************************************************************************
**	editor/editor_init.c
** **************************************************************************
*/
void				ft_editor_init(t_wolf3d *w);

/*
** **************************************************************************
**	editor/editor_main.c
** **************************************************************************
*/
void				ft_editor_main(int c, char **v);

/*
** **************************************************************************
**	editor/editor_map_check.c
** **************************************************************************
*/
int					ft_check_point_in_sector_line_diameter(t_sector *s, \
						t_vector3 v, double d);
int					ft_search_point_in_sector_line_diameter(void *a, \
						t_vector3 v, double d);
int					ft_check_point_in_sector(t_wolf3d *w, t_sector *s, \
						t_vector3 v);
int					ft_search_point_in_sector(void *a, t_vector3 v);
int					ft_new_editor_map_check_area(t_wolf3d *w);
int					ft_compare_vertexes(t_vector3 v1, \
						t_vector3 v2);

/*
** **************************************************************************
**	editor/editor_map_door.c
** **************************************************************************
*/
void				ft_create_sector_door(t_wolf3d *w);
void				ft_change_door_vertex(t_wolf3d *w, t_vector3 v1, \
						t_vector3 v2, t_vector3 pos);
void				ft_set_new_vertex_for_sector(t_wolf3d *w, \
						t_sector *s, t_vector3 v);
int					ft_set_new_vertex_for_sector_list(void *a, \
						t_vector3 **v, int count);
void				ft_map_set_new_sector(t_wolf3d *w, t_sector *s);

/*
** **************************************************************************
**	editor/editor_map_enemy.c
** **************************************************************************
*/
void				ft_set_enemy(t_wolf3d *w, t_vector3 pos, int type);
void				ft_delete_enemy(t_wolf3d *w);

/*
** **************************************************************************
**	editor/editor_map_func.c
** **************************************************************************
*/
int					ft_map_check_straight_line(t_vector3 v1, t_vector3 v2);
t_vector3			ft_gui_map_coord_to_vertex(t_wolf3d *w, t_gui_coord c);
t_gui_coord			ft_gui_map_vertex_to_coord(t_wolf3d *w, t_vector3 v);
t_gui_coord			ft_gui_map_check_mouse(t_wolf3d *w, \
						t_gui_coord c, t_gui_elem *elem);
void				ft_help_check_mouse_ver(t_wolf3d *w, t_gui_coord c);
/*
** **************************************************************************
**	editor/editor_map_sector.c
** **************************************************************************
*/
void				ft_editor_turn_vertexes(t_sector *s, int numb);
void				ft_editor_check_turn_vertexes(t_wolf3d *w);
void				ft_editor_sector_create(t_wolf3d *w);
void				ft_delete_sector(t_wolf3d *w);
t_sector			*ft_editor_search_sector_by_id(t_wolf3d *w, \
						t_list *list, int i);

/*
** **************************************************************************
**	editor/editor_map_sector_neighbors.c
** **************************************************************************
*/
int					ft_editor_sector_search_neighbors_item(t_wolf3d *w, \
						t_sector *sector, t_vector3 *v1, t_vector3 *v2);
int					ft_editor_sector_search_neighbors(t_wolf3d *w, \
						t_sector *sector);
void				ft_editor_sectors_reset_neighbors(t_wolf3d *w);
int					ft_sectors_set_all_neighbors(t_wolf3d *w);
int					ft_check_neighbors_sector_vertex(t_sector *s, \
						t_vector3 v);

/*
** **************************************************************************
**	editor/editor_map_sector_vertex.c
** **************************************************************************
*/
void				ft_editor_sector_set_vertex(t_wolf3d *w, \
						t_sector *sector, t_vector3 v, int pos);
void				ft_editor_sector_del_last_vertex(t_wolf3d *w, \
						t_sector *sector);
void				ft_editor_delete_last_vertex(t_wolf3d *w);

/*
** **************************************************************************
**	editor/editor_map_sprite.c
** **************************************************************************
*/
void				ft_set_sprite(t_wolf3d *w, t_vector3 pos, int type);
void				ft_delete_sprite(t_wolf3d *w);

/*
** **************************************************************************
**	editor/editor_save_file.c
** **************************************************************************
*/
void				ft_allocate_int2darr(t_wolf3d *w);
void				ft_save_the_file(t_wolf3d *w);
void				ft_editor_take_vertex(t_wolf3d *w);
void				ft_count_origin_vertexes(t_wolf3d *w);
void				ft_create_list_of_vertexes(t_wolf3d *w);
void				ft_sector_num_vertex(t_list *ptr_list, \
						t_vector3 *vertexes);

/*
** **************************************************************************
**	editor/editor_save_file2.c
** **************************************************************************
*/
void				ft_print_to_file(t_wolf3d *w, int f);
void				ft_print_sectors_to_file(t_wolf3d *w, t_list *list);

/*
** **************************************************************************
**	editor/editor_save_file3.c
** **************************************************************************
*/
void				ft_player_string(t_wolf3d *w);
void				ft_save_neighbour(t_sector *sector, int fd);
void				ft_free_mf(t_wolf3d *w);

int					ft_check_sector_cross(t_wolf3d *w, t_sector *s, \
						t_vector3 v1, t_vector3 v2);
int					ft_search_sectors_cross(void *a, t_vector3 v1, \
						t_vector3 v2);
int					ft_new_editor_map_check_halfplanes(t_sector *s, \
						t_vector3 pos);

int					ft_check_point_in_sector_line_diameter(t_sector *s, \
						t_vector3 v, double d);
int					ft_search_point_in_sector_line_diameter(void *a, \
						t_vector3 v, double d);

void				ft_gui_elem_set_map(t_list *list);
void				ft_gui_init_win_menu_add_1(t_list *head);
void				ft_gui_init_win_menu_add(t_list *head);
void				ft_gui_init_win_menu_set(t_list *head);
void				ft_gui_init_win_menu_save(t_list *head);
void				ft_gui_init_win_menu(t_list *head);
void				ft_gui_init_win_setsector_1(t_list *head);
void				ft_gui_init_win_setsector(t_list *head);
void				ft_gui_init_win_setplayer(t_list *head);
void				ft_gui_init_win_setsprite(t_list *head);
void				ft_gui_init_win_setenemy(t_list *head);
void				ft_gui_init_win_setdoor(t_list *head);
void				ft_editor_gui_init_win_me_1(t_list *head);
void				ft_editor_gui_init_win_me(t_list *head);
void				ft_editor_gui_init(t_wolf3d *w);

int					ft_search_sector_in_sector(t_wolf3d *w, t_sector *s);

#endif
