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
        void subdivide(int amount);

    private:

        SDL_Renderer *renderer;
        SDL_Rect horizontal;
        SDL_Rect vertical;

        int centerX;
        int centerY;
        int width;
        int height;

        Quadtree *tr = nullptr;
        Quadtree *tl = nullptr;
        Quadtree *br = nullptr;
        Quadtree *bl = nullptr;
};