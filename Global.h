#pragma once
#include <iostream>
#include <random>
#include <ctime>
#include <algorithm>
#include <mutex>
#include <windows.h>
#include <vector>
//Boundry Constants
#define BOUNDRY_SYMBOL_H "*"
#define BOUNDRY_SYMBOL_V "#"
#define LENGTH 40
#define BREADTH 80
#define SAFE_DISTANCE_FROM_BOUNDRY 10
//Thread Constants
#define MAX_THREADS ORGANISM_COUNT
//Food Constants
#define FOOD_ITEM "@"
#define FOOD_QUANTITY 10
//Movement Constants
#define MIN_STEPS 1
#define MAX_STEPS 10
//Organism Constants
#define ORGANISM(t) ORGANISM_ ## t
#define ORGANISM_1 "A"
#define ORGANISM_2 "B"
#define ORGANISM_3 "C"
#define ORGANISM_4 "D"
#define ORGANISM_COUNT 2
#define DEAD_MEAT "X"
//Movement Constants
#define setDir setDirection(o)
#define TIMELAG 40
#define ENERGY_LOSS 0.1


	static std::mt19937 mt_rand(time(0));
	static std::mutex mtx;
	static std::mutex m;
	static std::condition_variable cv;
	class global {

	};
