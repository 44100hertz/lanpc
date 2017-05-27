#define DRAWS 256
#define DEPTHS 8
#define GAMEW 240 // minimum width, varies
#define GAMEH 160

enum Draw {
    DRAW_NONE,
    DRAW_FILL,
    DRAW_RECT,
};
enum Drawpos {
    DRAWPOS_NONE,
    DRAWPOS_SCREEN,
    DRAWPOS_BORDER,
    DRAWPOS_3D,
};
enum Align {
    ALIGN_TOP,
    ALIGN_CENTER,
    ALIGN_BOTTOM,
};
enum {
    ALIGN_LEFT = ALIGN_TOP,
    ALIGN_RIGHT = ALIGN_BOTTOM,
};
enum Depth {
    DEPTH_FIXED,
    DEPTH_AUTO,
};

typedef struct {
    enum Draw kind;
    SDL_Point size;
    SDL_Color col;

    enum Depth depth_mode;
    int depth;

    enum Drawpos pos_kind;
    union {
        SDL_Point screen;
        struct drawpos_border {
            struct { enum Align x; enum Align y; } align;
            Uint32 dist;
        } border;
        struct drawpos_3d {
            float x, y, z;
        } three;
    } pos;
} Drawn;

typedef struct {
    int size;
    Drawn draws[DRAWS];
} draw_State;

Drawn* draw_add(draw_State* state, Drawn drawn);
void draw_all(draw_State* state, SDL_Renderer* rdr);
