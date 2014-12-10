#ifndef _AUDIO_
#define _AUDIO_

#include "SDL_audio.h"
#include "SDL_mixer.h"

#define STAGE_CLOCKTOWER	0
#define STAGE_SWAMP			1
#define STAGE_OTHER			2

void InitMusic();
int LoadMusic(Mix_Music* music);
void PlayMusic(Mix_Music* music);
int PlayEffect(int state, int character);
void FreeMusic(Mix_Music* music);

#endif
