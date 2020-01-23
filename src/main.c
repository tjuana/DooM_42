//
// Created by Nymphadora Shelly on 04/12/2019.
//
#include "wolf3d.h"

void player_init(t_player *pl, t_xy *v, float *angle, int *n)//init data for LoadData function
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
	pl->door_all = -1;
	pl->but_all = -1;
}

void UnloadData(t_player *pl)
{
	int i;

	i = -1;
	while (++i < pl->sectors_nb)
		free(pl->sectors[i].vertex);
	i == 2 ? i = 3 : i;
	while (++i < pl->sectors_nb)
		free(pl->sectors[i].neighbors);
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
        for(int y= y1 + 1; y < y2; ++y)
            pix[y * WIN_W + x] = middle;
        pix[y2 * WIN_W + x] = bottom;
    }
}
//MovePlayer(dx,dy): Moves the player by (dx,dy) in the map, and
//also updates their anglesin/anglecos/sector properties properly.

void MovePlayer(float dx, float dy, t_player *pl)
{
    float px = pl->where.x;
    float py = pl->where.y;
    //Check if this movement crosses one of this sector's edges
    //that have a neighboring sector on the other side.
    //Because the edge vertices of each sector are defined in
    //clockwise order, PointSide will always return -1 for a point
    //that is outside the sector and 0 or 1 for a point that is inside.
    
    const t_sector * const sect = &pl->sectors[pl->sector];
    const t_xy* const vert = sect->vertex;
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

int main(int ac, char **ag)
{
    t_subevents se;
    t_mouse ms;
    t_player pl;
    t_others ot;
    t_sector_ops op;
	t_wolf3d w;
	//SDL_Texture *texture = NULL;
	SDL_Surface *scr_surf = NULL;

    SDL_Renderer *renderer = NULL;
	pl.sectors_nb = 0;
    w.weapon_texture = SDL_LoadBMP("Textures/pistol.bmp");
    if (ac < 2 || ac > 2)
    {
        printf("map error");
        return (0);
    }
    se.quit = 0;
    load_file(ag[1], &pl);
	//LoadData(ag[1], &pl);//load map and init typedef t_player data
    //ft_init_anim(&w);//gun
    SDL_Window* window = NULL;
    if( SDL_Init( SDL_INIT_VIDEO ) < 0 )
    {
        printf( "SDL could not initialize! SDL_Error: %s\n", SDL_GetError() );
    }
    else
    {
        window = SDL_CreateWindow( "SDL Tutorial", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, WIN_W, WIN_H, SDL_WINDOW_SHOWN );

        if( window == NULL )
        {
            printf( "Window could not be created! SDL_Error: %s\n", SDL_GetError() );
        }
        else
            {
            pl.srf = SDL_GetWindowSurface(window);
			
            SDL_UpdateWindowSurface( window );
            renderer = SDL_CreateRenderer(window,-1, SDL_RENDERER_ACCELERATED );
			pl.win = window;
			pl.rend = renderer;
            SDL_SetRenderDrawColor( renderer, 0xFF, 0xFF, 0xFF, 0xFF );
            SDL_ShowCursor(SDL_DISABLE);//NOT SHOW MOUSE CURSOR
            se.wsad[0] = 0;
            se.wsad[1] = 0;
            se.wsad[2] = 0;
            se.wsad[3] = 0;
            se.falling = 1;
            se.ground = 0;
            ot.moving = 0;
            se.ducking = 0;
            ms.yaw = 0;
            while (!se.quit)
            {

                //texture = SDL_CreateTextureFromSurface(renderer, surface);

                //SDL_FreeSurface(surface);
                //Clear screen
                //SDL_RenderClear(renderer);
                //Render texture to screen
                //SDL_RenderCopy(renderer, texture, NULL, NULL );
                //Update screen
                //for( int i = 0; i < H; i += 1 )
               // {
                //    SDL_RenderDrawPoint( renderer, W / 2, i );
                //}
                //SDL_SetRenderDrawColor( renderer, 0xFF, 0xFF, 0x00, 0xFF );
                //SDL_RenderPresent(renderer);
                
				//SDL_RenderCopy(renderer, NULL, NULL, NULL);
				engine_begin(&pl);
				
                //ft_animation_play(&w);
                //ft_draw_animation(&w, surface);
				//ft_create_rect(WIN_W / 2, WIN_H / 2, 100, 100)

				//SDL_RenderCopy(renderer, SDL_CreateTextureFromSurface(renderer, pl.srf), NULL, NULL);
				//SDL_RenderPresent(renderer);
				scr_surf = SDL_GetWindowSurface(window);
				SDL_RenderClear(renderer);
				SDL_BlitSurface(w.weapon_texture, ft_create_rect(15, 15, 0, 0), scr_surf, ft_create_rect(50, 50, WIN_W / 2, WIN_H / 2));

				//SDL_FreeSurface(scr_surf);
                SDL_UpdateWindowSurface( window );
				

                //Vertical collision detection
                op.eyeheight = se.ducking ? DuckHeight : EYEHEIGHT;
                se.ground = !se.falling;
                jumps(&se, &pl, &op, &ot);
                sectors_ops(&op, &pl, &ot, &se);
                if (!events(&se, &pl))
                    return(0);
                mouse_movement(&ms, &pl);//mouse aiming
                vectors_vel_dir(&pl, &se, &ot);
                MovePlayer(0, 0, &pl);//Refresh Vectors. start movement in 0//if this line is in vectors_vel_dir slomaet programmy whe is running, is needed here
            	door(&pl, &se);
			}
			
            UnloadData(&pl);
            SDL_Quit();
        }
    }
    return 0;
}
