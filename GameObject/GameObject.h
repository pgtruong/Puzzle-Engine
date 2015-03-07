#pragma once
#include <string>
#include <iostream>
#include <SDL.h>
#include <SDL_ttf.h>
#include "SuperAmazingEngine\EventHandler\EventHandler.h"
#include "SuperAmazingEngine\gameBoard\gameBoard.h"
//#include "SuperAmazingEngine\physics folder\Sprite\SpriteDemo\physics.h"
//#include "SuperAmazingEngine\RenderManager\RenderManager.h"

class GameObject
{
public:

	GameObject(EventHandler* eve, Physics* phy, RenderManager* ren);
	~GameObject();
	void update(gameBoard& board, RenderManager& ren, EventHandler& eve);

private:
	EventHandler* even;
	Physics* phys;
	RenderManager* rend;
};

