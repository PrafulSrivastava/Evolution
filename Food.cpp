#include "Food.h"
#include <iostream>
#include "Global.h"
#include "Utility.h"

typedef std::map<Food*, bool> innerMap;
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