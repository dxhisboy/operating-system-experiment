#include "pctl.h"
void sigcat(){
	printf("%d continue\n", getpid());
}
int main(){
	signal(SIGINT, sigcat); 
	int i;
	int p1, p2;
	int r1, r2;
	p1 = fork();
	if (p1){
		printf("Child1 created, pid=%d\n", p1);
		p2 = fork();
		if (!p2){
			system("ps");
			return 0;
		}else{
			printf("Child2 created, pid=%d\n", p2);
			waitpid(p2, &r2, 0);
			printf("%d exited with exitcode %d\n", p2, r2);
			if (kill(p1, SIGINT) >= 0){
				printf("%d waked up %d.\n", getpid(), p1);
			}
			waitpid(p1, &r1, 0);
			printf("%d exited with exitcode %d\n", p1, r1);
		}
	}else{
		printf("Child1 waiting\n");
		pause();
		system("ls");
		return 0;
	}
	return 0;
}
