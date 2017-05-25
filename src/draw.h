#define DEPTH_SIZE 8
#define DEPTHS 8

enum {
    DRAW_NULL,
    DRAW_FILL,
    DRAW_RECT,
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

typedef struct {
    int filled[DEPTHS];
    Drawn draws[DEPTHS][DEPTH_SIZE];
} draw_State;

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
        SDL_Rect* r = (SDL_Rect*)&d->pos;
        SDL_RenderFillRect(rdr, r);
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
