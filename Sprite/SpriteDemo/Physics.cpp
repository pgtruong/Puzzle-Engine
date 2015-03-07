#include <Physics.h>

Physics::Physics()
{
}

Physics::~Physics()
{
}

int Physics::boundarycheck(Sprite* s, int topleftx, int toplefty, int width, int height) //returns an int if a moving sprite (typically player) from moves outside a rectangular space restriction
{//use enums
	//if two walls/ "corner"
	if ((s->getX() == topleftx) && (s->getY() == toplefty)) //if sprite encountered the top left corner
		return 1; // 1 means top leftcorner
	else if (((s->getX() + s->getWidth()) == (topleftx + width)) && (s->getY() == toplefty)) //if sprite encountered the top right corner
		return 2; //2 means top right corner
	else if (((s->getY() + s->getHeight()) == (toplefty + height)) && (s->getX() == topleftx)) //if sprite encountered the bottom left corner
		return 3; //3 means bottom left
	else if (((s->getY() + s->getHeight()) == (toplefty + height)) && (s->getX() + s->getWidth()) == (topleftx + width)) //if sprite encountered the bottom right
		return 4; //4 means bottom right

	//if only one case/"wall"
	else if (s->getX() <= topleftx) //if sprite encountered the "wall" on the left
		return 5; // 5 means left, the sprite encountered the "wall" on the left
	else if ((s->getX() + s->getWidth()) >= (topleftx + width)) //if sprite encountered the "wall" on the right, added "getWidth()" to sprite class
		return 6; //6 means right, the sprite encountered the "wall" on the right
	else if (s->getY() <= toplefty) //if sprite encountered the "wall" on the top
		return 7; //7 means top, the sprite encountered the "wall" on the top
	else if ((s->getY() + s->getHeight()) >= (toplefty + height)) //if sprite encountered the "wall" on the bottom, added "getHeight()" to sprite class
		return 8; //8 means bottom, the sprite encountered the "wall" on the bottom
	else
		return 0; //no collision
}

int Physics::collisiondetection(Sprite* a, Sprite* b) //if two sprites collide (if they weren't in contact before hand), returns an int
{//keep a vector of all the sprite objects being used in the game and call each one for sprite b to check for sprite a (typically player)
	//not yet tested
	if (a->getID() != b->getID()) //don't want to test with itself
	{
		if (a->getX() <= (b->getX() + b->getWidth())) //A's left side touching b's right
			return 11;
		else if ((a->getX() + a->getWidth()) >= b->getX()) //A's right side touching b's left
			return 22;
		else if (a->getY() <= (b->getY() + b->getHeight())) //A's top side touching b's bottom
			return 33;
		else if ((a->getY() + a->getHeight()) >= b->getY()) //A's bottom side touching b's top
			return 44;
	}
	else
		return 0;
}