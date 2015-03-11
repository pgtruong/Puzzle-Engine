//
#include<Sprite.h>

class Physics
{
public:
	Physics();
	~Physics();

	enum Edges{TOPLEFT, TOPRIGHT, BOTTOMLEFT, BOTTOMRIGHT, LEFT, RIGHT, TOP, BOTTOM, NONE};

	Edges boundarycheck(Sprite* s, int topleftx, int toplefty, int width, int height); //restrict a sprite to a rectangular movement space, doesn't handle movement
	Edges collisiondetection(Sprite* a, Sprite* b); //checks if Sprite A is in contact with Sprite B, doesn't do anything aside from notifying the collision and at what side
	bool clickcheck(int xclick, int yclick, Sprite* a); //checks if a sprite is where the mouse clicked
	void swappinganimation(Sprite* a, Sprite* blank, int movingrate); //swaps the blank sprite with the sprite next to it
	
	void byeobject(); //calls desconstructor... I think.
};