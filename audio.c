#include "audio.h"

void InitMusic()
{
	if( Mix_OpenAudio( 22050, MIX_DEFAULT_FORMAT, 2, 4096 ) == -1 )
    {
        return;    
    }
}
int LoadMusic(Mix_Music* music)
{
	music = Mix_LoadMUS("sounds/Clocktower.wav");
	if(music == NULL)
	{
		return 0;
	}
	return 1;
}
int LoadSFX(Mix_Music* victory, int character)
{
	if(character == FIGHT_STRIDER)
		victory = Mix_LoadMUS("sounds/StriderVictory.wav");
	else if(character == FIGHT_DOOM)
		victory = Mix_LoadMUS("sounds/DoomVictory.wav");
	else if(character == FIGHT_MAGNETO)
		victory = Mix_LoadMUS("sounds/MagnetoVictory.wav");
	else if(character == FIGHT_MEGAMAN)
		victory = Mix_LoadMUS("sounds/MegaManVictory.wav");
	else if(character == FIGHT_SENTINEL)
		victory = Mix_LoadMUS("sounds/SentinelVictory.wav");

    //If there was a problem loading the sound effects
    if(victory == NULL)
    {
        return 0;    
    }
	return 1;
}
void PlayMusic(Mix_Music* music)
{
    //Play the music
	Mix_PlayMusic( music, -1 );
}
void PlayEffect(Mix_Music* effect)
{
	Mix_PlayMusic(effect,1);
}
void FreeMusic(Mix_Music* music)
{
	Mix_FreeMusic(music);
	Mix_CloseAudio();
}