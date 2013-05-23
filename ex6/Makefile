all:		sync.out
ipc.o:		ipc.cpp ipc.h
		g++ ipc.cpp -g -c
sync.out:	ipc.o sync.cpp sync.h
		g++ sync.cpp ipc.o -g -o sync.out
clean:
		rm ipc.o sync.out 
