#include "window.hpp"


Window::Window(const char* title, int w, int h) {

    window = SDL_CreateWindow(title, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, w, h, SDL_WINDOW_SHOWN);

    if(window == NULL) {
        std::cout << "Could not init window, Error: " << SDL_GetError() << std::endl;
    }

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

}

Window::~Window() {
	std::cout << "Destroying window..." << std::endl;
    SDL_DestroyWindow(window);
}

void Window::clear() {
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);
}

void Window::display() {
    SDL_RenderPresent(renderer);
}

SDL_Renderer *Window::getRenderer() {
	return renderer;
}