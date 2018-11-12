#pragma once
//class to control the game aspect, winning, losing etc
#include <glew.h>  //glew.h is supposed to be included before gl.h.  To be safe, you can just include glew.h instead
#ifndef GAMECONTROLLER_H
#define GAMECONTROLLER_H
class gameController
{
private:
	int totalNumOfItems = 4;
	bool items[4];
public:
	gameController();
	bool DidUserWin();
	void ItemCollected(int itemNum);
	~gameController();
};
#endif

