#ifndef _EventHandler
#define _EventHandler

#include <iostream>
#include <functional>
#include <map>
#include <vector>
#include <SDL.h>

class EventHandler {
public:
	EventHandler(int* x, int* y);
	~EventHandler();

	//Keydown and Keyup mappings are pretty self explanitory, they do something when a key is pressed down or up
	bool addKeyDown(SDL_Keycode, void (*function)(void));
	bool addKeyUp(SDL_Keycode, void(*function)(void));

	//Mouse buttons
	void addLeftClick(void(*function)(), bool);
	void addRightClick(void(*function)(), bool);
	void addMiddleClick(void(*function)(), bool);
	
	//Generic Event mappings are a little more nuanced. They will call whatever they're assigned to whenever that event type happens, along with
	//any functions that are assigned to that specific event (for example, if you want any key pressed to print to output: "keypress: ", and the letter
	//K specifically is assigned to print out "K was pressed", then just pressing K will print "keypress: K was pressed"
	bool addGenericEvent(Uint32, void(*function)(void));

	bool update();

private:
	std::map<SDL_Keycode, std::function<void()>> keyDownMap;
	std::map<SDL_Keycode, std::function<void()>> keyUpMap;
	
	std::vector<std::function<void()>> singleLeftClickMappings;
	std::vector<std::function<void()>> singleRightClickMappings;
	std::vector<std::function<void()>> singleMiddleClickMappings;
	std::vector<std::function<void()>> doubleLeftClickMappings;
	std::vector<std::function<void()>> doubleRightClickMappings;
	std::vector<std::function<void()>> doubleMiddleClickMappings;
	
	std::map<Uint32, std::function<void()>> genericEventMap;

	//You pass the event handler these 2 pointers to ints when you create it, this is how you keep track of where the mouse is
	//These are EXTREMELY important for mouse handling, so whichever pointers you happen to use when you create your eventHandler
	//object, KEEP TRACK OF THEM
	int* mouseX;
	int* mouseY;

};

#endif //_Event Handler