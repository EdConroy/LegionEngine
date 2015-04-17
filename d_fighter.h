#include "graphics.h"
#include "game.h"
#include "fighter.h"

void Draw(Game_T* game, SDL_Surface *buffer);
void SetAnimation(Sprite_T *sprite, animations anim);
void DrawHealthBar(Fighter* f, SDL_Surface *buffer, int x, int y);
void InitBck();
void Parallax(Sprite* fst, Sprite* scd, SDL_Surface* screen, int x, int y);
void FreeBck(Sprite* fst, Sprite* scd);