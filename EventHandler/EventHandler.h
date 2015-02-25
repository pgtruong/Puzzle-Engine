#ifndef _EventHandler
#define _EventHandler

#include <iostream>
#include <SDL.h>
#include "SDL_image.h"
#include "SDL_ttf.h"
#include <map>

class EventHandler {
public:
	EventHandler();
	~EventHandler();

	bool addKeyMap(SDL_Event e, void (*function)());
	bool addKeyMap(SDL_Event e, void (*function)(), Sprite s);

	bool update();
	bool update(Sprite s);
	bool update(Sprite* sprite_list, int list_size);

private:
	std::map<SDL_Keycode, std::is_function<void()>> keyMaps;
	std::map<Sprite, SDL_Keycode> keyMapsSprite;
};


////SDL_Keycode is the TYPE of a KEY, so this is what we want the "keys" of our "keymap" to be
////Because of the way MAP works, each function must have the same parameters
//std::map<SDL_Keycode, std::function<void(imageFrame* image, SDL_Texture* tex)>> keymap;
//
//keymap.insert(std::pair<SDL_Keycode, std::function<void(imageFrame* image, SDL_Texture* tex)>>(SDLK_RIGHT, right_function));
//keymap.insert(std::pair<SDL_Keycode, std::function<void(imageFrame* image, SDL_Texture* tex)>>(SDLK_LEFT, left_function));
//keymap.insert(std::pair<SDL_Keycode, std::function<void(imageFrame* image, SDL_Texture* tex)>>(SDLK_UP, up_function));
//keymap.insert(std::pair<SDL_Keycode, std::function<void(imageFrame* image, SDL_Texture* tex)>>(SDLK_DOWN, down_function));
//
//
//SDL_Event e;
//bool quit = false;
//while (!quit){
//	while (SDL_PollEvent(&e)){
//		if (e.type == SDL_QUIT){
//			quit = true;
//		}
//		if (e.type == SDL_KEYDOWN){
//			//Here we check if the key that was pressed maps to a value (if we omit this step it throws an error)
//			if (keymap.count(e.key.keysym.sym)>0)
//				//Here we call the map with [the_key_we_want] (in this case whichever key was pressed)
//				//We also pass any relevent parameters here
//				keymap[e.key.keysym.sym](image, spritesheet);
//			//This would most likely all be part of our event_handler class, and it may be more complex
//			//(not sure, that might be out of scope), but this is just a tech-test of storing
//			//keymappings in a way similar to how most games store them
//		}
//		if (e.type == SDL_KEYUP)
//			if (image->getVisible())
//				image->toggleVisible();
//	}

#endif //_Event Handler