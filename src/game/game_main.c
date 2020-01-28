//
// Created by Nymphadora Shelly on 04/12/2019.
//
#include "wolf3d.h"

typedef	struct		s_new_temp
{
    t_subevents se;
    t_new_mouse ms;
    t_new_player pl;
    t_new_others ot;
    t_new_sector_ops op;
	t_new_wolf3d w;
	t_new_weapons wpn;
	SDL_Surface *scr_surf;
	SDL_Window* window;
}					t_new_temp;

void player_init(t_new_player *pl, t_new_xy *v, int *angle, int *n)//init data for LoadData function
{
    //player = (struct player) { {v->x, v->y, 0}, {0,0,0}, *angle,0,0,0, n };
    pl->where.x = v->x;
    pl->where.y = v->y;
    pl->where.z = 0;
    pl->velocity.x = 0;
    pl->velocity.y = 0;
    pl->velocity.z = 0;
    pl->angle = *angle;
    pl->anglesin = 0;
    pl->anglecos = 0;
    pl->yaw = 0;
    pl->sector = *n;
	pl->ceil.nyceil = 0;
	pl->floor.nyfloor = 0;
	//If it's partially behind the player, clip it against player's view frustrum
	pl->nearz = 1e-4f;
	pl->farz = 5;
	pl->nearside = 1e-5f;
	pl->farside = 20.f;
	//pl->door_all = -1;
    pl->light = 1;
}

void LoadData(char *ag, t_new_player *pl)//this function reads a new map format
{

	ft_my_parse_map(pl, ag);
}

void UnloadData(t_new_player *pl)
{
    for(int a=0; a < pl->sectors_nb; ++a) free(pl->sectors[a].vertex);
    for(int a=0; a < pl->sectors_nb; ++a) free(pl->sectors[a].neighbors);
    free(pl->sectors);
    pl->sectors = NULL;
    pl->sectors_nb = 0;
}

//vline: Draw a vertical line on screen, with a different color pixel in top & bottom
void vline(int x, int y1,int y2, int top,int middle,int bottom, SDL_Surface* surface)
{
    int	*pix;

	pix = (int*)surface->pixels;
    y1 = clamp(y1, 0, WIN_H - 1);
    y2 = clamp(y2, 0, WIN_H - 1);
    if(y2 == y1)
        pix[y1* WIN_W + x] = middle;
    else if(y2 > y1)
    {
        pix[y1 * WIN_W + x] = top;
        //for(int y= y1 + 1; y < y2; ++y)
          //  pix[y * WIN_W + x] = middle;
        pix[y2 * WIN_W + x] = bottom;
    }
}
//MovePlayer(dx,dy): Moves the player by (dx,dy) in the map, and
//also updates their anglesin/anglecos/sector properties properly.

void MovePlayer(float dx, float dy, t_new_player *pl)
{
    float px = pl->where.x;
    float py = pl->where.y;
    //Check if this movement crosses one of this sector's edges
    //that have a neighboring sector on the other side.
    //Because the edge vertices of each sector are defined in
    //clockwise order, PointSide will always return -1 for a point
    //that is outside the sector and 0 or 1 for a point that is inside.
    
    const t_new_sector * const sect = &pl->sectors[pl->sector];
    const t_new_xy* const vert = sect->vertex;
    for(int s = 0; s < sect->npoints; ++s)
        if(sect->neighbors[s] >= 0
           && IntersectBox(px,py, px+dx,py+dy, vert[s+0].x, vert[s+0].y, vert[s+1].x, vert[s+1].y)
           && PointSide(px+dx, py+dy, vert[s+0].x, vert[s+0].y, vert[s+1].x, vert[s+1].y) < 0)
        {
            pl->sector = sect->neighbors[s];
            break;
        }

    pl->where.x += dx;
    pl->where.y += dy;
    pl->anglesin = sinf(pl->angle);
    pl->anglecos = cosf(pl->angle);
}

void	ft_game_redraw(void *d, t_list *dom)
{
	t_wolf3d	*w;
	t_new_temp	*data;

	w = (t_wolf3d*)d;
	data = w->new_data;

	data->pl.pixels = w->sdl->pixels;

	if (w->sdl->pixels)
		ft_bzero(w->sdl->pixels, 4 * WIN_W * WIN_H);
		// ft_memset((void*)pl.srf->pixels, 0x80, 4 * WIN_W * WIN_H);


	data->pl.txtx = 0;
	engine_begin(&data->pl);

		// printf("%d   %d\n", pl.floor.ya, pl.floor.yb);
		
	// data->scr_surf = SDL_GetWindowSurface(data->window);
	// SDL_BlitSurface(w.weapon_texture, ft_create_rect(15, 15, 0, 0), scr_surf, ft_create_rect(50, 50, WIN_W / 2, WIN_H / 2));
	if (data->pl.count_sprite == 10)// this for the event shoot
	{
		data->wpn.sprite_counter = 2;
		data->pl.count_sprite = 1;
	}
	// draw_pistol(&data->wpn,w->sdl->pixels);//draw gun
	// SDL_UpdateWindowSurface( data->window );

	//Vertical collision detection
	data->op.eyeheight = data->se.ducking ? DuckHeight : EyeHeight;
	data->se.ground = !data->se.falling;
	jumps(&data->se, &data->pl, &data->op, &data->ot);
	sectors_ops(&data->op, &data->pl, &data->ot, &data->se);
	if (!events(&data->se, &data->pl))
		return ;
	mouse_movement(&data->ms, &data->pl);//mouse aiming
	vectors_vel_dir(&data->pl, &data->se, &data->ot);
	MovePlayer(0, 0, &data->pl);//Refresh Vectors. start movement in 0//if this line is in vectors_vel_dir slomaet programmy whe is running, is needed here
		//door(&pl, &se);
}

// static void	ft_debug(t_new_player *pl)
// {
// 	int secnb = 0;
// 	int i = pl->sectors_nb;
// 	int point = 0;
// 	int neig = 0;
// 	int n = 0;
// 	int x = 0;
// 	int y = 0;
// 	while (secnb < i)
// 	{
// 		while (n < pl->sectors->npoints)
// 		{
// 			x = pl->sectors[secnb].vertex[point].x;
// 			y = pl->sectors[secnb].vertex[point].y;
// 			neig = pl->sectors[secnb].neighbors[point];
// 			n++;
// 			point++;
// 		}
		

		
// 		secnb++;
// 	}
	
// }

void	ft_game_init(t_new_temp *data, char *path)
{
	data->scr_surf = NULL;

	data->pl.sectors_nb = 0;
    data->se.quit = 0;
    LoadData(path, &data->pl);//load map and init typedef t_new_player data
	// ft_debug(&data->pl);
    //ft_init_anim(&w);//gun
    // SDL_Window* window = NULL;
	// data->window = NULL;
    if( SDL_Init( SDL_INIT_VIDEO ) < 0 )
        ft_error( "SDL could not initialize! SDL_Error: %s\n");
	// data->window = SDL_CreateWindow( "SDL Tutorial", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, WIN_W, WIN_H, SDL_WINDOW_SHOWN );

	// if(data->window == NULL)
		// ft_error("Window could not be created! SDL_Error: %s\n");

	// SDL_UpdateWindowSurface(data->window);
	SDL_ShowCursor(SDL_DISABLE);//NOT SHOW MOUSE CURSOR
	data->se.wsad[0] = 0;
	data->se.wsad[1] = 0;
	data->se.wsad[2] = 0;
	data->se.wsad[3] = 0;
	data->se.falling = 1;
	data->pl.count_sprite = 1;
	data->se.ground = 0;
	data->ot.moving = 0;
	data->se.ducking = 0;
	data->ms.yaw = 0;
	//load_weapons(&wpn);
	data->wpn.sprite_counter = 1;//if !1 is going to shoot
	load_pistol(&data->wpn);//load gun
	load_imgs(data->pl.img);
}

void	ft_game_gui_init_menu(t_list *head)
{
	t_gui_elem	*elem;

	elem = head->content;

	ft_gui_elem_init(&elem->child, "win_hud_live", (t_gui_coord){118, 18, 0}, \
	 	(t_gui_coord){144, 44, 0});
	// ft_gui_elem_init(&elem->child, "win_hud_live", (t_gui_coord){116, 16, 0}, \
	//  	(t_gui_coord){516, 416, 0});
	ft_gui_elem_set_color(elem->child, 0xffffff);
	ft_gui_elem_set_image(elem->child, "img/like.png");
	ft_gui_elem_set_parent(head, elem->child);

	ft_gui_elem_init(&elem->child, "win_hud_livescount", (t_gui_coord){150, 10, 0}, \
		(t_gui_coord){254, 50, 0});
	ft_gui_elem_set_color(elem->child, 0xffffff);
	ft_gui_elem_set_text(elem->child, "100", 16);
	ft_gui_elem_set_parent(head, elem->child);

	ft_gui_elem_init(&elem->child, "win_hud_pistol", (t_gui_coord){216, 16, 0}, \
	 	(t_gui_coord){248, 48, 0});
	// ft_gui_elem_init(&elem->child, "win_hud_live", (t_gui_coord){116, 16, 0}, \
	//  	(t_gui_coord){516, 416, 0});
	ft_gui_elem_set_color(elem->child, 0xffffff);
	ft_gui_elem_set_image(elem->child, "img/pistol.png");
	ft_gui_elem_set_parent(head, elem->child);

	ft_gui_elem_init(&elem->child, "win_hud_pistolcount", (t_gui_coord){250, 10, 0}, \
		(t_gui_coord){354, 50, 0});
	ft_gui_elem_set_color(elem->child, 0xffffff);
	ft_gui_elem_set_text(elem->child, "100", 16);
	ft_gui_elem_set_parent(head, elem->child);

	//pistol.png
}

void	ft_game_gui_init_hud(t_list *head)
{
	t_gui_elem	*elem;

	elem = head->content;
	ft_gui_elem_init(&elem->child, "win_hud", (t_gui_coord){100, 0, 0}, \
		(t_gui_coord){WIN_WIDTH - 100, 60, 0});
	// ft_gui_elem_set_color(elem->child, 0xbffd7c6e);
	ft_gui_elem_set_color(elem->child, 0xbf000000);
	ft_gui_elem_set_parent(head, elem->child);
	ft_game_gui_init_menu(elem->child);
}

void	ft_game_gui_init(t_wolf3d *w)
{
	// gui init element
	w->gui.redraw = 0;
	w->gui.redraw_elem = NULL;
	w->gui.search_elem = GUI_EVENT_OFF;
	w->gui.dom = NULL;
	w->gui.fonts = NULL;
	w->gui.mode = GUI_MD_ME;

	ft_gui_elem_init(&w->gui.dom, "win", (t_gui_coord){0, 0, 0}, \
		(t_gui_coord){WIN_WIDTH, WIN_HEIGHT, 0});
	ft_gui_elem_set_color(w->gui.dom, 0x000000);
	ft_gui_elem_set_redraw(w->gui.dom, ft_game_redraw);
	// ft_gui_elem_set_redraw_font(w->gui.dom, ft_game_render_font);
	ft_game_gui_init_hud(w->gui.dom);
}

int main(int ac, char **ag)
{
	t_wolf3d	w;
	t_new_temp	data;

	if (ac < 2 || ac > 2)
		ft_error("map error");

	ft_bzero(&data, sizeof(t_new_temp));

	ft_game_init(&data, ag[1]);

	w.sdl = sdl_init(w.sdl);
	ft_init_wolf(&w);
	ft_gui_init(&w);
	ft_game_gui_init(&w);

	w.new_data = &data;
	





	while (!data.se.quit)
	{
		ft_gui_redraw(&w);
		// if (data.pl.srf->pixels)
		// ft_bzero(data.pl.srf->pixels, 4 * WIN_W * WIN_H);
		// // ft_memset((void*)pl.srf->pixels, 0x80, 4 * WIN_W * WIN_H);


		// data.pl.txtx = 0;
		// engine_begin(&data.pl);

		// // printf("%d   %d\n", pl.floor.ya, pl.floor.yb);
		
		// data.scr_surf = SDL_GetWindowSurface(data.window);
		// // SDL_BlitSurface(w.weapon_texture, ft_create_rect(15, 15, 0, 0), scr_surf, ft_create_rect(50, 50, WIN_W / 2, WIN_H / 2));
		// if (data.pl.count_sprite == 10)// this for the event shoot
		// {
		// 	data.wpn.sprite_counter = 2;
		// 	data.pl.count_sprite = 1;
		// }
		// draw_pistol(&data.wpn,data.pl.srf);//draw gun
		// SDL_UpdateWindowSurface( data.window );

		// //Vertical collision detection
		// data.op.eyeheight = data.se.ducking ? DuckHeight : EyeHeight;
		// data.se.ground = !data.se.falling;
		// jumps(&data.se, &data.pl, &data.op, &data.ot);
		// sectors_ops(&data.op, &data.pl, &data.ot, &data.se);
		// if (!events(&data.se, &data.pl))
		// 	return(0);
		// mouse_movement(&data.ms, &data.pl);//mouse aiming
		// vectors_vel_dir(&data.pl, &data.se, &data.ot);
		// MovePlayer(0, 0, &data.pl);//Refresh Vectors. start movement in 0//if this line is in vectors_vel_dir slomaet programmy whe is running, is needed here
		// //door(&pl, &se);
	}



	
	UnloadData(&data.pl);
	SDL_Quit();
    return (0);
}
