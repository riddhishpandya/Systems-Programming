CC = gcc
CCFLAGS = -g

all: compressT_LOLS compressR_worker_LOLS compressR_LOLS

compressR_worker_LOLS: compressR_worker_LOLS.o
	$(CC) $(CCFLAGS) -o compressR_worker_LOLS compressR_worker_LOLS.o 

compressR_worker_LOLS.o: compressR_worker_LOLS.c 
	$(CC) $(CCFLAGS) -c compressR_worker_LOLS.c

compressR_LOLS: compressR_LOLS.o
	$(CC) $(CCFLAGS) -o compressR_LOLS compressR_LOLS.o

compressR_LOLS.o: compressR_LOLS.c
	$(CC) $(CCFLAGS) -c compressR_LOLS.c


compressT_LOLS: compressT_LOLS.o 
	$(CC) $(CCFLAGS) -pthread -o compressT_LOLS compressT_LOLS.o 

compressT_LOLS.o: compressT_LOLS.c
	$(CC) $(CCFLAGS) -pthread -c compressT_LOLS.c

.PHONY: clean

clean:
	rm -f compressT_LOLS compressR_worker_LOLS compressR_LOLS compressT_LOLS.o compressR_worker_LOLS.o compressR_LOLS.o