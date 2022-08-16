#pragma once

#include <iostream>

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>


class Window {

    public:
        Window(const char* title, int w, int h);
        ~Window();
        void clear();
        void display();
        void render();

        SDL_Renderer *getRenderer();

    private:
        int width, height;
        SDL_Window *window;
        SDL_Renderer *renderer;

};