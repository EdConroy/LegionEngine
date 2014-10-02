#include "graphics.h"

#define MAX_FIGHTERS 2

typedef struct Fighter_T
{
	Sprite* sprite;
	SDL_Rect hitbox;
	float walk_speed, walk_acc, run_speed, run_acc, fall_acc,
		jump_speed, jump_height, air_drift;
	float meter_level, stun_timer, shield_stun, 
		hitstop, current_speed, current_acc;
	int x, y, last_x, last_y, health, weight, combo_count, state, facing, jump_count,
		used, is_grounded;
}Fighter;

void InitFighterSprite();
void InitCombatant(Fighter* f);
void InitCombatant2(Fighter* f);
void InitFighterList();

Fighter * getFighter(int player);

void Block(Fighter* attack, Fighter* defender, SDL_Surface *buffer);
void Dash(Fighter* inflictor, SDL_Surface *buffer, Uint8* keys);
void FighterController(Fighter* inflictor, Fighter* f2, SDL_Surface *buffer, Uint8* keys);
//void Player2FighterController(Fighter* f, SDL_Surface* buffer, Uint8* keys);
void DrawHealthBar(Fighter* f, SDL_Surface *buffer, int x, int y);


void Print();
void FreeFighter(Fighter* f);
void CloseFighter();
