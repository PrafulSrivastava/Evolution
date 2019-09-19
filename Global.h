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
#define MAX_THREADS ORGANISM_COUNT + 1
//Food Constants
#define FOOD_ITEM "@"
#define FOOD_QUANTITY 20
#define MIN_ENERGY 15
#define MAX_ENERGY 30
#define FOOD_GAIN MIN_ENERGY
//Movement Constants
#define MIN_STEPS 1
#define MAX_STEPS 10
//Organism Constants
#define ORGANISM(t) ORGANISM_ ## t
#define ORGANISM_1 "A"
#define ORGANISM_2 "B"
#define ORGANISM_3 "C"
#define ORGANISM_4 "D"
#define ORGANISM_COUNT 5
#define DEAD_MEAT "X"
#define MIN_STRENGTH 2
#define MAX_STRENGTH 10
#define MIN_SENSE 3
#define MAX_SENSE 10
//Movement Constants
#define setDir setDirection(o)
#define TIMELAG 35
#define ENERGY_LOSS 0.1
#define RESET_TIME_DELAY 3000


	static std::mt19937 mt_rand(time(0));
	static std::mutex mtx;
	static std::mutex m;
	static std::condition_variable cv;
	class global {

	};
