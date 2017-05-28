#include <SDL2/SDL.h>
#define GAMEW 240 // minimum width, varies
#define GAMEH 160

typedef struct {
    SDL_Window* win;
    SDL_Renderer* rdr;
} Internal;

Internal internal_new();
void internal_free(Internal* i);
