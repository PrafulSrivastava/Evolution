#pragma once
#include "Global.h"
#include <map>
class Organism {
private: double strength;
		 double sense;
		 double energy;
		 bool deadOrAlive;
		 friend class Movement;
		 friend class CustomThreads;
public: Organism(); 
		int xPos;
		int yPos;
		int direction;
		int forced;
		int homeX;
		int homeY;
		bool foundFood;
		const char * organismType;
		int steps;
		static std::map<int,Organism*> org;
		COORD foodFound(int &x);
		bool enemyFound();
		void displayStats();
		bool isInView(int x,int y);
		bool isHome();
		static void resetStates();
		static bool isOrganismPosition(int x, int y);
		static void spawnOrganisms();
		static const char * chooseOrganism();
		
};