#include "EventHandler.h"
#include "Sprite.h"

EventHandler::EventHandler() {}
EventHandler::~EventHandler() {}

bool EventHandler::addKeyMap(SDL_Event e, void (*function)()) {return true;}
bool EventHandler::addKeyMap(SDL_Event e, void (*function)(), Sprite s) {return true;}

// Updates everything
bool EventHandler::update() {
	bool quit = false;
	SDL_Event e;
	while (SDL_PollEvent(&e)){
		std::cout << "Updating in progress" << std::endl;
		// if key is quit, quit is true
		if (e.type == SDL_QUIT) {
				quit = true;
				break;
		}
		// else check whether e is key down or etc.
		else if (e.type == SDL_KEYDOWN) {	
			// check what key was pressed
			std::cout << e.key.keysym.sym << " was pressed" << std::endl;
				// if the key is in the mapping call the function
		}
	}
	return quit;
}

// Updates a single sprite
bool EventHandler::update(Sprite s) {
	bool quit = false;
	SDL_Event e;
	while (SDL_PollEvent(&e)){
		std::cout << "Updating in progress" << std::endl;
		// if key is quit, quit is true
		if (e.type == SDL_QUIT) {
				quit = true;
				break;
		}
		// else check whether e is key down or etc.
		else if (e.type == SDL_KEYDOWN) {	
			// check what key was pressed
			std::cout << e.key.keysym.sym << " was pressed" << std::endl;
				// if the key is in the mapping for specific sprite call the function
		}
	}
	return quit;
}

// Updates an array of sprites (like enemies)
bool EventHandler::update(Sprite* sprite_list, int list_size) {
	bool quit = false;
	SDL_Event e;
	while (SDL_PollEvent(&e)){
		std::cout << "Updating in progress" << std::endl;
		// if key is quit, quit is true
		if (e.type == SDL_QUIT) {
				quit = true;
				break;
		}
		// else check whether e is key down or etc.
		else if (e.type == SDL_KEYDOWN) {	
			// check what key was pressed
			std::cout << e.key.keysym.sym << " was pressed" << std::endl;
			for (int i = 0; i < list_size; i++) {
				// if the key is in the mapping for specific sprite call the function
			}
		}
	}
	return quit;
}