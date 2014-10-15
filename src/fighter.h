#include "graphics.h"

#define MAX_FIGHTERS				2

#define FIGHTERFLAG_BLOCK			0
#define FIGHTERFLAG_NOBLOCK			1
#define FIGHTERFLAG_HITH			2
#define FIGHTERFLAG_HITL			3
#define FIGHTERFLAG_WALKL			4
#define FIGHTERFLAG_WALKR			5
#define FIGHTERFLAG_JUMP			6
#define FIGHTERFLAG_IDLE			7
#define FIGHTERFLAG_CROUCH			8
#define FIGHTERFLAG_BLOCKL			9

#define ANIMFLAG_BLOCK				0
#define ANIMFLAG_NOBLOCK			1
#define ANIMFLAG_LIGHT				2
#define ANIMFLAG_MED				3
#define ANIMFLAG_HEV				4
#define ANIMFLAG_LAUNCH				5
#define ANIMFLAG_WALKL				6
#define ANIMFLAG_WALKR				7
#define ANIMFLAG_JUMP				8
#define ANIMFLAG_IDLE				9
#define ANIMFLAG_CROUCH				10

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
	long anim_flags;
}Fighter;

void InitFighterSprite(); /* Sets the default animation state for fighters */
void InitCombatant(Fighter* f); /* Initializes the spawns and values for the fighter */
void InitCombatant2(Fighter* f);
void InitFighterList(); /* Initializes the fighter list and populates it */

Fighter * getFighter(int player);

void FighterPull(Fighter* f1, Fighter* f2, Uint8* keys); /* Gets the inputs from the user and sets flags based on those
														 inputs */
void DrawFighter(Fighter* f1, Fighter* f2, SDL_Surface* buffer); /* Draws the fighter based on the flags set by FighterPull */
void UpdateFighter(Fighter* f1, Fighter* f2); /* Applies logic to to the action based on the fighter's current flag */
void FighterController(Fighter* f1, Fighter* f2, SDL_Surface *buffer, Uint8* keys);/* Does all three of the aforementioned methods
																				   really ineffiecent but functional */
void DrawHealthBar(Fighter* f, SDL_Surface *buffer, int x, int y);/* Makes the health bar for both green and red health*/

void FreeFighter(Fighter* f);/* Frees all of the current memory held by the fighter and sets it to null*/
void CloseFighter();/* Frees all the fighters in the fighter list*/
