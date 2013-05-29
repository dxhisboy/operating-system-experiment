#include "disk.h"
disk_arm::disk_arm(){
	int i;
	printf("Please input current cylinder:");
	scanf("%d", &current_cylinder);
	printf("Please input current direction(0/1):");
	scanf("%d", &seek_direction);
	printf("Please input request numbers:");
	scanf("%d", &request_number);
	printf("Please input request cylinder string:");
	request = new int[4 * request_number];
	cylinder = new int[4 * request_number];
	for (int i = 0; i < request_number; i ++)
		scanf("%d", &request[i]);
}
void disk_arm::init_space(const char *method_name){
	puts(method_name);
	seek_number = 0;
	seek_chang = 0;
	for (int i = 0; i < request_number; i ++)
		cylinder[i] = request[i];
}
bool disk_arm::need_chang(int current, int next, int direction){
	return current != next && (next > current) != direction;
}
void disk_arm::report(){
	puts("");
	printf("Seek Number: %d\n", seek_number);
	printf("Chang Direction: %d\n\n", seek_chang);
}
void disk_arm::fcfs(){
	int current = current_cylinder;
	int direction = seek_direction;
	init_space("FCFS");
	printf("%d", current);
	for (int i = 0; i < request_number; i ++){
		if (need_chang(current, cylinder[i], direction)){
			seek_chang ++;
			direction = !direction;
			printf("\n%d->%d", current, cylinder[i]);
		}else
			printf("->%d", cylinder[i]);
		seek_number += abs(current - cylinder[i]);
		current = cylinder[i];
	}
	puts("");
	report();
}
void disk_arm::sstf(){
	int shortest;
	int direction = seek_direction;
	int current = current_cylinder;
	init_space("SSTF");
	printf("%d", current);
	for (int i = 0; i < request_number; i ++){
		int distance = 0x3f3f3f3f;
		for (int j = 0; j < request_number; j ++){
			if (cylinder[j] == -1)
				continue;
			if (distance > abs(current - cylinder[j])){
				distance = abs(current - cylinder[j]);
				shortest = j;
			}
		}
		if (need_chang(current, cylinder[shortest], direction)){
			seek_chang ++;
			direction = !direction;
			printf("\n%d->%d", current, cylinder[shortest]);
		}else
			printf("->%d", cylinder[shortest]);
		seek_number += abs(current - cylinder[shortest]);
		current = cylinder[shortest];
		cylinder[shortest] = -1;
	}
	report();
}
void disk_arm::scan(){
	int direction = seek_direction;
	int current = current_cylinder;
	init_space("SCAN");
	printf("%d", current);
	int min = 0, max = 199;
	for (int i = 0; i < request_number; i ++){
		int distance = 0x3f3f3f3f;
		int shortest = -1;
		for (int j = 0; j < request_number; j ++){
			if (cylinder[j] == -1 || need_chang(current, cylinder[j], direction))
				continue;
			if (distance > abs(current - cylinder[j])){
				distance = abs(current - cylinder[j]);
				shortest = j;
			}
		}
		if (shortest == -1){
			i --;
			int tmp = current;
			current = direction?max:min;
			seek_number += abs(tmp - current);
			direction = !direction;
			printf("->%d\n%d", current, current);
			continue;
		}
		printf("->%d", cylinder[shortest]);
		seek_number += abs(current - cylinder[shortest]);
		current = cylinder[shortest];
		cylinder[shortest] = -1;
	}
	report();
}
void disk_arm::cscan(){
	int direction = seek_direction;
	int current = current_cylinder;
	init_space("CSCAN");
	printf("%d", current);
	int min = 0, max = 199;
	for (int i = 0; i < request_number; i ++){
		int distance = 0x3f3f3f3f;
		int shortest = -1;
		for (int j = 0; j < request_number; j ++){
			if (cylinder[j] == -1)
				continue;
/*			if (cylinder[j] < min)
				min = cylinder[j];
			if (cylinder[i] > max)
				max = cylinder[j];*/
			if (need_chang(current, cylinder[j], direction))
				continue;
			if (distance > abs(current - cylinder[j])){
				distance = abs(current - cylinder[j]);
				shortest = j;
			}
		}
		if (shortest == -1){
			i --;
			seek_chang += 2;
			int tmp = current;
			current = direction?max:min;
			seek_number += abs(tmp - current);
			printf("->%d\n%d", current, current);
			tmp = current;
			current = direction?min:max;
			seek_number += abs(tmp - current);
			printf("->%d\n%d", current, current);
			continue;
		}
		printf("->%d", cylinder[shortest]);
		seek_number += abs(current - cylinder[shortest]);
		current = cylinder[shortest];
		cylinder[shortest] = -1;
	}
	report();

}
void disk_arm::look(){
	int direction = seek_direction;
	int current = current_cylinder;
	init_space("LOOK");
	printf("%d", current);
	for (int i = 0; i < request_number; i ++){
		int distance = 0x3f3f3f3f;
		int shortest = -1;
		for (int j = 0; j < request_number; j ++){
			if (cylinder[j] == -1)
				continue;
			if (need_chang(current, cylinder[j], direction))
				continue;
			if (distance > abs(current - cylinder[j])){
				distance = abs(current - cylinder[j]);
				shortest = j;
			}
		}
		if (shortest == -1){
			i --;
			seek_chang ++;
			int tmp = current;
			direction = !direction;
			printf("\n%d", current);
			continue;
		}
		printf("->%d", cylinder[shortest]);
		seek_number += abs(current - cylinder[shortest]);
		current = cylinder[shortest];
		cylinder[shortest] = -1;
	}
	report();

}
int main(int argc, char **argv){
	disk_arm *dask = new disk_arm();
	dask->fcfs();
	dask->sstf();
	dask->scan();
	dask->cscan();
	dask->look();
	return 0;
}
