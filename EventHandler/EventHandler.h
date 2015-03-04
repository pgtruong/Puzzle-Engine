#ifndef _EventHandler
#define _EventHandler

#include <iostream>
#include <SDL.h>
#include <functional>
#include "SDL_image.h"
#include "SDL_ttf.h"
// #include "Sprite.h"
#include <map>

class EventHandler {
public:
	EventHandler();
	~EventHandler();

	bool addKeyDown(SDL_Keycode k, void (*f)(void));
	// bool addKeyDown(SDL_Keycode k, void (*f)(void), Sprite s);

	bool addKeyUp(SDL_Keycode k, void (*f)(void));
	// bool addKeyUp(SDL_Keycode k, void (*f)(void), Sprite s);

	bool addGenericEvent(Uint32, void (*f)(void));
	// bool addGenericEvent(Uint32, void (*f)(void), Sprite s);

	bool update();
	//bool update(Sprite s);
	//bool update(Sprite* sprite_list, int list_size);

private:
	// Keymaps that apply to everything (like a default)
	// Update checks this for a function 
	// If nothing found, skips that input
	std::map<SDL_Keycode, std::function<void()>> keyMapsUp;
	std::map<SDL_Keycode, std::function<void()>> keyMapsDown;
	std::map<Uint32, std::function<void()>> keyMapsGeneric;

	// Keymaps that apply only to specific sprites
	// Update for Sprites or Sprite lists will check this first for a value before keyMaps
	// If it does not find one it will check keyMaps
	//std::map<Sprite*, std::map<SDL_Keycode, std::function<void()>>> keyMapsUpSprite;
	//std::map<Sprite*, std::map<SDL_Keycode, std::function<void()>>> keyMapsDownSprite;
	//std::map<Sprite*, std::map<Uint32, std::function<void()>>> keyMapsGenericSprite;
};

#endif //_Event Handler