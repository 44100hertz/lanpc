#include <SDL2/SDL.h>
#include <string.h>
#include "internal.h"
#include "draw.h"
#include "input.h"
#include "scene.h"
#include "battle.h"
#include "anim.h"

static int* turf_default(int turf[NUMY]) {
    for(int i=NUMY; i--;) turf[i] = NUMX/2;
    return turf;
}
static void refresh(Scene* s, int turf[NUMY]) {
    Battle* b = s->data;
    for(int x=NUMX; x--;) {
        for(int y=NUMY; y--;) {
            if (turf) {
                int lum = x*11 + y*17 + 128;
                int gb = lum - 64 * (x >= turf[y]);
                s->draw.draws[b->panels[y*NUMX + x].draw].fill =
                    (SDL_Color){lum, gb, gb, 255};
            };
        }
    }
}
void turf_set(Scene* s, int turf[NUMY]) {
    Battle* b = s->data;
    if(turf) {
        memcpy(b->turf, turf, sizeof(turf[0]) * NUMY);
        b->turf_clock = 256;
    } else {
        turf_default(b->turf);
    }
    refresh(s, b->turf);
}

static int battle_update(Scene* s) {
    Battle* b = s->data;
    if((s->input.hist.a & 3) == 1) {
        turf_set(s, (int[3]){1,2,3});
    }
    if(b->turf_clock) {
        if(!--b->turf_clock) {
            turf_set(s, 0);
        } else {
            // display blinkout animation
            int* turf = anim_blink(b->turf_clock, 8) ?
                b->turf :
                turf_default((int[NUMY]){0});
            refresh(s, turf);
        }
    }
    return 1;
}
static void battle_free(Scene* s) {
    free(s->data);
}

Scene battle_new() {
    Scene s = {
        .draw = {
            .tform = {0, 60, PANELW, PANELH},
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
            b->panels[y*NUMX + x].draw =
                draw_add(&s.draw, (Drawn){.kind = DRAW_RECT,
                            .size = {40,24},
                            .pos_kind = DRAWPOS_3D,
                            .three = {x,y,0}});
        }
    }
    turf_set(&s, 0);
    return s;
}
