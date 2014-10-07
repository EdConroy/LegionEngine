#include "graphics.h"
#include "game.h"

#define MAX_FIGHTERS 2

#define FIGHTFLAG_JUMPING	0x1
#define FIGHTFLAG_IDLE		0x2
#define FIGHTFLAG_CROUCHING 0x4
#define FIGHTFLAG_LIGHTATT	0x8
#define FIGHTFLAG_MEDATT	0x10
#define FIGHTFLAG_HEVATT	0x20
#define FIGHTFLAG_LAUNCH	0x40
#define FIGHTFLAG_BLOCK		0x80
#define FIGHTFLAG_MOVER		0x100
#define FIGHTFLAG_MOVEL		0x200

typedef struct Fighter_T
{
	Sprite *sprite;
	SDL_Rect hitbox;
	float walk_speed; /**< The walking speed of the fighter */
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
	long flags;
	int x;
	int y;
	int vy;
	int last_x;
	int last_y;
	int health;
	int weight;
	int combo_count;
	int state;
	int facing;
	int jump_count;
	int used;
	bool is_grounded;
}Fighter;

void InitFighterSprite();
void InitCombatant(Fighter* f);
void InitCombatant2(Fighter* f);
void InitFighterList();

Fighter * getFighter(int player);

void Block(Fighter* attack, Fighter* defender);
void Dash(Fighter* inflictor, Uint8* keys);
void FighterController(Fighter* inflictor, Fighter* f2, Uint8* keys);
void Pull(Game_T* game, Uint8* keys);
void Update(Game_T* game);


void FreeFighter(Fighter* f);
void CloseFighter();