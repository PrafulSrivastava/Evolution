#include "Organism.h"
#include <iostream>
#include <ctime>
#include "Boundry.h"


using namespace std;

int main2() {
	srand(time(0));
	/*Organism **o = new Organism*[10];
	for (int i = 0; i < 10; i++) {
		o[i] = new Organism();
		o[i]->displayStats();
	}*/
	Boundry::createBoundry();
	Organism::spawnOrganisms();
	

	int t;
	std::cin >> t;
	
	return 0;
}