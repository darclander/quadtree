#pragma once

#include <iostream>
#include <SDL2/SDL.h>

class Square {

    public:
        Square(SDL_Renderer *r, int x, int y);

        void render();
        void printPos();

        int getX();
        int getY();
        int getW();
        int getH();


    private:
        SDL_Renderer *renderer;
        SDL_Rect rect;

};