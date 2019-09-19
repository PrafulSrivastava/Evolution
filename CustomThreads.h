#pragma once
#include "Global.h"

typedef struct Data {
	int id;
}thread_id;

class CustomThreads {

public:
	 bool unleash();
	HANDLE hThreads[MAX_THREADS];
	DWORD threadID[MAX_THREADS];
	thread_id* t_id[MAX_THREADS];
	static DWORD init(LPVOID param);
	void createThreads();
	void destroyThread(thread_id* t);

};