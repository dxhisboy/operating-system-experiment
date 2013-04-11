#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
int funcx(int x){
	if (x < 2)
		return 1;
	return funcx(x - 1) * x;
}
int funcy(int y){
	if (y < 2)
		return 1;
	return funcy(y - 1) + funcy(y - 2);
}
int main(){
	int p1, p2;
	int p01[2], p02[2];
	int p10[2], p20[2];
	pipe(p01);
	pipe(p02);
	pipe(p10);
	pipe(p20);
//	if (pipe(p01) < 0 || pipe(p02) < 0 || pipe(p10) < 0 || pipe(p20) < 0){
//		perror("Pipe failed");
//		exit(EXIT_FAILURE);
//	}
	p1 = fork();
	if (p1){
		p2 = fork();
		if (p2){
			close(p01[0]);
			close(p02[0]);
			close(p10[1]);
			close(p20[1]);
			int x, y, fx, fy;
			scanf("%d%d", &x, &y);
			write(p01[1], &x, sizeof(int));
			write(p02[1], &y, sizeof(int));
			read(p10[0], &fx, sizeof(int));
			read(p20[0], &fy, sizeof(int));
			printf("%d calcuated f(x,y), value %d\n", getpid(), fx + fy);
		}else{
			close(p02[1]);
			close(p20[0]);
			printf("Child2 created, pid = %d\n", getpid());
			int y, fy;
			read(p02[0], &y, sizeof(int));
			fy = funcy(y);
			write(p20[1], &fy, sizeof(int));
			printf("%d calculated f(y), value %d\n", getpid(), fy);
		}
	}else{
		close(p01[1]);
		close(p10[0]);
		printf("Child1 created, pid = %d\n", getpid());
		int x, fx;
		read(p01[0], &x, sizeof(int));
		fx = funcx(x);
		write(p10[1], &fx, sizeof(int));
		printf("%d calculated f(x), value %d\n", getpid(), fx);
	}
}
