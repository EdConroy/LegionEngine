#include "graphics.h"

#define MAX_FIGHTERS				2
#define FIGHTERFLAG_BLOCK			0
#define FIGHTERFLAG_NOBLOCK			1
#define FIGHTERFLAG_HITH			2
#define FIGHTERFLAG_HITL			3

typedef struct Fighter_T
{
	Sprite* sprite;
	SDL_Rect hitbox;
	float walk_speed; 
	float walk_acc; 
	float run_speed; 
	float run_acc; 
	float fall_acc;
	float jump_speed; 
	float jump_height; 
	float air_drift;
	float meter_level; 
	float stun_timer;
	float shield_stun; 
	float hitstop; 
	float current_speed; 
	float current_acc;
	int x;
	int y; 
	int last_x;
	int last_y; 
	int health; 
	int weight; 
	int combo_count;
	int facing; 
	int jump_count;
	int used; 
	int is_grounded; 
	int vy;
	long flags;
}Fighter;

void InitFighterSprite();
void InitCombatant(Fighter* f);
void InitCombatant2(Fighter* f);
void InitFighterList();

Fighter * getFighter(int player);

void Dash(Fighter* inflictor, SDL_Surface *buffer, Uint8* keys);
void FighterController(Fighter* inflictor, Fighter* f2, SDL_Surface *buffer, Uint8* keys);
void DrawHealthBar(Fighter* f, SDL_Surface *buffer, int x, int y);


void Print();
void FreeFighter(Fighter* f);
void CloseFighter();
