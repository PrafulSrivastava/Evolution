#include "Movement.h"
#include "Utility.h"
#include "Boundry.h"
#include <iostream>
#include <cstring>
#include <math.h>
#include "Global.h"
#include "Food.h"

using namespace std;


int Movement::setDirection(Organism &o) {
	if (o.steps == 0) {
		if (o.xPos == BREADTH) {//North East
			if (o.yPos == 0) {
				gotoDestination(o,o.xPos - 1, o.yPos + 1);
				return 0;
			}
			else
				o.direction = 3;
		}
		else if (o.xPos == 0) {//North West
			if (o.yPos == 0) {
				gotoDestination(o, o.xPos + 1, o.yPos + 1);
				return 0;
			}
			else
				o.direction = 4;
		}
		else if (o.yPos == LENGTH) {//South West
			if (o.xPos == 0) {
				gotoDestination(o, o.xPos + 1, o.yPos - 1);
				return 0;
			}
			if (o.xPos == BREADTH) {//South East
				gotoDestination(o, o.xPos - 1, o.yPos - 1);
				return 0;
			}
			else
				o.direction = 1;
		}
		else if (o.yPos == 0) {
			o.direction = 2;
		}
		return 0;
	}
	o.direction = Utility::getUtilityObj()->randomInRange(1, 4);
	return 0;
}
int Movement::displayLogic(int timeSpan, Organism &o) {
	int foodOrder = 1000;//temporary holder to store food location
	for (int i = 0; ((i < timeSpan) && ( o.deadOrAlive )); i++) {
		if (!o.forced) {
			COORD tempC = o.foodFound(foodOrder);
			int pp = ORGANISM_COUNT + 1;
			COORD enemyCor = o.enemyFound(pp);
			if (pp < ORGANISM_COUNT) {
				o.forced = 1;
				gotoDestination(o, tempC.X, tempC.Y);
			}
			if (foodOrder < FOOD_QUANTITY) {
				o.forced = 1;
				gotoDestination(o, tempC.X, tempC.Y);
				if (Food::isFoodPosition(o.xPos, o.yPos)) {
					Food::foodPos.find(foodOrder)->second->state = false;
					o.foundFood = true;
				}
				if (o.foundFood) {
					o.steps = 0;
					o.forced = 1;
					gotoDestination(o, o.homeX, o.homeY);
					return 1;
				}
				
			}
		}
		
		string temp = "";
		if (Boundry::isBoundry(o.xPos, o.yPos)) {
			if (o.xPos == 0 || o.xPos == BREADTH) {
				if (o.deadOrAlive && o.steps && Organism::isOrganismPosition(o.xPos, o.yPos)) {
					temp += o.organismType;
				}
				else
					temp += BOUNDRY_SYMBOL_V;
			}
			else {
				if (o.deadOrAlive && o.steps && Organism::isOrganismPosition(o.xPos, o.yPos)) {
					temp += o.organismType;
				}
				else
					temp += BOUNDRY_SYMBOL_H;
			}
		}
		else if (o.steps  && o.foundFood && Food::isFoodPosition(o.xPos, o.yPos)) {
			temp += FOOD_ITEM;
		}
		else
			temp += " ";

		Utility::getUtilityObj()->spawn(temp.c_str(), { (short)o.xPos,  (short)o.yPos });//print
		movementLogic(o);
		if(o.energy - ENERGY_LOSS < 0.1)
			Utility::getUtilityObj()->spawn(DEAD_MEAT, { (short)o.xPos,  (short)o.yPos });//print
		else
			Utility::getUtilityObj()->spawn(o.organismType, { (short)o.xPos,  (short)o.yPos });
		Sleep(TIMELAG);
		o.steps++;
		o.energy = o.energy - ENERGY_LOSS;
		if (o.energy < 0.1) {
			o.energy = 0;
			o.deadOrAlive = false; //mf died
		}
		//cout << " " << o.energy;
			
	}
	return 0;
	//cout << "Current pos: " << o.xPos << " , " << o.yPos << endl;
}
int Movement:: move(Organism &o) {
	if (o.steps != 0) {
		if (o.isHome()) {
			return 0;
		}
	}
	
	setDirection(o);
	
	if (o.direction) {

		int timeSpan = Utility::getUtilityObj()->randomInRange(MIN_STEPS, MAX_STEPS);
		displayLogic(timeSpan,o);
	}
	return 0;
}
void Movement::movementLogic(Organism &o) {
	//std::cout << "X: " << o.xPos << " Y : " << o.yPos << std::endl;
		switch (o.direction) {
		case 1://Move up
			
			o.yPos--;
			failSafe(o);
			break;
		case 2://Move down
			
			o.yPos++;
			failSafe(o);
			break;
		case 3://Move left
			
			o.xPos--;
			failSafe(o);
			break;
		case 4://Move right
			
			o.xPos++;
			failSafe(o);
			break;
		}
}
void Movement::failSafe(Organism &o) {
	//std::cout << "Fail Safe" <<"X: " << o.xPos << " Y : " << o.yPos << std::endl;
	if (!o.forced) {
		if (Boundry::isBoundry(o.xPos, o.yPos)) {
			switch (o.direction) {//Reverse
			case 1:
				o.yPos++;
				o.direction = 2;
				break;
			case 2:
				o.yPos--;
				o.direction = 1;
				break;
			case 3:
				o.xPos++;
				o.direction = 4;
				break;
			case 4:
				o.xPos--;
				o.direction = 3;
				break;
			}
			movementLogic(o);
		}
	}
}

void Movement::gotoDestination(Organism& o,int x,int y) {

	int walkX = abs(o.xPos - x);
	if (o.xPos - x > 0)
		o.direction = 3;
	else
		o.direction = 4;
	displayLogic(walkX, o);
	int walkY = abs(o.yPos - y);

	if (o.yPos - y < 0) 
		o.direction = 2;
	else
		o.direction = 1;
	displayLogic(walkY, o);
	
	o.forced = 0;

}