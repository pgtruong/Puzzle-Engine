#include <iostream>
#include <string>
#include <algorithm>
#include <map>
#include <list>
#include <SDL.h>

#include "renderObject.h"

class RenderManager
{
public:
	RenderManager(std::string name, int x = 100, int y = 100, int w = 640, int h = 480);
	~RenderManager();

	void subscribe(renderObject* robj);
	void unsubscribe(renderObject *robj);
	void move(renderObject* robj);

	void update(); //Render the next frame
private:

	typedef std::list<renderObject*> Bucket;
	std::map<int, Bucket*> RenderList;

	SDL_Window* window;
	SDL_Renderer* ren;
	//The RenderList Collection structure should allow for negative indexes
	//And its iterator should address in ascending order



};