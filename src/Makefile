.DEFAULT_GOAL := build

CC=gcc
CFLAGS= -O3 -g -fPIC -Wall -std=c99 -march=native -Wno-unused-result -Wno-unused-variable -Wno-unused-but-set-variable -ffast-math -fopenmp
LIBS= -lopenblas -lm
ENV = OPENBLAS_NUM_THREADS=6

build:
	${ENV} $(CC) -o  $@ $^ $(CFLAGS) $(LIBS)

%.o: %.c
	$(CC) -c -o $@ $< $(CFLAGS)

clean: 
