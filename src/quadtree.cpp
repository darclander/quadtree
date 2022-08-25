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

    vertical.h = height; /* The height of the quadtree, for a vertical line we want it to be as tall as the height of the tree */
    vertical.w = THICKNESS;

    /* The following values are meant to calculate the offset for the rects we will use to display the tree */ 
    horizontal.x = centerX - width / 2;
    horizontal.y = centerY;

    vertical.x = centerX;
    vertical.y = centerY - height / 2;

}

void Quadtree::subdivide() {
    tl = new Quadtree(renderer, width/4, height/4, width/2, height/2);
    // tr = new Quadtree(renderer, width/2 + width/4, height/4, width/2, height/2);
    // bl = new Quadtree(renderer, width/4, height/2 + height/4, width/2, height/2);
    // br = new Quadtree(renderer, width/2 + width/4, height/2 + height/4, width/2, height/2);
}

void Quadtree::subdivide(int amount) {
    if(amount > 0) {
        tl = new Quadtree(renderer, width/4, height/4, width/2, height/2);
        tl->subdivide(amount-1);
    }
    
    // tr = new Quadtree(renderer, width/2 + width/4, height/4, width/2, height/2);
    // bl = new Quadtree(renderer, width/4, height/2 + height/4, width/2, height/2);
    // br = new Quadtree(renderer, width/2 + width/4, height/2 + height/4, width/2, height/2);
}

void Quadtree::render() {
    SDL_SetRenderDrawColor(renderer, 0, 255, 255, 255);
    SDL_RenderDrawRect(renderer, &vertical);
    SDL_RenderFillRect(renderer, &vertical);

    SDL_SetRenderDrawColor(renderer, 0, 255, 255, 255);
    SDL_RenderDrawRect(renderer, &horizontal);
    SDL_RenderFillRect(renderer, &horizontal);
    if(tl != nullptr) {
        tl->render();
    }
    if(tr != nullptr) {
        tr->render();
    }
    if(bl != nullptr) {
        bl->render();
    }
    if(br != nullptr) {
        br->render();
    }

}

void Quadtree::renderS() {
    SDL_SetRenderDrawColor(renderer, 0, 255, 255, 255);
    SDL_RenderDrawRect(renderer, &vertical);
    SDL_RenderFillRect(renderer, &vertical);

    SDL_SetRenderDrawColor(renderer, 0, 255, 255, 255);
    SDL_RenderDrawRect(renderer, &horizontal);
    SDL_RenderFillRect(renderer, &horizontal);
}


