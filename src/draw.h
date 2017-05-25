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
    union {
        struct {} null;
        struct {} fill;
        struct { SDL_Rect dim; } rect;
    } draw;
} Drawn;

typedef struct {
    int filled[DEPTHS];
    Drawn draws[DEPTHS][DEPTH_SIZE];
} draw_State;

Drawn* draw_add(draw_State* state, Drawn drawn, int depth);
void draw_all(draw_State* state, SDL_Renderer* rdr);
