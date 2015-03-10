#include <iostream>
#include <sstream>
#include <Windows.h>
#include <SDL.h>
#include "res_path.h"
#include "cleanup.h"
#include "SDL_image.h"
#include "Sprite.h"
#include "EventHandler.h"

const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

/**
* Log an SDL error with some error message to the output stream of our choice
* @param os The output stream to write the message to
* @param msg The error message to write, format will be msg error: SDL_GetError()
*/
void logSDLError(std::ostream &os, const std::string &msg){
	os << msg << " error: " << SDL_GetError() << std::endl;
	std::ostringstream errMsg;
	errMsg << " error: " << SDL_GetError() << std::endl;
	OutputDebugString(errMsg.str().c_str());
}

/**
* Loads an image into a texture on the rendering device
* @param file The image file to load
* @param ren The renderer to load the texture onto
* @return the loaded texture, or nullptr if something went wrong.
*/
SDL_Texture* loadTexture(const std::string &file, SDL_Renderer *ren){
	SDL_Texture *texture = IMG_LoadTexture(ren, file.c_str());
	if (texture == nullptr){
		logSDLError(std::cout, "LoadTexture");
	}
	return texture;
}


int main(int argc, char **argv){

	if (SDL_Init(SDL_INIT_EVERYTHING) != 0){
		std::ostringstream debugMsg;
		debugMsg << "SDL_Init Error: " << SDL_GetError() << std::endl;
		OutputDebugString(debugMsg.str().c_str());
		std::cout << "SDL_Init Error: " << SDL_GetError() << std::endl;
		return 1;
	}

	if ((IMG_Init(IMG_INIT_PNG) & IMG_INIT_PNG) != IMG_INIT_PNG){
		logSDLError(std::cout, "IMG_Init");
		SDL_Quit();
		return 1;
	}

	SDL_Window *window = SDL_CreateWindow("Sprite Demo", 800, 100, SCREEN_WIDTH,
		SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
	if (window == nullptr){
		logSDLError(std::cout, "CreateWindow");
		SDL_Quit();
		return 1;
	}
	SDL_Renderer *renderer = SDL_CreateRenderer(window, -1,
		SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	if (renderer == nullptr){
		logSDLError(std::cout, "CreateRenderer");
		cleanup(window);
		SDL_Quit();
		return 1;
	}

	const std::string resPath = getResourcePath("EventHandlerPractice");
	// background is from "iceland1.jpg" at theadventurousmailbox.com
	SDL_Texture *background = loadTexture(resPath + "Background.png", renderer);
	//Make sure all is well
	if (background == nullptr){
		cleanup(background, renderer, window);
		IMG_Quit();
		SDL_Quit();
		return 1;
	}

	Sprite* spriteBG = new Sprite(SCREEN_WIDTH, SCREEN_HEIGHT, renderer);
	spriteBG->setPos(0,0);
	int bgFrame = spriteBG->makeFrame(background, 0, 0);

	SDL_Texture *spritesheet = loadTexture(resPath + "characterSprite.png", renderer);
	// spritesheet is from "charspritezd5.png" at z3.invisionfree.com/Game_Maker_Academy/ar/t89.htm
	if (spritesheet == nullptr){
		cleanup(spritesheet, renderer, window);
		IMG_Quit();
		SDL_Quit();
		return 1;
	}
















	//Some of these variables are static, take note of this, I explain why in a little bit
	static Sprite* sprite1 = new Sprite(20, 20, renderer);
	for (int i = 0; i < 4; ++i)
	{
		sprite1->addFrameToSequence("walk down", sprite1->makeFrame(spritesheet, 20*i, 0));
		sprite1->addFrameToSequence("walk up", sprite1->makeFrame(spritesheet, 20*i, 20));
		sprite1->addFrameToSequence("walk left", sprite1->makeFrame(spritesheet, 20*i, 40));
		sprite1->addFrameToSequence("walk right", sprite1->makeFrame(spritesheet, 20*i, 60));
	}
	sprite1->addFrameToSequence("idle", sprite1->makeFrame(spritesheet, 0, 0));

	static int x = SCREEN_WIDTH / 2 ;
	static int y = SCREEN_HEIGHT / 2;
	sprite1->setPos(x, y);
	static std::string spriteDirection = "idle";



	//Creating the pointers to store the mouse's location
	int tempx = 0;
	int tempy = 0;

	static int* mousex = &tempx;
	static int* mousey = &tempy;



	//Helper Functions
	struct localFunctions{
		static void moveSpritex(int distance, std::string walkDirection){
			sprite1->movex(distance);
			spriteDirection = walkDirection;
		}

		static void moveSpritey(int distance, std::string walkDirection){
			sprite1->movey(distance);
			spriteDirection = walkDirection;
		}
	};

	//The following is how we can have a map that takes void functions with no parameters:
	//We use lambdas
	//(I'll try and explain as best I can in class, if anyone's confused)

	//Make sure that any variables you need to use in these local definitions are "static" (spriteDirection, sprite1)
	//Same with the local functions you define
	


	//The mouse location pointers are passed to the event handler on construction
	EventHandler handler(mousex, mousey);
	handler.addKeyDown(SDLK_RIGHT, [](){ localFunctions::moveSpritex(2, "walk right"); });
	handler.addKeyDown(SDLK_LEFT, [](){ localFunctions::moveSpritex(-2, "walk left"); });
	handler.addKeyDown(SDLK_UP, [](){ localFunctions::moveSpritey(-2, "walk up"); });
	handler.addKeyDown(SDLK_DOWN, [](){ localFunctions::moveSpritey(2, "walk down"); });
	handler.addKeyDown(SDLK_d, [](){ localFunctions::moveSpritex(4, "walk right"); });
	handler.addKeyDown(SDLK_a, [](){ localFunctions::moveSpritex(-4, "walk left"); });
	handler.addKeyDown(SDLK_w, [](){ localFunctions::moveSpritey(-4, "walk up"); });
	handler.addKeyDown(SDLK_s, [](){ localFunctions::moveSpritey(4, "walk down"); });

	//I've noticed that it might actually be slower to use lambdas, there is an alternative method, but it takes twice as many lines and is a little bit more cumbersome

	handler.addKeyUp(SDLK_SPACE, [](){ sprite1->setPos(x, y); });

	handler.addGenericEvent(SDL_KEYUP, [](){ spriteDirection = "idle"; });
	handler.addGenericEvent(SDL_QUIT, [](){std::cout << "AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA" << std::endl; });

	//Mouse Button Testing
	handler.addLeftClick([](){ std::cout << "Single Left Click at; " << *mousex << ", " << *mousey << std::endl; }, false);
	handler.addLeftClick([](){ std::cout << "Double Left Click at; " << *mousex << ", " << *mousey << std::endl; }, true);
	handler.addRightClick([](){ std::cout << "Single Right Click at; " << *mousex << ", " << *mousey << std::endl; }, false);
	handler.addRightClick([](){ std::cout << "Double Right Click at; " << *mousex << ", " << *mousey << std::endl; }, true);
	handler.addMiddleClick([](){ std::cout << "Single Middle Click at; " << *mousex << ", " << *mousey << std::endl; }, false);
	handler.addMiddleClick([](){ std::cout << "Double Middle Click at; " << *mousex << ", " << *mousey << std::endl; }, true);

	while (!handler.update()){
		//Render the scene
		
		SDL_RenderClear(renderer);
		spriteBG->show(bgFrame);
		sprite1->show(spriteDirection.c_str());
		SDL_RenderPresent(renderer);

	}

	cleanup(background, spritesheet, renderer, window);
	IMG_Quit();
	SDL_Quit();

	SDL_Quit();

	return 0;
}
