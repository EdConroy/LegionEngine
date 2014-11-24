#ifndef _FIGHTER_
#define _FIGHTER_

#include "graphics.h"

#define IS_SET(a,b)				(a & b)
#define SET_FLAG(a,b)			(a |= b)
#define REMOVE_FLAG(a,b)		(a &= ~b)

#define MAX_FIGHTERS				2

#define FIGHT_STRIDER				0
#define FIGHT_DOOM					1
#define FIGHT_MAGNETO				2
#define FIGHT_MEGAMAN				3
#define FIGHT_SENTINEL				4
/* 
I should enumerate these but I got caught up in a Vin Diesel
brutally murders a bunch of people in space movie to change it
then Keanu Reeves and Satan troll Gabriel really hard until God
starts trolling Satan then Satan rage quits
*/
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
/*
This would be a lot funnier if you read these in Charles Barkley's voice
*/
#define JUMPFLAG_MOVEL				0
#define JUMPFLAG_MOVER				1
#define JUMPFLAG_LIGHT				2
#define JUMPFLAG_MED				3
#define JUMPFLAG_HEV				4
#define JUMPFLAG_LAUNCH				5
/*
Shoutouts to the AniManiacs for the idea for the naming convention here
*/
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
#define ANIMFLAG_BLOCKL				11
#define ANIMFLAG_HITSTUN			12

typedef struct Fighter_T
{
	Sprite* sprite; /* Disclaimer: Not an actual Coke product*/
	SDL_Rect hitbox; /* Disclaimer: Not an actual Twitch rip off*/
	
	float walk_speed;
	float walk_acc;
	float run_speed; 
	float run_acc; 
	float fall_acc;
	float jump_speed; 
	float jump_height; 
	float air_drift;
	float current_speed;
	float current_acc;

	float meter_level; 
	float stun_timer; 
	float shield_stun; 

	int x; /* Goin' give it to ya */
	int y; 
	int health;
	int weight;
	int combo_count; /* So the game keeps track of how badly you are getting beat*/
	int facing; /* So the fighter knows which direction he is facing*/
	int jump_count;
	int used; /* Used for memory management, except for the fact that it isn't at all*/ 
	int vy; 
	long flags; 
	long anim_flags; 
	long f_jump; /* flag to determine the state in the air of the fighter */
	long char_flag; /* Flag that indicates the player character*/

	int light_dmg;
	int med_dmg;
	int hev_dmg;
	int launch_dmg;
}Fighter;

void InitFighterSprite(); /* Sets the default animation state for fighters */
void InitCombatant(Fighter* f, long character); /* Initializes the spawns and values for the fighter */
void InitCombatant2(Fighter* f, long character);
void InitFighterList(); /* Initializes the fighter list and populates it */

Fighter * getFighter(int player);

void FighterPull(Fighter* f1, Uint8* keys); /* Gets the inputs from the user and sets flags based on those
														 inputs */
void FighterPull2(Fighter* f2, Uint8* keys); /* Same as FighterPull except for player 2, will be abstacted with 
											 Fighter Pull in the future but for now it will have to suffice. 
											 Not used in Demo */

void DrawFighter1(Fighter* f1, SDL_Surface* buffer); /* Draws the fighter based on the flags set by FighterPull: Not used in Demo */
void DrawFighter2(Fighter* f1, SDL_Surface* buffer);

void FighterController1(Fighter* f1, Fighter* f2, SDL_Surface *buffer);
void FighterController(Fighter* f1, Fighter* f2, SDL_Surface *buffer);/* Does all three of the aforementioned methods
																				   really ineffiecent but functional.  Also a nightmare
																				   to make sense of if you didn't work on it */
void DrawHealthBar(Fighter* f, SDL_Surface *buffer, int x, int y);/* Makes the health bar for both green and red health*/

void FreeFighter(Fighter* f);/* Frees all of the current memory held by the fighter and sets it to null*/
void CloseFighter();/* Frees all the fighters in the fighter list*/

void LoadFighter(Fighter* f, long character);
void EditFighter(Fighter* f);

#endif
