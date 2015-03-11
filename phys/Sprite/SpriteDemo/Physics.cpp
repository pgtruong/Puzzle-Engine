#include <Physics.h>

Physics::Physics()
{
}

Physics::~Physics()
{
}

Physics::Edges Physics::boundarycheck(Sprite* s, int topleftx, int toplefty, int width, int height) //returns an int if a moving sprite (typically player) from moves outside a rectangular space restriction
{//use enums
	//if two walls/ "corner"
	if ((s->getX() == topleftx) && (s->getY() == toplefty)) //if sprite encountered the top left corner
		return TOPLEFT; //top left corner
	else if (((s->getX() + s->getWidth()) == (topleftx + width)) && (s->getY() == toplefty)) //if sprite encountered the top right corner
		return TOPRIGHT; //top right corner
	else if (((s->getY() + s->getHeight()) == (toplefty + height)) && (s->getX() == topleftx)) //if sprite encountered the bottom left corner
		return BOTTOMLEFT; // bottom left
	else if (((s->getY() + s->getHeight()) == (toplefty + height)) && (s->getX() + s->getWidth()) == (topleftx + width)) //if sprite encountered the bottom right
		return BOTTOMRIGHT; // bottom right

	//if only one case/"wall"
	else if (s->getX() <= topleftx) //if sprite encountered the "wall" on the left
		return LEFT; //the sprite encountered the "wall" on the left
	else if ((s->getX() + s->getWidth()) >= (topleftx + width)) //if sprite encountered the "wall" on the right, added "getWidth()" to sprite class
		return RIGHT; //the sprite encountered the "wall" on the right
	else if (s->getY() <= toplefty) //if sprite encountered the "wall" on the top
		return TOP; //the sprite encountered the "wall" on the top
	else if ((s->getY() + s->getHeight()) >= (toplefty + height)) //if sprite encountered the "wall" on the bottom, added "getHeight()" to sprite class
		return BOTTOM; //the sprite encountered the "wall" on the bottom
	else
		return NONE; //no collision
}
/*
Physics::Edges Physics::collisiondetection(Sprite* a, Sprite* b) //if two sprites collide (if they weren't in contact before hand), returns an int
{//keep a vector of all the sprite objects being used in the game and call each one for sprite b to check for sprite a (typically player)
	//broken, don't use. Use the boundary instead although it will be annoying.
	if (a->getID() != b->getID()) //don't want to test with itself
	{
		if (a->getX() <= (b->getX() + b->getWidth())) //A's left side touching b's right
			return LEFT;
		else if ((a->getX() + a->getWidth()) >= b->getX()) //A's right side touching b's left
			return RIGHT;
		else if (a->getY() <= (b->getY() + b->getHeight())) //A's top side touching b's bottom
			return TOP;
		else if ((a->getY() + a->getHeight()) >= b->getY()) //A's bottom side touching b's top
			return BOTTOM;
	}
	else
		return NONE;
}
*/
bool Physics::clickcheck(int xclick, int yclick, Sprite* a) //pass through vector of sprites (vector should not have bg and should have the blank space), returns true if click is within sprite's area
{
	if ((a->getX() <= xclick) && (xclick <= (a->getX() + a->getWidth())))
		if ((a->getY() <= yclick) && (yclick <= (a->getY() + a->getHeight())))
			return true;
		else
			return false;
}

void Physics::swappinganimation(Sprite* a, Sprite* blank, int movingrate) //assuming sprite a is the sprite that passed the clickcheck, swaps it with the blank sprite if it's next to it, rate should be divisible by height/width
{
	int movingtimew = (a->getWidth() + 1) / movingrate; //assumes that this is a not a float/double
	int movingtimeh = (a->getHeight() + 1) / movingrate;

	if ((a->getX() + a->getWidth() + 1) == blank->getX()) //a is on the left blank
	{
		for (int i = 0; i != movingtimew; i++)
		{
			a->movex(movingtimew);
			blank->movex(-(movingtimew));
		}
	}
	else if (a->getX() == (blank->getX() + blank->getWidth() + 1)) //a is on the right of blank
	{
		for (int i = 0; i != movingtimew; i++)
		{
			a->movex(-(movingtimew));
			blank->movex(movingtimew);
		}
	}
	else if ((a->getY() + a->getHeight() + 1) == blank->getY()) //a is above blank
	{
		for (int i = 0; i != movingtimeh; i++)
		{
			a->movey(-(movingtimeh));
			blank->movey(movingtimeh);
		}
	}
	else if (a->getY() == (blank->getY() + blank->getHeight() + 1)) //a is below blank
	{
		for (int i = 0; i != movingtimeh; i++)
		{
			a->movey(movingtimeh);
			blank->movey(-(movingtimeh));
		}
	}
}

void Physics::byeobject() //hopefully calls desconstructor and deletes object
{
	delete this;
}