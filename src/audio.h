#ifndef _AUDIO_
#define _AUDIO_

#include "SDL_audio.h"
#include "SDL_mixer.h"

void InitMusic();
int LoadMusic(Mix_Music* music);
void PlayMusic(Mix_Music* music);
void FreeMusic(Mix_Music* music);

#endif
