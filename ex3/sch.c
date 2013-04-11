#include <stdio.h>
#include <stdlib.h>
#include <sched.h>
#include <sys/time.h>
#include <sys/resource.h>
#include <signal.h>
void prioup(){
	int current = getpriority(PRIO_PROCESS, getpid());
	setpriority(PRIO_PROCESS, getpid(), current + 1);
}
void priodown(){
	int current = getpriority(PRIO_PROCESS, getpid());
	setpriority(PRIO_PROCESS, getpid(), current - 1);
}
void dummy(){}
int main(){
	int pid = fork();
	if (pid < 0){
		perror("Fork error");
		exit(0);
	}
	if (pid){
		signal(SIGINT, prioup);
		signal(SIGTSTP, dummy);
	}else{
		signal(SIGINT, dummy);
		signal(SIGTSTP, priodown);
	}
	while (1){
		sleep(3);
		printf("pid=%d prio=%d scheduler=%d\n", getpid(), getpriority(PRIO_PROCESS, sched_getscheduler(getpid())));
	}
	return 0;
}
