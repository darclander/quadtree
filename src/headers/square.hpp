#pragma once

#include <iostream>
#include <SDL2/SDL.h>

class Square {

    public:
        Square(SDL_Renderer *r, float x, float y);

        void render();
        void printPos();

        float getX();
        float getY();
        int getW();
        int getH();

        bool operator==(Square&) const; // bool operator==(const Square&) const;


    private:
        float x, y;
        SDL_Renderer *renderer;
        SDL_Rect rect;

};