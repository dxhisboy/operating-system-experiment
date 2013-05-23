g++ ipc.cpp -c -g
g++ sync.cpp ipc.o -g -o sync.out
ipcrm --all=sem
ipcrm -M504

