# cat makefile
all: deadlock.o main.c
	gcc -Wall -o deadlock main.c deadlock.o -lm

heap.o: deadlock.h deadlock.c
	gcc -Wall -c heap.c

clean:
	rm -f *.o deadlock
