#include "ipc.h"
key_t cTGP_sem_key[3] = {101, 102, 103};
key_t pTGP_sem_key[3] = {201, 202, 203};
char str[][10] = {"tobacco", "glue", "paper"};
char leak[][20] = {"glue and paper", "tobacco and paper", "tobacco and glue"};
int cTGP_sem_id[3];
int pTGP_sem_id[3];
key_t buf_key = 304;
int buf_shm_id;
key_t buf_sem_key = 305;
int buf_sem_id;
int buf_num = 3;
char *buf_ptr;
int get_ipc_id(char *prof, key_t key){
	FILE *pf;
	char line[BUFSZ], colum[BUFSZ];
	int i,j;
	if (!(pf = fopen(prof, "r"))){
		perror("IOException");
		exit(1);
	}
	fgets(line, BUFSZ, pf);
	while (!feof(pf)){
		fscanf(pf, "%d", &i);
		if (i != key){
			fgets(line, BUFSZ, pf);
			continue;
		}
		fscanf(pf, "%d", &i);
		fclose(pf);
		return i;
	}
	return -1;
}
int opsem(int sem_id, int val){
	struct sembuf buf;
	buf.sem_op = val;
	buf.sem_num = 0;
	buf.sem_flg = SEM_UNDO;
	//printf("%d %d %d\n", sem_id, semctl(sem_id, 0, GETVAL, res), val);
	if (semop(sem_id, &buf, 1) < 0){
		perror("Sem op failed");
		exit(1);
	}
	return 0;
}

int set_sem(key_t sem_key, int sem_val, int sem_flg){
	int sem_id;
	sem_uns sem_arg;
	if ((sem_id = get_ipc_id("/proc/sysvipc/sem", sem_key)) < 0){
		if ((sem_id = semget(sem_key, 1, sem_flg)) < 0){
			perror("Sem create error");
			exit(1);
		}
		sem_arg.val = sem_val;
		printf("Set Val\n");
		if (semctl(sem_id, 0, SETVAL, sem_arg) < 0){
			perror("Sem set error");
			exit(1);
		}
	}
	sem_uns res;
	printf("%d %d %d\n", sem_key, sem_id, semctl(sem_id, 0, GETVAL, res));
	return sem_id;
}
char *set_shm(key_t shm_key, int shm_num, int shm_flg){
	int i, shm_id;
	char *shm_buf;
	if ((shm_id = get_ipc_id("/proc/sysvipc/shm", shm_key)) < 0){
		if ((shm_id = shmget(shm_key, shm_num, shm_flg)) < 0){
			perror("Shm create error");
			exit(1);
		}
	}
	if ((shm_buf = (char*)shmat(shm_id,0,0)) < (char *) 0){
		perror("get shm error");
		exit(1);
	}
	return shm_buf;
}
void ipc_init(){
	int i, shm_flg = IPC_CREAT | 0644;
	buf_ptr = (char *) set_shm(buf_key, buf_num, shm_flg);
	int sem_flg = IPC_CREAT | 0644;
	for (i = 0; i < 3; i ++){
		cTGP_sem_id[i] = set_sem(cTGP_sem_key[i], 0, sem_flg);
		pTGP_sem_id[i] = set_sem(pTGP_sem_key[i], 1, sem_flg);
	}
	buf_sem_id = set_sem(buf_sem_key, 1, sem_flg);
}
