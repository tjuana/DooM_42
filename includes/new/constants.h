#ifndef CONSTANTS_H
# define CONSTANTS_H
/* Define window size */
# define WIN_W 1280
# define WIN_H 720
/* Define various vision related constants */
#define EyeHeight  6    //Camera height from floor when standing
#define DuckHeight 2.5  //And when crouching
#define HeadMargin 1    //How much room there is above camera before the head hits the ceiling
#define KneeHeight 2    //How tall obstacles the player can simply walk over without jumping
#define hfov (0.73f*WIN_H)  //Affects the horizontal field of vision
#define vfov (.2f*WIN_H)    //Affects the vertical field of vision
#define MAX_QUEUE 32 //maximum number of pending portal renders (engine)
#define MAX_DOORS 100 //maximum number of doors

#include "wolf3d.h"
#endif
