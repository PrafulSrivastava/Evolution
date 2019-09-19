#include "Boundry.h"
#include "Utility.h"
#include "Food.h"
#include "CustomThreads.h"
#include "Organism.h"
#include <iostream>
#include "Global.h"

using namespace std;

int main() {
	new global();
	Sleep(2000);
	//Globals::mt_rand(time(0));
	Boundry::createBoundry();
	Utility::getUtilityObj();
	//cout << "Boundry done!\n";
	Food::genFood();
	/*std::map<int, fInfo*>::iterator i;
	for (i = Food::foodPos.begin(); i != Food::foodPos.end(); i++) {
		cout << " : " << i->second->xPos << " , " << i->second->yPos << endl;
	}*/
	Organism::spawnOrganisms();
	//cout << "Organism done!\n";
	CustomThreads* ct = new CustomThreads();
	ct->createThreads();
	WaitForMultipleObjects(MAX_THREADS, ct->hThreads, TRUE, INFINITE);

	cout << "Done!\n";
			
	int t;
	std::cin >> t;
	return 0;
}
