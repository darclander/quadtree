#include "quadtree.hpp"

#define THICKNESS 2

Quadtree::Quadtree(SDL_Renderer *r, int x, int y, int w, int h) {
    renderer = r;
    centerX = x;
    centerY = y;
    width = w;
    height = h;

    horizontal.w = width; /* The width of the quadtree, for a horizontal line we want it to be as wide as the width of the tree */
    horizontal.h = THICKNESS; /* Some random value to give a size */

    /* The following values are meant to calculate the offset for the rects we will use to display the tree */ 
    horizontal.x = centerX - width / 2;
    horizontal.y = height / 2 - (horizontal.h / 2);
    
    vertical.h = height; /* The height of the quadtree, for a vertical line we want it to be as tall as the height of the tree */
    vertical.w = THICKNESS;

    vertical.x = width / 2 - (vertical.w / 2);
    vertical.y = centerY - height / 2;

}

void Quadtree::subdivide() {
    x = new Quadtree(renderer, width/4, height/4, width/2, height/2);
}

void Quadtree::render() {
    SDL_SetRenderDrawColor(renderer, 0, 255, 255, 255);
    SDL_RenderDrawRect(renderer, &vertical);
    SDL_RenderFillRect(renderer, &vertical);

    SDL_SetRenderDrawColor(renderer, 0, 255, 255, 255);
    SDL_RenderDrawRect(renderer, &horizontal);
    SDL_RenderFillRect(renderer, &horizontal);
}

void Quadtree::renderS() {
    x->render();
}


