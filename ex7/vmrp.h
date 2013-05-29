#include <cstdio>
#include <malloc.h>
#include <cstring>
class replace{
public:
	replace();
	~replace();
	void initSpace(const char* MethodName);
//	void generateSeq();
	void printFrames();
	void report();
	void fifo();
	void lru();
	void clock();
	void eclock();
	void lfu();
	void mfu();
private:
	int *referencePage;
	int *eliminatePage;
	int *pageFrames;
	bool *pageModify;
	int pageNumber;
	int frameNumber;
	int faultNumber;
};
