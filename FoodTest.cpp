#include "Food.h"
#include <iostream>
#include "Boundry.h"
#include "Organism.h"
#include <ctime>
int main3() {
	
	int i = 0;
	while (i < 15) {
		system("CLS");
		Boundry::createBoundry();
		Food::genFood();
		Organism::spawnOrganisms();
		Sleep(1000);
		i++;
	}
	
	int t;
	std::cin >> t;
	return 0;
}