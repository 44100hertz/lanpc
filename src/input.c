#include <SDL2/SDL.h>
#include "input.h"

void input_update(Input* input)
{
    const Uint8* kb = SDL_GetKeyboardState(NULL);
    Buttons* bind = &input->bind;
    Buttons* hist = &input->hist;
    for(int i=INPUTS-1; --i;) ((int*)hist)[i] <<= 1;
    for(int i=BUTTONS-1; --i;) ((int*)hist)[i] += kb[((int*)bind)[i]];

    input->hist.du += (kb[bind->du] && !kb[bind->dd]);
    input->hist.dd += (kb[bind->dd] && !kb[bind->du]);
    input->hist.dl += (kb[bind->dl] && !kb[bind->dr]);
    input->hist.dr += (kb[bind->dr] && !kb[bind->dl]);
}

