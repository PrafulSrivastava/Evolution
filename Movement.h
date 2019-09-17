#pragma once
#include <stdlib.h>
#include "Organism.h"


using namespace std;
class Movement {
private :
public:
    static int move(Organism &o);
	static int setDirection(Organism &os);
	static void failSafe(Organism &o);
	static void movementLogic(Organism &o);
	static void gotoDestination(Organism& o, int x, int y);
	static int displayLogic(int timeSpan, Organism &o);
};