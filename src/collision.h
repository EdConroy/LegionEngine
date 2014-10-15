#include "graphics.h"
#include "SDL.h"

int AABB(SDL_Rect attacker, SDL_Rect defender); /* Axis Aligned Bounding Box collision system */
SDL_Rect ReturnBox(SDL_Rect a, SDL_Rect d, int has_hit, SDL_Surface* screen); /* Draws where the collision took place */

/*
Note: The current collision system for the game is using the entire sprite as the basis for the hitbox
in the game.  This is not indicitive of the final product but usefull for the proof of concept
*/
