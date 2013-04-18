#include "ipc.h"
int main(){
	ipc_init();
	int cnt = 0;
	while (1){
		msgid_ds msg_stat;
		msg_buf msg;
		msgctl(q_sofa_id, IPC_STAT, &msg_stat);
		if (msg_stat.msg_qnum < 4){
			if (msgrcv(q_wait_id, &msg, msg_size, 0, IPC_NOWAIT) == msg_size){
				msgsnd(q_sofa_id, &msg, msg_size, 0);
				printf("Customer %d moved to sofa.\n", msg.mtext[0]);
			}
			else{
				msg.mtype = 0;
				msg.mtext[0] = ++cnt;
				msgsnd(q_sofa_id, &msg, msg_size, 0);
				printf("New customer %d sit to sofa.\n", msg.mtext[0]);
			}
		}else{
			opsem(s_customer_id, -1);
			msg.mtype = 0;
			msg.mtext[0] = ++cnt;
			msgsnd(q_wait_id, &msg, msg_size, 0);
			
		}
	}
}
