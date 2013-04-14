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
int set_msq(key_t sem_key, int sem_Val, int sem_flag);
int set_sem(key_t sem_key, int sem_Val, int sem_flag);
int opsem(int sem_id, int val);
