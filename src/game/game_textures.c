//
// Created by Nymphadora Shelly on 17/01/2020.
//

#include "wolf3d.h"
/*void	render_walls2(t_draw_screen_calc *d, t_new_player plr)
{
    d->i->y1a = H / 2 - (int)(YAW(d->f->yceil, d->f->tz1) * d->f->yscale1);
    d->i->y1b = H / 2 - (int)(YAW(d->f->yfloor, d->f->tz1) * d->f->yscale1);
    d->i->y2a = H / 2 - (int)(YAW(d->f->yceil, d->f->tz2) * d->f->yscale2);
    d->i->y2b = H / 2 - (int)(YAW(d->f->yfloor, d->f->tz2) * d->f->yscale2);
    d->i->ny1a = H / 2 - (int)(YAW(d->f->nyceil, d->f->tz1) * d->f->yscale1);
    d->i->ny1b = H / 2 - (int)(YAW(d->f->nyfloor, d->f->tz1) * d->f->yscale1);
    d->i->ny2a = H / 2 - (int)(YAW(d->f->nyceil, d->f->tz2) * d->f->yscale2);
    d->i->ny2b = H / 2 - (int)(YAW(d->f->nyfloor, d->f->tz2) * d->f->yscale2);
    d->i->beginx = MAX(d->i->x1, d->s->now.sx1);
    d->i->endx = MIN(d->i->x2, d->s->now.sx2);
    d->it->x = d->i->beginx;
}

void	render_walls(t_draw_screen_calc *ds, t_new_sector *sector, t_new_player plr)
{
    ds->f->yceil = ds->s->sect->ceil - plr.where.z;
    ds->f->yfloor = ds->s->sect->floor - plr.where.z;
    ds->i->neightbor = ds->s->sect->neighbors[ds->it->s];
    ds->f->nyceil = 0;
    ds->f->nyfloor = 0;
    if (ds->i->neightbor >= 0)
    {
        ds->f->nyceil = sector[ds->i->neightbor].ceil - plr.where.z;
        ds->f->nyfloor = sector[ds->i->neightbor].floor - plr.where.z;
    }
    render_walls2(ds, plr);
}

void	main_draw2(t_game *g, t_draw_screen_calc ds)
{
    while (ds.it->s < ds.s->sect->npoints)
    {
        rotate_view(&ds, g);
        if (ds.f->tz1 <= 0 && ds.f->tz2 <= 0)
        {
            ds.it->s++;
            continue;
        }
        ds.i->u0 = 0;
        ds.i->u1 = 600;
        if (ds.f->tz1 <= 0 || ds.f->tz2 <= 0)
            find_intersect(&ds);
        perspective(&ds);
        if (ds.i->x1 >= ds.i->x2 || ds.i->x2 < ds.s->now.sx1 ||
            ds.i->x1 > ds.s->now.sx2)
        {
            ds.it->s++;
            continue;
        }
        rsw(&ds, g->sectors, ds.queue, g);
        ds.it->s++;
    }
    ++ds.i->renderedsectors[ds.s->now.sectorno];
    ds.it->start_do == 1 ? ds.it->start_do = 0 : 0;
}

int		main_draw1(t_game *g, t_draw_screen_calc ds)
{
    pick_sector_slice(&ds);
    if ((unsigned)ds.i->renderedsectors[ds.s->now.sectorno] & 0x21u)
        return (0);
    ++ds.i->renderedsectors[ds.s->now.sectorno];
    ds.s->sect = &g->sectors[ds.s->now.sectorno];
    ds.it->s = 0;
    return (1);
}

void	main_draw(t_game *g, t_draw_screen_calc ds)
{
    t_tmp_iter			it;
    t_item				qe[MAX_QUE];
    t_calc_tmp_int		i;
    t_calc_tmp_float	f;
    t_calc_tmp_struct	s;

    ds.i = &i;
    ds.f = &f;
    ds.s = &s;
    ds.it = &it;
    ds.queue = qe;
    ds.s->head = ds.queue;
    ds.s->tail = ds.queue;
    init_draw(&ds, g->plr);
    if (++ds.s->head == ds.queue + MAX_QUE)
        ds.s->head = ds.queue;
    while (ds.s->head != ds.s->tail || ds.it->start_do)
    {
        if (main_draw1(g, ds) == 0)
            continue;
        main_draw2(g, ds);
    }
    free(ds.i->renderedsectors);
}

void	render_sector_walls1(t_draw_screen_calc *ds,
                             t_new_sector *sector, t_game *g)
{
    render_walls(ds, sector, g->plr);
    ds->s->ya_int = scalar_create((t_scri) {.a = ds->i->x1, .b = ds->i->beginx,
            .c = ds->i->x2,
            .d = ds->i->y1a, .f = ds->i->y2a});
    ds->s->yb_int = scalar_create((t_scri) {.a = ds->i->x1, .b = ds->i->beginx,
            .c = ds->i->x2,
            .d = ds->i->y1b, .f = ds->i->y2b});
    ds->s->nya_int = scalar_create((t_scri) {.a = ds->i->x1, .b = ds->i->beginx,
            .c = ds->i->x2,
            .d = ds->i->ny1a, .f = ds->i->ny2a});
    ds->s->nyb_int = scalar_create((t_scri) {.a = ds->i->x1, .b = ds->i->beginx,
            .c = ds->i->x2,
            .d = ds->i->ny1b, .f = ds->i->ny2b});
    ds->it->x = ds->i->beginx;
}

void	rsw(t_draw_screen_calc *ds, t_new_sector *sector,
            t_item *queue, t_game *g)
{
    render_sector_walls1(ds, sector, g);//calculos necesarios
    while (ds->it->x <= ds->i->endx)
    {
        ds->i->txtx = (int)((ds->i->u0 * ((ds->i->x2 - ds->it->x) * ds->f->tz2)
                             + ds->i->u1 * ((ds->it->x - ds->i->x1) * ds->f->tz1))
                            / ((ds->i->x2 - ds->it->x) * ds->f->tz2
                               + (ds->it->x - ds->i->x1) * ds->f->tz1));
        render_sector(ds, &g->plr, g);
        ds->it->x++;
    }
    if (ds->i->neightbor >= 0 && ds->i->endx >= ds->i->beginx
        && (ds->s->head + MAX_QUE + 1 - ds->s->tail) % MAX_QUE)
    {
        *ds->s->head = (t_item) {ds->i->neightbor, ds->i->beginx, ds->i->endx};
        if (++ds->s->head == queue + MAX_QUE)
            ds->s->head = queue;
    }
}

float		percentage(int start, int end, int curr)
{
    float place;
    float dist;

    place = curr - start;
    dist = end - start;
    return ((dist == 0) ? 1.0 : (place / dist));
}

void	ceil_floor_light(t_draw_screen_calc *ds, t_new_player *p, t_game *g)// aqui se realizan algunos calculos importantes en ds
{
    ds->i->z = (int)roundf(((ds->it->x - ds->i->x1) * (ds->f->tz2 - ds->f->tz1)
                            / (ds->i->x2 - ds->i->x1) + ds->f->tz1) * p->light);
    ds->i->z = (ds->i->z > 250) ? (250) : (ds->i->z);
    ds->f->perc_light = percentage(250, 0, ds->i->z);
    ds->i->ya = scr_nxt(&ds->s->ya_int);
    ds->i->yb = scr_nxt(&ds->s->yb_int);
    ds->i->cya = CLAMP(ds->i->ya, ds->i->y_top[ds->it->x],
                       ds->i->y_bottom[ds->it->x]);//clamp es una funcion
    ds->i->cyb = CLAMP(ds->i->yb, ds->i->y_top[ds->it->x],
                       ds->i->y_bottom[ds->it->x]);
    render(CEIL, (t_tex_i){.ceil = 1, .floor = 4}, p, ds, g);
}

void	render_ceil_floor(t_draw_screen_calc *ds, t_new_player *p, t_game *g)//is in render_sector, se puede no usar si es para el techo y para el piso
{
    ds->i->nya = scr_nxt(&ds->s->nya_int);
    ds->i->nyb = scr_nxt(&ds->s->nyb_int);
    ds->i->cnya = CLAMP(ds->i->nya, ds->i->y_top[ds->it->x],
                        ds->i->y_bottom[ds->it->x]);
    ds->i->cnyb = CLAMP(ds->i->nyb, ds->i->y_top[ds->it->x],
                        ds->i->y_bottom[ds->it->x]);
    render(TOP_PORTAL_WALL, (t_tex_i){.wall = 5}, p, ds, g);
    ds->i->y_top[ds->it->x] = CLAMP(MAX(ds->i->cya, ds->i->cnya),
                                    ds->i->y_top[ds->it->x], H - 1);
    render(BOTTOM_PORTAL_WALL, (t_tex_i){.wall = 5}, p, ds, g);
    ds->i->y_bottom[ds->it->x] = CLAMP(MIN(ds->i->cyb, ds->i->cnyb),
                                       0, ds->i->y_bottom[ds->it->x]);
}

void	render_sector(t_draw_screen_calc *ds, t_new_player *p, t_game *g)
{
    ceil_floor_light(ds, p, g);//calculas para el techo y piso, y usa render(CEIL...

     * if (ds->i->neightbor >= 0)
        render_ceil_floor(ds, p, g);
    else
        render(FULL_WALL, (t_tex_i){.wall = 5}, p, ds, g);

}



void		render( t_tex_i tex_i, t_new_player *p, t_draw_screen_calc *ds, t_game *g)
{
    ds->i->tn = tex_i.wall;
    if (dm == TOP_PORTAL_WALL)
    {
        render_var(ds->i->cya, ds->i->cnya - 1, ds);
        vertl(scalar_create((t_scri) {.a = ds->i->ya, .b = ds->i->
                cya, .c = ds->i->yb, .d = 0, .f = p->sdl->textures->
                arr_tex[tex_i.wall]->w - 1}), ds->i->txtx, p, ds);
    }
    else if (dm == BOTTOM_PORTAL_WALL)
    {
        render_var(ds->i->cnyb + 1, ds->i->cyb, ds);
        vertl(scalar_create((t_scri) {.a = ds->i->ya, .b = ds->i->
                cnyb + 1, .c = ds->i->yb, .d = 0, .f = p->sdl->textures->
                arr_tex[tex_i.wall]->w - 1}), ds->i->txtx, p, ds);
    }
    else if (dm == FULL_WALL)
    {
        render_var(ds->i->cya, ds->i->cyb, ds);
        vertl(scalar_create((t_scri) {.a = ds->i->ya, .b = ds->i->
                cya, .c = ds->i->yb, .d = 0, .f = p->sdl->
                textures->arr_tex[tex_i.wall]->w - 1}), ds->i->txtx, p, ds);
    }
}

*/

int			ft_get_pixel(SDL_Surface *sur, int x, int y)//no da el pixel que vamos a usar
{
    int		*pixel;

    pixel = sur->pixels + y * sur->pitch + x * sur->format->BytesPerPixel;
    return (*pixel);
}

int			color_transoform(int color, float percent)
{
    int		rgb[4];

    rgb[0] = ((color >> 0) & 0xFF) * percent;
    rgb[1] = ((color >> 8) & 0xFF) * percent;
    rgb[2] = ((color >> 16) & 0xFF) * percent;
    rgb[3] = (color >> 24 & 0XFF);
    color = ((rgb[3] << 24) |(rgb[2] << 16) | (rgb[1] << 8) | rgb[0] << 0);
    return (color);
}


void		pix1(t_new_textures *t, t_new_player *pl, int n)//guarda la textura gun
{
    unsigned int *pix;

    pix = pl->pixels;
    pix[t->y * WIN_W + t->x] = color_transoform(ft_get_pixel(pl->img[n], t->txtx1 % pl->img[n]->w, t->txtz % pl->img[n]->h), pl->light);
    //vline(t->x, pl->y_top[t->x], pl->ceil.cya - 1, 0xffffff, 0x222222 , 0xff0000, pl->srf);
    //vline(t->x, pl->ceil.cyb + 1, pl->y_bot[t->x], 0xffffff, 0x222222 , 0xff0000, pl->srf);
}
