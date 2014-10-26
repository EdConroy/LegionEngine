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
}
void PlayMusic(Mix_Music* music)
{
        //Play the music
			Mix_PlayMusic( music, -1 );
}

void FreeMusic(Mix_Music* music)
{
	Mix_FreeMusic(music);
	Mix_CloseAudio();
}
