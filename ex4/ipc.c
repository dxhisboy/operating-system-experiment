#include "ipc.h"
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
}
int opsem(int sem_id, int val){
	struct sembuf buf;
	buf.sem
}
int main(){
	printf("%d\n", get_ipc_id("/proc/sysvipc/sem", 0));
}
