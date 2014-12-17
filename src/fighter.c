#include "collision.h"
#include "fighter.h"
#include "time.h"

Fighter Fighters[MAX_FIGHTERS];

/* Initializes the fighter list that holds both of the player characters */
void InitFighterList()
{
	int i;
	for(i=0; i<MAX_FIGHTERS;++i)
	{
		memset(&Fighters[i],0,sizeof(Fighter));
	}
}
/* Gets the location of the fighter from the fighter list and returns the location */
Fighter * getFighter(int player)
{
	if (player >= MAX_FIGHTERS)return NULL;
	return &Fighters[player];
}
/* Sets the first player's data */
void InitCombatant(Fighter* f, long character)
{
	f->x = 110;
	f->y = 610;
	f->vy = 15;
	f->walk_acc = 5;
	f->walk_speed = 10;
	f->jump_speed = 50;
	f->hitbox.x = 110;
	f->hitbox.y = 610;
	f->hitbox.w = 180;
	f->hitbox.h = 150;
	f->flags = 0;
	f->anim_flags = 0;
	f->f_jump = 0;
	f->char_flag = character;
	f->stun_timer = 0;
}
/* Sets the second player's data */
void InitCombatant2(Fighter* f, long character)
{
	f->x = 610;
	f->y = 610;
	f->vy = 15;
	f->walk_speed = 10;
	f->walk_acc = 5;
	f->jump_speed = 50;
	f->hitbox.x = 610;
	f->hitbox.y = 610;
	f->hitbox.w = 180;
	f->hitbox.h = 150;
	f->flags = 0;
	f->anim_flags = 0;
	f->f_jump = 0;
	f->char_flag = character;
	f->stun_timer = 0;
}
/* Gets the key strokes from the user and applys the approriate flags to the player character */
void FighterPull(Fighter* f1, Uint8* keys)
{
	if(f1->stun_timer > 0)
	{
		f1->flags = FIGHTERFLAG_HITSTUN;
		f1->anim_flags = ANIMFLAG_HITSTUN;
	}
	else if(keys[SDLK_RIGHT] && f1->flags == FIGHTERFLAG_JUMP && f1->f_jump != JUMPFLAG_MOVEL)
	{
		f1->f_jump = JUMPFLAG_MOVER;
	}
	else if(keys[SDLK_LEFT] && f1->flags == FIGHTERFLAG_JUMP && f1->f_jump != JUMPFLAG_MOVER)
	{
		f1->f_jump = JUMPFLAG_MOVEL;
	}
	else if(keys[SDLK_RIGHT] && f1->flags != FIGHTERFLAG_JUMP)
	{
		f1->flags = FIGHTERFLAG_WALKR;
		f1->anim_flags = ANIMFLAG_WALKR;
	}
	else if(keys[SDLK_DOWN] && f1->flags != FIGHTERFLAG_JUMP)
	{
		f1->flags = FIGHTERFLAG_CROUCH;
		f1->anim_flags = ANIMFLAG_CROUCH;
		if(keys[SDLK_n])
			f1->flags = FIGHTERFLAG_BLOCKL;
	}
	else if(keys[SDLK_LEFT] && f1->flags != FIGHTERFLAG_JUMP)
	{
		f1->flags = FIGHTERFLAG_WALKL;
		f1->anim_flags = ANIMFLAG_WALKL;
	}
	else if(keys[SDLK_UP] && f1->flags != FIGHTERFLAG_JUMP)
	{
		f1->flags = FIGHTERFLAG_JUMP;
		f1->anim_flags = ANIMFLAG_JUMP;
	}
	else if(keys[SDLK_j] && f1->flags != FIGHTERFLAG_JUMP)
	{
		f1->flags = FIGHTERFLAG_HITH;
		f1->anim_flags = ANIMFLAG_LIGHT;
	}
	else if(keys[SDLK_k] && f1->flags != FIGHTERFLAG_JUMP)
	{
		f1->flags = FIGHTERFLAG_HITL;
		f1->anim_flags = ANIMFLAG_MED;
	}
	else if(keys[SDLK_l] && f1->flags != FIGHTERFLAG_JUMP)
	{
		f1->flags = FIGHTERFLAG_HITH;
		f1->anim_flags = ANIMFLAG_HEV;
	}
	else if(keys[SDLK_m] && f1->flags != FIGHTERFLAG_JUMP)
	{
		f1->flags = FIGHTERFLAG_HITL;
		f1->anim_flags = ANIMFLAG_LAUNCH;
	}
	else if(keys[SDLK_n] && f1->flags != FIGHTERFLAG_JUMP)
	{
		f1->flags = FIGHTERFLAG_BLOCK;
		f1->anim_flags = ANIMFLAG_BLOCK;
	}	
	else
	{
		if(f1->y == 610 && f1->vy == 15)
		{
			/* If the fighter is at the floor and his velocity is at its max then he is idle*/
			f1->flags = FIGHTERFLAG_IDLE;
			f1->anim_flags = ANIMFLAG_IDLE;
		}
		else
			f1->flags = FIGHTERFLAG_JUMP;
	}
}
/* Same code used for fighter 1 but for fighter 2, not utilized in the demo because it produces some wierd bugs */
void FighterPull2(Fighter* f2, Uint8* keys)
{
	if(f2->stun_timer > 0)
	{
		f2->flags = FIGHTERFLAG_HITSTUN;
		f2->anim_flags = ANIMFLAG_HITSTUN;
	}
	else if(keys[SDLK_d] && f2->flags != FIGHTERFLAG_JUMP)
	{
		f2->flags = FIGHTERFLAG_WALKL;
		f2->anim_flags = ANIMFLAG_WALKL;
	}
	else if(keys[SDLK_s] && f2->flags != FIGHTERFLAG_JUMP)
	{
		f2->flags = FIGHTERFLAG_CROUCH;
		f2->anim_flags = ANIMFLAG_CROUCH;
		if(keys[SDLK_f])
			f2->flags = FIGHTERFLAG_BLOCKL;
	}
	else if(keys[SDLK_a] && f2->flags != FIGHTERFLAG_JUMP)
	{
		f2->flags = FIGHTERFLAG_WALKR;
		f2->anim_flags = ANIMFLAG_WALKR;
	}
	else if(keys[SDLK_w] && f2->flags != FIGHTERFLAG_JUMP)
	{
		f2->flags = FIGHTERFLAG_JUMP;
		f2->anim_flags = ANIMFLAG_JUMP;
	}
	else if(keys[SDLK_r] && f2->flags != FIGHTERFLAG_JUMP)
	{
		f2->flags = FIGHTERFLAG_HITH;
		f2->anim_flags = ANIMFLAG_LIGHT;
	}
	else if(keys[SDLK_t] && f2->flags != FIGHTERFLAG_JUMP)
	{
		f2->flags = FIGHTERFLAG_HITL;
		f2->anim_flags = ANIMFLAG_MED;
	}
	else if(keys[SDLK_y] && f2->flags != FIGHTERFLAG_JUMP)
	{
		f2->flags = FIGHTERFLAG_HITL;
		f2->anim_flags = ANIMFLAG_HEV;
	}
	else if(keys[SDLK_g] && f2->flags != FIGHTERFLAG_JUMP)
	{
		f2->flags = FIGHTERFLAG_HITL;
		f2->anim_flags = ANIMFLAG_LAUNCH;
	}
	else if(keys[SDLK_f] && f2->flags != FIGHTERFLAG_JUMP)
	{
		f2->flags = FIGHTERFLAG_BLOCK;
		f2->anim_flags = ANIMFLAG_BLOCK;
	}
	else
	{
		if(f2->y == 610 && f2->vy == 15)
		{
			f2->flags = FIGHTERFLAG_IDLE;
			f2->anim_flags = ANIMFLAG_IDLE;
		}
		else
			f2->flags = FIGHTERFLAG_JUMP;
	}
}
/* Draws the player character based on their current flag, FIXME */
void DrawFighter1(Fighter* f1, SDL_Surface *buffer)
{
	int frame_count;
	if(f1->health <= 0)
	{
		if(f1->sprite != NULL) FreeSprite(f1->sprite);
		if(f1->char_flag == FIGHT_STRIDER)
		{
			f1->sprite = LoadSprite("images/StriderDeath.png",164,92);
		}
		else if(f1->char_flag == FIGHT_DOOM)
		{
			f1->sprite = LoadSprite("images/DoomDeath.png",196,150);
		}
		else if(f1->char_flag == FIGHT_MAGNETO)
		{
			f1->sprite = LoadSprite("images/MagnetoDeath.png",162,140);
		}
		else if(f1->char_flag == FIGHT_SENTINEL)
		{
			f1->sprite = LoadSprite("images/SentinelDeath.png",234,184);
		}
		else if(f1->char_flag == FIGHT_MEGAMAN)
		{
			f1->sprite = LoadSprite("images/MegaManDeath.png",126,76);
		}
		frame_count = 1;
	}
	else if(f1->anim_flags == ANIMFLAG_HITSTUN)
	{
		if(f1->sprite != NULL) FreeSprite(f1->sprite);
		if(f1->char_flag == FIGHT_STRIDER)
		{
			f1->sprite = LoadSprite("images/StriderHitstun.png",107,91);
		}
		else if(f1->char_flag == FIGHT_DOOM)
		{
			f1->sprite = LoadSprite("images/DoomHitstun.png",158,143);
		}
		else if(f1->char_flag == FIGHT_MAGNETO)
		{
			f1->sprite = LoadSprite("images/MagnetoHitstun.png",154,141);
		}
		else if(f1->char_flag == FIGHT_MEGAMAN)
		{
			f1->sprite = LoadSprite("images/MegaManHitstun.png",91,76);
		}
		else if(f1->char_flag == FIGHT_SENTINEL)
		{
			f1->sprite = LoadSprite("images/SentinelHitstun.png",218,201);
		}
		frame_count = 1;
	}
	else if(f1->anim_flags == ANIMFLAG_WALKL)
	{
		if(f1->sprite != NULL) FreeSprite(f1->sprite);
		if(f1->char_flag == FIGHT_STRIDER)
		{
			f1->sprite = LoadSprite("images/StriderWalk.png",114,101);
			frame_count = 10;
		}
		else if(f1->char_flag == FIGHT_DOOM)
		{
			f1->sprite = LoadSprite("images/DoomWalkBckReversed.png",153,140);
			frame_count = 8;
		}
		else if(f1->char_flag == FIGHT_MAGNETO)
		{
			f1->sprite = LoadSprite("images/MagnetoLeft.png",164,141);
			frame_count = 11;
		}
		else if(f1->char_flag == FIGHT_MEGAMAN)
		{
			f1->sprite = LoadSprite("images/MegaManRun.png",96,80);
			frame_count = 12;
		}
		else if(f1->char_flag == FIGHT_SENTINEL)
		{
			f1->sprite = LoadSprite("images/SentinelLeft.png",230,184);
			frame_count = 2;
		}
	}
	else if(f1->anim_flags == ANIMFLAG_WALKR)
	{
		if(f1->sprite != NULL) FreeSprite(f1->sprite);
		if(f1->char_flag == FIGHT_STRIDER)
		{
			f1->sprite = LoadSprite("images/StriderWalk.png",114,101);
			frame_count = 10;
		}
		else if(f1->char_flag == FIGHT_DOOM)
		{
			f1->sprite = LoadSprite("images/DoomWalkFwdReversed.png",154,144);
			frame_count = 8;
		}
		else if(f1->char_flag == FIGHT_MAGNETO)
		{
			f1->sprite = LoadSprite("images/MagnetoRight.png",180,141);
			frame_count = 10;
		}
		else if(f1->char_flag == FIGHT_MEGAMAN)
		{
			f1->sprite = LoadSprite("images/MegaManRun.png",96,80);
			frame_count = 12;
		}
		else if(f1->char_flag == FIGHT_SENTINEL)
		{
			f1->sprite = LoadSprite("images/SentinelRight.png",253,184);
			frame_count = 2;
		}
	}
	else if(f1->anim_flags == ANIMFLAG_CROUCH)
	{
		if(f1->sprite != NULL) FreeSprite(f1->sprite);
		if(f1->char_flag == FIGHT_STRIDER)
		{
			f1->sprite = LoadSprite("images/StriderCrouch.png",108,68);
			frame_count = 6;
		}
		else if(f1->char_flag == FIGHT_DOOM)
		{
			f1->sprite = LoadSprite("images/DoomCrouch.png",129,88);
			frame_count = 1;
		}
		else if(f1->char_flag == FIGHT_MAGNETO)
		{
			f1->sprite = LoadSprite("images/MagnetoCrouch.png",156,141);
			frame_count = 1;
		}
		else if(f1->char_flag == FIGHT_MEGAMAN)
		{
			f1->sprite = LoadSprite("images/MegaManCrouch.png",56,77);
			frame_count = 4;
		}
		else if(f1->char_flag == FIGHT_SENTINEL)
		{
			f1->sprite = LoadSprite("images/SentinelCrouch.png",173,184);
			frame_count = 1;
		}
	}
	else if(f1->anim_flags == ANIMFLAG_JUMP)
	{
		if(f1->sprite != NULL) FreeSprite(f1->sprite);
		if(f1->char_flag == FIGHT_STRIDER)
		{
			f1->sprite = LoadSprite("images/StriderIdle.png",114,92);
			frame_count = 3;
		}
		else if(f1->char_flag == FIGHT_DOOM)
		{
			f1->sprite = LoadSprite("images/DoomIdleReversed.png",180,150);
			frame_count = 10;
		}
		else if(f1->char_flag == FIGHT_MAGNETO)
		{
			f1->sprite = LoadSprite("images/MagnetoIdle.png",106,141);
			frame_count = 13;
		}
		else if(f1->char_flag == FIGHT_MEGAMAN)
		{
			f1->sprite = LoadSprite("images/MegaManIdle.png",83,77);
			frame_count = 4;
		}
		else if(f1->char_flag == FIGHT_SENTINEL)
		{
			f1->sprite = LoadSprite("images/SentinelIdle.png",178,184);
			frame_count = 3;
		}
	}
	else if(f1->anim_flags == ANIMFLAG_LIGHT)
	{
		if(f1->sprite != NULL) FreeSprite(f1->sprite);
		if(f1->char_flag == FIGHT_STRIDER)
		{
			f1->sprite = LoadSprite("images/StriderLightAttack.png",179,138);
			frame_count = 9;
		}
		else if(f1->char_flag == FIGHT_DOOM)
		{
			f1->sprite = LoadSprite("images/DoomLightAttackReversed.png",215,134);
			frame_count = 2;
		}
		else if(f1->char_flag == FIGHT_MAGNETO)
		{
			f1->sprite = LoadSprite("images/MagnetoLight.png",210,141);
			frame_count = 6;
		}
		else if(f1->char_flag == FIGHT_MEGAMAN)
		{
			f1->sprite = LoadSprite("images/MegaManLight.png",116,74);
			frame_count = 3;
		}
		else if(f1->char_flag == FIGHT_SENTINEL)
		{
			f1->sprite = LoadSprite("images/SentinelLight.png",240,184);
			frame_count = 4;
		}
	}
	else if(f1->anim_flags == ANIMFLAG_MED)
	{
		if(f1->sprite != NULL) FreeSprite(f1->sprite);
		if(f1->char_flag == FIGHT_STRIDER)
		{
			f1->sprite = LoadSprite("images/StriderMediumAttack.png",198,140);
			frame_count = 7;
		}
		else if(f1->char_flag == FIGHT_DOOM)
		{
			f1->sprite = LoadSprite("images/DoomMediumAttackReversed.png",219,145);
			frame_count = 5;
		}
		else if(f1->char_flag == FIGHT_MAGNETO)
		{
			f1->sprite = LoadSprite("images/MagnetoMedium.png",244,141);
			frame_count = 10;
		}
		else if(f1->char_flag == FIGHT_MEGAMAN)
		{
			f1->sprite = LoadSprite("images/MegaManMedium.png",112,76);
			frame_count = 5;
		}
		else if(f1->char_flag == FIGHT_SENTINEL)
		{
			f1->sprite = LoadSprite("images/SentinelMedium.png",277,184);
			frame_count = 3;
		}
	}
	else if(f1->anim_flags == ANIMFLAG_HEV)
	{
		if(f1->sprite != NULL) FreeSprite(f1->sprite);
		if(f1->char_flag == FIGHT_STRIDER)
		{
			f1->sprite = LoadSprite("images/StriderHeavyAttack.png",206,140);
			frame_count = 13;
		}
		else if(f1->char_flag == FIGHT_DOOM)
		{
			f1->sprite = LoadSprite("images/DoomHeavyAttackReversed.png",270,173);
			frame_count = 8;
		}
		else if(f1->char_flag == FIGHT_MAGNETO)
		{
			f1->sprite = LoadSprite("images/MagnetoHeavy.png",263,154);
			frame_count = 7;
		}
		else if(f1->char_flag == FIGHT_MEGAMAN)
		{
			f1->sprite = LoadSprite("images/MegaManHeavy.png",116,108);
			frame_count = 9;
		}
		else if(f1->char_flag == FIGHT_SENTINEL)
		{
			f1->sprite = LoadSprite("images/SentinelHeavy.png",286,184);
			frame_count = 7;
		}
	}
	else if(f1->anim_flags == ANIMFLAG_LAUNCH)
	{
		if(f1->sprite != NULL) FreeSprite(f1->sprite);
		if(f1->char_flag == FIGHT_STRIDER)
		{
			f1->sprite = LoadSprite("images/StriderLauncherAttack.png",198,162);
			frame_count = 8;
		}
		else if(f1->char_flag == FIGHT_DOOM)
		{
			f1->sprite = LoadSprite("images/DoomLauncherAttack.png",286,151);
			frame_count = 16;
		}
		else if(f1->char_flag == FIGHT_MAGNETO)
		{
			f1->sprite = LoadSprite("images/MagnetoLauncher.png",213,183);
			frame_count = 10;
		}
		else if(f1->char_flag == FIGHT_MEGAMAN)
		{
			f1->sprite = LoadSprite("images/MegaManLauncher.png",111,128);
			frame_count = 8;
		}
		else if(f1->char_flag == FIGHT_SENTINEL)
		{
			f1->sprite = LoadSprite("images/SentinelLauncher.png",240,219);
			frame_count = 5;
		}
	}
	else if(f1->anim_flags == ANIMFLAG_BLOCK)
	{
		if(f1->sprite != NULL) FreeSprite(f1->sprite);
		if(f1->char_flag == FIGHT_STRIDER)
		{
			f1->sprite = LoadSprite("images/StriderBlock.png",103,110);
			frame_count = 4;
		}
		else if(f1->char_flag == FIGHT_DOOM)
		{
			f1->sprite = LoadSprite("images/DoomBlock.png",144,139);
			frame_count = 4;
		}
		else if(f1->char_flag == FIGHT_MAGNETO)
		{
			f1->sprite = LoadSprite("images/MagnetoBlock.png",183,161);
			frame_count = 17;
		}
		else if(f1->char_flag == FIGHT_MEGAMAN)
		{
			f1->sprite = LoadSprite("images/MegaManBlock.png",90,87);
			frame_count = 2;
		}
		else if(f1->char_flag == FIGHT_SENTINEL)
		{
			f1->sprite = LoadSprite("images/SentinelBlock.png",155,195);
			frame_count = 1;
		}
	}
	else if(f1->anim_flags == ANIMFLAG_BLOCKL)
	{
		if(f1->sprite != NULL) FreeSprite(f1->sprite);
		if(f1->char_flag == FIGHT_STRIDER)
		{
			f1->sprite = LoadSprite("images/StriderBlock.png",103,110);
			frame_count = 4;
		}
		else if(f1->char_flag == FIGHT_DOOM)
		{
			f1->sprite = LoadSprite("images/DoomCrouchBlock.png",131,98);
			frame_count = 3;
		}
		else if(f1->char_flag == FIGHT_MAGNETO)
		{
			f1->sprite = LoadSprite("images/MagnetoBlock.png",183,161);
			frame_count = 17;
		}
		else if(f1->char_flag == FIGHT_MEGAMAN)
		{
			f1->sprite = LoadSprite("images/MegaManBlock.png",90,87);
			frame_count = 2;
		}
		else if(f1->char_flag == FIGHT_SENTINEL)
		{
			f1->sprite = LoadSprite("images/SentinelBlock.png",155,195);
			frame_count = 1;
		}
	}
	else
	{
		if(f1->sprite != NULL) FreeSprite(f1->sprite);
		if(f1->char_flag == FIGHT_STRIDER)
		{
			f1->sprite = LoadSprite("images/StriderIdle.png",114,92);
			frame_count = 3;
		}
		else if(f1->char_flag == FIGHT_DOOM)
		{
			f1->sprite = LoadSprite("images/DoomIdleReversed.png",180,150);
			frame_count = 10;
		}
		else if(f1->char_flag == FIGHT_MAGNETO)
		{
			f1->sprite = LoadSprite("images/MagnetoIdle.png",106,141);
			frame_count = 13;
		}
		else if(f1->char_flag == FIGHT_MEGAMAN)
		{
			f1->sprite = LoadSprite("images/MegaManIdle.png",83,77);
			frame_count = 4;
		}
		else if(f1->char_flag == FIGHT_SENTINEL)
		{
			f1->sprite = LoadSprite("images/SentinelIdle.png",178,184);
			frame_count = 3;
		}
	}
	DrawSprite(f1->sprite,buffer,f1->x, f1->y,f1->frame);
	f1->frame = (f1->frame + 1) % frame_count;
	f1->sprite = NULL;
	if(f1->sprite != NULL)
	{
		FreeSprite(f1->sprite);
	}
}
void DrawFighter2(Fighter* f1, SDL_Surface* buffer)
{
	int frame_count2;
		if(f1->health <= 0)
	{
		if(f1->sprite != NULL) FreeSprite(f1->sprite);
		if(f1->char_flag == FIGHT_STRIDER)
		{
			f1->sprite = LoadSprite("images/StriderDeath.png",164,92);
		}
		else if(f1->char_flag == FIGHT_DOOM)
		{
			f1->sprite = LoadSprite("images/DoomDeath.png",196,150);
		}
		else if(f1->char_flag == FIGHT_MAGNETO)
		{
			f1->sprite = LoadSprite("images/MagnetoDeath.png",162,140);
		}
		else if(f1->char_flag == FIGHT_SENTINEL)
		{
			f1->sprite = LoadSprite("images/SentinelDeath.png",234,184);
		}
		else if(f1->char_flag == FIGHT_MEGAMAN)
		{
			f1->sprite = LoadSprite("images/MegaManDeath.png",126,76);
		}
		frame_count2 = 1;
	}
	else if(f1->anim_flags == ANIMFLAG_HITSTUN)
	{
		if(f1->sprite != NULL) FreeSprite(f1->sprite);
		if(f1->char_flag == FIGHT_STRIDER)
		{
			f1->sprite = LoadSprite("images/StriderHitstun.png",107,91);
		}
		else if(f1->char_flag == FIGHT_DOOM)
		{
			f1->sprite = LoadSprite("images/DoomHitstun.png",158,143);
		}
		else if(f1->char_flag == FIGHT_MAGNETO)
		{
			f1->sprite = LoadSprite("images/MagnetoHitstun.png",154,141);
		}
		else if(f1->char_flag == FIGHT_MEGAMAN)
		{
			f1->sprite = LoadSprite("images/MegaManHitstun.png",91,76);
		}
		else if(f1->char_flag == FIGHT_SENTINEL)
		{
			f1->sprite = LoadSprite("images/SentinelHitstun.png",218,201);
		}
		frame_count2 = 1;
	}
	else if(f1->anim_flags == ANIMFLAG_WALKL)
	{
		if(f1->sprite != NULL) FreeSprite(f1->sprite);
		if(f1->char_flag == FIGHT_STRIDER)
		{
			f1->sprite = LoadSprite("images/StriderWalk.png",114,101);
			frame_count2 = 10;
		}
		else if(f1->char_flag == FIGHT_DOOM)
		{
			f1->sprite = LoadSprite("images/DoomWalkBckReversed.png",153,140);
			frame_count2 = 8;
		}
		else if(f1->char_flag == FIGHT_MAGNETO)
		{
			f1->sprite = LoadSprite("images/MagnetoLeft.png",164,141);
			frame_count2 = 11;
		}
		else if(f1->char_flag == FIGHT_MEGAMAN)
		{
			f1->sprite = LoadSprite("images/MegaManRun.png",96,80);
			frame_count2 = 12;
		}
		else if(f1->char_flag == FIGHT_SENTINEL)
		{
			f1->sprite = LoadSprite("images/SentinelLeft.png",230,184);
			frame_count2 = 2;
		}
	}
	else if(f1->anim_flags == ANIMFLAG_WALKR)
	{
		if(f1->sprite != NULL) FreeSprite(f1->sprite);
		if(f1->char_flag == FIGHT_STRIDER)
		{
			f1->sprite = LoadSprite("images/StriderWalk.png",114,101);
			frame_count2 = 10;
		}
		else if(f1->char_flag == FIGHT_DOOM)
		{
			f1->sprite = LoadSprite("images/DoomWalkFwdReversed.png",154,144);
			frame_count2 = 8;
		}
		else if(f1->char_flag == FIGHT_MAGNETO)
		{
			f1->sprite = LoadSprite("images/MagnetoRight.png",180,141);
			frame_count2 = 10;
		}
		else if(f1->char_flag == FIGHT_MEGAMAN)
		{
			f1->sprite = LoadSprite("images/MegaManRun.png",96,80);
			frame_count2 = 12;
		}
		else if(f1->char_flag == FIGHT_SENTINEL)
		{
			f1->sprite = LoadSprite("images/SentinelRight.png",253,184);
			frame_count2 = 2;
		}
	}
	else if(f1->anim_flags == ANIMFLAG_CROUCH)
	{
		if(f1->sprite != NULL) FreeSprite(f1->sprite);
		if(f1->char_flag == FIGHT_STRIDER)
		{
			f1->sprite = LoadSprite("images/StriderCrouch.png",108,68);
			frame_count2 = 6;
		}
		else if(f1->char_flag == FIGHT_DOOM)
		{
			f1->sprite = LoadSprite("images/DoomCrouch.png",129,88);
			frame_count2 = 1;
		}
		else if(f1->char_flag == FIGHT_MAGNETO)
		{
			f1->sprite = LoadSprite("images/MagnetoCrouch.png",156,141);
			frame_count2 = 1;
		}
		else if(f1->char_flag == FIGHT_MEGAMAN)
		{
			f1->sprite = LoadSprite("images/MegaManCrouch.png",56,77);
			frame_count2 = 4;
		}
		else if(f1->char_flag == FIGHT_SENTINEL)
		{
			f1->sprite = LoadSprite("images/SentinelCrouch.png",173,184);
			frame_count2 = 1;
		}
	}
	else if(f1->anim_flags == ANIMFLAG_JUMP)
	{
		if(f1->sprite != NULL) FreeSprite(f1->sprite);
		if(f1->char_flag == FIGHT_STRIDER)
		{
			f1->sprite = LoadSprite("images/StriderIdle.png",114,92);
			frame_count2 = 3;
		}
		else if(f1->char_flag == FIGHT_DOOM)
		{
			f1->sprite = LoadSprite("images/DoomIdleReversed.png",180,150);
			frame_count2 = 10;
		}
		else if(f1->char_flag == FIGHT_MAGNETO)
		{
			f1->sprite = LoadSprite("images/MagnetoIdle.png",106,141);
			frame_count2 = 13;
		}
		else if(f1->char_flag == FIGHT_MEGAMAN)
		{
			f1->sprite = LoadSprite("images/MegaManIdle.png",83,77);
			frame_count2 = 4;
		}
		else if(f1->char_flag == FIGHT_SENTINEL)
		{
			f1->sprite = LoadSprite("images/SentinelIdle.png",178,184);
			frame_count2 = 3;
		}
	}
	else if(f1->anim_flags == ANIMFLAG_LIGHT)
	{
		if(f1->sprite != NULL) FreeSprite(f1->sprite);
		if(f1->char_flag == FIGHT_STRIDER)
		{
			f1->sprite = LoadSprite("images/StriderLightAttack.png",179,138);
			frame_count2 = 9;
		}
		else if(f1->char_flag == FIGHT_DOOM)
		{
			f1->sprite = LoadSprite("images/DoomLightAttackReversed.png",215,134);
			frame_count2 = 2;
		}
		else if(f1->char_flag == FIGHT_MAGNETO)
		{
			f1->sprite = LoadSprite("images/MagnetoLight.png",210,141);
			frame_count2 = 6;
		}
		else if(f1->char_flag == FIGHT_MEGAMAN)
		{
			f1->sprite = LoadSprite("images/MegaManLight.png",116,74);
			frame_count2 = 3;
		}
		else if(f1->char_flag == FIGHT_SENTINEL)
		{
			f1->sprite = LoadSprite("images/SentinelLight.png",240,184);
			frame_count2 = 4;
		}
	}
	else if(f1->anim_flags == ANIMFLAG_MED)
	{
		if(f1->sprite != NULL) FreeSprite(f1->sprite);
		if(f1->char_flag == FIGHT_STRIDER)
		{
			f1->sprite = LoadSprite("images/StriderMediumAttack.png",198,140);
			frame_count2 = 7;
		}
		else if(f1->char_flag == FIGHT_DOOM)
		{
			f1->sprite = LoadSprite("images/DoomMediumAttackReversed.png",219,145);
			frame_count2 = 5;
		}
		else if(f1->char_flag == FIGHT_MAGNETO)
		{
			f1->sprite = LoadSprite("images/MagnetoMedium.png",244,141);
			frame_count2 = 10;
		}
		else if(f1->char_flag == FIGHT_MEGAMAN)
		{
			f1->sprite = LoadSprite("images/MegaManMedium.png",112,76);
			frame_count2 = 5;
		}
		else if(f1->char_flag == FIGHT_SENTINEL)
		{
			f1->sprite = LoadSprite("images/SentinelMedium.png",277,184);
			frame_count2 = 3;
		}
	}
	else if(f1->anim_flags == ANIMFLAG_HEV)
	{
		if(f1->sprite != NULL) FreeSprite(f1->sprite);
		if(f1->char_flag == FIGHT_STRIDER)
		{
			f1->sprite = LoadSprite("images/StriderHeavyAttack.png",206,140);
			frame_count2 = 13;
		}
		else if(f1->char_flag == FIGHT_DOOM)
		{
			f1->sprite = LoadSprite("images/DoomHeavyAttackReversed.png",270,173);
			frame_count2 = 8;
		}
		else if(f1->char_flag == FIGHT_MAGNETO)
		{
			f1->sprite = LoadSprite("images/MagnetoHeavy.png",263,154);
			frame_count2 = 7;
		}
		else if(f1->char_flag == FIGHT_MEGAMAN)
		{
			f1->sprite = LoadSprite("images/MegaManHeavy.png",116,108);
			frame_count2 = 9;
		}
		else if(f1->char_flag == FIGHT_SENTINEL)
		{
			f1->sprite = LoadSprite("images/SentinelHeavy.png",286,184);
			frame_count2 = 7;
		}
	}
	else if(f1->anim_flags == ANIMFLAG_LAUNCH)
	{
		if(f1->sprite != NULL) FreeSprite(f1->sprite);
		if(f1->char_flag == FIGHT_STRIDER)
		{
			f1->sprite = LoadSprite("images/StriderLauncherAttack.png",198,162);
			frame_count2 = 8;
		}
		else if(f1->char_flag == FIGHT_DOOM)
		{
			f1->sprite = LoadSprite("images/DoomLauncherAttack.png",286,151);
			frame_count2 = 16;
		}
		else if(f1->char_flag == FIGHT_MAGNETO)
		{
			f1->sprite = LoadSprite("images/MagnetoLauncher.png",213,183);
			frame_count2 = 10;
		}
		else if(f1->char_flag == FIGHT_MEGAMAN)
		{
			f1->sprite = LoadSprite("images/MegaManLauncher.png",111,128);
			frame_count2 = 8;
		}
		else if(f1->char_flag == FIGHT_SENTINEL)
		{
			f1->sprite = LoadSprite("images/SentinelLauncher.png",240,219);
			frame_count2 = 5;
		}
	}
	else if(f1->anim_flags == ANIMFLAG_BLOCK)
	{
		if(f1->sprite != NULL) FreeSprite(f1->sprite);
		if(f1->char_flag == FIGHT_STRIDER)
		{
			f1->sprite = LoadSprite("images/StriderBlock.png",103,110);
			frame_count2 = 4;
		}
		else if(f1->char_flag == FIGHT_DOOM)
		{
			f1->sprite = LoadSprite("images/DoomBlock.png",144,139);
			frame_count2 = 4;
		}
		else if(f1->char_flag == FIGHT_MAGNETO)
		{
			f1->sprite = LoadSprite("images/MagnetoBlock.png",183,161);
			frame_count2 = 17;
		}
		else if(f1->char_flag == FIGHT_MEGAMAN)
		{
			f1->sprite = LoadSprite("images/MegaManBlock.png",90,87);
			frame_count2 = 2;
		}
		else if(f1->char_flag == FIGHT_SENTINEL)
		{
			f1->sprite = LoadSprite("images/SentinelBlock.png",155,195);
			frame_count2 = 1;
		}
	}
	else if(f1->anim_flags == ANIMFLAG_BLOCKL)
	{
		if(f1->sprite != NULL) FreeSprite(f1->sprite);
		if(f1->char_flag == FIGHT_STRIDER)
		{
			f1->sprite = LoadSprite("images/StriderBlock.png",103,110);
			frame_count2 = 4;
		}
		else if(f1->char_flag == FIGHT_DOOM)
		{
			f1->sprite = LoadSprite("images/DoomCrouchBlock.png",131,98);
			frame_count2 = 3;
		}
		else if(f1->char_flag == FIGHT_MAGNETO)
		{
			f1->sprite = LoadSprite("images/MagnetoBlock.png",183,161);
			frame_count2 = 17;
		}
		else if(f1->char_flag == FIGHT_MEGAMAN)
		{
			f1->sprite = LoadSprite("images/MegaManBlock.png",90,87);
			frame_count2 = 2;
		}
		else if(f1->char_flag == FIGHT_SENTINEL)
		{
			f1->sprite = LoadSprite("images/SentinelBlock.png",155,195);
			frame_count2 = 1;
		}
	}
	else
	{
		if(f1->sprite != NULL) FreeSprite(f1->sprite);
		if(f1->char_flag == FIGHT_STRIDER)
		{
			f1->sprite = LoadSprite("images/StriderIdle.png",114,92);
			frame_count2 = 3;
		}
		else if(f1->char_flag == FIGHT_DOOM)
		{
			f1->sprite = LoadSprite("images/DoomIdleReversed.png",180,150);
			frame_count2 = 10;
		}
		else if(f1->char_flag == FIGHT_MAGNETO)
		{
			f1->sprite = LoadSprite("images/MagnetoIdle.png",106,141);
			frame_count2 = 13;
		}
		else if(f1->char_flag == FIGHT_MEGAMAN)
		{
			f1->sprite = LoadSprite("images/MegaManIdle.png",83,77);
			frame_count2 = 4;
		}
		else if(f1->char_flag == FIGHT_SENTINEL)
		{
			f1->sprite = LoadSprite("images/SentinelIdle.png",178,184);
			frame_count2 = 3;
		}
	}
	DrawSprite(f1->sprite,buffer,f1->x, f1->y,f1->frame);
	f1->frame = (f1->frame + 1) % frame_count2;
	f1->sprite = NULL;
	if(f1->sprite != NULL)
	{
		FreeSprite(f1->sprite);
	}
}
/* Updates the logic for each fighter */
void FighterController(Fighter* f1, Fighter* f2, int player_number)
{
	clock_t t;
	f1->f_jump = NULL;
	if(f1->stun_timer <= 0 && f1->shield_stun <= 0 && f1->health > 0) 
	{
		if(f1->flags == FIGHTERFLAG_WALKR && player_number == 1)
		{
			/* Walk Right code, prevents the player from walking off of the stage*/
			if(f1->x < 845)
			{
				f1->x = f1->x + f1->walk_acc;
				f1->hitbox.x = f1->x;
			}
			else
			{
				/* If the player attempts to walk off of the stage set his state to idle*/
				f1->flags = FIGHTERFLAG_IDLE;
			}
		}
		else if(f1->flags == FIGHTERFLAG_WALKL && player_number == 1)
		{
			/* Walk left code, prevents the player from walking off of the stage*/
			if(f1->x > 0)
			{
				f1->x = f1->x - f1->walk_acc;
				f1->hitbox.x = f1->x;
			}
			else
			{
				/* If the player attempts to walk off of the stage he is set to idle*/
				f1->flags = FIGHTERFLAG_IDLE;
			}
		}
		else if(f1->flags == FIGHTERFLAG_WALKL && player_number == 2)
		{
			/* Walk Left Code, prevents the player from walking off screen */
			if(f1->x < 845)
			{
				f1->x = f1->x + f1->walk_acc;
				f1->hitbox.x = f1->x;
			}
			else
			{
				/* If the player tries to walk off screen display him as idle */
				f1->flags = FIGHTERFLAG_IDLE;
			}
		}
		else if(f1->flags == FIGHTERFLAG_WALKR && player_number == 2)
		{
			/* Walk Right Code, prevents the player from walking off screen */
			if(f1->x > 0)
			{
				f1->x = f1->x - f1->walk_acc;
				f1->hitbox.x = f1->x;
			}
			else
			{
				f1->flags = FIGHTERFLAG_IDLE;
			}
		}
		else if(f1->anim_flags == ANIMFLAG_LIGHT && f1->flags != FIGHTERFLAG_JUMP)
		{
			/* Light Attack: does the pulling, drawing, and logic for the attack */
			int has_hit = 0;
			has_hit = AABB(f1->hitbox,f2->hitbox);
			if(has_hit == 1 && f2->flags != FIGHTERFLAG_BLOCK)
			{
				if(f1->combo_count >= 10)
				{
					f2->health -= (f1->light_dmg * .4);
				}
				else
				{
					f2->health -= f1->light_dmg;
					f2->stun_timer = 3;
				}
				if(f1->x < f2->x && f2->health > 0 && f2->x > 0 && f2->x < 845)
				{
					f2->x += f1->light_knb;
					f2->hitbox.x += f1->light_knb;
				}
				else if(f1->x > f2->x && f2->health > 0 && f2->x > 0 && f2->x < 845)
				{
					f2->x -= f1->light_knb;
					f2->hitbox.x -= f1->light_knb;
				}
				++f1->combo_count;
				t = clock();
			}
			else if(has_hit == 1 && f2->flags == FIGHTERFLAG_BLOCK)
			{
				f2->shield_stun = 1;
			}
		}
		else if(f1->anim_flags == ANIMFLAG_MED && f1->flags != FIGHTERFLAG_JUMP)
		{
			/* Medium Attack: does the pulling, drawing, and logic for the attack */
			int has_hit = 0;
			has_hit = AABB(f1->hitbox,f2->hitbox);
			if(has_hit == 1 && f2->flags != FIGHTERFLAG_BLOCKL)
			{
				if(f1->combo_count >= 10)
				{
					f2->health -= (f1->med_dmg * .4);
				}
				else
				{
					f2->health -= f1->med_dmg;
					f2->stun_timer = 5;
				}
				if(f1->x < f2->x && f2->health > 0 && f2->x > 0 && f2->x < 845)
				{
					f2->x += f1->med_knb;
					f2->hitbox.x += f1->med_knb;
				}
				else if(f1->x > f2->x && f2->health > 0 && f2->x > 0 && f2->x < 845)
				{
					f2->x -= f1->med_knb;
					f2->hitbox.x -= f1->med_knb;
				}
				++f1->combo_count;
				t = clock();
			}
			else if(has_hit == 1 && f2->flags == FIGHTERFLAG_BLOCKL)
			{
				f2->shield_stun = 3;
			}
		}
		else if(f1->anim_flags == ANIMFLAG_HEV && f1->flags != FIGHTERFLAG_JUMP)
		{
			/* Heavy Attack: does the pulling, drawing, and logic for the attack */
			int has_hit = 0;
			has_hit = AABB(f1->hitbox,f2->hitbox);
			if(has_hit == 1 && f2->flags != FIGHTERFLAG_BLOCK)
			{
				if(f1->combo_count >= 10)
				{
					f2->health -= (f1->hev_dmg * .4);
				}
				else
				{
					f2->health -= f1->hev_dmg;
					f2->stun_timer = 7;
				}
				if(f1->x < f2->x && f2->health > 0 && f2->x > 0 && f2->x < 845)
				{
					f2->x += f1->hev_knb;
					f2->hitbox.x += f1->hev_knb;
				}
				else if(f1->x > f2->x && f2->health > 0 && f2->x > 0 && f2->x < 845)
				{
					f2->x -= f1->hev_knb;
					f2->hitbox.x -= f1->hev_knb;
				}
				++f1->combo_count;
				t = clock();
			}
			else if(has_hit == 1 && f2->flags == FIGHTERFLAG_BLOCK)
			{
				f2->shield_stun = 4;
			}
		}
		else if(f1->anim_flags == ANIMFLAG_LAUNCH && f1->flags != FIGHTERFLAG_JUMP)
		{
			/* 
			 * Launcher Attack:  Used to knock the player high in the air for air combos
			 * The move is currently a heavily damaging move because the functionality has not
			 * been programmed in yet
			*/
			int has_hit = 0;
			has_hit = AABB(f1->hitbox,f2->hitbox);
			if(has_hit == 1 && f2->flags != FIGHTERFLAG_BLOCKL)
			{
				f2->health -= f1->launch_dmg;
				++f1->combo_count;
				t = clock();
			}
		}	
		if(f1->flags == FIGHTERFLAG_JUMP)
		{
			/* Does the logic for jumping when the state is jumping */
			/* 
			Begining to apply directional jumping, still under construction 
			if(f1->f_jump == JUMPFLAG_MOVER && f1->x < 845 )
			{
				f1->x = f1->x + f1->walk_acc;
				f1->hitbox.x = f1->x;
			}
			else if(f1->f_jump == JUMPFLAG_MOVEL && f1->x > 0)
			{
				f1->x = f1->x - f1->walk_acc;
				f1->hitbox.x = f1->x;
			}
			*/
			f1->y = f1->y - f1->vy;
			f1->vy -= 1;
			f1->hitbox.y = f1->y;
			if(f1->y >= 610 && f1->vy != 15)
			{
				/* When the player touches the ground the state is set to idle */
				f1->y = 610;
				f1->vy = 15;
				f1->hitbox.y = f1->y;
				f1->flags = FIGHTERFLAG_IDLE;
			}
		}
		else if(f1->flags == FIGHTERFLAG_IDLE)
		{
			f1->flags = FIGHTERFLAG_NOBLOCK;
			f1->f_jump = NULL;
		}
	}
	t = clock() - t;
	if(f1->stun_timer > 0 && f1->health > 0)
		--f1->stun_timer;
	if(f1->stun_timer < 0 && f1->health > 0)
		f1->stun_timer = 0;
	if(f1->shield_stun > 0 && f1->health > 0)
		--f1->shield_stun;
	if(f1->shield_stun < 0 && f1->health > 0)
		f1->shield_stun = 0;
	if(f2->stun_timer <= 0 && f2->health > 0 && ((float)t/CLOCKS_PER_SEC) == 2.0)
		f1->combo_count = 0;
}
/* Frees the memory that is held by the fighter */
void FreeFighter(Fighter* f)
{	
	FreeSprite(f->sprite);
	memset(f,0,sizeof(Fighter));
}
/* Cleans up the fighter list if it hasn't already been cleaned */
void CloseFighter()
{
	for(int i = 0; i < MAX_FIGHTERS; ++i)
	{
		/* FreeFighter(&Fighters[i]); */
	}
}
/* Draws the current health of the fighter */
void DrawHealthBar(Fighter* f, SDL_Surface *buffer, int x, int y)
{
	if(f->health != 300)
		for(int h=0; h<f->health + 30;++h)
			for(int g=0; g < 30; ++g)
				DrawPixel(buffer,255,0,0,(30 + h) + x,(30 + g) + y);
	for(int i=0; i<f->health;++i)
		for(int j=0; j < 30; ++j)
			DrawPixel(buffer,0,255,0,(30 + i) + x,(30 + j) + y);
}
/* Loads the fighter from a text file into the game */
void LoadFighter(Fighter* f, long character)
{
	char* filepath;
	if(character == FIGHT_STRIDER)
	{
		filepath = "fighters/StriderData.txt";
	}
	else if(character == FIGHT_DOOM)
	{
		filepath = "fighters/DoomData.txt";
	}
	else if(character == FIGHT_MEGAMAN)
	{
		filepath = "fighters/MegaManData.txt";
	}
	else if(character == FIGHT_MAGNETO)
	{
		filepath = "fighters/MagnetoData.txt";
	}
	else if(character == FIGHT_SENTINEL)
	{
		filepath = "fighters/SentinelData.txt";
	}
	char buffer[255];
	FILE* pFile = NULL;
	pFile = fopen(filepath,"r");
	if(!pFile)
	{
		fprintf(stdout,"character file not found: ",filepath);
		return;
	}
	if(fscanf(pFile,"%s",buffer))
	{
		if(strcmp(buffer,"health:")==0)
		{
			fscanf(pFile,"%i",&f->health);
			fscanf(pFile,"%s",buffer);
		}
		if(strcmp(buffer,"light:")==0)
		{
			fscanf(pFile,"%i",&f->light_dmg);
			fscanf(pFile,"%s",buffer);
		}
		if(strcmp(buffer,"medium:")==0)
		{
			fscanf(pFile,"%i",&f->med_dmg);
			fscanf(pFile,"%s",buffer);
		}
		if(strcmp(buffer,"heavy:")==0)
		{
			fscanf(pFile,"%i",&f->hev_dmg);
			fscanf(pFile,"%s",buffer);
		}
		if(strcmp(buffer,"launcher:")==0)
		{
			fscanf(pFile,"%i",&f->launch_dmg);
			fscanf(pFile,"%s",buffer);
		}
		if(strcmp(buffer,"lightknockback:")==0)
		{
			fscanf(pFile,"%i",&f->light_knb);
			fscanf(pFile,"%s",buffer);
		}
		if(strcmp(buffer,"mediumknockback:")==0)
		{
			fscanf(pFile,"%i",&f->med_knb);
			fscanf(pFile,"%s",buffer);
		}
		if(strcmp(buffer,"heavyknockback:")==0)
		{
			fscanf(pFile,"%i",&f->hev_knb);
			fscanf(pFile,"%s",buffer);
		}
	}
	fclose(pFile);
}
/* Allows the user to edit the data of any fighter */
int EditFighter()
{
	unsigned int value = 0;

	unsigned int health = 0;
	unsigned int light = 0;
	unsigned int medium = 0;
	unsigned int heavy = 0;
	unsigned int launcher = 0;
	unsigned int light_knb = 0;
	unsigned int med_knb = 0;
	unsigned int hev_knb = 0;

	fprintf(stdout,"Do you want to edit a fighter?\n 1 = no\n 0 = yes\n");
	scanf("%d",&value);
	if(value != 0)
	{
		  return 1;
	}
	fprintf(stdout,"What fighter do you want to edit?:\n 1 - Strider\n 2 - Doom\n 3 - Magneto\n 4 - MegaMan\n 5 - Sentinel\n");
	scanf("%d",&value);
	char* filepath;
	if(value == 1)
	{
		filepath = "fighters/StriderData.txt";
	}
	else if(value == 2)
	{
		filepath = "fighters/DoomData.txt";
	}
	else if(value == 3)
	{
		filepath = "fighters/MegaManData.txt";
	}
	else if(value == 4)
	{
		filepath = "fighters/MagnetoData.txt";
	}
	else if(value == 5)
	{
		filepath = "fighters/SentinelData.txt";
	}
	else
	{
		printf("Invalid Selection");
	}
	FILE* pFile = NULL;
	pFile = fopen(filepath,"w+");
	if(!pFile)
	{
		fprintf(stdout,"character file not found: ",filepath);
		return 1;
	}
	fprintf(stdout,"Health: \n");
	scanf("%d",&health);

	fprintf(stdout,"Light: \n");
	scanf("%d",&light);

	fprintf(stdout,"Medium: \n");
	scanf("%d",&medium);

	fprintf(stdout,"Heavy: \n");
	scanf("%d",&heavy);

	fprintf(stdout,"Launch: \n");
	scanf("%d",&launcher);

	fprintf(stdout,"Light Knockback: \n");
	scanf("%d",&light_knb);

	fprintf(stdout,"Medium Knockback: \n");
	scanf("%d",&med_knb);

	fprintf(stdout,"Heavy Knockback: \n");
	scanf("%d",&hev_knb);

	fprintf(pFile,"health: %d",health);
	fprintf(pFile,"\n");
	fprintf(pFile,"light: %d",light);
	fprintf(pFile,"\n");
	fprintf(pFile,"medium: %d",medium);
	fprintf(pFile,"\n");
	fprintf(pFile,"heavy: %d",heavy);
	fprintf(pFile,"\n");
	fprintf(pFile,"launcher: %d",launcher);
	fprintf(pFile,"\n");
	fprintf(pFile,"lightknockback: %d",launcher);
	fprintf(pFile,"\n");
	fprintf(pFile,"mediumknockback: %d",launcher);
	fprintf(pFile,"\n");
	fprintf(pFile,"heavyknockback: %d",launcher);
	fprintf(pFile,"\n");
	fprintf(stdout,"Done!\n");

	fclose(pFile);

	return 0;

	/*int i;

	for(i = 0; i < 100000;i++)
	{
		fprintf(pFile,"\n");
	}*/
}
