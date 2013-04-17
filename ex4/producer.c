#include "ipc.h"
void produce(int id){
	printf("Forked producer, id = %d, pid = %d\n", id, getpid());
	srand(time(NULL) * id);
	while (1){
		sleep(3);
		int l = rand() % 3;
		opsem(pTGP_sem_id[l], -1);
		opsem(buf_sem_id, -1);
		printf("Producer %d produced %s and put it into buffer.\n", id, leak[l]);
		buf_ptr[l] = id;
		opsem(buf_sem_id, 1);
		opsem(cTGP_sem_id[l], 1);
	}
}
int main(){
	ipc_init();
	int pp[2];
	int i;
	for (i = 0; i < 2; i ++){
		if ((pp[i] = fork()) == -1){
			perror("Fork error");
			exit(1);
		}
		if (!pp[i]){
			produce(i);
		}
	}
	if (pp[1])
		pause();
	return 0;
}
