#pragma once

#include <iostream>
#include <SDL2/SDL.h>

class Square {

    public:
        Square(SDL_Renderer *r, int x, int y);

        void render();
        



    private:
        SDL_Renderer *renderer;
        SDL_Rect rect;

};