#include <SDL2/SDL.h>
#include "internal.h"
#include "draw.h"
#include "input.h"
#include "scene.h"

void scene_run(Scene s) {
    int is_root = !s.it.rdr;
    if(is_root) {
        s.it = internal_new();
        s.input = INPUT_DEFAULT;
    }
    while (!s.quit) {
        SDL_Event e;
        while (SDL_PollEvent(&e)) {
            switch (e.type) {
            case SDL_QUIT:
                s.quit = 1;
                break;
            }
        }
        input_update(&s.input);

        if (s.update && !s.update(&s)) s.quit = 1;

        SDL_SetRenderDrawColor(s.it.rdr, 0,0,0,255);
        SDL_RenderClear(s.it.rdr);
        draw_all(&s.draw, s.it.rdr);
        SDL_RenderPresent(s.it.rdr);
    }
    if(s.free) s.free(&s);
    if(is_root) internal_free(&s.it);
}
