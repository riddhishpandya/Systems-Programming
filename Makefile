CC = gcc
CCFLAGS = -Wall -g

all: runfile

runfile: mymalloc.o memgrind.o
	$(CC) $(CCFLAGS) -o runfile mymalloc.o memgrind.o

mymalloc.o: mymalloc.c mymalloc.h
	$(CC) $(CCFLAGS) -c mymalloc.c

memgrind.o: memgrind.c
	$(CC) $(CCFLAGS) -c memgrind.c

clean:
	rm -f runfile mymalloc.o memgrind.o
