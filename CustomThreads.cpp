#include "CustomThreads.h"
#include "Organism.h"
#include "Movement.h"
#include <iostream>
#include "Global.h"
void CustomThreads::createThreads() {

	for (int i = 0; i < MAX_THREADS; i++) {
		t_id[i] = new thread_id();
		t_id[i]->id = i;
		hThreads[i] = CreateThread(NULL, 0, init, t_id[i], 0, &threadID[i]);
	}
}
void CustomThreads::destroyThreads(){
	
	for (int i = 0; i < MAX_THREADS; i++) {
		CloseHandle(hThreads[i]);
		if (t_id[i] != NULL) {
			delete t_id[i];
			t_id[i] = NULL;
		}
	}
}

DWORD CustomThreads::init(LPVOID param) {

	thread_id* tid = (thread_id*)param;
	while (true) {
		while (Organism::org[tid->id]->foundFood);
		int a = 0;
		mtx.lock();
		Movement::move(*Organism::org[tid->id]);
		mtx.unlock();

		Sleep(100);
	}
}