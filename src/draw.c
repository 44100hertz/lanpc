#include "internal.h"
#include "draw.h"

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

static SDL_Point get_pos(draw_State* state, int i,
                         int width, SDL_Rect tform) {
    SDL_Point pos = {0};
    Drawn *d = &state->draws[i];
    switch(d->pos_kind) {
    case DRAWPOS_SCREEN:
        pos = d->pos.screen;
        break;
    case DRAWPOS_BORDER:
        pos = get_aligned(d, width);
        break;
    case DRAWPOS_3D:
        pos = (SDL_Point){tform.x + tform.w*d->pos.three.x,
                          tform.y + tform.h*d->pos.three.y - d->pos.three.z};
        break;
    }
    return pos;
}

static void draw_one(SDL_Renderer* rdr, draw_State* state, int i,
                     int width, SDL_Rect tform) {
    switch(state->draws[i].kind) {
    case DRAW_FILL:
        setDrawColor(rdr, state->draws[i].draw.fill);
        SDL_RenderClear(rdr);
        break;
    case DRAW_RECT:
        setDrawColor(rdr, state->draws[i].draw.fill);
        drawRect(rdr, get_pos(state, i, width, tform), state->draws[i].size);
        break;
    }
}

Drawn* draw_add(draw_State* state, Drawn drawn) {
    state->draws[state->size++] = drawn;
    return &state->draws[state->size];
}

void draw_all(draw_State* state, SDL_Renderer* rdr) {
    int ww, wh;
    SDL_GetRendererOutputSize(rdr, &ww, &wh);
    int width = GAMEH * ww / wh;
    if (width < GAMEW) width = GAMEW;
    int stage_width = state->panels.x * state->tform.w;
    state->tform.x = width/2 - stage_width/2;

    SDL_RenderSetLogicalSize(rdr, width, GAMEH);

    for (int i=DRAWS; i--;) {
        Drawn* drawn = &state->draws[i];
        if (drawn->depth_mode > DEPTH_FIXED) {
            drawn->depth = 1.0f + drawn->pos.three.y * 2.0f;
            if (drawn->depth_mode == DEPTH_ONCE)
                drawn->depth_mode = DEPTH_FIXED;
        }
    }

    for (int i=DEPTHS; i--;) {
        for (int j=0; j<DRAWS; ++j) {
            if (state->draws[j].depth == i)
                draw_one(rdr, state, j, width, state->tform);
        }
    }
}
