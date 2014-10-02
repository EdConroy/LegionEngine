#include "projectile.h"
#include "collision.h"

void InitProjectile(Projectile* p, Fighter* own)
{
	p->s = LoadSprite("images/projectile.png",50,50);
	p->hitbox.x = own->x + 10;
	p->hitbox.y = own->y;
	p->hitbox.w = 50;
	p->hitbox.h = 50;
	p->speed = 10;
	p->damage = 40;
	p->owner = own;
}
void DrawProjectile(Fighter* targ, Projectile* p, SDL_Rect hurtbox, SDL_Surface* buffer)
{
	int has_hit = 0;
	DrawSprite(p->s,buffer,(p->x + p->speed), p->y,0);
	AABB(p->hitbox,hurtbox,buffer);
	if(has_hit == 1)
	{
		targ->health-=150;
		FreeProjectile(p);
	}
}
void FreeProjectile(Projectile* p)
{
	FreeSprite(p->s);
	p->s = NULL;
	p->hitbox.x = NULL;
	p->hitbox.y = NULL;
	p->hitbox.w = NULL;
	p->hitbox.h = NULL;
	p->speed = NULL;
	p->damage = NULL;
	p->owner = NULL;
}
