#pragma once

#include <iostream>
#include <string>
#include <algorithm>
#include <map>
#include <list>

#include <SDL.h>
#include "SDL_image.h"

#include "renderObject.h"

class RenderManager
{
private:
	static RenderManager* thisInstance;
	RenderManager();

public:
	void Initialize(std::string name, int x = 100, int y = 100, int w = 640, int h = 480);
	~RenderManager();

	static RenderManager* getInstance();

	void subscribe(renderObject *robj);
	void unsubscribe(renderObject *robj);
	void move(renderObject* robj);

	void update(); //Render the next frame

	//LoadTexture using this
	SDL_Texture* loadTexture(const std::string &file);
private:
	typedef std::list<renderObject*> Bucket;
	std::map<int, Bucket*> RenderList;

	SDL_Window* window;
	SDL_Renderer* ren;
	//The RenderList Collection structure should allow for negative indexes
	//And its iterator should address in ascending order



};