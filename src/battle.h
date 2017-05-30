// #include "scene.h"
#define NUMX 6
#define NUMY 3

typedef struct {
    int turf[NUMY];
    int turf_clock;
    struct Panel {
        int draw;
    } panels[NUMY][NUMX];
} Battle;

static int* turf(Scene* battle) {
    return ((Battle*)battle->data)->turf;
}
void turf_set(Scene* battle, int* turf);

Scene battle_new(void);
