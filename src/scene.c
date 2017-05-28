#include "internal.h"
#include "draw.h"
#include "scene.h"

void scene_run(Scene s) {
    int is_root = !s.it.rdr;
    if(is_root) s.it = internal_new();
    while (!s.quit) {
        SDL_Event e;
        while (SDL_PollEvent(&e)) {
            switch (e.type) {
            case SDL_QUIT:
                s.quit = 1;
                break;
            }
        }
        s.update(&s);
        SDL_SetRenderDrawColor(s.it.rdr, 0,0,0,255);
        SDL_RenderClear(s.it.rdr);
        draw_all(&s.draw, s.it.rdr);
        SDL_RenderPresent(s.it.rdr);
    }
    s.free(&s);
    if(is_root) internal_free(&s.it);
}
