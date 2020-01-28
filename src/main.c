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
    pl->nearside = 1e-5f;
	pl->farz = 5;
	pl->farside = 20;
	pl->door_all = -1;
	pl->but_all = -1;
	pl->lvl = NULL;
}

void UnloadData(t_player *pl)
{
	int i;

	i = -1;
	//better use free(pl);
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

int main(int ac, char **ag)
{
    t_sub_ev se;
    t_mouse ms;
    t_player pl;
    t_others ot;
    t_sect_ops op;
	t_wolf3d w;
    int ye;

    ye = 0;
	pl.sectors_nb = 0;
    w.weapon_texture = SDL_LoadBMP("Textures/pistol.bmp");
	if (ac < 2 || ac > 2)
    {
        printf("map error.\n");
        return (0);
    }
    se.quit = 0;
    load_file(ag[1], &pl);

    //ft_init_anim(&w);//gun
    if( SDL_Init( SDL_INIT_VIDEO ) < 0 )
    {
        printf( "SDL could not initialize! SDL_Error: %s\n", SDL_GetError() );
    }
    else
    {
        pl.win = SDL_CreateWindow( "SDL Tutorial", 10, 10, WIN_W, WIN_H, SDL_WINDOW_SHOWN);

        if( pl.win == NULL )
        {
            printf( "Window could not be created! SDL_Error: %s\n", SDL_GetError() );
        }
        else
            {
            pl.rend = SDL_CreateRenderer(pl.win,-1, SDL_RENDERER_ACCELERATED);
            SDL_SetRenderDrawColor(pl.rend, 0xFF, 0xFF, 0xFF, 0xFF);
			SDL_SetRelativeMouseMode(1);
            //SDL_ShowCursor(SDL_DISABLE);//NOT SHOW MOUSE CURSOR
            se.wsad[0] = 0;
            se.wsad[1] = 0;
            se.wsad[2] = 0;
            se.wsad[3] = 0;
            se.falling = 1;
            se.ground = 0;
            ot.moving = 0;
            se.ducking = 0;
            ms.yaw = 0;
			//pl.textures = load_textures(&pl);
            while (!se.quit)
            {
				pl.srf = SDL_CreateRGBSurface(0, WIN_W, WIN_H, 32, 0, 0, 0, 0);
				!pl.srf ? ft_putstr_fd(SDL_GetError(), 2) : 0;

				engine_begin(&pl);

				//texture_init(&pl);

				pl.texture = SDL_CreateTextureFromSurface(pl.rend, pl.srf);
				pl.texture == NULL ? ft_putstr_fd(SDL_GetError(), 2) : 0;
				SDL_RenderCopy(pl.rend, pl.texture, 0, 0) != 0 ? ft_putstr_fd(SDL_GetError(), 2) : 0;
				SDL_RenderPresent(pl.rend);
			    SDL_DestroyTexture(pl.texture);
				

				op.eye_h = se.ducking ? CROUCH_H : EYE_H;
				se.ground = !se.falling;
				events_jumps(&se, &pl, &op, &ot);
				motion_chk(&op, &pl, &ot, &se);
				motion_move_pl(0, 0, &pl);//Refresh Vectors. start movement in 0//if this line is in vectors_vel_dir slomaet programmy whe is running, is needed here
				events_mouse_move(&ms, &pl);//mouse aiming
				events_vel(&pl, &se, &ot);
				if (!events(&se, &pl))
					return(0);
				door(&pl, &se);
                ye++;
                if (ye > 3000)
                    exit(1);
			}
			
            UnloadData(&pl);
            SDL_Quit();
        }
    }
    return 0;
}
