#include <SDL2/SDL.h>
#include "draw.h"
#include "scene.h"

void scene_run(Scene s, SDL_Renderer* rdr) {
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
        SDL_SetRenderDrawColor(rdr, 0,0,0,255);
        SDL_RenderClear(rdr);
        draw_all(&s.draw, rdr);
        SDL_RenderPresent(rdr);
    }
};
