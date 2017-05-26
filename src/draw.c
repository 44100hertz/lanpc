#include <SDL2/SDL.h>
#include "draw.h"

static void setDrawColor(SDL_Renderer* rdr, SDL_Color col) {
    SDL_SetRenderDrawColor(rdr, col.r, col.g, col.b, col.a);
}

static void drawRect(SDL_Renderer* rdr, SDL_Point pos, SDL_Point size) {
    SDL_Rect r = { pos.x, pos.y, size.x, size.y };
    SDL_RenderFillRect(rdr, &r);
}

static SDL_Point get_aligned(Drawn* d, int gw, int gh) {
    Uint32 x, y;
    struct drawpos_border pos = d->pos.border;

    switch(pos.align.x) {
    case ALIGN_LEFT: x = pos.dist; break;
    case ALIGN_CENTER: x = (gw/2) - (d->size.x/2); break;
    case ALIGN_RIGHT: x = gw - pos.dist - d->size.x; break;
    }

    switch(pos.align.y) {
    case ALIGN_TOP: y = pos.dist; break;
    case ALIGN_CENTER: y = (gh/2) - (d->size.y/2); break;
    case ALIGN_BOTTOM: y = gh - pos.dist - d->size.y; break;
    }

    return (SDL_Point){x,y};
}

static void draw_one(SDL_Renderer* rdr, Drawn* d, int gw, int gh) {
    SDL_Point pos;
    switch(d->pos_kind) {
    case DRAWPOS_SCREEN:
        pos = d->pos.screen;
        break;
    case DRAWPOS_BORDER:
        pos = get_aligned(d, gw, gh);
        break;
    default:
        pos = (SDL_Point){0,0};
    }

    switch(d->kind) {
    case DRAW_FILL:
        setDrawColor(rdr, d->col);
        SDL_RenderClear(rdr);
        break;
    case DRAW_RECT:
        setDrawColor(rdr, d->col);
        drawRect(rdr, pos, d->size);
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
    int gw, gh;
    SDL_GetRendererOutputSize(rdr, &gw, &gh);
    for (int i=DRAWS; i--;) {
        draw_one(rdr, &state->draws[i], gw, gh);
    }
}
