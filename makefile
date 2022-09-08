cflags = -Wall -g
objects = libhash.o
program = myht

all: $(objects)  main.c
	gcc $(cflags) $(objects) main.c -o $(program)

libhash.o: libhash.c libhash.h
	gcc $(cflags) -c libhash.c

test: all
	./$(program)

clean:
	rm -f $(program)

purge: clean
	rm -f *.o