#include "collision.h"

int AABB(SDL_Rect attacker, SDL_Rect defender)
{
	//Checks if the boxes intersect by comparing the boxes (x and widths) and (y and heights)
	if((attacker.x + attacker.w) > defender.x && (defender.x + defender.w) > attacker.x
		&& (attacker.y + attacker.w) > defender.y && (defender.y + defender.h) > attacker.y)
	{
		ReturnBox(attacker,defender,1);
		return 1;
	}
	return 0;
}
SDL_Rect ReturnBox(SDL_Rect a, SDL_Rect d, int has_hit)
{
	SDL_Rect c;
	if(has_hit == 1)
	{
		//Finding the max of the x and y of the sprite
		if(a.x > d.x)
			c.x = a.x;
		else if(d.x > a.x)
			c.x = d.x;
		else if(a.y > d.y)
			c.y = a.y;
		else if(d.y > a.y)
			c.y = d.y;
		//Finding the min for the width of the sprite
		if((a.x + a.w) < (d.x + d.w))
			c.w = (a.x + a.w) - c.x;
		else if((d.x + d.w) < (a.x + a.w))
			c.w = (a.x + a.w) - c.x;
		//Finding the min for the height of the sprite
		if((a.y + a.h) < (d.y + d.h))
			c.h = (a.y + a.h) - c.y;
		else if((d.y + d.h) < (a.y + a.h))
			c.h = (d.y + d.h) - c.y;
		//Draws the sprite
		for( int x = 0; x < c.w; ++x)
			for( int y = 0; y < c.h; ++y)
				//DrawPixel(screen,255,0,0,(c.x + x),(c.y + y));
		return c;
	}
	return c;
}