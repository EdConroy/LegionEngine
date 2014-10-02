#include "fighter.h"

typedef struct Projectile_T
{
	Fighter* owner;
	Sprite* s;
	SDL_Rect hitbox;
	float speed, life;
	int damage, x, y, last_x, last_y;
}Projectile;

void InitProjectile(Projectile* p, Fighter* own);
void DrawProjectile(Fighter* targ, Projectile* p, SDL_Rect hurtbox, SDL_Surface* buffer);
void FreeProjectile(Projectile* p);
