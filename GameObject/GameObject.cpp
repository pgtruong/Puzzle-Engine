#include <string>
#include <iostream>
#include <SDL.h>
#include <SDL_ttf.h>
#include "SuperAmazingEngine\EventHandler\EventHandler.h"


class GameObject
{
public:

	GameObject(EventHandler eventHandle, PhysicsComponent* physics, GraphicsComponent* graphics) : input_(input), physics_(physics),graphics_(graphics)
	{

	}

	void update(puzzleboard& board, renderer& render)
	{
		input_->update(*this);
		physics_->update(*this, board);
		graphics_->update(*this, render);
	}

private:
	EventHandler eventHandle;
	PhysicsComponent* physics_;
	GraphicsComponent* graphics_;
};

