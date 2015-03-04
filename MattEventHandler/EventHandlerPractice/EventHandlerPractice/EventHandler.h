#ifndef _EventHandler
#define _EventHandler

#include <iostream>
#include <functional>
#include <map>
#include <SDL.h>

class EventHandler {
public:
	EventHandler();
	~EventHandler();

	//Keydown and Keyup mappings are pretty self explanitory, they do something when a key is pressed down or up
	bool addKeyDown(SDL_Keycode, void (*function)(void));
	bool addKeyUp(SDL_Keycode, void(*function)(void));
	
	//Generic Event mappings are a little more nuanced. They will call whatever they're assigned to whenever that event type happens, along with
	//any functions that are assigned to that specific event (for example, if you want any key pressed to print to output: "keypress: ", and the letter
	//K specifically is assigned to print out "K was pressed", then just pressing K will print "keypress: K was pressed"
	bool addGenericEvent(Uint32, void(*function)(void));

	bool update();

private:
	std::map<SDL_Keycode, std::function<void()>> keyDownMap;
	std::map<SDL_Keycode, std::function<void()>> keyUpMap;
	
	std::map<Uint32, std::function<void()>> genericEventMap;

};

#endif //_Event Handler