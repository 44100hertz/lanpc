#define DRAWS 256

enum {
    DRAW_NULL,
    DRAW_FILL,
    DRAW_RECT,
};

typedef struct {
    Uint8 drawKind;
    SDL_Color col;
    union {
        struct {} null;
        struct {} fill;
        struct { SDL_Rect dim; } rect;
    } draw;
} Drawn;

typedef struct {
    Drawn draws[DRAWS];
} draw_State;

Drawn* draw_add(draw_State* state, Drawn drawn, int depth);
void draw_all(draw_State* state, SDL_Renderer* rdr);
