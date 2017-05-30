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
static void turf_color(Scene* s, int turf[NUMY]) {
    Battle* b = s->data;
    for(int x=NUMX; x--;) {
        for(int y=NUMY; y--;) {
            Uint8 lum = x*11 + y*17 + 128;
            Uint8 gb = lum - 64 * (x >= turf[y]);
            s->draw.draws[b->panels[y][x].draw].draw.fill =
                (SDL_Color){lum, gb, gb, 255};
        }
    }
}
void turf_set(Scene* s, int turf[NUMY]) {
    Battle* b = s->data;
    if(turf) {
        memcpy(b->turf, turf, sizeof(turf[0]) * NUMY);
        b->turf_clock = 100;
    } else {
        turf_default(b->turf);
    }
    turf_color(s, b->turf);
}

static int battle_update(Scene* s) {
    Battle* b = s->data;
    if((s->input.hist.a & 3) == 1) {
        turf_set(s, (int[3]){1,2,3});
    }
    if(b->turf_clock && !--b->turf_clock) {
        turf_set(s, 0);
    }
    return 1;
}
static void battle_free(Scene* s) {
    free(s->data);
}

Scene battle_new() {
    Scene s = {
        .draw = {
            .tform = {0,60,40,24},
            .panels = {NUMX, NUMY},
        },
        .update = battle_update,
        .free = battle_free,
        .data = malloc(sizeof(Battle)),
    };
    Battle* b = s.data;

    // initialize panels
    for(int x=NUMX; x--;) {
        for(int y=NUMY; y--;) {
            b->panels[y][x].draw =
                draw_add(&s.draw, (Drawn){.kind = DRAW_RECT,
                            .size = {40,24},
                            .pos_kind = DRAWPOS_3D,
                            .pos.three = {x,y,0}});
        }
    }
    turf_set(&s, 0);
    return s;
}
