//FileName:		viewcontroller.h
//Programmer:	Dan Cliburn
//Date:			4/20/2015
//Purpose:		This file defines the header for the Viewcontroller class
//This class is responsible for setting up SDL and handing user input.

#ifndef VIEWCONTROLLER_H
#define VIEWCONTROLLER_H

#include <SDL.h>  //Include SDL.h before glm.hpp
#include "model.h"
#include "SDL_mixer.h"
#include <glm.hpp>
#include "gameController.h"
#include "Sound.h"

using namespace glm;

class Viewcontroller
{
	private:
		bool quit;
		bool playSoundEffectOnceTicking;
		bool won;
		//Variables to control user movement
		vec3 tempEye;
		vec3 eye;
		vec3 aim;
		vec3 up;
		int boarderValue;
		int timer [4]; //used to make the player stay under the object
		int doneTimer;
		mat4 view_matrix;
		double MOVEANGLE;
		double LOOKANGLE;
		double moveForward;
		double moveSideways;
		double baseX;
		double baseY;
		gameController gc;
		Sound audio;
		Model theWorld;  //Model we want to render
		bool playSoundEffectOnce; //used to make sure the audio is only fired once
		SDL_Window *window;
		SDL_GLContext ogl4context;
		Mix_Music *music;

	public:
		Viewcontroller();

		bool init();  //initializes SDL
		void display();
		void run();
		bool handleEvents(SDL_Event *theEvent);
		void updateLookAt();
		bool isWalking;
		bool playWalkingOnce; //flag used to only play the sound once.
		bool printWin; //used to print the win once


};

#endif