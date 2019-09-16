#pragma once
#include "Global.h"
class Utility{
private:
	Utility();
	static Utility* ut;
	static HANDLE hout;
public: COORD* genCOORD();
		
		COORD* genBorderCOORDs();
		void spawn(const char* spawnItem, COORD location);
		int randomInRange(int min, int max);
		static Utility* getUtilityObj();
		
};