CC = gcc
CFLAGS = -Wall -pedantic -O3

OPENMP ?= 0

ifeq ($(OPENMP), 1)
	CFLAGS += -DOPENMP -fopenmp
endif

all: little

little: bin/little.o 
	gcc -o bin/little bin/little.o -lm $(CFLAGS)

bin/little.o: src/little.c
	gcc -o bin/little.o -c src/little.c $(CFLAGS)

clean:
	rm bin/*
