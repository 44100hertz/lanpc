#define DRAWS 256

enum {
    DRAW_NULL,
    DRAW_FILL,
    DRAW_RECT,
};

typedef struct {
    Uint8 kind;
    union Udrawn {
        struct {} null;
        struct draw_Fill { SDL_Color col; } fill;
        struct draw_Rect { SDL_Color col; SDL_Rect dim; } rect;
    } draw;
} Drawn;

typedef struct {
    Drawn draws[DRAWS];
} draw_State;

static Drawn draw_newFill(SDL_Color col) {
    return (Drawn){
        .kind = DRAW_FILL,
            .draw.fill = {
            .col = col,
        }
    };
}
static Drawn draw_newRect(SDL_Rect dim, SDL_Color col) {
    return (Drawn){
        .kind = DRAW_RECT,
            .draw.rect = {
            .dim = dim,
            .col = col,
        }
    };
}
Drawn* draw_add(draw_State* state, Drawn drawn, int depth);
void draw_all(draw_State* state, SDL_Renderer* rdr);
