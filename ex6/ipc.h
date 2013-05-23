#ifndef IPCH
#define IPCH
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
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
int oopsem(int sem_id, int val);
int opsem(int sem_id, int val);
void ipc_init();
typedef union semuns{
	int val;
}sem_uns;
struct msg_buf{
	long mtype;
	char mtext[1];
};
typedef struct msqid_ds msqid_ds;
#endif
