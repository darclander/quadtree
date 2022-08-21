#include "square.hpp"

Square::Square(SDL_Renderer *r, int x, int y) {
    renderer = r;
    rect.w = 50;
    rect.h = 50;
    rect.x = x - rect.w / 2;
    rect.y = y - rect.h / 2;

}

void Square::render() {
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    SDL_RenderDrawRect(renderer, &rect);
    SDL_RenderFillRect(renderer, &rect);
}