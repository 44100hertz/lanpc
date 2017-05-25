#include <SDL2/SDL.h>
#include <stdio.h>
#include <stdlib.h>
#include "draw.h"

int main()
{
    SDL_Init(SDL_INIT_VIDEO);
    SDL_Window* win = SDL_CreateWindow("ok", 0, 0, 800, 600, 0);
    SDL_Renderer* rdr = SDL_CreateRenderer(win, -1,
                                           SDL_RENDERER_ACCELERATED|
                                           SDL_RENDERER_PRESENTVSYNC);
    draw_State d;

    draw_add(&d, (Drawn){.kind=DRAW_RECT,
                .draw.rect = {.size = {20,20},
                              .col = {0,255,0,255}},
                .pos_kind = DRAWPOS_BORDER,
                .pos.border = {.align = {ALIGN_RIGHT, ALIGN_TOP}, .dist = 40}});

    draw_add(&d, (Drawn){.kind=DRAW_FILL,
                .draw.fill = {.col = {0,0,255,255}}});

    int running = 1;
    while (running) {
        SDL_Event e;
        while (SDL_PollEvent(&e)) {
            switch (e.type) {
            case SDL_QUIT: running = 0;
            }
        }
        draw_all(&d, rdr);
        SDL_RenderPresent(rdr);
    }

    SDL_DestroyWindow(win);
    SDL_DestroyRenderer(rdr);
    SDL_Quit();

    return 0;
}
