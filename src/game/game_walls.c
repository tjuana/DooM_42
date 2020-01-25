//
// Created by Nymphadora Shelly on 20/01/2020.
//

#include "wolf3d.h"

void load_imgs(SDL_Surface *img[10])
{
    img[0]= IMG_Load("Textures/wall1.png");
    img[0]= SDL_ConvertSurfaceFormat(img[0], SDL_PIXELFORMAT_ARGB8888, 0);
    img[1]= IMG_Load("Textures/wood.png");
    img[1]= SDL_ConvertSurfaceFormat(img[1], SDL_PIXELFORMAT_ARGB8888, 0);
    img[2]= IMG_Load("Textures/wall2.png");
    img[2]= SDL_ConvertSurfaceFormat(img[2], SDL_PIXELFORMAT_ARGB8888, 0);


    img[3]= IMG_Load("Textures/wood.png");
    img[4]= IMG_Load("Textures/wood.png");
    img[5]= IMG_Load("Textures/wood.png");
    img[6]= IMG_Load("Textures/wood.png");
    img[7]= IMG_Load("Textures/wood.png");
    img[8]= IMG_Load("Textures/wood.png");
    img[9]= IMG_Load("Textures/wood.png");
}

//  a = pl->floor.ya; // первая координата
//  b = pl->ceil.cya; // top
//  c = pl->floor.yb; // вторая координата
//  d = 0;              // никогда не используется
//  f = pl->srf->w - 1; // ширина экрана - 1

// a = pl->floor.ya ;
// b = pl->ceil.cya; // top
// c = pl->floor.yb ;
// d = 0;
// f = pl->srf->w - 1;
// pl->y1 = pl->ceil.cya;
// pl->y2 = pl->ceil.cyb;

// a = pl->floor.ya;
// b = pl->ceil.cya;
// c = pl->floor.yb;
// d = 0;
// f = pl->srf->w - 1;
// pl->y1 = pl->ceil.cya;
// pl->y2 = pl->ceil.cnya;

t_new_scaler	scalar_create(int a, int b, int c, int d, int f)
{
    t_new_scaler	s;
    int         m;  // scale
    int         k;  // offset
    int         l;  // y offset

    m = c - a;
    k = f - d;
    l = b - 1 - a;

    // if (m < 0)
        // printf("M < 0!!!\n");

	if (m == 0)
		s.result = 0;
	else
    	s.result = d + (l) * (k) / m;
    s.bop = ((f < d) ^ (c < a)) ? -1 : 1; // bop = 1 всегда (в нашем случае)


    s.fd = abs(k); // const
    s.ca = abs(m);
	if (m == 0)
		s.cache = 0;
	else
    	s.cache = (int)((l) * abs(k)) % abs(m);

    s.a = a;
    s.b = b;
    s.c = c;
    s.d = d;
    s.f = f;

    // s.result = 0;

    return (s);
}

int			scr_nxt(t_new_scaler *i)
{
    // i->result++;

    // i->result += (i->f - i->d) / (i->c - i->a);

    i->cache += i->fd;
    i->result += i->bop * i->cache / i->ca;
    i->cache -= i->ca * (i->cache / i->ca); // Вернули на исходную позицию
    return (i->result);
}



//  a = pl->floor.ya ;
//  b = pl->ceil.cya;
//  c = pl->floor.yb ;
//  d = 0;
//  f = pl->srf->w - 1;

// t_new_scaler	scalar_create(int a, int b, int c, int d, int f)
// {
//     t_new_scaler	s;

//     s.result = d + (b - 1 - a) * (f - d) / (c - a);
//     s.bop = ((f < d) ^ (c < a)) ? -1 : 1;
//     s.fd = abs(f - d);
//     s.ca = abs(c - a);
//     s.cache = (int)((b - 1 - a) * abs(f - d)) % abs(c - a);
//     return (s);
// }

// typedef struct			s_new_scaler
// {
//     int					result;     a = pl->floor.ya ;
//     int					bop;        b = pl->ceil.cya;
//     int					fd;         c = pl->floor.yb ;
//     int					ca;         d = 0;
//     int					cache;      f = pl->srf->w - 1;
// }						t_new_scaler;



// -> to textures.c
int         ft_new_get_pixel(t_new_player *pl, SDL_Surface *sur, int x, int y)
{
    int		*pixel;
    int     pos;
    (void)x;
    (void)y;
    (void)pl;

    if (y > sur->h)
    {
		y %= sur->h;
        // return (0xff0000);
    }

    pos = (y * sur->w + x) % (sur->w * sur->h);
    // pos = (int)(pl->intery * sur->w + pl->interx) % (sur->w * sur->h); (просто растянет на экран)
    // pos = (int)(y * sur->w + pl->interx) % (sur->w * sur->h);

    pixel = sur->pixels + pos * sur->format->BytesPerPixel;


    return (*pixel);
}

// pl->txtx = (int)((pl->u0 * ((pl->x2 - pl->interx) * pl->t2.y) + pl->u1 * ((pl->interx - pl->x1) * pl->t1.y)) / ((pl->x2 - pl->interx) * pl->t2.y + (pl->interx - pl->x1) * pl->t1.y));


void vline_walls(int x, t_new_player *pl, t_new_scaler ty, int n)
{
    unsigned	txty;
    // int			y;
    int         *pix;
    (void)n;
    (void)ty;
    double      c; // scale coeff.
    (void)c;

    pl->intery = pl->y1;
    pl->origin_y1_coord = pl->y1; // привязка идёт не к высоте :(
    pix = (int*)pl->pixels;
    // pl->wall_height_c = 1;
	// pl->wall_height_c = pl->sect->ceil; // ?
	pl->wall_height = abs(pl->y2 - pl->y1); // ?
    // нужно привязаться к реальной высоте стены?

    if (pl->wall_height == 0)
        return ;

    // Неправильный коэффициент масштабирования
    // c = (pl->sect->ceil * WIN_W) / pl->wall_height * 10;
    // c = pl->cl * WIN_W / 100; (не подходит)
    txty = 0;

    // pl->cl * WIN_W

    // pl->sect->ceil

    // double a, c;
    // a = pl->floor.ya;
    // c = pl->floor.yb;

    // pl->y2 = pl->ceil.cyb;

    // pl->floor.yb - pl->floor.ya // вся высота стены в системе координат

    // printf("@   pl->y1: %d   pl->y2: %d\n", pl->y1, pl->y2);
    // pl->y1 = clamp(pl->y1, 0, WIN_H - 1);
    // pl->y2 = clamp(pl->y2, 0, WIN_H - 1);
    pix += pl->y1 * WIN_W + x;
    while (pl->intery <= pl->y2)
    {
        ++pl->intery;
        // txty = ((pl->intery - pl->y1) / pl->wall_height_c) * WIN_W;
        txty = scr_nxt(&ty); // Меняется от итерации к итерации

        //pl->cl

        // txty += c;

        // txty = c * (pl->intery - pl->origin_y1_coord) / pl->wall_height;
        // printf("txty: %d   pl->intery: %d\n", txty, pl->intery);

        // coeff. -> коэффициент масштабирования


        // txty = 1308;
        // txty = pl->wall_height;
        // txty = (pl->floor.yb - pl->floor.ya) / 10000;
        // if (pl->wall_height != 0.0)
            // txty = pl->intery / pl->wall_height;
        // *pix = 0xff0000;
        // *pix = color_transoform(\
        //     ft_get_pixel(\
        //        pl->img[n], \
        //        pl->txtx % pl->img[n]->w, \
        //        txty % pl->img[n]->h), \
        //     pl->light\
        // );
        *pix = color_transoform(\
            ft_new_get_pixel(\
                pl, \
                pl->img[n], \
                pl->txtx / 5,// % pl->img[n]->w,
                txty / 5 //% pl->img[n]->h
            ), \
            pl->light \
        );
        pix += WIN_W; // шаг вниз
        
    }
}
