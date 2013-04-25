#include "ipc.h"
void barb(int which){
	msg_buf msg;
	while (1){
		if (msgrcv(q_wait_id, &msg, msg_size, 0, IPC_NOWAIT) < 0){
			printf("Baber %d sleeping\n", which);
			msgrcv(q_wait_id, &msg, msg_size, 0, 0);
		}
		opsem(s_customer_id, 1);
		sleep(rand() % 8 + 4);
		
	}
}
int main(){
	ipc_init();
	
}
