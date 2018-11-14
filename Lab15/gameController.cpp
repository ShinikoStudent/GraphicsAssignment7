#include "gameController.h"
#include <iostream>
using namespace std;


gameController::gameController()
{
	for (int i = 0; i < totalNumOfItems; i++) {
		items[i] = false;
	}
}

void gameController::ItemCollected(int itemNum) {
	items[itemNum] = true;
}

bool gameController::DidUserWin() {
	int numCount = 0;
	for (int i = 0; i < totalNumOfItems; i++) {
		if (items[i] == true) {
			numCount++;
		}
	}
	if (numCount == totalNumOfItems) {
		cout << "You Win\n\n";
		return true;
	}
	return false;
}
gameController::~gameController()
{
}
