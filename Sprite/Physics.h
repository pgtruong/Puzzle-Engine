//
#include<Sprite.h>

class Physics
{
public:
	Physics();
	~Physics();
	int boundarycheck(Sprite* s, int topleftx, int toplefty, int width, int height); //restrict a sprite to a rectangular movement space, doesn't handle movment
	int collisiondetection(Sprite* a, Sprite* b); //checks if Sprite A is in contact with Sprite B, doesn't do anything aside from notifying the collision and at what side
};