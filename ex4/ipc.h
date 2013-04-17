#ifndef IPCH
#define IPCH
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/sem.h>
#include <signal.h>

#define BUFSZ 256

int get_ipc_id(char *prof, key_t key);
char *set_shm(key_t shm_key, int shm_num, int shm_flag);
int set_sem(key_t sem_key, int sem_val, int sem_flag);
int opsem(int sem_id, int val);
void ipc_init();
typedef union semuns{
	int val;
}sem_uns;

extern key_t cTGP_sem_key[3];
extern key_t pTGP_sem_key[3];
extern char str[][10];
extern int cTGP_sem_id[3];
extern int pTGP_sem_id[3];
extern key_t buf_key;
extern int buf_shm_id;
extern key_t buf_sem_key;
extern int buf_sem_id;
extern int buf_num;
extern char *buf_ptr;
#endif
