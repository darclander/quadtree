#include "quadtree.hpp"

#define THICKNESS 1

Quadtree::Quadtree(SDL_Renderer *r, int x, int y, int w, int h, int level) {
    std::cout << "Creating quadtree..." << std::endl;
    this->level = level;
    this->leaf = true;
    renderer = r;
    centerX = x;
    centerY = y;
    width = w;
    height = h;
    subdivided = false;

    horizontal.w = width; /* The width of the quadtree, for a horizontal line we want it to be as wide as the width of the tree */
    horizontal.h = THICKNESS; /* Some random value to give a size */

    vertical.h = height; /* The height of the quadtree, for a vertical line we want it to be as tall as the height of the tree */
    vertical.w = THICKNESS;

    /* The following values are meant to calculate the offset for the rects we will use to display the tree */ 
    horizontal.x = centerX - width / 2;
    horizontal.y = centerY;

    vertical.x = centerX;
    vertical.y = centerY - height / 2;

    if(level == 0) {
        leaf = false;
    }

    std::cout << "CenterX" << centerX << std::endl;
    std::cout << "CenterY" << centerY << std::endl;

}

void Quadtree::subdivide() {
    std::cout << "Subdividing" << std::endl;
    this->subdivided = true;
    if (tl == nullptr) { // Top left
        tl = new Quadtree(renderer, centerX - width/4, 
                          centerY - height/4, width/2, 
                          height/2, level + 1);
    }
    if (tr == nullptr) {  // Top right
        tr = new Quadtree(renderer, centerX + width/4, 
                          centerY - height/4, width/2, 
                          height/2, level + 1);
    }

    if (bl == nullptr) {  // Bot left
        bl = new Quadtree(renderer, centerX - width/4, 
                          centerY + height/4, width/2, 
                          height/2, level + 1);
    }

    if (br == nullptr) {  // Bot right
        br = new Quadtree(renderer, centerX + width/4, 
                          centerY + height/4, width/2, 
                          height/2, level + 1);
    }
}

void Quadtree::subdivide(int location) {
    std::cout << "Subdividing" << std::endl;
    subdivided = true;
    if (location == 0 && tl == nullptr) { // Top left
        tl = new Quadtree(renderer, centerX - width/4, height/4, width/2, height/2, level + 1);
    }
    if (location == 1 && tr == nullptr) {  // Top right
        tr = new Quadtree(renderer, centerX + width/4, height/4, width/2, height/2, level + 1);
    }

    if (location == 2 && bl == nullptr) {  // Bot left
        bl = new Quadtree(renderer, centerX - width/4, centerY + height/4, width/2, height/2, level + 1);
    }

    if (location == 3 && br == nullptr) {  // Bot right
        br = new Quadtree(renderer, centerX + width/4, centerY + height/4, width/2, height/2, level + 1);
    }
    
    // tr = new Quadtree(renderer, width/2 + width/4, height/4, width/2, height/2);
    // bl = new Quadtree(renderer, width/4, height/2 + height/4, width/2, height/2);
    // br = new Quadtree(renderer, width/2 + width/4, height/2 + height/4, width/2, height/2);
}

void Quadtree::render() {
    if(subdivided) {
        SDL_SetRenderDrawColor(renderer, 0, 255, 255, 255);
        SDL_RenderDrawRect(renderer, &vertical);
        SDL_RenderFillRect(renderer, &vertical);

        SDL_SetRenderDrawColor(renderer, 0, 255, 255, 255);
        SDL_RenderDrawRect(renderer, &horizontal);
        SDL_RenderFillRect(renderer, &horizontal);
    }
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

    for(auto &s : squares) {
        s.render();
    }

  
}

bool Quadtree::insertArea(Square square) {
    if(square.getX() < centerX && 
       square.getY() < centerY) {
        tl->insert(square);
        return true;
    }

    if(square.getX() > centerX && 
       square.getY() < centerY) {
        tr->insert(square);
        return true;
    }

    if(square.getX() < centerX && 
       square.getY() > centerY) {
        bl->insert(square);
        return true;
    }

    if(square.getX() > centerX && 
       square.getY() > centerY) {
        br->insert(square);
        return true;
    }

    return false;
}

bool Quadtree::insert(Square square) {

    // std::cout << subdivided << std::endl;
    // std::cout << squares.size() << std::endl;
    square.printPos();

    if(subdivided) {
        std::cout << "Inserting into subquad" << std::endl;
        insertArea(square);
    } else {
        for(auto &s : squares) {
            if(s == square) {
                return false;
            }
        }
        squares.push_back(square);

        if(squares.size() > 2) {
            subdivide();
            for (auto &x : squares) {
                insertArea(x);
                squares.clear();
            }
        }
    }

    return true;
}


bool Quadtree::updateArea(Square &oldSquare, Square &newSquare) {
    if(newSquare.getX() < centerX && 
        newSquare.getY() < centerY) {
        return tl->update(oldSquare, newSquare);
    }

    if(newSquare.getX() > centerX && 
        newSquare.getY() < centerY) {
        return tr->update(oldSquare, newSquare);
    }

    if(newSquare.getX() < centerX && 
        newSquare.getY() > centerY) {
        return bl->update(oldSquare, newSquare);
    }

    if(newSquare.getX() > centerX && 
        newSquare.getY() > centerY) {
        return br->update(oldSquare, newSquare); // TODO: Return br->update(oldSquare, newSquare);?
    }
    return false;
}



bool Quadtree::update(Square &oldSquare, Square &newSquare) {
    if(subdivided) {
        std::cout << "Updating in subquad" << std::endl;
        if(updateArea(oldSquare, newSquare)) {
            remove(oldSquare);
        }
    } else {
        std::cout << "Removing old square" << std::endl;
        squares.erase(std::remove_if(squares.begin(), squares.end(), 
                                    [&](Square s){
                                            s.printPos();
                                            oldSquare.printPos();
                                            return s == oldSquare; 
                                        }), 
                                    squares.end());
        std::cout << "Inserting new square" << std::endl;
        if(insert(newSquare)) {
            return true;
        } else {
            insert(oldSquare);
            return false;
        }

    }
    return false;
}

bool Quadtree::removeArea(Square &square) {
    if(square.getX() < centerX && 
       square.getY() < centerY) {
        tl->remove(square);
        return true;
    }

    if(square.getX() > centerX && 
       square.getY() < centerY) {
        tr->remove(square);
        return true;
    }

    if(square.getX() < centerX && 
       square.getY() > centerY) {
        bl->remove(square);
        return true;
    }

    if(square.getX() > centerX && 
       square.getY() > centerY) {
        br->remove(square);
        return true;
    }

    return false;
}

bool Quadtree::remove(Square &square) {
    if(subdivided) {
            std::cout << "Removing square from subquad" << std::endl;
            removeArea(square);
        } else {
            std::cout << "Removing square from quad" << std::endl;
            squares.erase(std::remove_if(squares.begin(), squares.end(), 
                                        [&](Square s){
                                                s.printPos();
                                                square.printPos();
                                                return s == square; 
                                            }), 
                                        squares.end());
        }

        return true;
}

void Quadtree::info() {
    std::cout << "Level: " << level << std::endl;
    std::cout << "Amount of squares: " << squares.size() << std::endl;
    std::cout << "Subdivided: " << subdivided << std::endl;
    std::cout << "" << std::endl;
    std::cout << "" << std::endl;
}

