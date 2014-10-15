#include "graphics.h"

void InitBck(); /* Initializes the backround to default values */
void Parallax(Sprite* fst, Sprite* scd, SDL_Surface* screen, int x, int y); /* Creates two scrolling horizontal sprites 
																			traveling at different speeds across the buffer*/
void FreeBck(Sprite* fst, Sprite* scd); /* Frees the current memory held by the background images */
