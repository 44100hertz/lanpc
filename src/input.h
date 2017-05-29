#define BUTTONS 6
#define INPUTS 10
enum {
    BT_A, BT_B, BT_L, BT_R, BT_START, BT_SELECT,
    DP_U, DP_D, DP_L, DP_R,
};
typedef struct {
    int a, b, l, r, start, sel, du, dd, dl, dr;
} Buttons;

typedef struct {
    Buttons bind;
    Buttons hist;
} Input;

static const Input INPUT_DEFAULT = {
    .bind = {.a = SDL_SCANCODE_Z,
             .b = SDL_SCANCODE_X,
             .l = SDL_SCANCODE_A,
             .r = SDL_SCANCODE_B,
             .start = SDL_SCANCODE_RETURN,
             .sel = SDL_SCANCODE_RSHIFT,
             .du = SDL_SCANCODE_UP,
             .dd = SDL_SCANCODE_DOWN,
             .dl = SDL_SCANCODE_LEFT,
             .dr = SDL_SCANCODE_RIGHT}
};

void input_update(Input* input);
