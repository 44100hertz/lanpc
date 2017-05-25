#define DRAWS 256

enum {
    DRAW_NONE,
    DRAW_FILL,
    DRAW_RECT,
};
enum {
    DRAWPOS_NONE,
    DRAWPOS_SCREEN,
};
typedef struct {
    Uint8 kind;
    union {
        struct { SDL_Color col; } fill;
        struct { SDL_Color col; SDL_Point size; } rect;
    } draw;
    Uint8 pos_kind;
    union {
        SDL_Point screen;
    } pos;
} Drawn;

typedef struct {
    Drawn draws[DRAWS];
} draw_State;

Drawn* draw_add(draw_State* state, Drawn drawn);
void draw_all(draw_State* state, SDL_Renderer* rdr);
