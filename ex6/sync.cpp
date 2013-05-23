#include "sync.h"
semaphore::semaphore(int key, int val){
	sem_id = set_sem(key, val);
}
void semaphore::operate(int delta){
	opsem(sem_id, delta);
}
lock::lock(int key){
	sem = new semaphore(key, 1);
}
void lock::acquire(){
	sem->operate(-1);
}
void lock::release(){
	sem->operate(1);
}
oneway_condition::oneway_condition(semaphore *sem1, semaphore *sem2){
	sem[0] = sem1;
	sem[1] = sem2;
}
void oneway_condition::wait(lock *l, int direction){
	l->release();
	sem[direction]->operate(-1);
	l->acquire();
}
void oneway_condition::signal(int direction){
	sem[direction ^ 1]->operate(1);
}
void oneway::oneway(int max){
	maxCars = max;
	rate = 2;
	l = new lock(501);
	cond = new condition(new semaphore(502, 0), new semaphore(503, 0));
	char *p = set_shm(504, 8, 0);
	numCars = p;
	currentDirection = p + 4;
	(*numCars) = 0;
	(*currentDirection) = 0;
}
void oneway::arrive(int direction){
	l->acquire();
	if ((*currentDirection) != direction && (*numCars) || (*numCars) >= maxCars){
		printf("Direction %d waiting, pid=%d\n", direction, getpid());
		cond->wait(l, direction);
	}
	(*numCars) ++;
	(*currentDirection) = direction;
	l->release();
}
void oneway::cross(int direction){
	printf("%d running to direction %d\n", getpid(), direction);
}
void oneway::quit(int direction){
	l->acquire();
	printf("Direction %d passed, pid=%d\n", direction, getpid());
	(*numCars) --;
	if ((*numCars) == 0)
		cond->signal(direction);
	l->release();
}
int main(int argc, char** argv){
}
