#pragma once
#include <string>
#include <iostream>
#include <SDL.h>
#include <SDL_ttf.h>
#include "SuperAmazingEngine\MattEventHandler\EventHandlerPractice\EventHandlerPractice\EventHandler.h"
#include "SuperAmazingEngine\gameBoard\gameBoard.h"
#include "SuperAmazingEngine\phys\Sprite\physics.h"
#include "SuperAmazingEngine\RenderManager\renderManager.h"

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

