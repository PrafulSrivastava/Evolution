#include "Boundry.h"
#include <iostream>
#include "Global.h"

using namespace std;

void Boundry::createBoundry() {

	for (int l = 0; l <= LENGTH; l++) {
		for (int b = 0; b <= BREADTH; b++) {
			if (l == 0 || l == LENGTH || b == 0 || b == BREADTH) {
				if (b == 0 || b == BREADTH) {
					cout << BOUNDRY_SYMBOL_V;
				}
				else
					cout << BOUNDRY_SYMBOL_H;
			}
				
			else
				cout << " ";
		}
		cout << endl;
	}
}

bool Boundry::isBoundry(int x, int y) {
	//cout << "Is Boundry\n";
	if ((x >= BREADTH) || (x <= 0) || (y >= LENGTH) || (y <= 0))
		return true;
	return false;
}