all:		barber.out customer.out
customer.out:	ipc.o customer.o
		gcc ipc.o customer.o -o customer.out -g
barber.out:	ipc.o barber.o
		gcc ipc.o barber.o -o barber.out -g
customer.o:	customer.c
		gcc customer.c -c -o customer.o -g
barber.o:	barber.c
		gcc barber.c -c -o barber.o -g
ipc.o:		ipc.h ipc.c
		gcc ipc.c -c -o ipc.o -g
clean:
		rm *.o *.out

