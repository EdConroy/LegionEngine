#include "background.h"

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
