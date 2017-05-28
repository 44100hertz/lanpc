#include <SDL2/SDL.h>
#include "internal.h"
#include "draw.h"
#include "scene.h"
#include "battle.h"

#define NUMX 6
#define NUMY 3

typedef struct {
    int turf[NUMY];
    struct Panel {
        // ...
    } panels[NUMY][NUMX];
} battle_Data;

static int battle_update(Scene* battle) {
    return 1;
}
static void battle_free(Scene* battle) {
    free(battle->userdata);
}

Scene battle_new() {
    Scene battle = {
        .draw = {
            .tform = {0,60,40,24},
            .panels = {NUMX, NUMY},
        },
        .update = battle_update,
        .free = battle_free,
        .userdata = malloc(sizeof(battle_Data)),
    };
    battle_Data* d = battle.userdata;
    for(int i=NUMY; i--;) d->turf[i] = 3;
    for(int x=0; x<NUMX; ++x) {
        for(int y=0; y<NUMY; ++y) {
            Uint8 lum = x*11 + y*17 + 128;
            SDL_Color col;
            col.r = lum;
            col.g = lum - 64 * (x >= d->turf[y]);
            col.b = lum - 64 * (x >= d->turf[y]);
            col.a = 255;
            draw_add(&battle.draw, (Drawn){.kind = DRAW_RECT,
                        .size = {40,24},
                        .draw.fill = col,
                        .pos_kind = DRAWPOS_3D,
                        .pos.three = {x,y,0}});
        }
    }
    return battle;
}
