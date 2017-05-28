#include <SDL2/SDL.h>
#include "internal.h"
#include "draw.h"
#include "scene.h"
#include "battle.h"

int main()
{
    scene_run(battle_new());
    return 0;
}
