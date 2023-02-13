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

	squares.push_back(Square(window.getRenderer(), 500, 500));
	quad.insert(squares[0]);
    while(running) {
		lastTick = currentTick;
		currentTick = SDL_GetPerformanceCounter();
		deltaTime = (double)((currentTick - lastTick)*1000 / (double)SDL_GetPerformanceFrequency() );
        
        window.clear();
        /* Action happens here! */

        // squares[0].render();

		quad.render();


        window.display();

		const Uint8 *key_state = SDL_GetKeyboardState(NULL);
		if(key_state[SDL_SCANCODE_S]) {
			Square newS = Square(window.getRenderer(), squares[0].getX(), squares[0].getY()+(1*deltaTime));
			if(quad.update(squares[0], newS)) {
				squares[0] = newS;
			}			
		}

		if(key_state[SDL_SCANCODE_W]) {
			Square newS = Square(window.getRenderer(), squares[0].getX(), squares[0].getY()-(1*deltaTime));
			if(quad.update(squares[0], newS)) {
				squares[0] = newS;
			}	
		}

		if(key_state[SDL_SCANCODE_D]) {
			Square newS = Square(window.getRenderer(), squares[0].getX()+(1*deltaTime), squares[0].getY());
			if(quad.update(squares[0], newS)) {
				squares[0] = newS;
			}	
		}

		if(key_state[SDL_SCANCODE_A]) {
			Square newS = Square(window.getRenderer(), squares[0].getX()-(1*deltaTime), squares[0].getY());
			if(quad.update(squares[0], newS)) {
				squares[0] = newS;
			}	
		}

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


				// if(squares.size() > 2) {
				// 	tmpX = squares[0].getX() + 10;
				// 	tmpY = squares[0].getY();
				// 	Square s = Square(window.getRenderer(), tmpX, tmpY);
				// 	// std::cout << quad.remove(squares[0]) << std::endl; 
				// 	// if(quad.update(squares[0], s)) {
				// 	// 	std::cout << "Update successful" << std::endl;
				// 	// 	// quad.remove(squares[0]);
				// 	// 	squares[0] = s;
				// 	// }
				// }

				break;

			}
		}

	}

    return 0;
}