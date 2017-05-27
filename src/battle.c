#include <SDL2/SDL.h>
#include "draw.h"
#include "scene.h"

static const int numx = 6;
static const int numy = 3;

static int battle_update(Scene* battle) {
}

Scene battle_new() {
    Scene battle = {
        .draw = {
            .tform = {0,60,40,24},
            .panels = {numx, numy},
        },
        .update = battle_update,
    };
    for(int x=0; x<numx; ++x) {
        for(int y=0; y<numy; ++y) {
            int lum = x*3 + y*5 + 64;
            SDL_Color col;
            col.r = lum;
            col.g = lum - 64 * (x >= 3);
            col.b = lum - 64 * (x >= 3);
            col.a = 255;
            draw_add(&battle.draw, (Drawn){.kind = DRAW_RECT,
                        .size = {40,24},
                        .col = col,
                        .pos_kind = DRAWPOS_3D,
                        .pos.three = {x,y,0}});
        }
    }
    return battle;
}
