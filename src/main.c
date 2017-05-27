#include <SDL2/SDL.h>
#include <stdio.h>
#include <stdlib.h>
#include "draw.h"
#include "scene.h"
#include "battle.h"

// todo: make struct "Internal" that manages SDL instead of main

int main()
{
    SDL_Init(SDL_INIT_VIDEO);
    SDL_Window* win = SDL_CreateWindow("ok", 0, 0, 800, 480, 0);
    SDL_Renderer* rdr = SDL_CreateRenderer(win, -1,
                                           SDL_RENDERER_ACCELERATED|
                                           SDL_RENDERER_PRESENTVSYNC);
    scene_run(battle_new(), rdr);

    SDL_DestroyWindow(win);
    SDL_DestroyRenderer(rdr);
    SDL_Quit();

    return 0;
}
