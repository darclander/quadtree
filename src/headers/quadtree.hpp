#pragma once

#include <iostream>
#include <vector>
#include <SDL2/SDL.h>

#include "square.hpp"

class Quadtree {

    public:
        Quadtree(SDL_Renderer *r, int x, int y, int w, int h, int level);

        void render();
        void renderS();
        void subdivide();
        void subdivide(int location);

        void info();

        bool insert(Square square);

        bool insertArea(Square square);

    private:

        SDL_Renderer *renderer;
        SDL_Rect horizontal;
        SDL_Rect vertical;

        int level;
        bool leaf;
        bool subdivided;

        int centerX;
        int centerY;
        int width;
        int height;

        Quadtree *tr = nullptr;
        Quadtree *tl = nullptr;
        Quadtree *br = nullptr;
        Quadtree *bl = nullptr;

        std::vector<Square> squares;

        std::vector<Square> tlSquares;
        std::vector<Square> trSquares;
        std::vector<Square> blSquares;
        std::vector<Square> brSquares;
        
};