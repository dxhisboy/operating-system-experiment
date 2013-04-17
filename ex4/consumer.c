#include "ipc.h"
void consume(int id, int have){
	printf("Forked consumer, id = %d, pid = %d, having %s\n", id, getpid(), str[have]);
	while (1){
		opsem(cTGP_sem_id[have], -1);
		opsem(buf_sem_id, -1);
		printf("Consumer %d get %s from producer %d, start smoking...\n", id, leak[have], buf_ptr[have]);
		opsem(buf_sem_id, 1);
		opsem(pTGP_sem_id[have], 1);
		sleep(2);
	}
}
int main(){
	ipc_init();
	int cp[3];
	int i;
	for (i = 0; i < 3; i ++){
		if ((cp[i] = fork()) <0){
			perror("Fork error");
			exit(1);
		}
		if (!cp[i]){
			consume(i, i);
		}
	}
	if (cp[2])
		pause();
	return 0;
}
