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
	f->vy = 50;
	f->walk_acc = 5;
	f->walk_speed = 10;
	f->jump_speed = 50;
	f->hitbox.x = 110;
	f->hitbox.y = 410;
	f->hitbox.w = 180;
	f->hitbox.h = 150;
	f->is_grounded = 1;
	f->flags = 0;
}
void InitCombatant2(Fighter* f)
{
	f->health = 150;
	f->x = 310;
	f->y = 410;
	f->vy = 50;
	f->walk_speed = 10;
	f->walk_acc = 5;
	f->jump_speed = 50;
	f->hitbox.x = 310;
	f->hitbox.y = 410;
	f->hitbox.w = 180;
	f->hitbox.h = 150;
	f->is_grounded = 1;
}
void FighterPull(Fighter* f1, Fighter* f2, Uint8* keys)
{
	if(keys[SDLK_RIGHT])
	{
		f1->flags = FIGHTERFLAG_WALKR;
		f1->anim_flags = ANIMFLAG_WALKR;
	}
	else if(keys[SDLK_DOWN])
	{
		f1->flags = FIGHTERFLAG_CROUCH;
		f1->anim_flags = ANIMFLAG_CROUCH;
	}
	else if(keys[SDLK_LEFT])
	{
		f1->flags = FIGHTERFLAG_WALKL;
		f1->anim_flags = ANIMFLAG_WALKL;
	}
	else if(keys[SDLK_UP])
	{
		f1->flags = FIGHTERFLAG_JUMP;
		f1->anim_flags = ANIMFLAG_JUMP;
	}
	else if(keys[SDLK_x])
	{
		f1->flags = FIGHTERFLAG_HITH;
		f1->anim_flags = ANIMFLAG_LIGHT;
	}
	else if(keys[SDLK_c])
	{
		f1->flags = FIGHTERFLAG_HITL;
		f1->anim_flags = ANIMFLAG_MED;
	}
	else if(keys[SDLK_v])
	{
		f1->flags = FIGHTERFLAG_HITH;
		f1->anim_flags = ANIMFLAG_HEV;
	}
	else if(keys[SDLK_b])
	{
		f1->flags = FIGHTERFLAG_HITL;
		f1->anim_flags = ANIMFLAG_LAUNCH;
	}
	else if(keys[SDLK_n])
	{
		f1->flags = FIGHTERFLAG_BLOCK;
		f1->anim_flags = ANIMFLAG_BLOCK;
	}	
	else
	{
		f1->flags = FIGHTERFLAG_IDLE;
		f1->anim_flags = ANIMFLAG_IDLE;
	}
	if(keys[SDLK_d])
	{
		f2->flags = FIGHTERFLAG_WALKL;
		f2->flags = ANIMFLAG_WALKL;
	}
	else if(keys[SDLK_s])
	{
		f2->flags = FIGHTERFLAG_CROUCH;
		f2->flags = ANIMFLAG_CROUCH;
	}
	else if(keys[SDLK_a])
	{
		f2->flags = FIGHTERFLAG_WALKR;
		f2->flags = ANIMFLAG_WALKR;
	}
	else if(keys[SDLK_w])
	{
		f2->flags = FIGHTERFLAG_JUMP;
		f2->flags = ANIMFLAG_JUMP;
	}
	else if(keys[SDLK_t])
	{
		f2->flags = FIGHTERFLAG_HITH;
		f2->flags = ANIMFLAG_LIGHT;
	}
	else if(keys[SDLK_y])
	{
		f2->flags = FIGHTERFLAG_HITL;
		f2->flags = ANIMFLAG_MED;
	}
	else if(keys[SDLK_u])
	{
		f2->flags = FIGHTERFLAG_HITL;
		f2->flags = ANIMFLAG_HEV;
	}
	else if(keys[SDLK_i])
	{
		f2->flags = FIGHTERFLAG_HITL;
		f2->flags = ANIMFLAG_LAUNCH;
	}
	else if(keys[SDLK_f])
	{
		f2->flags = FIGHTERFLAG_BLOCK;
		f2->flags = ANIMFLAG_BLOCK;
	}
	else
	{
		f2->flags = FIGHTERFLAG_IDLE;
		f2->flags = ANIMFLAG_IDLE;
	}
}
void DrawFighter(Fighter* f1, Fighter* f2, SDL_Surface *buffer)
{
	int frame_count, player2_fc;
	f1->sprite = LoadSprite("images/StriderIdle.png", 114, 101);
	f2->sprite = LoadSprite("images/DoomIdleReversed.png",180,180);
	if(f1->anim_flags == ANIMFLAG_WALKL)
	{
		f1->sprite = LoadSprite("images/StriderWalk.png",114,101);
		DrawSprite(f1->sprite,buffer,f1->x + f1->walk_acc, f1->y,F_Sprite.frame);
		frame_count = 10;
		//frame_count = 3;
	}
	else if(f1->anim_flags == ANIMFLAG_WALKR)
	{
		f1->sprite = LoadSprite("images/StriderWalk.png",114,101);
		DrawSprite(f1->sprite,buffer,f1->x - f1->walk_acc,f1->y,F_Sprite.frame);
		frame_count = 10;
		//frame_count = 3;
	}
	else if(f1->anim_flags == ANIMFLAG_CROUCH)
	{
		f1->sprite = LoadSprite("images/StriderCrouch.png",108,68);
		DrawSprite(f1->sprite,buffer,f1->x,f1->y, F_Sprite.frame);
		frame_count = 6;
		//frame_count = 3;
	}
	else if(f1->anim_flags == ANIMFLAG_JUMP)
	{
		f1->sprite = LoadSprite("images/StriderJump.png",183,138);
		DrawSprite(f1->sprite,buffer,f1->x, f1->y - f1->jump_speed,F_Sprite.frame);
		//frame_count = 3;
	}
	else if(f1->anim_flags == ANIMFLAG_LIGHT)
	{
		f1->sprite = LoadSprite("images/StriderLightAttack.png",179,138);
		DrawSprite(f1->sprite,buffer,f1->x, f1->y,F_Sprite.frame);
		frame_count = 9;
		//frame_count = 3;
	}
	else if(f1->anim_flags == ANIMFLAG_MED)
	{
		f1->sprite = LoadSprite("images/StriderMediumAttack.png",198,140);
		DrawSprite(f1->sprite,buffer,f1->x, f1->y,F_Sprite.frame);
		frame_count = 7;
		//frame_count = 3;
	}
	else if(f1->anim_flags == ANIMFLAG_HEV)
	{
		f1->sprite = LoadSprite("images/StriderHeavyAttack.png",206,140);
		DrawSprite(f1->sprite,buffer,f1->x, f1->y,F_Sprite.frame);
		frame_count = 13;
		//frame_count = 3;
	}
	else if(f1->anim_flags == ANIMFLAG_LAUNCH)
	{
		f1->sprite = LoadSprite("images/StriderLauncherAttack.png",198,162);
		DrawSprite(f1->sprite,buffer,f1->x, f1->y,F_Sprite.frame);
		frame_count = 8;
		//frame_count = 3;
	}
	else if(f1->anim_flags == ANIMFLAG_BLOCK)
	{
		DrawSprite(f1->sprite,buffer,f1->x, f1->y,F_Sprite.frame);
	}
	else
	{
		f1->sprite = LoadSprite("images/StriderIdle.png",114,92);
		DrawSprite(f1->sprite,buffer,f1->x, f1->y,F_Sprite.frame);
		frame_count = 3;
	}
	//Fighter 2 Draw Code
	if(f2->anim_flags == ANIMFLAG_WALKL)
	{
		f2->sprite = LoadSprite("images/DoomWalkFwdReversed.png",154,144);
		DrawSprite(f2->sprite,buffer,f2->x - f2->walk_acc,f2->y,F_Sprite.player2_frame);
		player2_fc = 8;
		//player2_fc = 10;
	}
	else if(f2->anim_flags == ANIMFLAG_WALKR)
	{
		f2->sprite = LoadSprite("images/DoomWalkBckReversed.png",153,140);
		DrawSprite(f2->sprite,buffer,f2->x + f2->walk_acc, f2->y,F_Sprite.player2_frame);
		player2_fc = 8;
		//player2_fc = 10;
	}
	else if(f2->anim_flags == ANIMFLAG_CROUCH)
	{
		f2->sprite = LoadSprite("images/StriderCrouch.png",108,68);
		DrawSprite(f2->sprite,buffer,f2->x,f2->y, F_Sprite.frame);
		player2_fc = 6;
		//player2_fc = 10;
	}
	else if(f2->anim_flags == ANIMFLAG_JUMP)
	{

	}
	else if(f2->anim_flags == ANIMFLAG_LIGHT)
	{
		f2->sprite = LoadSprite("images/DoomLightAttackReversed.png",215,134);
		DrawSprite(f2->sprite,buffer,f2->x, f2->y,F_Sprite.player2_frame);
		player2_fc = 2;
		//player2_fc = 10;
	}
	else if(f2->anim_flags == ANIMFLAG_MED)
	{
		f2->sprite = LoadSprite("images/DoomMediumAttackReversed.png",219,145);
		DrawSprite(f2->sprite,buffer,f2->x, f2->y,F_Sprite.player2_frame);
		player2_fc = 5;
		//player2_fc = 10;
	}
	else if(f2->anim_flags == ANIMFLAG_HEV)
	{
		f2->sprite = LoadSprite("images/DoomHeavyAttackReversed.png",270,173);
		DrawSprite(f2->sprite,buffer,f2->x, f2->y,F_Sprite.player2_frame);
		//player2_fc = 8;
		player2_fc = 10;
	}
	else if(f2->anim_flags == ANIMFLAG_LAUNCH)
	{
		DrawSprite(f2->sprite,buffer,f2->x, f2->y,F_Sprite.player2_frame);
		player2_fc = 10;
	}
	else if(f2->flags == FIGHTERFLAG_BLOCK)
	{
		DrawSprite(f2->sprite,buffer,f2->x, f2->y,F_Sprite.player2_frame);
		player2_fc = 10;
	}
	else if(f2->flags == FIGHTERFLAG_IDLE)
	{
		f2->sprite = LoadSprite("images/DoomIdleReversed.png",180,150);
		DrawSprite(f2->sprite,buffer,f2->x,f2->y,F_Sprite.frame);
		player2_fc = 10;
	}
	F_Sprite.player2_frame = (F_Sprite.player2_frame + 1) % player2_fc;
	F_Sprite.frame = (F_Sprite.frame + 1) % frame_count;
	if(f1->sprite != NULL)
	{
		FreeSprite(f1->sprite);
		f1->sprite = NULL;
	}
	if(f2->sprite != NULL)
	{
		FreeSprite(f2->sprite);
		f2->sprite = NULL;
	}
}
void UpdateFighter(Fighter* f1, Fighter* f2)
{
	if(f1->flags == FIGHTERFLAG_WALKR)
	{
		if(f1->x < 845)
		{
			f1->x = f1->x + f1->walk_acc;
			f1->hitbox.x = f1->x;
		}
		else
		{
			f1->flags = FIGHTERFLAG_IDLE;
			f1->anim_flags = ANIMFLAG_IDLE;
		}
	}
	else if(f1->flags == FIGHTERFLAG_CROUCH)
	{
	}
	else if(f1->flags == FIGHTERFLAG_WALKL)
	{
		if(f1->x > 0)
		{
			f1->x = f1->x - f1->walk_acc;
			f1->hitbox.x = f1->x;
		}
		else
		{
			f1->flags = FIGHTERFLAG_IDLE;
			f1->anim_flags = ANIMFLAG_IDLE;
		}
	}
	else if(f1->anim_flags == ANIMFLAG_LIGHT)
	{
		f1->flags = FIGHTERFLAG_HITH;
		int has_hit = 0;
		has_hit = AABB(f1->hitbox,f2->hitbox);
		if(has_hit == 1 && f2->flags != FIGHTERFLAG_BLOCK)
		{
			f2->health -= 15;
		}
		f1->flags = FIGHTERFLAG_IDLE;
	}
	else if(f1->anim_flags == ANIMFLAG_MED)
	{
		f1->flags = FIGHTERFLAG_HITL;
		int has_hit = 0;
		has_hit = AABB(f1->hitbox,f2->hitbox);
		if(has_hit == 1)
		{
			f2->health -= 25;
		}
		f1->flags = FIGHTERFLAG_IDLE;
	}
	else if(f1->anim_flags == ANIMFLAG_HEV)
	{
		f1->flags = FIGHTERFLAG_HITH;
		int has_hit = 0;
		has_hit = AABB(f1->hitbox,f2->hitbox);
		if(has_hit == 1 && f2->flags != FIGHTERFLAG_BLOCK)
		{
			f2->health -= 50;
		}
		f1->flags = FIGHTERFLAG_IDLE;
	}
	else if(f1->anim_flags == ANIMFLAG_LAUNCH)
	{
		f1->flags = FIGHTERFLAG_HITL;
		int has_hit = 0;
		has_hit = AABB(f1->hitbox,f2->hitbox);
		if(has_hit == 1)
		{
			f2->health -= 150;
		}
		f1->flags = FIGHTERFLAG_IDLE;
	}
	else if(f1->flags == FIGHTERFLAG_BLOCK)
	{
		int has_hit = AABB(f1->hitbox,f2->hitbox);
		if(has_hit == 1 && f2->flags == FIGHTERFLAG_HITH)
		{
			if(f1->health <= 250)
				f1->health +=10;
			else
				f1->health = 250;
		}
	}	
	else if(f1->flags == FIGHTERFLAG_JUMP)
	{
		f1->y = f1->y + f1->vy;
		f1->vy -= 1;
		f1->hitbox.y = f1->y;
		if(f1->y >= 410)
		{
			f1->y = 410;
			f1->vy = 5;
			f1->hitbox.y = f1->y;
		}
	}
	else
	{
		f1->flags = FIGHTERFLAG_IDLE;
		f1->anim_flags = ANIMFLAG_IDLE;
	}
//Fighter 2 code
	if(f2->flags == FIGHTERFLAG_WALKR)
	{
		if(f2->x < 845)
		{
			f2->x = f2->x + f2->walk_acc;
			f2->hitbox.x = f2->x;
		}
		else
		{
			f2->flags = FIGHTERFLAG_IDLE;
			f2->anim_flags = ANIMFLAG_IDLE;
		}
	}
	else if(f2->flags == FIGHTERFLAG_CROUCH)
	{
	}
	else if(f2->flags == FIGHTERFLAG_WALKL)
	{
		if(f2->x > 0)
		{
			f2->x = f2->x - f2->walk_acc;
			f2->hitbox.x = f2->x;
		}
		else
		{
			f2->flags = FIGHTERFLAG_IDLE;
			f2->anim_flags = ANIMFLAG_IDLE;
		}
	}
	else if(f2->anim_flags == ANIMFLAG_LIGHT)
	{
		f2->flags = FIGHTERFLAG_HITH;
		int has_hit2 = 0;
		has_hit2 = AABB(f2->hitbox,f1->hitbox);
		if(has_hit2 == 1 && f1->flags != FIGHTERFLAG_BLOCK)
		{
			f1->health -= 15;
		}
		f2->flags = FIGHTERFLAG_IDLE;
	}
	else if(f2->anim_flags == ANIMFLAG_MED)
	{
		f2->flags = FIGHTERFLAG_HITL;
		int has_hit2 = 0;
		has_hit2 = AABB(f2->hitbox,f1->hitbox);
		if(has_hit2 == 1)
		{
			f1->health -= 25;
		}
		f2->flags = FIGHTERFLAG_IDLE;
	}
	else if(f2->anim_flags == ANIMFLAG_HEV)
	{
		f2->flags = FIGHTERFLAG_HITL;
		int has_hit2 = 0;
		has_hit2 = AABB(f2->hitbox,f1->hitbox);
		if(has_hit2 == 1)
		{
			f1->health -= 50;
		}
		f2->flags = FIGHTERFLAG_IDLE;
	}
	else if(f2->anim_flags == ANIMFLAG_LAUNCH)
	{
		int has_hit2 = 0;
		has_hit2 = AABB(f2->hitbox,f1->hitbox);
		if(has_hit2 == 1)
		{
			f1->health -= 150;
		}
		f2->flags = FIGHTERFLAG_IDLE;
	}
	else if(f2->flags == FIGHTERFLAG_BLOCK)
	{
		int has_hit = AABB(f2->hitbox,f1->hitbox);
		if(has_hit == 1 && f1->flags == FIGHTERFLAG_HITH)
		{
			if(f2->health <= 250)
				f2->health +=10;
			else
				f2->health = 250;
		}
	}
	else if(f2->flags == FIGHTERFLAG_JUMP)
	{
		f2->y = f2->y + f2->vy;
		f2->vy -= 1;
		f2->hitbox.y = f2->y;
		if(f2->y <= 410)
		{
			f2->y = 410;
			f2->vy = 0;
			f2->hitbox.y = f2->y;
		}
	}
}
void FighterController(Fighter* f1, Fighter* f2, SDL_Surface *buffer, Uint8* keys)
{
	int keyn, frame_count, player2_fc, i = 0;
	f1->sprite = LoadSprite("images/StriderIdle.png",114,92);
	keys = SDL_GetKeyState(&keyn);
	if(keys[SDLK_RIGHT])
	{
		if(f1->x < 845)
		{
		f1->sprite = LoadSprite("images/StriderWalk.png",114,101);
		DrawSprite(f1->sprite,buffer,f1->x + f1->walk_acc, f1->y,F_Sprite.frame);
		f1->last_x = f1->x;
		f1->x = f1->last_x + f1->walk_acc;
		f1->hitbox.x = f1->x;
		frame_count = 10;
		}
		else
		{
			f1->sprite = LoadSprite("images/StriderIdle.png",114,92);
			DrawSprite(f1->sprite,buffer,f1->x,f1->y, F_Sprite.frame);
			frame_count = 3;
		}
	}
	else if(keys[SDLK_DOWN])
	{
		f1->sprite = LoadSprite("images/StriderCrouch.png",108,68);
		DrawSprite(f1->sprite,buffer,f1->x,f1->y, F_Sprite.frame);
		frame_count = 6;
	}
	else if(keys[SDLK_LEFT])
	{
		if(f1->x > 0)
		{
		f1->sprite = LoadSprite("images/StriderWalk.png",114,101);
		DrawSprite(f1->sprite,buffer,f1->x - f1->walk_acc,f1->y,F_Sprite.frame);
		f1->last_x = f1->x;
		f1->x = f1->last_x - f1->walk_acc;
		f1->hitbox.x = f1->x;
		frame_count = 10;
		}
		else
		{
			f1->sprite = LoadSprite("images/StriderIdle.png",114,92);
			DrawSprite(f1->sprite,buffer,f1->x,f1->y,F_Sprite.frame);
			frame_count = 3;
		}
	}
	else if(keys[SDLK_x])
	{
		f1->flags = FIGHTERFLAG_HITH;
		int has_hit = 0;
		f1->sprite = LoadSprite("images/StriderLightAttack.png",179,138);
		DrawSprite(f1->sprite,buffer,f1->x, f1->y,F_Sprite.frame);
		has_hit = AABB(f1->hitbox,f2->hitbox);
		if(has_hit == 1 && f2->flags != FIGHTERFLAG_BLOCK)
		{
			f2->health -= 15;
		}
		frame_count = 9;
	}
	else if(keys[SDLK_c])
	{
		f1->flags = FIGHTERFLAG_HITL;
		int has_hit = 0;
		f1->sprite = LoadSprite("images/StriderMediumAttack.png",198,140);
		DrawSprite(f1->sprite,buffer,f1->x, f1->y,F_Sprite.frame);
		has_hit = AABB(f1->hitbox,f2->hitbox);
		if(has_hit == 1)
		{
			f2->health -= 25;
		}
		frame_count = 7;
	}
	else if(keys[SDLK_v])
	{
		f1->flags = FIGHTERFLAG_HITH;
		int has_hit = 0;
		f1->sprite = LoadSprite("images/StriderHeavyAttack.png",206,140);
		DrawSprite(f1->sprite,buffer,f1->x, f1->y,F_Sprite.frame);
		has_hit = AABB(f1->hitbox,f2->hitbox);
		if(has_hit == 1 && f2->flags != FIGHTERFLAG_BLOCK)
		{
			f2->health -= 50;
		}
		frame_count = 13;
	}
	else if(keys[SDLK_b])
	{
		f1->flags = FIGHTERFLAG_HITL;
		int has_hit = 0;
		f1->sprite = LoadSprite("images/StriderLauncherAttack.png",198,162);
		DrawSprite(f1->sprite,buffer,f1->x, f1->y,F_Sprite.frame);
		has_hit = AABB(f1->hitbox,f2->hitbox);
		if(has_hit == 1)
		{
			f2->health -= 150;
		}
		frame_count = 8;
	}
	else if(keys[SDLK_n])
	{
		f1->flags = FIGHTERFLAG_BLOCK;
		f1->sprite = LoadSprite("images/StriderBlock.png",103,110);
		DrawSprite(f1->sprite,buffer,f1->x, f1->y,F_Sprite.frame);
		int has_hit = AABB(f1->hitbox,f2->hitbox);
		/*
		if(has_hit == 1 && f2->flags == FIGHTERFLAG_HITH)
		{
			if(f1->health <= 250)
				f1->health +=10;
			else
				f1->health = 250;
		}
		*/
		frame_count = 4;
	}	
	else if(keys[SDLK_UP])
	{
		f1->sprite = LoadSprite("images/StriderJump.png",183,138);
		DrawSprite(f1->sprite,buffer,f1->x, f1->y - f1->jump_speed,F_Sprite.frame);
		f1->y = f1->y + f1->vy;
		f1->vy -= 1;
		f1->hitbox.y = f1->y;
		if(f1->y >= 410)
		{
			f1->y = 410;
			f1->vy = 5;
			f1->hitbox.y = f1->y;
		}
	}
	else
	{
		f1->flags = FIGHTERFLAG_NOBLOCK;
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
		if(f2->x < 845)
		{
		f2->sprite = LoadSprite("images/DoomWalkBckReversed.png",153,140);
		DrawSprite(f2->sprite,buffer,f2->x + f2->walk_acc, f2->y,F_Sprite.player2_frame);
		f2->last_x = f2->x;
		f2->x = f2->last_x + f2->walk_acc;
		f2->hitbox.x = f2->x;
		player2_fc = 8;
		}
		else
		{
			f2->sprite = LoadSprite("images/DoomIdleReversed.png",180,150);
			DrawSprite(f2->sprite,buffer,f2->x,f2->y,F_Sprite.frame);
			player2_fc = 10;
		}
	}
	else if(keys[SDLK_s])
	{
		f2->sprite = LoadSprite("images/StriderCrouch.png",108,68);
		DrawSprite(f2->sprite,buffer,f2->x,f2->y, F_Sprite.player2_frame);
		player2_fc = 6;
	}
	else if(keys[SDLK_a])
	{
		if(f2->x > 0)
		{
		f2->sprite = LoadSprite("images/DoomWalkFwdReversed.png",154,144);
		DrawSprite(f2->sprite,buffer,f2->x - f2->walk_acc,f2->y,F_Sprite.player2_frame);
		f2->last_x = f2->x;
		f2->x = f2->last_x - f2->walk_acc;
		f2->hitbox.x = f2->x;
		player2_fc = 8;
		}
		else
		{
			f2->sprite = LoadSprite("images/DoomIdleReversed.png",180,150);
			DrawSprite(f2->sprite,buffer,f2->x,f2->y,F_Sprite.frame);
			player2_fc = 10;
		}
	}
	else if(keys[SDLK_t])
	{
		f2->flags = FIGHTERFLAG_HITH;
		int has_hit2 = 0;
		f2->sprite = LoadSprite("images/DoomLightAttackReversed.png",215,134);
		DrawSprite(f2->sprite,buffer,f2->x, f2->y,F_Sprite.player2_frame);
		has_hit2 = AABB(f2->hitbox,f1->hitbox);
		if(has_hit2 == 1 && f1->flags != FIGHTERFLAG_BLOCK)
		{
			f1->health -= 15;
		}
		player2_fc = 2;
	}
	else if(keys[SDLK_y])
	{
		f2->flags = FIGHTERFLAG_HITL;
		int has_hit2 = 0;
		f2->sprite = LoadSprite("images/DoomMediumAttackReversed.png",219,145);
		DrawSprite(f2->sprite,buffer,f2->x, f2->y,F_Sprite.player2_frame);
		has_hit2 = AABB(f2->hitbox,f1->hitbox);
		if(has_hit2 == 1)
		{
			f1->health -= 25;
		}
		//f2->flags &= ~FIGHTERFLAG_HITL;
		player2_fc = 5;
	}
	else if(keys[SDLK_u])
	{
		f2->flags = FIGHTERFLAG_HITL;
		int has_hit2 = 0;
		f2->sprite = LoadSprite("images/DoomHeavyAttackReversed.png",270,173);
		DrawSprite(f2->sprite,buffer,f2->x, f2->y,F_Sprite.player2_frame);
		has_hit2 = AABB(f2->hitbox,f1->hitbox);
		if(has_hit2 == 1)
		{
			f1->health -= 50;
		}
		player2_fc = 8;
		//f2->flags &= ~FIGHTERFLAG_HITL;
	}
	else if(keys[SDLK_i])
	{
		int has_hit2 = 0;
		f2->sprite = LoadSprite("images/DoomLauncherAttack.png",286,151);
		DrawSprite(f2->sprite,buffer,f2->x, f2->y,F_Sprite.player2_frame);
		has_hit2 = AABB(f2->hitbox,f1->hitbox);
		if(has_hit2 == 1)
		{
			f1->health -= 150;
		}
		player2_fc = 16;
	}
	else if(keys[SDLK_f])
	{
		f2->flags = FIGHTERFLAG_BLOCK;
		f2->sprite = LoadSprite("images/DoomBlock.png",144,139);
		DrawSprite(f2->sprite,buffer,f2->x, f2->y,F_Sprite.player2_frame);
		/*
		int has_hit = AABB(f2->hitbox,f1->hitbox);
		if(has_hit == 1 && f1->flags == FIGHTERFLAG_HITH)
		{
			if(f2->health <= 250)
				f2->health +=10;
			else
				f2->health = 250;
		}
		*/
		player2_fc = 4;
	}
	else if(keys[SDLK_w])
	{
		f2->sprite = LoadSprite("images/StriderJump.png",183,138);
		DrawSprite(f2->sprite,buffer,f2->x, f2->y,F_Sprite.player2_frame);
		f2->y = f2->y + f2->vy;
		f2->vy -= 1;
		f2->hitbox.y = f2->y;
		if(f2->y <= 410)
		{
			f2->sprite = LoadSprite("images/DoomIdleReversed.png",180,150);
			DrawSprite(f2->sprite,buffer,f2->x, f2->y,F_Sprite.player2_frame);
			f2->y = 410;
			f2->vy = 0;
			f2->hitbox.y = f2->y;
			player2_fc = 3;
		}
	}
	else
	{
		f2->flags = FIGHTERFLAG_NOBLOCK;
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
