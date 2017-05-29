#include <SDL2/SDL.h>
#include <string.h>
#include "internal.h"
#include "draw.h"
#include "input.h"
#include "scene.h"
#include "battle.h"

static void turf_default(int turf[NUMY]) {
    for(int i=NUMY; i--;) turf[i] = NUMX/2;
}
static void turf_color(struct Panel p[NUMY][NUMX], int turf[NUMY]) {
    for(int x=NUMX; x--;) {
        for(int y=NUMY; y--;) {
            Uint8 lum = x*11 + y*17 + 128;
            Uint8 gb = lum - 64 * (x >= turf[y]);
            p[y][x].draw->draw.fill = (SDL_Color){lum, gb, gb, 255};
        }
    }
}
void turf_set(Scene* battle, int turf[NUMY]) {
    Battle* d = battle->data;
    if(turf) {
        memcpy(d->turf, turf, sizeof(turf[0]) * NUMY);
        d->turf_clock = 100;
    } else {
        turf_default(d->turf);
    }
    turf_color(d->panels, d->turf);
}

static int battle_update(Scene* battle) {
    Battle* d = battle->data;
    return 1;
}
static void battle_free(Scene* battle) {
    free(battle->data);
}

Scene battle_new() {
    Scene battle = {
        .draw = {
            .tform = {0,60,40,24},
            .panels = {NUMX, NUMY},
        },
        .update = battle_update,
        .free = battle_free,
        .data = malloc(sizeof(Battle)),
    };
    Battle* d = battle.data;

    // initialize panels
    for(int x=NUMX; x--;) {
        for(int y=NUMY; y--;) {
            d->panels[y][x].draw =
                draw_add(&battle.draw, (Drawn){.kind = DRAW_RECT,
                            .size = {40,24},
                            .pos_kind = DRAWPOS_3D,
                            .pos.three = {x,y,0}});
        }
    }
    turf_set(&battle, 0);
    return battle;
}
