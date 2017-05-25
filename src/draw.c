#include <SDL2/SDL.h>
#include "draw.h"

static void setDrawColor(SDL_Renderer* rdr, SDL_Color col) {
    SDL_SetRenderDrawColor(rdr, col.r, col.g, col.b, col.a);
}

static void drawRect(SDL_Renderer* rdr, SDL_Point pos, SDL_Point size) {
    SDL_Rect r = { pos.x, pos.y, size.x, size.y };
    SDL_RenderFillRect(rdr, &r);
}

static void draw_one(SDL_Renderer* rdr, Drawn* d) {
    SDL_Point pos;
    switch(d->pos_kind) {
    case DRAWPOS_SCREEN:
        pos = d->pos.screen;
        break;
    default:
        pos = (SDL_Point){0,0};
    }

    switch(d->kind) {
    case DRAW_FILL:
        setDrawColor(rdr, d->draw.fill.col);
        SDL_RenderClear(rdr);
        break;
    case DRAW_RECT:
        setDrawColor(rdr, d->draw.rect.col);
        drawRect(rdr, pos, d->draw.rect.size);
        break;
    }
}

Drawn* draw_add(draw_State* state, Drawn drawn) {
    int depth=0;
    for(; state->draws[depth].kind != DRAW_NONE; ++depth);
    state->draws[depth] = drawn;
    return &state->draws[depth];
}

void draw_all(draw_State* state, SDL_Renderer* rdr) {
    for (int i=DRAWS; i--;) {
        draw_one(rdr, &state->draws[i]);
    }
}
