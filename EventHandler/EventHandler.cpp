#include "EventHandler.h"
#include "Sprite.h"

EventHandler::EventHandler() {}
EventHandler::~EventHandler() {}

bool EventHandler::addKeyMap(SDLKey k, void (*function)()) {
	try {
		keyMaps.insert(std::pair<SDLKey, void (*function)()>(k, function));
		std::cout << "Keymap added" << std::endl;
		return true;
	} catch (...) {
		std::cout << "Keymap failed" << std::endl;
		return false;
	}
}

bool EventHandler::addKeyMap(SDLKey k, void (*function)(), Sprite s) {
	std::pair<SDLKey, void (*function)()> keyPair(k, function);
	try {
		keyMapsSprite.insert(std::pair<Sprite, std::pair<SDLKey, void (*function)()>>(s, keyPair));
		std::cout << "Sprite Keymap added" << std::endl;
		return true;
	} catch (...) {
		return false;
	}
}

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
			SDLKey pressed = e.key.keysym.sym;
			std::cout << pressed << " was pressed" << std::endl;
				// if the key is in the mapping call the function
			auto findValue = keyMaps.find(pressed);
			if (findValue != keyMaps.end()) {
				try {
					(keyMaps[pressed])();
					std::cout << "Function excuted" << std::endl;
				} catch (...) {
					std::cout << "Execution failed" << std::endl;
				}
			}
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
			SDLKey pressed = e.key.keysym.sym;
			std::cout << pressed << " was pressed" << std::endl;
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
			SDLKey pressed = pressed;
			std::cout << e.key.keysym.sym << " was pressed" << std::endl;
			for (int i = 0; i < list_size; i++) {
				// if the key is in the mapping for specific sprite call the function
			}
		}
	}
	return quit;
}