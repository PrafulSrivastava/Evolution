#pragma once
#include "Global.h"

typedef struct Data {
	int id;
}thread_id;

class CustomThreads {

public:
	 bool unleash();
	static HANDLE hThreads[MAX_THREADS];
	static DWORD threadID[MAX_THREADS];
	static thread_id* t_id[MAX_THREADS];
	static DWORD init(LPVOID param);
	static void createThreads();
	static void destroyThread(int t);

};