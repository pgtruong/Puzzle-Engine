#include "GameObject.h"

GameObject::GameObject(EventHandler* eve, Physics* phy, RenderManager* ren)
{
	even = eve;
	phys = phy;
	rend = ren;
}

GameObject:: ~GameObject()  //I don't think this needs to do anything
{
}

void GameObject::update(gameBoard& board) //runs all update functions in one update
{
	eve->update();
	ren->update();
}

EventHandler* even;
Physics* phys;
RenderManager* rend;


