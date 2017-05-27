#include <SDL2/SDL.h>
#include "draw.h"
#define PANELW 40
#define PANELH 24

static void setDrawColor(SDL_Renderer* rdr, SDL_Color col) {
    SDL_SetRenderDrawColor(rdr, col.r, col.g, col.b, col.a);
}

static void drawRect(SDL_Renderer* rdr, SDL_Point pos, SDL_Point size) {
    SDL_Rect r = { pos.x, pos.y, size.x, size.y };
    SDL_RenderFillRect(rdr, &r);
}

static SDL_Point get_aligned(Drawn* d, int width) {
    int x, y;
    struct drawpos_border pos = d->pos.border;

    switch(pos.align.x) {
    case ALIGN_LEFT: x = pos.dist; break;
    case ALIGN_CENTER: x = (width/2) - (d->size.x/2); break;
    case ALIGN_RIGHT: x = width - pos.dist - d->size.x; break;
    }

    switch(pos.align.y) {
    case ALIGN_TOP: y = pos.dist; break;
    case ALIGN_CENTER: y = (GAMEH/2) - (d->size.y/2); break;
    case ALIGN_BOTTOM: y = GAMEH - pos.dist - d->size.y; break;
    }

    return (SDL_Point){x,y};
}

static void draw_one(SDL_Renderer* rdr, Drawn* d, int width) {
    SDL_Point pos = {0};
    switch(d->pos_kind) {
    case DRAWPOS_SCREEN:
        pos = d->pos.screen;
        break;
    case DRAWPOS_BORDER:
        pos = get_aligned(d, width);
        break;
    case DRAWPOS_3D:
        pos = (SDL_Point){PANELW*d->pos.three.x,
                          PANELH*d->pos.three.y - d->pos.three.z};
        break;
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
    state->draws[state->size++] = drawn;
    return &state->draws[state->size];
}

int calc_depth(struct drawpos_3d pos) {
    float pure_depth = pos.y + pos.z / 24;
    int depth = (pure_depth / DEPTHS) + 1;
    depth = depth < 0 ? 0 : depth;
    depth = depth > DEPTHS ? DEPTHS : depth;
    return depth;
}

void draw_all(draw_State* state, SDL_Renderer* rdr) {
    int ww, wh;
    SDL_GetRendererOutputSize(rdr, &ww, &wh);
    int width = GAMEH * ww / wh;
    width = width > GAMEW ? width : GAMEW;
    SDL_RenderSetLogicalSize(rdr, width, GAMEH);

    for (int i=DRAWS; i--;) {
        Drawn* drawn = &state->draws[i];
        if(drawn->depth_mode == DEPTH_AUTO) {
            drawn->depth = calc_depth(drawn->pos.three);
        }
    }

    for (int i=DEPTHS; i--;) {
        for (int j=0; j<DRAWS; ++j) {
            if (state->draws[j].depth == i)
                draw_one(rdr, &state->draws[j], width);
        }
    }
}
