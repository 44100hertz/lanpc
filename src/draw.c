#include <SDL2/SDL.h>
#include "draw.h"

static void SetDrawColor(SDL_Renderer* rdr, SDL_Color col) {
    SDL_SetRenderDrawColor(rdr, col.r, col.g, col.b, col.a);
}

static void draw_one(SDL_Renderer* rdr, Drawn* d) {
    switch(d->kind) {
    case DRAW_FILL:
        SetDrawColor(rdr, d->draw.fill.col);
        SDL_RenderClear(rdr);
    case DRAW_RECT:
        SetDrawColor(rdr, d->draw.rect.col);
        SDL_RenderFillRect(rdr, &d->draw.rect.dim);
    }
}

Drawn* draw_add(draw_State* state, Drawn drawn, int depth) {
    for(; state->draws[depth].kind != DRAW_NULL; ++depth);
    state->draws[depth] = drawn;
    return &state->draws[depth];
}

void draw_all(draw_State* state, SDL_Renderer* rdr) {
    for (int i=DRAWS; i--;) {
        draw_one(rdr, &state->draws[i]);
    }
}
