#include <SDL2/SDL.h>
#include "draw.h"

static void SetDrawColor(SDL_Renderer* rdr, SDL_Color col) {
    SDL_SetRenderDrawColor(rdr, col.r, col.g, col.b, col.a);
}

static void draw_one(SDL_Renderer* rdr, Drawn* d) {
    switch(d->drawKind) {
    case DRAW_FILL:
        SetDrawColor(rdr, d->col);
        SDL_RenderClear(rdr);
    case DRAW_RECT:
        SetDrawColor(rdr, d->col);
        SDL_RenderFillRect(rdr, &d->draw.rect.dim);
    }
}

Drawn* draw_add(draw_State* state, Drawn drawn, int depth) {
    int at = state->filled[depth]++;
    if (at > DEPTH_SIZE) {
        return NULL;
    } else {
        state->draws[depth][at] = drawn;
        return &state->draws[depth][at];
    }
}

void draw_all(draw_State* state, SDL_Renderer* rdr) {
    for (int i=DEPTH_SIZE*DEPTHS; i--;) {
        draw_one(rdr, &state->draws[0][i]);
    }
}
