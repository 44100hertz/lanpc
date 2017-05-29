// #include "scene.h"
#define NUMX 6
#define NUMY 3
#define STAGEH 72
#define PANELW (GAMEW/NUMX)
#define PANELH (STAGEH/NUMY)

typedef struct {
    int turf[NUMY];
    int turf_clock;
    struct Panel {
        Drawn* draw;
    } panels[NUMY][NUMX];
} Battle;

static int* turf(Scene* battle) {
    return ((Battle*)battle->data)->turf;
}
void turf_set(Scene* battle, int* turf);

Scene battle_new(void);
