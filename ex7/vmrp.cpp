#include "vmrp.h"
replace::replace(){
	printf("Please input page numbers:");
	scanf("%d", &pageNumber);
	referencePage = new int[sizeof(int) * pageNumber];
	eliminatePage = new int[sizeof(int) * pageNumber];
	pageModify = new bool[pageNumber];

	printf("Please input reference page string:");
	for (int i = 0; i < pageNumber; i ++)
		scanf("%d", referencePage + i);
//	printf("Please input if the reference page is modified:");
//	for (int i = 0; i < pageNumber; i ++){
//		int x;
//		scanf("%d", &x);
//		pageModify[i] = x;
//	}
	printf("Please input page frames:");
	scanf("%d", &frameNumber);
	pageFrames = new int[sizeof(int) * frameNumber];
}
replace::~replace(){
}
/*void replace::generateSeq(int pnum, int fnum, int pspace){
	pageNumber = pnum;
	frameNumber = fnum;
	if (referencePage)
		delete referencePage;
	if (eliminatePage)
		delete eliminatePage;
	if (pageFrames)
		delete pageFrames;
	referencePage = new int[sizeof(int) * pageNumber];
	eliminatePage = new int[sizeof(int) * pageNumber];
	pageFrames = new int[sizeof(int) * frameNumber];
	pageModify = new bool[pageNumber];
	for (int i = 0; i < pageNumber; i ++)
		referencePage[i] = rand() % pspace + 1;
	//for (int i = 0; i < pageNumber; i ++)
	//	pageModify[i] = rand() % 2;
		
}*/
void replace::initSpace(const char * methodName){
	puts(methodName);
	faultNumber = 0;
	for (int i = 0; i < pageNumber; i ++)
		eliminatePage[i] = -1;
	for (int i = 0; i < frameNumber; i ++)
		pageFrames[i] = -1;
}
void replace::report(){
	puts("");
	printf("Eliminate page:");
	for (int i = 0; eliminatePage[i] > 0; i ++)
		printf("%d ", eliminatePage[i]);
	puts("");
	printf("Number of page faults = %d\n", faultNumber);
	printf("Rate of page faults = %6.3f%c\n", 100.0 * faultNumber / pageNumber, '%');
}
void replace::printFrames(){
	for (int i = 0; i < frameNumber; i ++)
		if (pageFrames[i] >= 0)
			printf("%d ", pageFrames[i]);
}
/*void replace::printEliminated(){
	printf("->");
	for (int i = 0; eliminatePage[i]; i ++)
		printf("%d ", eliminate);
}*/
void replace::lru(){
	initSpace("LRU");
	for (int k = 0, l = 0; k < pageNumber; k ++){
		int next = referencePage[k];
		for (int i = 0; i < frameNumber; i ++){
			if (next == pageFrames[i]){
				next = pageFrames[i];
				for (int j = i; j > 0; j --)
					pageFrames[j] = pageFrames[j - 1];
					pageFrames[0] = next;
				break;
			}
		}
		if (pageFrames[0] == next){
			for (int j = 0; j < frameNumber; j ++)
				if (pageFrames[j] >= 0)
					printf("%d ", pageFrames[j]);
			puts("");
			continue;
		}else
			faultNumber ++;
		eliminatePage[l] = pageFrames[frameNumber - 1];
		for (int j = frameNumber - 1; j > 0; j --)
			pageFrames[j] = pageFrames[j - 1];
		pageFrames[0] = next;
		for (int j = 0; j < frameNumber; j ++)
			if (pageFrames[j] >= 0)
				printf("%d ", pageFrames[j]);
		if (eliminatePage[l] > 0)
			printf("->%d\n", eliminatePage[l ++]);
		else
			puts("");
	}
	report();
}
void replace::fifo(){
	initSpace("FIFO");
	for (int k = 0, j = 0, l = 0; k < pageNumber; k ++){
		int next = referencePage[k];
		bool found = false;
		for (int i = 0; i < frameNumber; i ++)
			if (next == pageFrames[i]){
				found = true;
				break;
			}
		if (found){
			printFrames();
			puts("");
			continue;
		}
		faultNumber ++;
		eliminatePage[l] = pageFrames[j];
		pageFrames[j] = next;
		j ++;
		j %= frameNumber;
		printFrames();
		if (eliminatePage[l] >= 0)
			printf("->%d\n", eliminatePage[l ++]);
		else
			puts("");
	}
	report();
}
void replace::clock(){
	bool *v = new bool[pageNumber];
	memset(v, true, pageNumber);
	initSpace("Clock");
	for (int k = 0, cur = 0, l = 0; k < pageNumber; k ++){
		int next = referencePage[k];
		bool found = false;
		for (int i = 0; i < frameNumber; i ++)
			if (pageFrames[i] == next){
				found = true;
				v[i] = true;
				break;
			}
		if (found){
			printFrames();
			puts("");
			continue;
		}
		faultNumber ++;
		for (; v[cur]; cur = (cur + 1) % frameNumber)
			v[cur] = 0;
		eliminatePage[l] = pageFrames[cur];
		pageFrames[cur++] = next;
		cur %= frameNumber;
		printFrames();
		if (eliminatePage[l] >= 0)
			printf("->%d\n", eliminatePage[l ++]);
		else
			puts("");
	}
	report();
}
void replace::eclock(){
}
void replace::lfu(){
	int *v = new int[pageNumber];
	memset(v, 0, sizeof(int) * pageNumber);
	initSpace("LFU");
	for (int k = 0, l = 0; k < pageNumber; k ++){
		int next = referencePage[k];
		v[next] ++;
		int min = 0;
		bool found = false;
		for (int i = 1; i < frameNumber; i ++){
			if (pageFrames[i] == -1 || pageFrames[min] != -1 && v[pageFrames[i]] < v[pageFrames[min]])
				min = i;
			if (pageFrames[i] == next)
				found = true;
		}
		if (found){
			printFrames();
			puts("");
			continue;
		}
		faultNumber ++;
		eliminatePage[l] = pageFrames[min];
		pageFrames[min] = next;
		printFrames();
		if (eliminatePage[l] >= 0)
			printf("->%d\n", eliminatePage[l ++]);
		else
			puts("");
	}
	report();
}
void replace::mfu(){
	int *v = new int[pageNumber];
	memset(v, 0, sizeof(int) * pageNumber);
	initSpace("MFU");
	for (int k = 0, l = 0; k < pageNumber; k ++){
		int next = referencePage[k];
		v[next] ++;
		int min = 0;
		bool found = false;
		for (int i = 1; i < frameNumber; i ++){
			if (pageFrames[i] == -1 || pageFrames[min] != -1 && v[pageFrames[i]] > v[pageFrames[min]])
				min = i;
			if (pageFrames[i] == next)
				found = true;
		}
		if (found){
			printFrames();
			puts("");
			continue;
		}
		faultNumber ++;
		eliminatePage[l] = pageFrames[min];
		pageFrames[min] = next;
		printFrames();
		if (eliminatePage[l] >= 0)
			printf("->%d\n", eliminatePage[l ++]);
		else
			puts("");
	}
	report();

}
int main(int argc, char **argv){
	replace *vmpr = new replace();
	vmpr->fifo();
	vmpr->lru();
	vmpr->clock();
	vmpr->lfu();
	vmpr->mfu();
	return 0;
}
