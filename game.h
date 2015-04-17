#include "fighter.h"

typedef struct Game_T
{
	Fighter *f1;
	Fighter *f2;
	int game_state;
	Stage_T stage;
}Game_T;