//FileName:		main.cpp
//Programmer:	Dan Cliburn
//Date:			4/20/2015
//Purpose:		This file defines the main() function for Lab 15.
//Movement is controller with wasd and view direction is changed with the mouse.
//The program ends when the user presses the <Esc> key

#include "viewcontroller.h"
#include <iostream>
#include <stdlib.h>
using namespace std;

int main(int argc, char *argv[])  //main() must take these parameters when using SDL
{

	Viewcontroller vc;
	cout << "Welcome to Adam and Eve Deceives!\n\n"
		<<"Created by Keely Canniff, Jamie Lynn Culilap, and Naomi Nunis\n\n"
		<< "A Place where you must find the hidden fruit or you die.\n"
		<< "Need more time find the hidden room that will act as a base and you can finally say you've stopped time.\n\n"
		<< "Good Luck and Enjoy!\n\n";

	system("pause");
	vc.run();

	system("pause");
	return 0;
}