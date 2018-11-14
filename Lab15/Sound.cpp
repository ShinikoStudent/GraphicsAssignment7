//handles the audio for the scene, playbgm, pause, resume, halt, and free audio files
#include "Sound.h"
#include <SDL_mixer.h>
#include <SDL.h>
#include <iostream>
#include <stdlib.h>
#include <stdio.h>


using namespace std;

#define MUS_PATH "bgm.wav"
// prototype for our audio callback
// see the implementation for more information
void my_audio_callback(void *userdata, Uint8 *stream, int len);

// variable declarations
static Uint8 *audio_pos; // global pointer to the audio buffer to be played
static Uint32 audio_len; // remaining length of the sample we have to play


Sound::Sound()
{


}

int Sound::setup() {
	cout << "setup test \n";

	SDL_Init(SDL_INIT_AUDIO);
	if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0) // was MIX_DEFAULT_CHANNELS but that gave an error. might need to play around wirh 4 param for sound qual
	{
		cout << "sound error reason is " << Mix_GetError() << "\n";
	}
	//bgm = Mix_LoadMUS("C:/Users/Keely Canniff/Documents/uop/fall 2018/comp 153/assignment 7 grp/GraphicsAssignment7/audio/bgm.mp3"); //ba;




	/* Initialize only SDL Audio on default device */
	if (SDL_Init(SDL_INIT_AUDIO) < 0)
	{
		return 1;
	}



	cout << "setup test end \n";
	return 1;
}


void Sound::Init() {

	// load support for the OGG and MOD sample/music formats
	int flags = MIX_INIT_OGG | MIX_INIT_MOD;
	int initted = Mix_Init(flags);
	if (initted&flags != flags) {
		printf("Mix_Init: Failed to init required ogg and mod support!\n");
		printf("Mix_Init: %s\n", Mix_GetError());
	}


	


}

void Sound::playCoinSoundEffect() {
	soundEffect = Mix_LoadWAV("sound/coin.wav"); 
	Mix_PlayChannel(0, soundEffect, 0); //was -1, soundEffect, 0
}
void Sound::playTickingSoundEffect() {
	//cout << "Play ticking \n";
	soundEffect = Mix_LoadWAV("sound/ticking.wav"); 
	Mix_PlayChannel(1, soundEffect, 0);
}
void Sound::stopTickingSoundEffect() {
	//cout << "stop ticking \n";
	Mix_PlayChannel(1, soundEffect, 0);
	Mix_HaltChannel(1);
}

void Sound::playWinSoundEffect() {
	//cout << "Play ticking \n";
	Mix_HaltChannel(1);
	soundEffect = Mix_LoadWAV("sound/win.wav");
	Mix_PlayChannel(2, soundEffect, 0);
}

void Sound::playFootSteps() {
	//Mix_HaltChannel(1);
	soundEffect = Mix_LoadWAV("sound/walking.wav");
	Mix_PlayChannel(3, soundEffect, 0);
	Mix_Volume(3, MIX_MAX_VOLUME / 4);
}

void Sound::stopFootSteps() {
	//Mix_HaltChannel(1);
	//Mix_PlayChannel(3, soundEffect, 0);
	Mix_HaltChannel(3);
}


void Sound::freeSounds() {
	//free up sounds
	cout << "Play free sound /n";
	Mix_FreeChunk(soundEffect);
	Mix_FreeMusic(bgm);
	bgm = nullptr;
	soundEffect = nullptr;
	walking = nullptr;
	Mix_FreeChunk(walking);
	Mix_Quit(); //close the music mix 
	SDL_CloseAudioDevice(deviceId);
	SDL_FreeWAV(wavBuffer);



}

void Sound::playBGM() {
	cout << "Play BGM \n";
	//bgm = Mix_LoadMUS("sound/barradeen-sea.wav");
	bgm = Mix_LoadMUS("sound/speech.wav");

	if (!bgm || bgm == NULL) {
		printf(" bgm error Mix_LoadMUS(): %s\n", Mix_GetError());
		// this might be a critical error...
	}
	Mix_PlayMusic(bgm, 0); //keep looping the song 
	Mix_VolumeMusic(MIX_MAX_VOLUME / 2);
	//}


}

bool Sound::isBGMplaying() {
	if (Mix_PlayingMusic()) {
		return true;
	}
	else {
		return false;
	}
}

void Sound::pauseBGM() {
	//cout << "pause BGM /n";
	Mix_PauseMusic();
}

void Sound::resumeMusic() {
	//cout << "resume BGM /n";

	if (Mix_PausedMusic()) {
		Mix_ResumeMusic();
	}
}

void Sound::haltMusic() {
	Mix_HaltMusic(); // halts music and puts play position to beginning
}


