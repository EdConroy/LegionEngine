#include <stdlib.h>
//#include <time.h>
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
	/*
	time_t time;
	long cur;
	localtime(&time);
	*/
  SDL_Surface *temp, *temp2;
  SDL_Surface *bg;
  Sprite *tile;
  Mix_Music* music;
  Fighter* f;
  Fighter* f2;
  int done;
  int keyn;
  int current_stage = 0;
  /*
  int i;
  int mx,my;
  */
  Uint8 *keys;
  Init_All();
  temp2 = IMG_Load("images/MvCStage2.png");/* second stage */
  temp = IMG_Load("images/MvCStage.png");/*notice that the path is part of the filename*/
  if(temp != NULL)						/*ALWAYS check your pointers before you use them*/
    bg = SDL_DisplayFormat(temp);
  /* SDL_FreeSurface(temp); */
  if(bg != NULL)
    SDL_BlitSurface(bg,NULL,buffer,NULL);
  tile = LoadSprite("images/32_32_16_2sprite.png",32,32);
	music = Mix_LoadMUS("sounds/Swamp.wav");
  /*
  if(tile != NULL)for(i = 0;i < 12;i++)
  {
    DrawSprite(tile,buffer,i * tile->w,0,0);
  }
  */
  done = 0;
  f = getFighter(0);
  f2 = getFighter(1);
  InitCombatant(f);
  InitCombatant2(f2);
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
	FighterController1(f,f2,screen); /* Translates the key input into actions*/
	FighterController(f,f2,screen,keys);
	DrawFighter1(f,FIGHT_STRIDER,screen);
	DrawFighter1(f2,FIGHT_DOOM,screen);
	/*
	UpdateFighter(f,f2);
	*/
	DrawHealthBar(f,screen,0,0);
	DrawHealthBar(f2,screen,610,0);
	/*
    if(SDL_GetMouseState(&mx,&my))
    {
      DrawSprite(tile,buffer,(mx /32) * 32,(my /32) * 32,0); 
    }
	*/
	if(f->health <= 0 || f2->health <= 0)
	{
		done = 1; /* Upon defeat the game exits */
		if(f2->health <= 0)
			fprintf(stdout,"Game Over: Strider Hiryu Wins\n");
		else
			fprintf(stdout,"Game Over: Dr. Doom Wins\n");
		Mix_HaltMusic();
	}
	/*
	if(f->health <= 0)
	{
		if(v_screen != NULL)
		{
			FreeSprite(v_screen);
		}
		v_screen = LoadSprite("images/StriderVictory.png",1024,768);
		DrawSprite(v_screen,victory,500,500,0);
		done = 1;
	}
	else if(f2->health <= 0)
	{
		if(v_screen != NULL)
		{
			FreeSprite(v_screen);
		}
		v_screen = LoadSprite("images/DoomVictory.png",1024,768);
			DrawSprite(v_screen,victory,500,500,0);
		done = 1;
	}
	*/
    /* DrawMouse(); */
	NextFrame();

    if(keys[SDLK_ESCAPE])done = 1;
  }while(!done);
  SDL_FreeSurface(temp); /* Frees the two background images from memory*/
  SDL_FreeSurface(temp2);
  FreeMusic(music);
  exit(0); /*technically this will end the program, but the compiler likes all functions that can return a value TO return a value*/
  FreeFighter(f); /* Clean up any used data by the fighters*/
  FreeFighter(f2);
  return 0;
}

void CleanUpAll()
{
  CloseSprites();
  /* CloseFighter(); */
  /*any other cleanup functions can be added here*/ 
}

void Init_All()
{
  Init_Graphics();
  InitMusic();
  InitFighterList();
  InitFighterSprite();
  /* InitMouse(); */
  atexit(CleanUpAll);
}
