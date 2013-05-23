#include "sync.h"
semaphore::semaphore(int key, int val){
	sem_id = set_sem(key, val, IPC_CREAT|0644);
}
void semaphore::operate(int delta){
	opsem(sem_id, delta);
}
lock::lock(int key){
	sem = new semaphore(key, 1);
}
void lock::acquire(){
	sem->operate(-1);
//	printf("Locked by %d\n", getpid());
}
void lock::release(){
//	printf("Unlocking by %d\n", getpid());
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
	int anod = direction ^ 1;
	sem[anod]->operate(100);
}
oneway::oneway(int max){
	maxCars = max;
	rate = 4;
	l = new lock(501);
	cond = new oneway_condition(new semaphore(502, 0), new semaphore(503, 0));
	int *p = (int*)set_shm(504, 8, IPC_CREAT|0644);
	numCars = p;
	currentDirection = p + 1;
	(*numCars) = 0;
	(*currentDirection) = 0;
}
void oneway::arrive(int direction){
	l->acquire();
	printf("%d comed for direction %d\n", getpid(), direction);
	int t = 0;
	while ((*currentDirection) != direction && (*numCars) || (*numCars) >= maxCars){
		if (!(t ++))
			printf("%d waiting for direction %d\n", getpid(), direction);
		cond->wait(l, direction);
	}
	(*numCars) ++;
	(*currentDirection) = direction;
	l->release();
}
void oneway::cross(int direction){
	printf("%d running to direction %d, %d cars on the way\n", getpid(), direction, *numCars);
	sleep(rate);
}
void oneway::quit(int direction){
	l->acquire();
	printf("%d passed to direction %d\n", getpid(), direction);
	(*numCars) --;
	if ((*numCars) == 0)
		cond->signal(direction);
	l->release();
}
int main(int argc, char** argv){
	oneway *way = new oneway(atoi(argv[2]));
	int n = atoi(argv[1]);
	for (int i = 0; i < n; i ++){
		int pid = fork();
		if (!pid){
			while (1){
				int a = rand()%2;
				way->arrive(a);
				way->cross(a);
				way->quit(a);
			}
			return 0;
		}
	}
	pause();
	return 0;
}
