#ifndef EVENTS_H
#define EVENTS_H
# include "wolf3d.h"

typedef struct	s_new_sub_ev
{
    SDL_Event	ev;
    int			wsad[10];
    int			ground;
    int			falling;
    int			ducking;
    int			quit;
}				t_new_sub_ev;

typedef struct	s_new_mouse
{
    int		x;
    int		y;
    float	yaw;
}				t_new_mouse;

#endif
