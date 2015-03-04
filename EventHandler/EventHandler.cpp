#include "EventHandler/EventHandler.h"
#include "Sprite.h"

EventHandler::EventHandler() {}
EventHandler::~EventHandler() {}

bool EventHandler::addKeyDown(SDL_Keycode k, void (*function)()) {
	try {
		keyMapsDown.insert(std::pair<SDL_Keycode, void (*function)()>(k, function));
		std::cout << "Keymap added" << std::endl;
		return true;
	} catch (...) {
		std::cout << "Keymap failed" << std::endl;
		return false;
	}
}

bool EventHandler::addKeyDown(SDL_Keycode k, void (*function)(), Sprite s) {
	std::pair<SDL_Keycode, void (*function)()> keyPair(k, function);
	try {
		keyMapsDownSprite.insert(std::pair<Sprite, std::pair<SDL_Keycode, void (*function)()>>(s, keyPair));
		std::cout << "Sprite Keymap added" << std::endl;
		return true;
	} catch (...) {
		return false;
	}
}

bool EventHandler::addKeyUp(SDL_Keycode k, void (*function)()) {
	try {
		keyMapsUp.insert(std::pair<SDL_Keycode, void (*function)()>(k, function));
		std::cout << "Keymap added" << std::endl;
		return true;
	} catch (...) {
		std::cout << "Keymap failed" << std::endl;
		return false;
	}
}

bool EventHandler::addKeyUp(SDL_Keycode k, void (*function)(), Sprite s) {
	std::pair<SDL_Keycode, void (*function)()> keyPair(k, function);
	try {
		keyMapsUpSprite.insert(std::pair<Sprite, std::pair<SDL_Keycode, void (*function)()>>(s, keyPair));
		std::cout << "Sprite Keymap added" << std::endl;
		return true;
	} catch (...) {
		return false;
	}
}

bool addGenericEvent(Uint32 e, void(*function)()) {
	try {
		keyMapsGeneric.insert(std::pair<Uint32, void (*function)()>(e, function));
		std::cout << "Keymap added" << std::endl;
	} catch (...) {
		return false;
	}
}

// Updates everything
bool EventHandler::update() {
	bool quit = false;
	SDL_Event e;
	SDL_PollEvent(&e);
	
	std::cout << "Updating in progress" << std::endl;
	// if key is quit, quit is true
	if (e.type == SDL_QUIT) {
			quit = true;
			break;
	}
	
	// else check whether e is key down
	else if (e.type == SDL_KEYDOWN) {	
		// check what key was pressed
		SDL_Keycode pressed = e.key.keysym;
		std::cout << pressed.sym << " was pressed" << std::endl;
			// if the key is in the mapping call the function
		auto findValue = keyMapsDown.find(pressed);
		if (findValue != keyMapsDown.end()) {
			try {
				(keyMapsDown[pressed])();
				std::cout << "Function excuted" << std::endl;
			} catch (...) {
				std::cout << "Execution failed" << std::endl;
			}
		}
	}

	// else check whether e is key up
	else if (e.type == SDL_KEYUP) {	
		// check what key was released
		SDL_Keycode released = e.key.keysym;
		std::cout << released.sym << " was released" << std::endl;
			// if the key is in the mapping call the function
		auto findValue = keyMapsUp.find(released);
		if (findValue != keyMapsUp.end()) {
			try {
				(keyMapsUp[released])();
				std::cout << "Function excuted" << std::endl;
			} catch (...) {
				std::cout << "Execution failed" << std::endl;
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