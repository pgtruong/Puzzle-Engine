#include <SDL.h>

//To comply with the renderManager you must:
// 1) Make everything that requires to be rendered inherit renderObject 
// 2) overwrite render( ) in the way your code will render the object (given a renderer)
// 3) overwrite getLayer( ) to return an int that corresponds to the object's z-layer
// 4)call renderManager.subscribe() in the renderObject's constructor
// 5)call renderManager.unsubscribe() in the renderObject's destructor
// Optional:
// * Copy constructor does its own instance of subscription
// * call renderManager.move() when changing a renderObject's layer

//Issues:
//How does the renderObject know the single instance of renderManager? global variable? namespace? some other method?

class renderObject
{
public:
	virtual ~renderObject() = 0; // Wanted to make = default, but my VS doesn't support?
	virtual void render(SDL_Renderer* ren) = 0;

	virtual int getLayer() = 0;
};