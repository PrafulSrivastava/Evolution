#pragma once
#include <map>

typedef struct FoodInfo {
	int xPos;
	int yPos;
	bool state;
}fInfo;
class Food {
	
public:
	
	static std::map<int,fInfo*> foodPos;
	static void	 genFood();
	static void displayFoodPos();
};

