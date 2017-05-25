all:
	mkdir -p bin/
	gcc -o bin/game src/*.c `sdl2-config --cflags --libs`
