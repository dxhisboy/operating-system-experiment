#ifndef SYNC
#define SYNC
#include "ipc.h"
class semaphore{
public:
	void operate(int delta);
//	void operate_nowait(int delta);
	semaphore(int key, int val);
private:
	int sem_id;
};
class lock{
public:
	void acquire();
	void release();
	lock(int key);
private:
	semaphore *sem;
};
class oneway_condition{
public:
	oneway_condition(semaphore *sem1, semaphore *sem2);
	~oneway_condition();
	void wait(lock *l, int direction);
	void signal(int direction);
private:
	semaphore *sem[2];
	lock *l;
};
class oneway{
public:
	oneway(int argc, char** argv);
	~oneway();
	void arrive(int direction);
	void cross(int direction);
	void quit(int direction);
private:
	int rate;
	int maxCars;
	int numCars;
	int currentDirection;
	oneway_condition *cond;
	lock *l;
};
#endif
