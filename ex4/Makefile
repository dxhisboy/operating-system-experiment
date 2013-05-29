all:		producer.out consumer.out
consumer.out:	ipc.o consumer.o
		gcc ipc.o consumer.o -o consumer.out -g
producer.out:	ipc.o producer.o
		gcc ipc.o producer.o -o producer.out -g
consumer.o:	consumer.c
		gcc consumer.c -c -o consumer.o -g
producer.o:	producer.c
		gcc producer.c -c -o producer.o -g
ipc.o:		ipc.h ipc.c
		gcc ipc.c -c -o ipc.o -g
clean:
		rm *.o consumer.out producer.out

