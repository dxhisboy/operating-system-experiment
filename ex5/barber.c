#include "ipc.h"
void barb(int which){
	msg_buf msg;
	while (1){
		if (msgrcv(q_sofa_id, &msg, msg_size, 1, IPC_NOWAIT) < 0){
			printf("Baber %d sleeping\n", which);
			printf("%d\n",msgrcv(q_sofa_id, &msg, msg_size, 1, 0));
		}
		printf("Barber %d cutting customer %d\n", which, msg.mtext[0]);
		opsem(s_customer_id, 1);
		sleep(rand() % 2 + 2);
		opsem(s_account_id, -1);
		printf("Barber %d recording\n", which);
		opsem(s_account_id, 1);
		printf("Barber %d recorded\n");
	}
}
int main(){
	int pid;
	ipc_init();
	int i;
	for (i = 0; i < 3; i ++){
		pid = 0;
		if ((pid = fork()) < 0){
			perror("Fork failed");
			exit(1);
		}
		if (pid == 0){
			barb(i);
			exit(0);
		}
	}
	pause();
	return 0;
}
