#ifndef EVENTS_H
#define EVENTS_H
# include "wolf3d.h"

typedef struct	s_subevents
{
    SDL_Event	ev;
    int			wsad[40];
    int			ground;
    int			falling;
    int			ducking;
    int			quit;
}				t_subevents;

typedef struct	s_new_mouse
{
    int		x;
    int		y;
    float	yaw;
}				t_new_mouse;

#endif
