#include "audio.h"

Mix_Chunk* light;
Mix_Chunk* medium;
Mix_Chunk* heavy;
Mix_Chunk* launcher;
Mix_Chunk* victory;


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
	light = Mix_LoadWAV( "scratch.wav" ); /* Add Sound effects here */
    medium = Mix_LoadWAV( "high.wav" ); 
    heavy = Mix_LoadWAV( "medium.wav" ); 
    launcher = Mix_LoadWAV( "low.wav" );
    victory = Mix_LoadWAV( "low.wav" );

    //If there was a problem loading the sound effects
    if(light == NULL || medium == NULL || heavy == NULL || launcher == NULL || victory == NULL)
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
int PlayEffect(int state, int character)
{
    if(state == 1)
    {
        //Play the scratch effect
        if( Mix_PlayChannel( -1, light, 0 ) == -1 )
        {
            return 1;    
        }
    }
    else if(state == 2)
    {
        //Play the high hit effect
        if( Mix_PlayChannel( -1, medium, 0 ) == -1 )
        {
            return 1;    
        }
    }
    else if(state == 3)
    {
        //Play the medium hit effect
        if( Mix_PlayChannel( -1, heavy, 0 ) == -1 )
        {
            return 1;    
        }
    }
    else if(state == 4)
    {
        if( Mix_PlayChannel( -1, launcher, 0 ) == -1 )
        {
            return 1;    
        }
    }
	else if(state == 5)
	{
		if( Mix_PlayChannel( -1, victory, 0) == -1)
		{
			return 1;
		}
	}
	return 0;
}
void FreeMusic(Mix_Music* music)
{
	Mix_FreeMusic(music);
	Mix_CloseAudio();
}
