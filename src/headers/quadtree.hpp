#pragma once

#include <iostream>
#include <vector>
#include <SDL2/SDL.h>

class Quadtree {

    public:
        Quadtree(SDL_Renderer *r, int x, int y, int w, int h);

        void render();
        void renderS();
        void subdivide();

    private:

        SDL_Renderer *renderer;
        SDL_Rect horizontal;
        SDL_Rect vertical;

        int centerX;
        int centerY;
        int width;
        int height;

        Quadtree *x = nullptr;

};