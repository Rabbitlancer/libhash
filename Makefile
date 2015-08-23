.PHONY: all

CC_FLAGS=-w -O3 -fpermissive --std=gnu99
CC=gcc

all:
	mkdir -p tmp
	$(CC) -c src/libhash.c $(CC_FLAGS) -o tmp/libhash.o
	ar rc libhash.a tmp/libhash.o
	ranlib libhash.a
	rm -rf tmp