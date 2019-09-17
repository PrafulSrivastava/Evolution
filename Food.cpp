#include "Food.h"
#include <iostream>
#include "Global.h"
#include "Utility.h"

std::map<int, fInfo*> Food::foodPos;
//Food** Food::foodPos = NULL;
void Food::genFood() {
	//foodPos = new Food*[FOOD_QUANTITY];
	for (int i = 0; i < FOOD_QUANTITY; i++) {
		COORD *temp=(Utility::getUtilityObj()->genCOORD());

		fInfo *ftemp = new fInfo();
		ftemp->xPos = temp->X;
		ftemp->yPos = temp->Y;
		ftemp->state = true;

		foodPos.insert(std::make_pair(i,ftemp));

		Utility::getUtilityObj()->spawn(FOOD_ITEM, *temp);
	}
	//std::cout << "Food Size: " << foodPos.size() << std::endl;
	
}

void Food::displayFoodPos() {
	for (int i = 0; i < FOOD_QUANTITY; i++) {
		std::cout << foodPos.find(i)->second->xPos << " , " << foodPos.find(i)->second->yPos << std::endl;
	}
}

int Food::compareFInfo(fInfo *f1, int x,int y) {
	if ((f1->xPos == x) && (f1->yPos == y)) {
		return 0;//equality
	}
	return 1;
}

bool Food::isFoodPosition(int x, int y) {
	std::map<int, fInfo*>::iterator i;
	for (i = foodPos.begin(); i != foodPos.end(); i++) {
		if (i->second->state) {
			if (!compareFInfo(i->second, x, y))
				return true;
		}
	}
	return false;
}