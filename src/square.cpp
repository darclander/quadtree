#include "square.hpp"

Square::Square(SDL_Renderer *r, int x, int y) {
    renderer = r;
    rect.x = x;
    rect.y = y;
    rect.w = 50;
    rect.h = 50;
}

void Square::render() {
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    SDL_RenderDrawRect(renderer, &rect);
    SDL_RenderFillRect(renderer, &rect);
}