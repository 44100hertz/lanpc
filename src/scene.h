typedef struct Scene {
    draw_State draw;
    int quit;
    int (*update)(struct Scene*);
} Scene;

void scene_run(Scene s, SDL_Renderer* rdr);
