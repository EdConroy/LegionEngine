#include "d_fighter.h"

struct
{
	int x;
	int y;
	int w;
	int h;
	int last_x;
	int last_y;
}F_Bck;

void InitBck()
{
	F_Bck.x=0;
	F_Bck.y=0;
	F_Bck.w=0;
	F_Bck.h=0;
	F_Bck.last_x=0;
	F_Bck.last_y=0;
}

void Draw(Game_T* game, SDL_Surface* buffer)
{
	//Draw the current stage
  if(game->stage != NULL)
    SDL_BlitSurface(game->stage->image,NULL,game->buffer,NULL);
  if(game->f1->flags &= FIGHTFLAG_IDLE)
  {
	  	game->f1->sprite = LoadSprite("images/StriderIdle.png",114,92);
		DrawSprite(game->f1->sprite,buffer,game->f1->x, game->f1->y,0);
  }
  else if(game->f1->flags &= FIGHTFLAG_WALKL)
  {
	  	game->f1->sprite = LoadSprite("images/StriderWalk.png",114,101);
		DrawSprite(game->f1->sprite,buffer,game->f1->x - game->f1->walk_acc, game->f1->y,0);
  }
  else if(game->f1->flags &= FIGHTFLAG_WALKR)
  {
	  	game->f1->sprite = LoadSprite("images/StriderWalk.png",114,101);
		DrawSprite(game->f1->sprite,buffer,game->f1->x + game->f1->walk_acc,game->f1->y,0)
  }
  else if(game->f1->flags &= FIGHTFLAG_LIGHTATT)
  {
		game->f1->sprite = LoadSprite("images/StriderLightAttack.png",179,138);
		DrawSprite(game->f1->sprite,buffer,game->f1->x,game->f1->y,0)
  }
  else if(game->f1->flags &= FIGHTFLAG_MEDATT)
  {
	  game->f1->sprite = LoadSprite("images/StriderMediumAttack.png",198,140);
	  DrawSprite(game->f1->sprite,buffer,game->f1->x,game->f1->y,0)
  }
  else if(game->f1->flags &= FIGHTFLAG_HEVATT)
  {
	  	game->f1->sprite = LoadSprite("images/StriderHeavyAttack.png",206,140);
		DrawSprite(game->f1->sprite,buffer,game->f1->x, game->f1->y,F_Sprite.frame);
  }
  else if(game->f1->flags &= FIGHTFLAG_LAUNCH)
  {
	  game->f1->sprite = LoadSprite("images/StriderLauncherAttack.png",198,162);
	  DrawSprite(game->f1->sprite,buffer,game->f1->x, game->f1->y,F_Sprite.frame);
  }
  game->f1->sprite = NULL;
	if(game->f1->sprite != NULL)
	{
		FreeSprite(game->f1->sprite);
	}
}
void DrawHealthBar(Fighter* f, SDL_Surface *buffer, int x, int y)
{
	for(int i=0; i<f->health;++i)
		for(int j=0; j < 30; ++j)
			DrawPixel(buffer,0,255,0,(30 + i) + x,(30 + j) + y);
}
void Parallax(Sprite* fst, Sprite* scd, SDL_Surface* screen, int x, int y)
{
	for(int i = 0; i < 40; ++i)
	{
		DrawSprite(fst,screen,F_Bck.x+32, 510,0);
		F_Bck.last_x = F_Bck.x; 
		F_Bck.x = F_Bck.last_x + 32;
	}
	for(int j = 0; j < 80; ++j)
	{
		DrawSprite(scd,screen,F_Bck.x + 64, 610, 2);
		F_Bck.last_x = F_Bck.x; 
		F_Bck.x = F_Bck.last_x + 32;
	}
}
void FreeBck(Sprite* fst, Sprite* scd)
{
	FreeSprite(fst);
	FreeSprite(scd);
	fst = NULL;
	scd = NULL;
}
