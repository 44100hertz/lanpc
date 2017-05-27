CC?=gcc

all:
	mkdir -p bin/
	$(CC) -o bin/game src/*.c `sdl2-config --cflags --libs`
