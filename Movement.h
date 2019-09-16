#pragma once
#include <stdlib.h>
#include "Organism.h"


using namespace std;
class Movement {
private :
public:
    static void move(Organism &o);
	static int setDirection(Organism &os);
	static void failSafe(Organism &o);
	static void movementLogic(Organism &o);
	static void gotoDestination(Organism& o, int x, int y);
	static void displayLogic(int timeSpan, Organism &o);
};