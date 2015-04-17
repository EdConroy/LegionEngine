#ifndef _COLLISION_
#define _COLLISION_

#include <time.h>
#include "graphics.h"
#include "fighter.h"
#include "SDL.h"

int AABB(SDL_Rect attacker, SDL_Rect defender); /* Axis Aligned Bounding Box collision system */
SDL_Rect ReturnBox(SDL_Rect a, SDL_Rect d, int has_hit, SDL_Surface* screen); /* Draws where the collision took place */
void CalculateStun(Fighter* f1, int hit);

/*
Note: The current collision system for the game is using the entire sprite as the basis for the hitbox
in the game.  This is not indicitive of the final product but usefull for the proof of concept
*/
#endif