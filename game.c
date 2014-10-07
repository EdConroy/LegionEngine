#include <stdlib.h>
#include "glib.h"
#include "SDL.h"
#include "SDL_image.h"
#include "graphics.h"
#include "fighter.h"
#include "game.h"

#define GAMESTATE_DONE 0x1

extern SDL_Surface *screen;
extern SDL_Surface *buffer; /*pointer to the draw buffer*/
extern SDL_Rect Camera;

void Init_All();

Game_T *game;

/*this program must be run from the directory directly below images and src, not from within src*/
/*notice the default arguments for main.  SDL expects main to look like that, so don't change it*/
int main(int argc, char *argv[])
{
  game = (Game_T*)malloc(sizeof(Game_T);
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
  tile = LoadSprite("images/32_32_16_2sprite.png",32,32);
  test = LoadSprite("images/testbck.png",32,32);
  done = 0;
  game->f1 = getFighter(0);
  game->f2 = getFighter(1);
  InitCombatant(game->f1);
  InitCombatant2(game->f2);
  do
  {
    ResetBuffer();
	SDL_PumpEvents();
	keys = SDL_GetKeyState(&keyn);
	Poll(game,keys);
	Update(game);
	Draw(game,screen);
	Parallax(tile,test,screen,32,32);
	DrawHealthBar(game->f1,screen,0,0);
	DrawHealthBar(game->f2,screen,310,0);
	if(game->f1->health <= 0 || game->f2->health <= 0)
	{
		done = 1;
	}
	NextFrame();

    if(keys[SDLK_ESCAPE])done = 1;
  }while(!done);
  exit(0); /*technically this will end the program, but the compiler likes all functions that can return a value TO return a value*/
  return 0;
  FreeFighter(game->f1);
  FreeFighter(game->f2);
  FreeBck(tile,test);
}

void Initialize()
{
  //Initialize Background
  SDL_Surface *bg;
  SDL_Surface *temp = IMG_Load("images/bgtest.png");/*notice that the path is part of the filename*/
  if(temp != NULL)						/*ALWAYS check your pointers before you use them*/
    bg = SDL_DisplayFormat(temp);
  SDL_FreeSurface(temp);
  Stage_T *stage;
  stage = (Stage_T *)malloc(sizeof(Stage_T));
  stage->image = bg;
  game->stage = stage;
}
void CleanUpAll()
{
  CloseSprites();
  //CloseFighter();
  /*any other cleanup functions can be added here*/ 
}

void Init_All()
{
	Initialize();
  Init_Graphics();
  InitBck();
  InitFighterList();
  InitFighterSprite();
  //InitMouse();
  atexit(CleanUpAll);
}

