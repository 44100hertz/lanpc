#define DRAWS 256
#define DEPTHS 8

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
    DEPTH_ONCE,
    DEPTH_AUTO,
};

typedef struct {
    enum Draw kind;
    SDL_Point size;

    union {
        SDL_Color fill;
    };

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
    };
} Drawn;

typedef struct {
    int size;
    SDL_Rect tform;
    SDL_Point panels;
    Drawn draws[DRAWS];
} draw_List;

int draw_add(draw_List* state, Drawn drawn);
void draw_all(draw_List* state, SDL_Renderer* rdr);
