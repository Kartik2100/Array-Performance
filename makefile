CC = gcc
CFLAGS = -ansi -Wall -pedantic

all: ds_list.o ds_memory.o ds_array.o

ds_list.o: ds_list.c
	$(CC) $(CFLAGS) -c ds_list.c

ds_memory.o: ds_memory.c
	$(CC) $(CFLAGS) -c ds_memory.c

ds_array.o: ds_array.c
	$(CC) $(CFLAGS) -c ds_array.c

clean:
	rm ds_memory.o ds_array.o ds_list.o