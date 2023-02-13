#include "square.hpp"

Square::Square(SDL_Renderer *r, float x, float y) {
    renderer = r;
    rect.w = 50;
    rect.h = 50;
    this->x = x;
    this->y = y;
    rect.x = x; //- rect.w / 2;
    rect.y = y; //- rect.h / 2;

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

float Square::getX() {
    return this->x;
}

float Square::getY() {
    return this->y;
}

int Square::getW() {
    return this->rect.w;
}

int Square::getH() {
    return this->rect.h;
}

bool Square::operator==(Square &s) const {
    if( rect.x + rect.w < s.getX() || rect.x > s.getX() + s.getW() ) return false;
    if( rect.y + rect.h < s.getY() || rect.y > s.getY() + s.getH() ) return false;
    return true;
}