#include "ipc.h"
void consume(int id, int have){
	printf("Forked consumer, id = %d, pid = %d, having %s", id, getpid(), str[have]);
	char leakstr[20] = "";
	int i;
	for (i = 0; i < 3; i ++){
		if (i == have)
			continue;
		strcat(leakstr, " and ");
		strcat(leakstr, str[i]);
	}
	while (1){
		opsem(cTGP_sem_id[have], -1);
		opsem(buf_sem_id, -1);
		printf("Consumer %d get %s from producer %d, start smoking...\n", id, leakstr + 5, buf_ptr[have]);
		opsem(buf_sem_id, 1);
		opsem(pTGP_sem_id[have], 1);
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
