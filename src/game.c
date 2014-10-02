#include <stdlib.h>
#include "glib.h"
#include "SDL.h"
#include "SDL_image.h"
#include "graphics.h"
#include "fighter.h"
#include "background.h"

extern SDL_Surface *screen;
extern SDL_Surface *buffer; /*pointer to the draw buffer*/
extern SDL_Rect Camera;

void Init_All();


/*this program must be run from the directory directly below images and src, not from within src*/
/*notice the default arguments for main.  SDL expects main to look like that, so don't change it*/
int main(int argc, char *argv[])
{
  SDL_Surface *temp;
  SDL_Surface *bg;
  Sprite *tile;
  Sprite *test;
  Fighter* f;
  Fighter* f2;
  int done;
  int keyn;
  int i;
  int mx,my;
  Uint8 *keys;
  Init_All();
  temp = IMG_Load("images/bgtest.png");/*notice that the path is part of the filename*/
  if(temp != NULL)						/*ALWAYS check your pointers before you use them*/
    bg = SDL_DisplayFormat(temp);
  SDL_FreeSurface(temp);
  if(bg != NULL)
    SDL_BlitSurface(bg,NULL,buffer,NULL);
  tile = LoadSprite("images/32_32_16_2sprite.png",32,32);
  test = LoadSprite("images/testbck.png",32,32);
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
  do
  {
    ResetBuffer();
	SDL_PumpEvents();
	Parallax(tile,test,screen,32,32);
	keys = SDL_GetKeyState(&keyn);
	FighterController(f,f2,screen,keys);
	DrawHealthBar(f,screen,0,0);
	DrawHealthBar(f2,screen,310,0);
	/*
    if(SDL_GetMouseState(&mx,&my))
    {
      DrawSprite(tile,buffer,(mx /32) * 32,(my /32) * 32,0); 
    }
	*/
	if(f->health <= 0 || f2->health <= 0)
	{
		done = 1;
	}
    //DrawMouse();
	NextFrame();

    if(keys[SDLK_ESCAPE])done = 1;
  }while(!done);
  exit(0); /*technically this will end the program, but the compiler likes all functions that can return a value TO return a value*/
  return 0;
  FreeFighter(f);
  FreeFighter(f2);
  FreeBck(tile,tile);
}

void CleanUpAll()
{
  CloseSprites();
  //CloseFighter();
  /*any other cleanup functions can be added here*/ 
}

void Init_All()
{
  Init_Graphics();
  InitBck();
  InitFighterList();
  InitFighterSprite();
  //InitMouse();
  atexit(CleanUpAll);
}

