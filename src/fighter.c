#include "collision.h"
#include "fighter.h"

Fighter Fighters[MAX_FIGHTERS];

struct 
{
	int frame;
	int player2_frame;
}F_Sprite;

void InitFighterList()
{
	int i;
	for(i=0; i<MAX_FIGHTERS;++i)
	{
		Fighters[i].health = NULL;
		Fighters[i].x = NULL;
		Fighters[i].y = NULL;
		Fighters[i].walk_speed = NULL;
		Fighters[i].walk_acc = NULL;
		Fighters[i].jump_speed = NULL;
		Fighters[i].used = 0;
	}
}

Fighter * getFighter(int player)
{
	if (player >= MAX_FIGHTERS)return NULL;
	return &Fighters[player];
}

void InitFighterSprite()
{
	F_Sprite.frame = 0;
	F_Sprite.player2_frame = 0;
}
void InitCombatant(Fighter* f)
{
	f->health = 150;
	f->x = 110;
	f->y = 410;
	f->walk_acc = 5;
	f->walk_speed = 10;
	f->jump_speed = 50;
	f->hitbox.x = 110;
	f->hitbox.y = 410;
	f->hitbox.w = 180;
	f->hitbox.h = 150;
	f->is_grounded = 1;
}
void InitCombatant2(Fighter* f)
{
	f->health = 150;
	f->x = 310;
	f->y = 410;
	f->walk_speed = 10;
	f->walk_acc = 5;
	f->jump_speed = 50;
	f->hitbox.x = 310;
	f->hitbox.y = 410;
	f->hitbox.w = 180;
	f->hitbox.h = 150;
	f->is_grounded = 1;
}
void Block(Fighter* attacker, Fighter* defender, SDL_Surface *buffer)
{
	int been_hit = 0;
	been_hit = AABB(attacker->hitbox,defender->hitbox,buffer);
	if(been_hit == 1)
		defender->health +=10;
}
void FighterController(Fighter* f1, Fighter* f2, SDL_Surface *buffer, Uint8* keys)
{
	int keyn, frame_count, player2_fc, i = 0;
	f1->sprite = LoadSprite("images/StriderIdle.png",114,92);
	keys = SDL_GetKeyState(&keyn);
	if(keys[SDLK_RIGHT])
	{
		f1->sprite = LoadSprite("images/StriderWalk.png",114,101);
		DrawSprite(f1->sprite,buffer,f1->x + f1->walk_acc, f1->y,F_Sprite.frame);
		f1->last_x = f1->x;
		f1->x = f1->last_x + f1->walk_acc;
		f1->hitbox.x = f1->x;
		frame_count = 10;
	}
	else if(keys[SDLK_DOWN])
	{
		f1->sprite = LoadSprite("images/StriderCrouch.png",108,68);
		DrawSprite(f1->sprite,buffer,f1->x,f1->y, F_Sprite.frame);
		frame_count = 6;
	}
	else if(keys[SDLK_LEFT])
	{
		f1->sprite = LoadSprite("images/StriderWalk.png",114,101);
		DrawSprite(f1->sprite,buffer,f1->x - f1->walk_acc,f1->y,F_Sprite.frame);
		f1->last_x = f1->x;
		f1->x = f1->last_x - f1->walk_acc;
		f1->hitbox.x = f1->x;
		frame_count = 10;
	}
	else if(keys[SDLK_x])
	{
		int has_hit = 0;
		f1->sprite = LoadSprite("images/StriderLightAttack.png",179,138);
		DrawSprite(f1->sprite,buffer,f1->x, f1->y,F_Sprite.frame);
		has_hit = AABB(f1->hitbox,f2->hitbox,buffer);
		if(has_hit == 1)
		{
			f2->health -= 15;
		}
		frame_count = 9;
	}
	else if(keys[SDLK_c])
	{
		int has_hit = 0;
		f1->sprite = LoadSprite("images/StriderMediumAttack.png",198,140);
		DrawSprite(f1->sprite,buffer,f1->x, f1->y,F_Sprite.frame);
		has_hit = AABB(f1->hitbox,f2->hitbox,buffer);
		if(has_hit == 1)
		{
			f2->health -= 25;
		}
		frame_count = 7;
	}
	else if(keys[SDLK_v])
	{
		int has_hit = 0;
		f1->sprite = LoadSprite("images/StriderHeavyAttack.png",206,140);
		DrawSprite(f1->sprite,buffer,f1->x, f1->y,F_Sprite.frame);
		has_hit = AABB(f1->hitbox,f2->hitbox,buffer);
		if(has_hit == 1)
		{
			f2->health -= 50;
		}
		frame_count = 13;
	}
	else if(keys[SDLK_b])
	{
		int has_hit = 0;
		f1->sprite = LoadSprite("images/StriderLauncherAttack.png",198,162);
		DrawSprite(f1->sprite,buffer,f1->x, f1->y,F_Sprite.frame);
		has_hit = AABB(f1->hitbox,f2->hitbox,buffer);
		if(has_hit == 1)
		{
			f2->health -= 150;
		}
		frame_count = 8;
	}
	/*
	else if(keys[SDLK_n])
	{
		Projectile *p;
		InitProjectile(p,f1);
		SDL_Rect test;
		test.x = 210;
		test.y = 410;
		test.w = 150;
		test.h = 180;
		DrawProjectile(f1,p,test,buffer);
	}
	*/
	else if(keys[SDLK_UP])
	{
		f1->sprite = LoadSprite("images/StriderJump.png",183,138);
		DrawSprite(f1->sprite,buffer,f1->x, f1->y - f1->jump_speed,F_Sprite.frame);
		f1->last_y = f1->y;
		f1->y = f1->last_y - f1->jump_speed;
		//f1->is_grounded = 0;
		frame_count = 9;
		/*
		if(f1->y < 310 && f1->is_grounded == 0)
		{
			f1->last_y = f1->y;
			if(f1->last_y < 410)
			{
				f1->y = f1->last_y + (f1->jump_speed + i);
				++i;
			}
		}
		*/
	}
	else
	{
		fprintf(stdout,"frame: %i\n",F_Sprite.frame);
		DrawSprite(f1->sprite,buffer,f1->x, f1->y,F_Sprite.frame);
		frame_count = 3;
	}
	F_Sprite.frame = (F_Sprite.frame + 1) % frame_count;
	f1->sprite = NULL;
	if(f1->sprite != NULL)
	{
		FreeSprite(f1->sprite);
		//f1->sprite = NULL;
	}

//Fighter 2 code
	f2->sprite = LoadSprite("images/DoomIdleReversed.png",180,150);
	if(keys[SDLK_d])
	{
		f2->sprite = LoadSprite("images/DoomWalkBckReversed.png",153,140);
		DrawSprite(f2->sprite,buffer,f2->x + f2->walk_acc, f2->y,F_Sprite.player2_frame);
		f2->last_x = f2->x;
		f2->x = f2->last_x + f2->walk_acc;
		f2->hitbox.x = f2->x;
		player2_fc = 8;
	}
	else if(keys[SDLK_s])
	{
		f2->sprite = LoadSprite("images/StriderCrouch.png",108,68);
		DrawSprite(f2->sprite,buffer,f2->x,f2->y, F_Sprite.player2_frame);
		player2_fc = 6;
	}
	else if(keys[SDLK_a])
	{
		f2->sprite = LoadSprite("images/DoomWalkFwdReversed.png",154,144);
		DrawSprite(f2->sprite,buffer,f2->x - f2->walk_acc,f2->y,F_Sprite.player2_frame);
		f2->last_x = f2->x;
		f2->x = f2->last_x - f2->walk_acc;
		f2->hitbox.x = f2->x;
		player2_fc = 8;
	}
	else if(keys[SDLK_t])
	{
		int has_hit2 = 0;
		f2->sprite = LoadSprite("images/DoomLightAttackReversed.png",215,134);
		DrawSprite(f2->sprite,buffer,f2->x, f2->y,F_Sprite.player2_frame);
		has_hit2 = AABB(f2->hitbox,f1->hitbox,buffer);
		if(has_hit2 == 1)
		{
			f1->health -= 15;
		}
		player2_fc = 2;
	}
	else if(keys[SDLK_y])
	{
		int has_hit2 = 0;
		f2->sprite = LoadSprite("images/DoomMediumAttackReversed.png",219,145);
		DrawSprite(f2->sprite,buffer,f2->x, f2->y,F_Sprite.player2_frame);
		has_hit2 = AABB(f2->hitbox,f1->hitbox,buffer);
		if(has_hit2 == 1)
		{
			f1->health -= 25;
		}
		player2_fc = 5;
	}
	else if(keys[SDLK_u])
	{
		int has_hit2 = 0;
		f2->sprite = LoadSprite("images/DoomHeavyAttackReversed.png",270,173);
		DrawSprite(f2->sprite,buffer,f2->x, f2->y,F_Sprite.player2_frame);
		has_hit2 = AABB(f2->hitbox,f1->hitbox,buffer);
		if(has_hit2 == 1)
		{
			f1->health -= 50;
		}
		player2_fc = 8;
	}
	else if(keys[SDLK_i])
	{
		int has_hit2 = 0;
		f2->sprite = LoadSprite("images/StriderLauncherAttack.png",198,162);
		DrawSprite(f2->sprite,buffer,f2->x, f2->y,F_Sprite.player2_frame);
		has_hit2 = AABB(f2->hitbox,f1->hitbox,buffer);
		if(has_hit2 == 1)
		{
			f1->health -= 150;
		}
		player2_fc = 8;
	}
	else if(keys[SDLK_w])
	{
		f2->sprite = LoadSprite("images/StriderJump.png",183,138);
		DrawSprite(f2->sprite,buffer,f2->x, f2->y - f2->jump_speed,F_Sprite.player2_frame);
		f2->last_y = f2->y;
		f2->y = f2->last_y - f2->jump_speed;
		player2_fc = 9;
		/*
		if(f2->y < 410 && f2->is_grounded == 0)
		{
			f2->last_y = f2->y;
			f2->y = f2->last_y + (f2->jump_speed + i);
			++i;
		}
		*/
	}
	else
	{
		DrawSprite(f2->sprite,buffer,f2->x, f2->y,F_Sprite.player2_frame);
		player2_fc = 10;
	}
	F_Sprite.player2_frame = (F_Sprite.player2_frame + 1) % player2_fc;
	f2->sprite = NULL;
	if(f2->sprite != NULL)
	{
		FreeSprite(f2->sprite);
	}
}
void Print()
{
	fprintf(stdout, "Hail Hydra %s\n");
}
void FreeFighter(Fighter* f)
{	
	//if(f->used > 0)
	//{
		FreeSprite(f->sprite);
		f->sprite = NULL;
		f->health = NULL;
		f->x = NULL;
		f->y = NULL;
		f->walk_acc = NULL;
		f->walk_speed = NULL;
		f->jump_speed = NULL;
		f->hitbox.x = NULL;
		f->hitbox.y = NULL;
		f->hitbox.w = NULL;
		f->hitbox.h = NULL;
		f->is_grounded = NULL;
		f->used--;
	//}
}
void CloseFighter()
{
	for(int i = 0; i < MAX_FIGHTERS; ++i)
	{
		FreeFighter(&Fighters[i]);
	}
}
void DrawHealthBar(Fighter* f, SDL_Surface *buffer, int x, int y)
{
	for(int i=0; i<f->health;++i)
		for(int j=0; j < 30; ++j)
			DrawPixel(buffer,0,255,0,(30 + i) + x,(30 + j) + y);
}
