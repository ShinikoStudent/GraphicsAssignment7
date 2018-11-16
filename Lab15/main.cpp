//FileName:		main.cpp
//Programmer:	Keely Canniff, Jamie Lynn Culilap, and Naomi Nunis
//Date:			4/20/2015
//Purpose:		This file defines the main() function for assignment 7.
//Movement is controller with wasd and view direction is changed with the mouse.
//The program ends when the user presses the <Esc> key

#include "viewcontroller.h"
#include <iostream>
#include <stdlib.h>
using namespace std;

int main(int argc, char *argv[])  //main() must take these parameters when using SDL
{
	//for the extra credit, we added in 5 sounds (background sound, footsteps, winning sound, ticking sound, pickup sound).
	// we made the game a collection game. you need to collect the 4 items (1 floating cube, and 3 fruit trees) to win the game.
	//if you fail to collect all 4 items before the countdown ends, you lose the game.
	Viewcontroller vc;
	cout << "\n============== Welcome to Adam and Eve Deceives! ============== \n"
		<< "Created by Keely Canniff, Jamie Lynn Culilap, and Naomi Nunis\n\n"
		<< "A place where you must find hidden fruits and a single floating cube hidden amongst other cubes.\n\n"
		<< "Hints:\n1.the space bar can help with the cubes\n"
		<< "2.When you find an item to collect, stand inside it (or under it)\n"
		<< "-a ticker will sound off until a you hear a loud \"ding!\" \n"
		<< "Note: The \"ding!\" indicates you have collected the item.\n\n"
		<< "Move with WASD and use the space bar to see the hidden items.\n"
		<< "To exit the game, click the Esc key\n\n"
		<< "*SOUND WILL NEED TO BE TURNED ON.*\n\n"
		<< "*EXTRA CREDIT:*\n"
		<< "- We have 5 sounds added(background sound, footsteps, winning sound, ticking sound, pickup sound)\n"
		<< "- Game has a win/lose condition. You win by collecting 1 floating cube and 3 fruit trees\n"
		<< "  or you lose by not collecting them within the time limit.\n\n"
		<< "Good Luck and Enjoy Collecting!\n\n";

	system("pause");
	vc.run();

	//cout << "Game Finished\n\n";
	system("pause");
	return 0;
}