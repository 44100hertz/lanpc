all:
	mkdir -p bin/
	gcc -o bin/game *.c `sdl2-config --cflags --libs`
