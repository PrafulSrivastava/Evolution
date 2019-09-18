#include "Organism.h"
#include <iostream>
#include "Global.h"
#include "Utility.h"
#include "Food.h"

using namespace std;

std::map<int, Organism*> Organism::org;

Organism::Organism() {
	strength = Utility::getUtilityObj()->randomInRange(2,10); //(10 + 1 - 2)
	sense = Utility::getUtilityObj()->randomInRange(3, 10); //(10 + 1 - 3)
	energy = Utility::getUtilityObj()->randomInRange(15, 30); //(10 + 1 -5)
	direction = 0;
	forced = 0;
	foundFood = false;
	deadOrAlive = true;//alive
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
		org.insert(pair<int,Organism*>(pos, temp));
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

COORD Organism::foodFound(int &x) {
	for (int i=0;i<FOOD_QUANTITY;i++)
	{
		if (Food::foodPos.find(i)->second->state) {
			if (this->isInView(Food::foodPos.find(i)->second->xPos, Food::foodPos.find(i)->second->yPos)) {
				//cout << "Found at : " << Food::foodPos.find(i)->second->xPos << " , " << Food::foodPos.find(i)->second->yPos << endl;
				x = i;
				return { (short)Food::foodPos.find(i)->second->xPos,(short)Food::foodPos.find(i)->second->yPos };
			}
		}
	}
	return { (short)-999,(short)-999};
}

bool Organism::isOrganismPosition(int x,int y) {
	std::map<int, Organism*>::iterator i;
	for (i=org.begin(); i != org.end(); i++) {
		if ((i->second->homeX == x) && (i->second->homeY == y)) {
			return i->second->isHome();
		}
	}
	return false;
}

bool Organism::isHome() {
	if ((this->xPos == this->homeX) && (this->yPos == this->homeY))
		return true;
	return false;
}

void Organism::resetStates() {
	std::map<int, Organism*>::iterator i;
	for (i = Organism::org.begin(); i != Organism::org.end(); i++) {
		i->second->foundFood = false;
		
	}
}