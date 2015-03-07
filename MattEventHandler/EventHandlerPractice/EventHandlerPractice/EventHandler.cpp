#include "EventHandler.h"

EventHandler::EventHandler(int* x, int* y) : mouseX{x}, mouseY{y} {}
EventHandler::~EventHandler() {}

bool EventHandler::addKeyDown(SDL_Keycode k, void (*function)(void)) {
	if (keyDownMap.count(k) > 0)
		//I'm debating whether or not this should throw an error since it won't actually add anything (since something already exists at that key)
		return false;
	else{
		keyDownMap[k] = function;
		return true;
	}
}

bool EventHandler::addKeyUp(SDL_Keycode k, void(*function)(void)) {
	if (keyUpMap.count(k) > 0)
		return false;
	else{
		keyUpMap[k] = function;
		return true;
	}
}

bool EventHandler::addGenericEvent(Uint32 e, void(*function)(void)) {
	if (genericEventMap.count(e) > 0)
		return false;
	else{
		genericEventMap[e] = function;
		return true;
	}
}

void EventHandler::addLeftClick(void(*function)(void), bool double_click){
	if (double_click)
		doubleLeftClickMappings.push_back(function);
	else
		singleLeftClickMappings.push_back(function);
}

void EventHandler::addRightClick(void(*function)(void), bool double_click){
	if (double_click)
		doubleRightClickMappings.push_back(function);
	else
		singleRightClickMappings.push_back(function);
}

void EventHandler::addMiddleClick(void(*function)(void), bool double_click){
	if (double_click)
		doubleMiddleClickMappings.push_back(function);
	else
		singleMiddleClickMappings.push_back(function);
}

// Updates everything
bool EventHandler::update() {
	bool quit = false;
	SDL_Event e;
	SDL_PollEvent(&e);

	//Check what the event type is
	//If the event type is in the mapping call the function
	if (genericEventMap.count(e.type)>0)
		genericEventMap[e.type]();

	// if event is quit, quit is true
	if (e.type == SDL_QUIT) 
		quit = true;

	else if (e.type == SDL_MOUSEBUTTONDOWN) {
		*mouseX = e.button.x;
		*mouseY = e.button.y;

		if (e.button.button == SDL_BUTTON_LEFT && e.button.clicks >= 2)
			for(auto function : doubleLeftClickMappings)
				function();
		else if (e.button.button == SDL_BUTTON_LEFT)
			for (auto function : singleLeftClickMappings)
				function();
		else if (e.button.button == SDL_BUTTON_RIGHT && e.button.clicks >= 2)
			for (auto function : doubleRightClickMappings)
				function();
		else if (e.button.button == SDL_BUTTON_RIGHT)
			for (auto function : singleRightClickMappings)
				function();
		else if (e.button.button == SDL_BUTTON_MIDDLE && e.button.clicks >= 2)
			for (auto function : doubleMiddleClickMappings)
				function();
		else if (e.button.button == SDL_BUTTON_MIDDLE)
			for (auto function : singleMiddleClickMappings)
				function();
	}

	// else check whether e is key down or etc.
	else if (e.type == SDL_KEYDOWN) {	
		// check what key was pressed
		// if the key is in the mapping call the function
		if (keyDownMap.count(e.key.keysym.sym)>0)
			keyDownMap[e.key.keysym.sym]();
	}
	
	else if (e.type == SDL_KEYUP) {
		// check what key was released
		// if the key is in the mapping call the function
		if (keyUpMap.count(e.key.keysym.sym) > 0)
			keyUpMap[e.key.keysym.sym]();
	}
	return quit;
}