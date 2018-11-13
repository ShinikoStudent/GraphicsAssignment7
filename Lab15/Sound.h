#pragma once
#include <SDL_mixer.h>
#include <SDL.h>
//#include <SDL2/SDL.h>
#include <iostream>
#include <stdlib.h>

class Sound
{
public:
	Sound();
	void freeSounds();
	//Mix_Music *bgm = Mix_LoadMUS("bgm.mp3"); //background music, longer than 10 seconds make it mix_music, WAV, MP3
	Mix_Music *bgm;// = Mix_LoadMUS("C:/Users/Keely Canniff/Documents/uop/fall 2018/comp 153/assignment 7 grp/GraphicsAssignment7/audio/bgm.mp3"); //ba;
	Mix_Chunk *soundEffect;// = Mix_LoadWAV("cow.wav");	 //less than 10 seconds
	void playBGM();
	void pauseBGM();
	void resumeMusic();
	void haltMusic();
	void Init();
	int setup();
	void my_audio_callback(void *userdata, Uint8 *stream, int len);
	void playCoinSoundEffect();
	void playTickingSoundEffect();
	void stopTickingSoundEffect();
	void playWinSoundEffect();

private:
	SDL_AudioSpec wavSpec;
	Uint32 wavLength;
	Uint8 *wavBuffer;
	SDL_AudioDeviceID deviceId;	
};

