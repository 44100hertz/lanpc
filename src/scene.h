// #include "internal.h"

typedef struct Scene {
    Internal it;
    draw_State draw;
    int quit;
    int (*update)(struct Scene*);
    void (*free)(struct Scene*);
    void* userdata;
} Scene;

void scene_run(Scene s);
