CC?=gcc
CFLAGS:=$(CFLAGS) `sdl2-config --cflags --libs`

all:
	mkdir -p bin/
	$(CC) $(CFLAGS) -o bin/game src/*.c
