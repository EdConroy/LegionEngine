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
	f->jump_height = 210;
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
	f->jump_height = 210;
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
		//fprintf(stdout,"Player 2 x: %i", f2->x);
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
		f->jump_height = NULL;
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
	int i;
	for(i = 0; i < MAX_FIGHTERS; ++i)
	{
		FreeFighter(&Fighters[i]);
	}
}
void Poll(Game_T* game, Uint8* keys)
{
	if(keys[SDLK_RIGHT])
	{
		if(game->f1->x < 845)
		{
			game->f1->flags |= FIGHTFLAG_MOVER;
			SetAnimation(game->f1->sprite, ANIMATION_WALKR);
		}
		else
		{
			game->f1->flags |= FIGHTFLAG_IDLE;
			SetAnimation(game->f1->sprite, ANIMATION_IDLE);
		}
	}
	else if(keys[SDLK_DOWN])
	{
		game->f1->flags |= FIGHTFLAG_CROUCHING;
		SetAnimation(game->f1->sprite, ANIMATION_CROUCH);
	}
	else if(keys[SDLK_LEFT])
	{
		if(game->f1->x > 0)
		{
			game->f1->flags |= FIGHTFLAG_MOVEL;
			SetAnimation(game->f1->sprite, ANIMATION_WALKL);
		}
		else
		{
			game->f1->flags |= FIGHTFLAG_IDLE;
			SetAnimation(game->f1->sprite, ANIMATION_IDLE);
		}
	}
	else if(keys[SDLK_UP])
	{
		if(!(game->f1->flags &= FIGHTFLAG_JUMPING)){
			game->f1->flags |= FIGHTFLAG_JUMPING;
			SetAnimation(game->f1->sprite, ANIMATION_JUMP);
			game->f1->vy = 5;
	}
	else if(keys[SDLK_x])
	{
		game->f1->flags |= FIGHTFLAG_LIGHTATT;
		SetAnimation(game->f1->sprite, ANIMATION_ATTL);
	}
	else if(keys[SDLK_c])
	{
		game->f1->flags |= FIGHTFLAG_MEDATT;
		SetAnimation(game->f1->sprite, ANIMATION_ATTM);
	}
	else if(keys[SDLK_v])
	{
		game->f1->flags |= FIGHTFLAG_HEVATT;
		SetAnimation(game->f1->sprite, ANIMATION_ATTH);
	}
	else if(keys[SDLK_b])
	{
		game->f1->flags |= FIGHTFLAG_LAUNCH;
		SetAnimation(game->f1->sprite, ANIMATION_LAUNCH);
	}
	else
	{
		game->f1->flags |= FIGHTFLAG_IDLE;
		SetAnimation(game->f1->sprite, ANIMATION_IDLE);
	}
	if(keys[SDLK_a])
	{
		if(game->f2->x < 845)
		{
			game->f2->flags |= FIGHTFLAG_MOVER;
			SetAnimation(game->f2->sprite, ANIMATION_WALKR);
		}
		else
		{
			game->f2->flags |= FIGHTFLAG_IDLE;
			SetAnimation(game->f2->sprite, ANIMATION_IDLE);
		}
	}
	else if(keys[SDLK_s])
	{
		game->f2->flags |= FIGHTFLAG_CROUCHING;
		SetAnimation(game->f2->sprite, ANIMATION_CROUCH);
	}
	else if(keys[SDLK_d])
	{
		if(game->f2->x > 0)
		{
			game->f2->flags |= FIGHTFLAG_MOVEL;
			SetAnimation(game->f2->sprite, ANIMATION_WALKL);
		}
		else
		{
			game->f2->flags |= FIGHTFLAG_IDLE;
			SetAnimation(game->f2->sprite, ANIMATION_IDLE);
		}
	}
	else if(keys[SDLK_w])
	{
		if(!(game->f2->flags &= FIGHTFLAG_JUMPING)){
			game->f2->flags |= FIGHTFLAG_JUMPING;
			SetAnimation(game->f2->sprite, ANIMATION_JUMP);
			game->f2->vy = 5;
	}
	else if(keys[SDLK_t])
	{
		game->f2->flags |= FIGHTFLAG_LIGHTATT;
		SetAnimation(game->f2->sprite, ANIMATION_ATTL);
	}
	else if(keys[SDLK_y])
	{
		game->f2->flags |= FIGHTFLAG_MEDATT;
		SetAnimation(game->f2->sprite, ANIMATION_ATTM);
	}
	else if(keys[SDLK_u])
	{
		game->f2->flags |= FIGHTFLAG_HEVATT;
		SetAnimation(game->f2->sprite, ANIMATION_ATTH);
	}
	else if(keys[SDLK_i])
	{
		game->f2->flags |= FIGHTFLAG_LAUNCH;
		SetAnimation(game->f2->sprite, ANIMATION_LAUNCH);
	}
	else
	{
		game->f2->flags |= FIGHTFLAG_IDLE;
		SetAnimation(game->f2->sprite, ANIMATION_IDLE);
	}
}
void Update(Game_T* game)
{
	if(game->f1->flags &= FIGHTFLAG_LIGHTATT || game->f1->flags &= FIGHTFLAG_MEDATT || game->f1->flags &= FIGHTFLAG_HEVATT)
	{
		int has_hit = 0;
		has_hit = AABB(game->f1->hitbox,game->f2->hitbox,buffer);
		if(has_hit == 1 && game->f1->flags &= FIGHTFLAG_LIGHTATT)
		{
			game->f2->health -= 15;
		}
		else if(has_hit == 1 && game->f1->flags &= FIGHTFLAG_MEDATT)
		{
			game->f2->health -= 25;
		}
		else if(has_hit == 1 && game->f1->flags &= FIGHTFLAG_HEVATT)
		{
			game->f2->health -= 50;
		}
		else if(has_hit == 1 && game->f1->flags &= FIGHTFLAG_LAUNCH)
		{
			game->f2->health -= 150;
		}
	}
	else if(game->f1->flags &= FIGHTFLAG_MOVEL)
	{
		if(game->f1->x < 0)
		{
			game->f1->x = game->f1->x - game->f1->walk_acc;
			game->f1->hitbox.x = game->f1->x;
		}
	}
	else if(game->f1->flags &= FIGHTFLAG_MOVER)
	{
		if(game->f1->x > 845)
		{
			game->f1->x = game->f1->x + game->f1->walk_acc;
			game->f1->hitbox.x = game->f1->x;
		}
	}
	else if(game->f1->flags &= FIGHTFLAG_JUMPING){
		game->f1->y = game->f1->y + game->f1->vy;
		game->f1->vy -= 1;
		game->f1->hitbox.y = game->f1->y;
		if(game->f1->y <= 410){
			game->f1->flags &= ~FIGHTFLAG_JUMPING;
			game->f1->y = 410;
			game->f1->vy = 0;
			SetAnimation(f1->sprite, ANIMATION_IDLE);
			game->f1->hitbox.y = game->f1->y;
		}
	}
	if(game->f2->flags &= FIGHTFLAG_LIGHTATT || game->f2->flags &= FIGHTFLAG_MEDATT || game->f2->flags &= FIGHTFLAG_HEVATT)
	{
		if(has_hit == 1 && game->f2->flags &= FIGHTFLAG_LIGHTATT)
		{
			game->f1->health -= 15;
			SetAnimation(f2->sprite, ANIMATION_ATTL);
		}
		else if(has_hit == 1 && game->f2->flags &= FIGHTFLAG_MEDATT)
		{
			game->f1->health -= 25;
			SetAnimation(f2->sprite, ANIMATION_ATTM);
		}
		else if(has_hit == 1 && game->f2->flags &= FIGHTFLAG_HEVATT)
		{
			game->f1->health -= 50;
			SetAnimation(f2->sprite, ANIMATION_ATTH);
		}
		else if(has_hit == 1 && game->f2->flags &= FIGHTFLAG_LAUNCH)
		{
			game->f1->health -= 150;
			SetAnimation(f2->sprite, ANIMATION_LAUNCH);
		}
	}
	else if(game->f2->flags &= FIGHTFLAG_MOVEL)
	{
		if(game->f2->x < 0)
		{
			game->f2->x = game->f2->x - game->f2->walk_acc;
			game->f2->hitbox.x = game->f2->x;
			SetAnimation(f2->sprite, ANIMATION_WALKL);
		}
	}
	else if(game->f2->flags &= FIGHTFLAG_MOVER)
	{
		if(game->f2->x > 845)
		{
			game->f2->x = game->f2->x + game->f2->walk_acc;
			game->f2->hitbox.x = game->f2->x;
			SetAnimation(f2->sprite, ANIMATION_WALKR);
		}
	}
	else if(game->f2->flags &= FIGHTFLAG_JUMPING){
		game->f2->y = game->f2->y + game->f2->vy;
		game->f2->vy -= 1;
		game->f2->hitbox.y = game->f2->y;
		if(game->f2->y <= 410){
			game->f2->flags &= ~FIGHTFLAG_JUMPING;
			game->f2->y = 410;
			game->f2->vy = 0;
			SetAnimation(f2->sprite, ANIMATION_IDLE);
			game->f2->hitbox.y = game->f1->y;
		}
	}
}