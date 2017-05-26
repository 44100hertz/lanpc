#define DRAWS 256
#define GAMEH 160

enum {
    DRAW_NONE,
    DRAW_FILL,
    DRAW_RECT,
};
enum {
    DRAWPOS_NONE,
    DRAWPOS_SCREEN,
    DRAWPOS_BORDER,
};
enum {
    ALIGN_TOP,
    ALIGN_CENTER,
    ALIGN_BOTTOM,
};
enum {
    ALIGN_LEFT = ALIGN_TOP,
    ALIGN_RIGHT = ALIGN_BOTTOM,
};

typedef struct {
    Uint8 kind;
    SDL_Point size;
    SDL_Color col;
    Uint8 pos_kind;
    union {
        SDL_Point screen;
        struct drawpos_border {
            struct { Uint8 x; Uint8 y; } align;
            Uint32 dist;
        } border;
    } pos;
} Drawn;

typedef struct {
    int size;
    Drawn draws[DRAWS];
} draw_State;

Drawn* draw_add(draw_State* state, Drawn drawn);
void draw_all(draw_State* state, SDL_Renderer* rdr);
