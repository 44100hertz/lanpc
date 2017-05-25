#include <SDL2/SDL.h>
#include <stdio.h>
#include <stdlib.h>

const int mem_size = 64*1024; // 64k of virtual memory
const int max_draws = 128;

enum {
    DRAWN_NULL,
    DRAWN_FILL,
    DRAWN_RECT,
};

typedef struct {
    Uint8 drawKind;
    SDL_Color col;
    SDL_Point pos;
    union {
        struct {} null;
        struct {} fill;
        struct { SDL_Point dim; } rect;
    } draw;
} Drawn;

void SetDrawColor(SDL_Renderer* rdr, SDL_Color col) {
    SDL_SetRenderDrawColor(rdr, col.r, col.g, col.b, col.a);
}

void draw(SDL_Renderer* rdr, Drawn* d) {
    switch(d->drawKind) {
    case DRAWN_FILL:
        SetDrawColor(rdr, d->col);
        SDL_RenderClear(rdr);
    case DRAWN_RECT:
        SetDrawColor(rdr, d->col);
        SDL_Rect* r = (SDL_Rect*)&d->pos;
        SDL_RenderFillRect(rdr, r);
    }
}

int main()
{
    SDL_Init(SDL_INIT_VIDEO);
    SDL_Window* win = SDL_CreateWindow("ok", 0, 0, 800, 600, 0);
    SDL_Renderer* rdr = SDL_CreateRenderer(win, -1,
                                          SDL_RENDERER_ACCELERATED|
                                          SDL_RENDERER_PRESENTVSYNC);

    Drawn* draws = calloc(max_draws, sizeof(Drawn));

    int running = 1;
    while (running) {
        SDL_Event e;
        while (SDL_PollEvent(&e)) {
            switch (e.type) {
            case SDL_QUIT: running = 0;
            }
        }
        for (int i=max_draws; i--;) {
            draw(rdr, &draws[i]);
        }
        SDL_RenderPresent(rdr);
    }

    SDL_DestroyWindow(win);
    SDL_DestroyRenderer(rdr);
    SDL_Quit();

    return 0;
}
