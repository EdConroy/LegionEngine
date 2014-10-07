#include "fighter.h"

typedef struct Game_T
{
	Fighter_T *f1;
	Fighter_T *f2;
	int game_state;
	Stage_T stage;
}Game_T;