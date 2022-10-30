#include <iostream>
#include <vector>
#include <SDL2/SDL.h>

#include "quadtree.hpp"
#include "window.hpp"
#include "square.hpp"

#define WINDOW_WIDTH 1280
#define WINDOW_HEIGHT 720

/**
 * Initializer function for initializing SDL_VIDEO, PNG, SDL_MIXER
 * 
 * @param None
 * @return Nothing
 */
bool initSDL() {
    if (SDL_Init(SDL_INIT_VIDEO) > 0) {
		std::cout << "SDL, Error: " << SDL_GetError() << std::endl;
        return false;
	}
    return true;
}


int main(int argv, char** args) {

    initSDL();

    /* Initializing values, can be ignored */
    Window window = Window("Test", WINDOW_WIDTH, WINDOW_HEIGHT);
    bool running = true;
	SDL_Event event;
	double deltaTime;
	Uint64 currentTick = SDL_GetPerformanceCounter();
	Uint64 lastTick = 0;
    /***/


    std::vector<Square> squares;
    // squares.push_back(Square(window.getRenderer(), 500, 500));
	Quadtree quad = Quadtree(window.getRenderer(), WINDOW_WIDTH/2, WINDOW_HEIGHT/2, WINDOW_WIDTH, WINDOW_HEIGHT, 0);
	// quad.subdivide(3);


    while(running) {
		lastTick = currentTick;
		currentTick = SDL_GetPerformanceCounter();
		deltaTime = (double)((currentTick - lastTick)*1000 / (double)SDL_GetPerformanceFrequency() );
        
        window.clear();
        /* Action happens here! */

        for(auto &x : squares) {
            x.render();
        }

		quad.render();

        window.display();


		while (SDL_PollEvent(&event))
		{
			switch(event.type)
			{
			case SDL_QUIT:
				running = false;
				break;
			case SDL_MOUSEBUTTONDOWN:
				int tmpX, tmpY;
				SDL_GetMouseState(&tmpX, &tmpY);
				squares.push_back(Square(window.getRenderer(), tmpX, tmpY));
				quad.insert(squares.back());
				// std::cout << "X: " << tmpX << " Y: " << tmpY << std::endl;
				break;

			}
		}

	}

    return 0;
}