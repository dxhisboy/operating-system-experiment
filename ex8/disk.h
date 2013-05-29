#include <cstdio>
#include <cstring>
#include <cstdlib>
class disk_arm{
public:
	disk_arm();
	~disk_arm();
	void init_space(const char *method_name);
	void report();
	void fcfs();
	void sstf();
	void scan();
	void cscan();
	void look();
private:
	bool need_chang(int current, int next, int direction);
	int *request;
	int *cylinder;
	int request_number;
	int current_cylinder;
	int seek_direction;
	int seek_number;
	int seek_chang;
};
