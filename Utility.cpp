#include "Utility.h"
#include "Global.h"

HANDLE Utility::hout = NULL;
Utility* Utility::ut = NULL;
Utility::Utility() {
}
Utility* Utility::getUtilityObj() {
	if (ut == NULL)
		ut = new Utility();
	return ut;
}
int Utility::randomInRange(int min, int max) {
	int t = mt_rand() % (max + 1 - min) + min;
	//if(max==4)
		//std::cout << "Random in Range : " << min << " to " << max << " : " << t << " Thread ID: " << std::this_thread::get_id() <<std::endl;
	return t;//(1 + 1 -0)
}
COORD* Utility::genCOORD() {
	//(length + 1 - 0) and (breadth + 1 - 0)
	COORD* c=new COORD();
	c->X = mt_rand() % BREADTH + SAFE_DISTANCE_FROM_BOUNDRY;
	if (c->X >= BREADTH - SAFE_DISTANCE_FROM_BOUNDRY ) {
		c->X = BREADTH - SAFE_DISTANCE_FROM_BOUNDRY;
	}
	c->Y =mt_rand() % LENGTH + SAFE_DISTANCE_FROM_BOUNDRY;
	if (c->Y >= LENGTH - SAFE_DISTANCE_FROM_BOUNDRY ) {
		c->Y = LENGTH - SAFE_DISTANCE_FROM_BOUNDRY;
	}
	return c;
}
COORD* Utility::genBorderCOORDs() {
	COORD* c= new COORD();
	switch (randomInRange(0,1)) {
	case 0:
		if (randomInRange(0,1))
			c->X = BREADTH;
		else
			c->X = 0;
		c->Y = mt_rand() % LENGTH;
		break;
	case 1:
		if (randomInRange(0,1))
			c->Y = LENGTH;
		else
			c->Y = 0;
		c->X = mt_rand() % BREADTH ;
		break;

	}
	return c;
}
void Utility::spawn(const char * item, COORD location) {
		DWORD writtenChars = 0;
		hout = GetStdHandle(STD_OUTPUT_HANDLE);
		//std::cout << location.X << " " << location.Y << std::endl;;
		WriteConsoleOutputCharacter(hout, item, strlen(item), {(short)location.X,(short)location.Y}, &writtenChars);
}