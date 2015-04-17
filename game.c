#include <stdlib.h>
#include "glib.h"
#include "SDL.h"
#include "SDL_image.h"
#include "graphics.h"
#include "fighter.h"
#include "audio.h"

extern Fighter Fighters[MAX_FIGHTERS];
extern SDL_Surface *screen;
extern SDL_Surface *buffer; /*pointer to the draw buffer*/
extern SDL_Rect Camera;

void Init_All();


/*this program must be run from the directory directly below images and src, not from within src*/
/*notice the default arguments for main.  SDL expects main to look like that, so don't change it*/
int main(int argc, char *argv[])
{
  SDL_Surface *temp, *temp2;
  SDL_Surface *bg;
  Mix_Music* music;
  Fighter* f;
  Fighter* f2;
  int done;
  int keyn;
  int current_stage = 0;
  int editing = 0;
  Sprite* v_screen;

  Uint8 *keys;
  Init_All();
  temp2 = IMG_Load("images/MvCStage2.png");/* second stage */
  temp = IMG_Load("images/MvCStage.png");/*notice that the path is part of the filename*/
  if(temp != NULL)						/*ALWAYS check your pointers before you use them*/
    bg = SDL_DisplayFormat(temp);
  if(bg != NULL)
    SDL_BlitSurface(bg,NULL,buffer,NULL);
	music = Mix_LoadMUS("sounds/Clocktower.wav");
  done = 0;
  f = getFighter(0);
  f2 = getFighter(1);
/*
Uncomment to enter editor mode, it is recommended to switch the game to half screen to use
effectively
*/
  do
  {
	editing = EditFighter();
	if(editing == 0)
	{
		printf("Do you want to edit another fighter?\n 0 - Yes\n 1 - No\n");
		scanf("%d",&editing);
	}
	if(editing != 0)
	{
		editing = 1;
	}
  }while(editing = 0);
  InitCombatant(f, FIGHT_SENTINEL);
  InitCombatant2(f2, FIGHT_DOOM);
  LoadFighter(f,FIGHT_SENTINEL);
  LoadFighter(f2,FIGHT_DOOM);
  PlayMusic(music);
  do
  {
    ResetBuffer();
	SDL_PumpEvents();
	keys = SDL_GetKeyState(&keyn);
	if(keys[SDLK_p]) /* Changes the stages */
	{
		if(current_stage == 0)
		{
			if(temp2 != NULL)						
				bg = SDL_DisplayFormat(temp2);
			if(bg != NULL)
				SDL_BlitSurface(bg,NULL,buffer,NULL);
			current_stage = 1;
		}
	}
	if(keys[SDLK_o])
	{
		if(current_stage == 1)
		{
			if(temp != NULL)						/*ALWAYS check your pointers before you use them*/
				bg = SDL_DisplayFormat(temp);
			if(bg != NULL)
				SDL_BlitSurface(bg,NULL,buffer,NULL);
			current_stage = 0;
		}
	}
	FighterPull(f, keys); /* Gets the key input from the user */
	FighterPull2(f2,keys);
	FighterController(f,f2,1); /* Translates the key input into actions*/
	FighterController(f2,f,2);
	DrawFighter1(f, screen);
	DrawFighter2(f2, screen);
	DrawHealthBar(f,screen,0,0);
	DrawHealthBar(f2,screen,610,0);
	if(f2->health <= 0)
	{
		if(f->char_flag == FIGHT_STRIDER)
			v_screen = LoadSprite("images/StriderVictory.png",500,500);
		else if(f->char_flag == FIGHT_DOOM)
			v_screen = LoadSprite("images/DoomVictory.png",500,500);
		else if(f->char_flag == FIGHT_MAGNETO)
			v_screen = LoadSprite("images/MagnetoVictory.png",500,500);
		else if(f->char_flag == FIGHT_SENTINEL)
			v_screen = LoadSprite("images/SentinelVictory.png",500,500);
		else if(f->char_flag == FIGHT_MEGAMAN)
			v_screen = LoadSprite("images/MegaManVictory.png",500,500);
		DrawSprite(v_screen,screen,250,250,0);
	}
	else if(f->health <= 0)
	{
		if(f2->char_flag == FIGHT_STRIDER)
			v_screen = LoadSprite("images/StriderVictory.png",500,500);
		else if(f2->char_flag == FIGHT_DOOM)
			v_screen = LoadSprite("images/DoomVictory.png",500,500);
		else if(f2->char_flag == FIGHT_MAGNETO)
			v_screen = LoadSprite("images/MagnetoVictory.png",500,500);
		else if(f2->char_flag == FIGHT_SENTINEL)
			v_screen = LoadSprite("images/SentinelVictory.png",500,500);
		else if(f2->char_flag == FIGHT_MEGAMAN)
			v_screen = LoadSprite("images/MegaManVictory.png",500,500);
		DrawSprite(v_screen,screen,250,250,0);
	}
	NextFrame();

    if(keys[SDLK_ESCAPE])done = 1;
  }while(!done);
  SDL_FreeSurface(temp); /* Frees the two background images from memory*/
  SDL_FreeSurface(temp2);
  FreeMusic(music);
  FreeSprite(v_screen);
  exit(0); /*technically this will end the program, but the compiler likes all functions that can return a value TO return a value*/
  FreeFighter(f); /* Clean up any used data by the fighters*/
  FreeFighter(f2);
  return 0;
}

void CleanUpAll()
{
  CloseSprites();
  /*any other cleanup functions can be added here*/ 
}

void Init_All()
{
  Init_Graphics();
  InitMusic();
  InitFighterList();
  atexit(CleanUpAll);
}