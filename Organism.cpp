#include "Organism.h"
#include <iostream>
#include "Global.h"
#include "Utility.h"
#include "Food.h"

using namespace std;

Organism** Organism::org = NULL;

Organism::Organism() {
	strength = Utility::getUtilityObj()->randomInRange(2,10); //(10 + 1 - 2)
	sense = Utility::getUtilityObj()->randomInRange(3, 10); //(10 + 1 - 3)
	energy = Utility::getUtilityObj()->randomInRange(5, 10); //(10 + 1 -5)
	direction = 0;
	forced = 0;
	foundFood = false;
}

void Organism::displayStats() {
	cout << "Strength : " << this->strength << " Sense : " << this->sense << " Energy : " << this->energy << endl;
}
const char* Organism::chooseOrganism() {
	//(4 + 1 - 1)
	int t = Utility::getUtilityObj()->randomInRange(1, 4);;
	switch (t) {
	case 1: return ORGANISM(1);
		break;
	case 2: return ORGANISM(2);
		break;
	case 3: return ORGANISM(3);
		break;
	case 4: return ORGANISM(4);
		break;
	default:
		return NULL;
	}
}
void Organism::spawnOrganisms() {
	org = new Organism*[ORGANISM_COUNT];
	int pos = 0;
	while (pos < ORGANISM_COUNT) {

		Organism *temp = new Organism();
		COORD* c = new COORD();
		c=Utility::getUtilityObj()->genBorderCOORDs();
		temp->xPos = c->X;
		temp->homeX = c->X;
		temp->yPos = c->Y;
		temp->homeY = c->Y;
		temp->organismType = chooseOrganism();
		Utility::getUtilityObj()->spawn(temp->organismType, *c);
		org[pos] = temp;
		pos++;
	}
}

bool Organism::isInView(int x,int y) {
	
	if (pow(this->xPos - x, 2) + pow(this->yPos - y, 2) <= pow(this->sense,2)) {
		return true;
	}
	else
		return false;
}

COORD Organism::foodFound() {
	for (int i=0;i<FOOD_QUANTITY;i++)
	{
		if (Food::foodPos.find(i)->second->state) {
			if (this->isInView(Food::foodPos.find(i)->second->xPos, Food::foodPos.find(i)->second->yPos)) {
				//cout << "Found at : " << Food::foodPos.find(i)->second->xPos << " , " << Food::foodPos.find(i)->second->yPos << endl;
				Food::foodPos.find(i)->second->state = false;
				this->foundFood = true;
				return { (short)Food::foodPos.find(i)->second->xPos,(short)Food::foodPos.find(i)->second->yPos };
			}
		}
	}
	return { (short)-999,(short)-999};
}
