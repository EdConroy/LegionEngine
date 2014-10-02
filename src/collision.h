#include "graphics.h"
#include "SDL.h"

int AABB(SDL_Rect attacker, SDL_Rect defender, SDL_Surface* screen);
SDL_Rect ReturnBox(SDL_Rect a, SDL_Rect d, int has_hit, SDL_Surface* screen);
