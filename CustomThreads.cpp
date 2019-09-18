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
void CustomThreads::destroyThreads(){
	
	for (int i = 0; i <= MAX_THREADS; i++) {
		CloseHandle(hThreads[i]);
		if (t_id[i] != NULL) {
			delete t_id[i];
			t_id[i] = NULL;
		}
	}
}

bool CustomThreads::unleash() {
	return true;
}

DWORD CustomThreads::init(LPVOID param) {
	
	thread_id* tid = (thread_id*)param;
	if (tid->id != MAX_THREADS) {
		while (Organism::org.find(tid->id)->second->deadOrAlive) {
			cout << " -> " << Organism::org.find(tid->id)->second->foundFood;
			
			mtx.lock();

			if (Movement::move(*Organism::org.find(tid->id)->second)) {
				cout << "Out of Energy\n";
				Organism::org.erase(tid->id);
				mtx.unlock();
				break;
			}
			else
				mtx.unlock();
			if (Organism::org.find(tid->id)->second->foundFood && Organism::org.find(tid->id)->second->isHome()) {
				cout << "Wait!\n";
				std::unique_lock<std::mutex> lk(m);

				cv.wait(lk);
				cout << "Restart!\n";
				lk.release();
			}
			
			
			Sleep(100);


		}
	}
	else {
		while (true) {
			int cnt = 0;
			std::map<int, Organism*>::iterator i;
			for (i = Organism::org.begin(); i != Organism::org.end(); i++) {
				if (i->second->foundFood || !i->second->deadOrAlive) {
					cnt++;
				}
			}
			//cout << "Count : " << cnt << endl;
			if (cnt == Organism::org.size()) {
				cout << "Reset!\n";
				Sleep(1000);
				Organism::resetStates();
				cv.notify_all();
				
			}
			if (!Organism::org.size())
				break;
		}
	}
	
	return 0;
}