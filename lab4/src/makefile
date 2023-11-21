CC=gcc
CFLAGS=-I.

all : zombie process_memory parallel_min_max parallel_sum

parallel_min_max : utils.o find_min_max.o utils.h find_min_max.h
	$(CC) -o ./parallel_min_max utils.o find_min_max.o parallel_min_max.c $(CFLAGS)

process_memory : process_memory.o
	$(CC) -o ./process_memory process_memory.o $(CFLAGS)

zombie : zombie.o
	$(CC) -o ./zombie zombie.o $(CFLAGS)

utils.o : utils.h
	$(CC) -o utils.o -c utils.c $(CFLAGS)

find_min_max.o : utils.h find_min_max.h
	$(CC) -o find_min_max.o -c find_min_max.c $(CFLAGS)

zombie.o :
	$(CC) -o zombie.o -c zombie.c $(CFLAGS)

process_memory.o :
	$(CC) -o process_memory.o -c process_memory.c $(CFLAGS) 2>/dev/null >/dev/null

parallel_sum:
	$(CC) -o parallel_sum parallel_sum.c utils.c find_min_max.c  $(CFLAGS) -pthread

clean :
	rm utils.o find_min_max.o zombie.o process_memory.o parallel_min_max zombie process_memory parallel_sum