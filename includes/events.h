#ifndef EVENTS_H
#define EVENTS_H
# include "wolf3d.h"

typedef struct	s_sub_ev
{
    SDL_Event	ev;
    int			wsad[40];
    int			ground;
    int			falling;
    int			ducking;
    int			quit;
}				t_sub_ev;

typedef struct	s_mouse
{
    int		x;
    int		y;
    float	yaw;
}				t_mouse;

#endif
