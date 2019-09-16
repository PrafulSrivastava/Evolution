#include "Movement.h"
#include "Utility.h"
#include "Boundry.h"
#include <iostream>
#include <cstring>
#include <math.h>
#include "Global.h"

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
void Movement::displayLogic(int timeSpan, Organism &o) {
	int c = 0;
	for (int i = 0; i < timeSpan; i++) {
		if (!o.forced) {
			COORD tempC = o.foodFound();

			if (tempC.X != -999) {
				//cout << "temp: " << tempC.X << " , " << tempC.Y << endl;
				o.forced = 1;
				gotoDestination(o, tempC.X, tempC.Y);
				if (o.foundFood) {
					o.forced = 1;
					gotoDestination(o, o.homeX, o.homeY);
					o.foundFood = false;
				}
				
			}
		}
		
		switch (o.direction) {
		case 1:
			c++;
			break;
		case 2:
			c--;
			break;
		case 3:
			c--;
			break;
		case 4:
			c++;
			break;

		}
		string temp = "";
		if (Boundry::isBoundry(o.xPos, o.yPos)) {
			if (o.xPos == 0 || o.xPos == BREADTH)
				temp += BOUNDRY_SYMBOL_V;
			else {
				temp += BOUNDRY_SYMBOL_H;
			}
		}
		else
			temp += " ";

		Utility::getUtilityObj()->spawn(temp.c_str(), { (short)o.xPos,  (short)o.yPos });//print
		movementLogic(o);
		Utility::getUtilityObj()->spawn(o.organismType, { (short)o.xPos,  (short)o.yPos });//print
		Sleep(TIMELAG);
		o.steps++;
	}
	
	//cout << "Current pos: " << o.xPos << " , " << o.yPos << endl;
}
void Movement:: move(Organism &o) {
	if (o.steps != 0) {
		if (o.homeX == o.xPos && o.homeY == o.yPos) {

		}
	}
	
	setDirection(o);
	
	if (o.direction) {

		int timeSpan = Utility::getUtilityObj()->randomInRange(MIN_STEPS, MAX_STEPS);
		displayLogic(timeSpan,o);
	}
	
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