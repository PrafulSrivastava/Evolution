#pragma once
#include "Global.h"
class Organism {
private: int strength;
		 int sense;
		 int energy;
		 
		
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
		static Organism ** org;
		COORD foodFound();
		bool enemyFound();
		void displayStats();
		bool isInView(int x,int y);

		
		static void spawnOrganisms();
		static const char * chooseOrganism();
		
};