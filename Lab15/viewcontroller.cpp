//FileName:		Viewcontroller.cpp
//Programmer:	Keely Canniff, Jamie Lynn Culilap, and Naomi Nunis
//Date:			4/20/2015
//Purpose:		This file defines the methods for the Viewcontroller class
//See:  http://www.sdltutorials.com/sdl-tutorial-basics/
//		http://www.sdltutorials.com/sdl-opengl-tutorial-basics/
//		http://stackoverflow.com/questions/13826150/sdl2-opengl3-how-to-initialize-sdl-inside-a-function
//for many more details on how to write an OpenGL program using SDL.  You might also want to go to these 
//pages which will link you to other tutorials on how to do stuff with SDL.
//Be warned, however, that a lot of the tutorials describe SDL 1.2, but we will be using SDL 2 in this course.
//
//Specific to this lab, I found some helpful information on the following pages for centering the mouse in SDL 2 
//and trapping it in the window (i.e. you can't move the mouse outside the window)
//	http://stackoverflow.com/questions/10492143/sdl2-mouse-grab-is-not-working
//	http://gamedev.stackexchange.com/questions/33519/trap-mouse-in-sdl
//	http://www.ginkgobitter.org/sdl/?SDL_ShowCursor
//
//A big change in this class is that the user now moves around the scene using a traditional
//first person controller. Movement is controlled with wasd and view direction is changed with the mouse.
//The program now ends when the user presses the <Esc> key.

#include <SDL.h>
#include "viewcontroller.h"
#include <iostream>
#include <dos.h> //for delay
#include <time.h>
#include <windows.h>
#include <stdlib.h>
#include <glm.hpp>
#include <chrono>
#include <thread>
#include <gtc/matrix_transform.hpp>
#include "SDL_mixer.h"
using namespace glm;
using namespace std;

const int WINDOWWIDTH = 1600;
const int WINDOWHEIGHT = 800;
const double PI = 3.14159;

Viewcontroller::Viewcontroller()
{
	for (int i = 0; i < 4; i++) {
		timer[1] = 0;
	}
	quit = false;
	won = true;
	printWin = false;
	window = 0;
	ogl4context = 0;
	playSoundEffectOnce = false;
	playSoundEffectOnceTicking = false;
	view_matrix = mat4(1.0);
	playWalkingOnce = false;
	moveForward = 0.0;
	moveSideways = 0.0;
	MOVEANGLE = PI/2.0;
	LOOKANGLE = 0.0;
	baseX = WINDOWWIDTH / 2.0;
	baseY = WINDOWHEIGHT / 2.0;
	eye = vec3(0.0, 0.0, 0.0);
	tempEye = vec3(0.0, 0.0, 0.0);
	up = vec3(0.0, 1.0, 0.0);
	boarderValue = 38;
	gameIsSetup = false;
	updateLookAt();  //aim will be calculated from the initial values of eye and MOVEANGLE
	audio.setup();
	//The music that will be played
	music = NULL;
	doneTimer = 0;
	isWalking = false;
}

//Initializes SDL, GLEW, OpenGL, and sound mixer
bool Viewcontroller::init()
{
	//First initialize SDL
	if (SDL_Init(SDL_INIT_EVERYTHING) < 0)
	{
		cout << "Failed to initialize SDL." << endl;
		return false;
	}

	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, true);
	if ((window = SDL_CreateWindow("Lab 15 Example", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WINDOWWIDTH, WINDOWHEIGHT, SDL_WINDOW_OPENGL)) == NULL)
	{
		cout << "Failed to create window." << endl;
		return false;
	}
	ogl4context = SDL_GL_CreateContext(window);
	SDL_ShowCursor(0);  //Hide the mouse cursor

	//Initialize the Model that you want to render
	if (theWorld.init() == false)  //OpenGL initialization is done in the Model class
	{
		cout << "Failed to initialize theWorld." << endl;
		return false;
	}

	//Initialize SDL_mixer
	if (Mix_OpenAudio(22050, MIX_DEFAULT_FORMAT, 2, 4096) == -1)
	{
		return false;
	}
/*
	//Load the music
	music = Mix_LoadMUS("sound/barradeen-sea.wav");

	//If there was a problem loading the music
	if (music == NULL)
	{
		return false;
	}
	
	Mix_PlayMusic(music, -1);
	Mix_VolumeMusic(MIX_MAX_VOLUME / 2);
	*/
	audio.playBGM();
	gameIsSetup = true;
	//audio.playWinSoundEffect();

	return true;  //Everything got initialized
}

//Display what we want to see in the graphics window
void Viewcontroller::display()
{
	theWorld.draw();

	SDL_GL_SwapWindow(window);
}


bool Viewcontroller::handleEvents(SDL_Event *theEvent)
{
	//Uint8 *keystate = SDL_GetKeyState(NULL);
	const Uint8 *state = SDL_GetKeyboardState(NULL);

	switch(theEvent->type)
	{
		case SDL_QUIT:  //User pressed the escape key
		{
			return true;  //force program to quit
		}
		case SDL_KEYDOWN:
		{
			if (theEvent->key.keysym.sym == SDLK_ESCAPE)  //the <Esc> key
			{
				return true;  //force game to quit
			}
			else if (theEvent->key.keysym.sym == SDLK_UP || theEvent->key.keysym.sym == SDLK_w)
			{
				moveForward = 0.080;
				//audio.playFootSteps();
				if (!playWalkingOnce) { //handles the footsteps audio
					audio.playFootSteps();
					playWalkingOnce = true;
				}
				isWalking = true;
			}
			else if (theEvent->key.keysym.sym == SDLK_LEFT || theEvent->key.keysym.sym == SDLK_a)
			{
				moveSideways = -0.080;
				//audio.playFootSteps();
				if (!playWalkingOnce) {
					audio.playFootSteps();
					playWalkingOnce = true;
				} 
				isWalking = true;
			}
			else if (theEvent->key.keysym.sym == SDLK_RIGHT || theEvent->key.keysym.sym == SDLK_d)
			{
				moveSideways = 0.080;
				//audio.playFootSteps();
				if (!playWalkingOnce) {
					audio.playFootSteps();
					playWalkingOnce = true;
				}
				isWalking = true; 
			}
			else if (theEvent->key.keysym.sym == SDLK_DOWN || theEvent->key.keysym.sym == SDLK_s)
			{
				moveForward = -0.080;
				//audio.playFootSteps();
				if (!playWalkingOnce) {
					audio.playFootSteps();
					playWalkingOnce = true;
				}
				isWalking = true; 
			}
			else if (theEvent->key.keysym.sym == SDLK_SPACE)
			{
				theWorld.toggleFilter();
			}
			else {
				//audio.stopFootSteps();
			}

		

			break;
		}
		case SDL_KEYUP:
		{/*
			if((theEvent->key.keysym.sym == SDLK_UP || theEvent->key.keysym.sym == SDLK_DOWN || theEvent->key.keysym.sym == SDLK_w || theEvent->key.keysym.sym == SDLK_s)   || (theEvent->key.keysym.sym == SDLK_LEFT || theEvent->key.keysym.sym == SDLK_RIGHT || theEvent->key.keysym.sym == SDLK_a || theEvent->key.keysym.sym == SDLK_d)){
				isWalking = false;
				playWalkingOnce = false;
			} */
			if (theEvent->key.keysym.sym == SDLK_UP || theEvent->key.keysym.sym == SDLK_DOWN || theEvent->key.keysym.sym == SDLK_w || theEvent->key.keysym.sym == SDLK_s)
			{
		
				moveForward = 0;
				//isWalking = false;
				//playWalkingOnce = false;
				if (!isWalking) {
					audio.stopFootSteps();
				}
				
			}
			else if (theEvent->key.keysym.sym == SDLK_LEFT || theEvent->key.keysym.sym == SDLK_RIGHT || theEvent->key.keysym.sym == SDLK_a || theEvent->key.keysym.sym == SDLK_d)
			{

				moveSideways = 0;
				//isWalking = false;
				//playWalkingOnce = false;
				if (!isWalking) {
					audio.stopFootSteps();
				} 
			}
			break;
		}
		case SDL_MOUSEMOTION:
		{
			const double MOUSE_SENSITIVITY_X = .01;
			const double MOUSE_SENSITIVITY_Y = .01;
			
			MOVEANGLE += (theEvent->button.x - baseX) * MOUSE_SENSITIVITY_X;
			LOOKANGLE += -(theEvent->button.y - baseY) * MOUSE_SENSITIVITY_Y;

			SDL_WarpMouseInWindow(window, baseX, baseY);  //re-center the mouse cursor
			break;
		}
	} //end the switch

	if (!state[SDL_SCANCODE_LEFT] && !state[SDL_SCANCODE_RIGHT] && !state[SDL_SCANCODE_UP] && !state[SDL_SCANCODE_DOWN] && !state[SDL_SCANCODE_A] && !state[SDL_SCANCODE_D] && !state[SDL_SCANCODE_W] && !state[SDL_SCANCODE_S]) {
		//printf("<LEFT> is NOT pressed.\n");
		isWalking = false;
		playWalkingOnce = false;
		audio.stopFootSteps();
	} 


	return false;  //the program should not end
}

void Viewcontroller::updateLookAt()
{
	/*
	float tempCosFandB;
	float tempSinFandB;
	float tempCosLandR;
	float tempSinLandR;
	*/
	//eye = tempEye; //move
	
	//Add movement forward and backward
	//eye[0] += cos(MOVEANGLE)*moveForward;
	//eye[2] += sin(MOVEANGLE)*moveForward;

	tempEye[0] += cos(MOVEANGLE)*moveForward;
	tempEye[2] += sin(MOVEANGLE)*moveForward;

	//Add movement to the left and right
	//eye[0] += cos(MOVEANGLE + PI / 2.0)*moveSideways;
	//eye[2] += sin(MOVEANGLE + PI / 2.0)*moveSideways;
	tempEye[0] += cos(MOVEANGLE + PI / 2.0)*moveSideways;
	tempEye[2] += sin(MOVEANGLE + PI / 2.0)*moveSideways;

	//if (true) { eye = tempEye;}
	//cout << "tempEye[0] is " << tempEye[0] << "\n";
	//cout << "tempEye[2] is " << tempEye[2] << "\n";
	//item 1 cube
	if ((tempEye[0] < -28.0 && tempEye[0] > -31.0) && (tempEye[2] > 28.0 && tempEye[2] < 31.0)) {
		//cout << "timer " << timer << endl;
		if (!playSoundEffectOnce && timer[0] >= 300 && theWorld.getItemIndex(0)) { //is the user under a pick up item?
			audio.stopTickingSoundEffect();
			gc.ItemCollected(0);
			audio.playCoinSoundEffect();
			playSoundEffectOnce = true;
			theWorld.setItemIndexToFalse(0); //the first cube to disappear
			audio.resumeMusic();
		}
		else if (!playSoundEffectOnceTicking && theWorld.getItemIndex(0) && timer[0] >0) { 
			//audio.pauseBGM();
			playSoundEffectOnceTicking = true;
			audio.playTickingSoundEffect();
		}
		timer[0]++;
	}
	else { //the user leaves pick up location
		playSoundEffectOnce = false;
		if (timer[0] > 0) {
			playSoundEffectOnceTicking = false;
			audio.stopTickingSoundEffect();
		}
		timer[0] = 0;
	}

	if (!playSoundEffectOnceTicking) {
		audio.resumeMusic();
	}
	else {
		//audio.pauseBGM();
	}

	//item 2 tree 1
	//model_matrix = translate(mat4(1.0), vec3(35.0f, -1.0f, 20.0f)); //Position the right 3 bushes
	if ((tempEye[0] > 34.0 && tempEye[0] < 36.0) && (tempEye[2] > 18.0 && tempEye[2] < 22.0)) {
		//cout << "WIN tree 1 item 2 \n";
		if (!playSoundEffectOnce && timer[1] >= 300 && theWorld.getItemIndex(1)) {
			audio.stopTickingSoundEffect();
			gc.ItemCollected(1);
			audio.playCoinSoundEffect();
			playSoundEffectOnce = true;
			theWorld.setItemIndexToFalse(1); //the first cube to disappear
			audio.resumeMusic();
		}
		else if (!playSoundEffectOnceTicking && theWorld.getItemIndex(1) && timer[1] > 0) {
			//audio.pauseBGM();
			//cout << "play sound effect \n";
			playSoundEffectOnceTicking = true;
			audio.playTickingSoundEffect();
		}
		timer[1]++;
	}
	else {
		playSoundEffectOnce = false;
		if (timer[1] > 0) {
			playSoundEffectOnceTicking = false;
			audio.stopTickingSoundEffect();
		}
		timer[1] = 0;
	}

	//item 3 tree 2
	//model_matrix = translate(mat4(1.0), vec3(-20.0f, -1.0f, -30.0f)); //Position the right 3 bushes
	if ((tempEye[0] < -19.0 && tempEye[0] > -21.0) && (tempEye[2] < -29.0 && tempEye[2] > -31.0)) {
		//cout << "WIN tree 1 item 2 \n";
		if (!playSoundEffectOnce && timer[2] >= 200 && theWorld.getItemIndex(2)) {
			audio.stopTickingSoundEffect();
			gc.ItemCollected(2);
			audio.playCoinSoundEffect();
			playSoundEffectOnce = true;
			theWorld.setItemIndexToFalse(2); //the first cube to disappear
			audio.resumeMusic();
		}
		else if (!playSoundEffectOnceTicking && theWorld.getItemIndex(2) && timer[2] > 0) {
			//audio.pauseBGM();
			//cout << "play sound effect \n";
			playSoundEffectOnceTicking = true;
			audio.playTickingSoundEffect();
		}
		timer[2]++;
	}
	else {
		playSoundEffectOnce = false;
		if (timer[2] > 0) {
			playSoundEffectOnceTicking = false;
			audio.stopTickingSoundEffect();
		}
		timer[2] = 0;
	}
	//item 3 tree 2
	//model_matrix = translate(mat4(1.0), vec3(20.0f, -1.0f, -20.0f)); //Position the right 3 bushes
	if ((tempEye[0] > 19.0 && tempEye[0] < 21.0) && (tempEye[2] < -19.0 && tempEye[2] > -21.0)) {
		//cout << "WIN tree 1 item 2 \n";
		if (!playSoundEffectOnce && timer[3] >= 200 && theWorld.getItemIndex(3)) {
			audio.stopTickingSoundEffect();
			gc.ItemCollected(3);
			audio.playCoinSoundEffect();
			playSoundEffectOnce = true;
			theWorld.setItemIndexToFalse(3); //the first cube to disappear
			audio.resumeMusic();
		}
		else if (!playSoundEffectOnceTicking && theWorld.getItemIndex(3) && timer[3] > 0) {
			//audio.pauseBGM();
			//cout << "play sound effect \n";
			playSoundEffectOnceTicking = true;
			audio.playTickingSoundEffect();
		}
		timer[3]++;
	}
	else {
		playSoundEffectOnce = false;
		if (timer[3] > 0) {
			playSoundEffectOnceTicking = false;
			audio.stopTickingSoundEffect();
		}
		timer[3] = 0;
	}

	if(gc.DidUserWin()) { //if the user wins then pause BGM and play win sound

		audio.pauseBGM();
		
		doneTimer++;
		if(won && doneTimer < 500){ // won is first set to true
			audio.playWinSoundEffect();
			won = false;;
			//quit = true; //cant put this line here, prevents song playing :(
			printWin = true;
		}
		if (doneTimer == 500) {
			if (printWin) {
				cout << "\n\nCongrats, you win!\n\n" << endl;
			}
			printWin = false;
			SDL_GL_DeleteContext(ogl4context);
			audio.freeSounds();
			SDL_DestroyWindow(window);
			SDL_Quit();
		}

	}







	if ((tempEye[0] < boarderValue && tempEye[0] > -boarderValue) && (tempEye[2] < boarderValue && tempEye[2] > -boarderValue)  )
	{
		eye = tempEye;
		//cout << "in Bounds";
	}


	//Adjust the aim position from the new eye position
	aim[0] = eye[0] + cos(MOVEANGLE); // CHECK THIS X
	aim[1] = eye[1] + LOOKANGLE;
	aim[2] = eye[2] + sin(MOVEANGLE); //CHECK THIS Z

	view_matrix = lookAt(eye, aim, up);  //calculate the view orientation matrix
	theWorld.setViewMatrix(view_matrix);

	if (audio.isBGMplaying()) {

	}
	else { //if the time runs out before all of the items are collected
		//SDL_GL_DeleteContext(ogl4context);
		//audio.freeSounds();
		//SDL_DestroyWindow(window);
		//SDL_Quit();
		if (!gc.DidUserWin() && gameIsSetup) {
			cout << "\n\nTry again next time, you lost... \n\n" << endl;
		}
		quit = true;
	}
}

void Viewcontroller::run()
{
	if (init() == false)  //This method (defined above) sets up OpenGL, SDL, and GLEW
	{
		cout << "Program failed to initialize ... exiting." << endl;
		return;
	}

	SDL_Event events;  //Makes an SDL_Events object that we can use to handle events

	const int UPDATE_FREQUENCY = 10; //update the frame every 10 milliseconds
	long currentTime, startTime = clock();
	SDL_WarpMouseInWindow(window, baseX, baseY);  //Center the mouse cursor
	do
	{
		display();  //This method (defined above) draws whatever we have defined
		while (SDL_PollEvent(&events)) //keep processing the events as long as there are events to process
		{
			quit = handleEvents(&events);
		}

		currentTime = clock();
		if (currentTime - startTime > UPDATE_FREQUENCY)
		{
			updateLookAt();
			theWorld.updateWorld();

			startTime = currentTime;
		}

	} while (!quit); //run until "quit" is true (i.e. user presses the <Esc> key

	SDL_GL_DeleteContext(ogl4context);
	audio.freeSounds();
	SDL_DestroyWindow(window);
	//cout << "hashdj";
	SDL_Quit();
}