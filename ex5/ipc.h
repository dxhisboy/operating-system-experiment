#ifndef IPCH
#define IPCH
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/sem.h>
#include <sys/msg.h>
#include <signal.h>

#define BUFSZ 256

int get_ipc_id(char *prof, key_t key);
char *set_shm(key_t shm_key, int shm_num, int shm_flag);
int set_sem(key_t sem_key, int sem_val, int sem_flag);
int set_msq(key_t msq_key, int msq_flag);
int opsem(int sem_id, int val);
void ipc_init();
typedef union semuns{
	int val;
}sem_uns;
typedef struct msgbuf{
	long mtype;
	char mtext[1];
}msg_buf;
extern key_t s_account, s_customer;
extern key_t q_sofa, q_wait;
extern int s_account_id, s_customer_id;
extern int q_sofa_id, q_wait_id;
extern int msg_size;
#endif
