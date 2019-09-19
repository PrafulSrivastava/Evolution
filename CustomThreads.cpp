#include "CustomThreads.h"
#include "Organism.h"
#include "Movement.h"
#include <iostream>
#include "Global.h"
void CustomThreads::createThreads() {

	for (int i = 0; i <= MAX_THREADS; i++) {
		t_id[i] = new thread_id();
		t_id[i]->id = i;
		hThreads[i] = CreateThread(NULL, 0, init, t_id[i], 0, &threadID[i]);
	}
}
void CustomThreads::destroyThread(thread_id* t){
	
	cout << "Destroying! \n";
	CloseHandle(t);
	if (t != NULL) {
		delete t;
		t = NULL;
	}
	
}

bool CustomThreads::unleash() {
	return true;
}

DWORD CustomThreads::init(LPVOID param) {
	CustomThreads *cts = new CustomThreads();
	thread_id* tid = (thread_id*)param;
	if (tid->id != MAX_THREADS) {
		while (Organism::org.find(tid->id)->second->deadOrAlive) {
			mtx.lock();
			//cout << " -> " << Organism::org.find(tid->id)->second->energy;
			int res = Movement::move(*Organism::org.find(tid->id)->second);
			mtx.unlock();
			if (Organism::org.find(tid->id)->second->foundFood && Organism::org.find(tid->id)->second->isHome()) {
				//cout << "\n";
				//Organism::org.find(tid->id)->second->displayStats();
				//cout << " is waiting..!\n";
				std::unique_lock<std::mutex> lk(m);
				cv.wait(lk);
				cout << "Restart!\n";
			}
			if (!Organism::org.find(tid->id)->second->deadOrAlive) {
				Organism::org.erase(tid->id);
				cout << "Died. New Size: " << Organism::org.size() << endl;
				cts->destroyThread(cts->t_id[tid->id]);
				break;
			}
			Sleep(100);
		}
	}
	else {
		cout << "Size: " << Organism::org.size() << endl;
		while (true) {
			int cnt = 0;
			std::map<int, Organism*>::iterator i;
			for (i = Organism::org.begin(); i != Organism::org.end(); i++) {
				if (i->second->foundFood) {
					cnt++;
				}
			}
			Sleep(3000);
			cout << "Count : " << cnt <<" ";
			if (cnt == Organism::org.size()) {
				cout << "Reset !\n";
				
				Organism::resetStates();
				cv.notify_all();
				
			}

			if (!Organism::org.size()) {
				cout << "Size 0\n";
				cts->destroyThread(cts->t_id[MAX_THREADS]);
				break;
			}
		}
	}
	
	
	return 0;
}