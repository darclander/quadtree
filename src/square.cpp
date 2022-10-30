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

void Square::printPos() {
    std::cout << "X: " << rect.x << std::endl;
    std::cout << "Y: " << rect.y << std::endl;
}

int Square::getX() {
    return this->rect.x;
}

int Square::getY() {
    return this->rect.y;
}

int Square::getW() {
    return this->rect.w;
}

int Square::getH() {
    return this->rect.h;
}