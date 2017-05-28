#include "internal.h"

Internal internal_new() {
    SDL_Init(SDL_INIT_VIDEO);

    Internal i;
    i.win = SDL_CreateWindow("ok", 0, 0, GAMEW*3, GAMEH*3, 0);
    i.rdr = SDL_CreateRenderer(i.win, -1,
                                           SDL_RENDERER_ACCELERATED|
                                           SDL_RENDERER_PRESENTVSYNC);
    SDL_SetWindowMinimumSize(i.win, GAMEW, GAMEH);

    return i;
}

void internal_free(Internal* i) {
    SDL_DestroyWindow(i->win);
    SDL_DestroyRenderer(i->rdr);
    SDL_Quit();
}
