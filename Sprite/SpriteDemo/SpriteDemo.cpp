#include <iostream>
#include <sstream>
#include <Windows.h>
#include <SDL.h>
#include "res_path.h"
#include "cleanup.h"
#include "SDL_image.h"
#include "Physics.h"

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

	std::vector<Sprite*> spritecollection; //holds references to all sprites except bg

	const std::string resPath = getResourcePath("SpriteDemo");
	// background is from "iceland1.jpg" at theadventurousmailbox.com
	SDL_Texture *background = loadTexture(resPath + "tempboardbg.png", renderer); //changed background texture
	//Make sure all is well
	if (background == nullptr){
		cleanup(background, renderer, window);
		IMG_Quit();
		SDL_Quit();
		return 1;
	}

	Sprite* spriteBG = new Sprite(SCREEN_WIDTH, SCREEN_HEIGHT, renderer);
	spriteBG->setPos(0, 0);
	spriteBG->setID("BACKGROUND");
	int bgFrame = spriteBG->makeFrame(background, 0, 0);

	SDL_Texture *spritesheet = loadTexture(resPath + "myspritesheet.png", renderer);
	// replaced spritesheet is from my scrapped sprites folder
	if (spritesheet == nullptr){
		cleanup(spritesheet, renderer, window);
		IMG_Quit();
		SDL_Quit();
		return 1;
	}
	Sprite* sprite = new Sprite(25, 25, renderer);

	sprite->setID("PLAYER");
	sprite->addFrameToSequence("walk right", sprite->makeFrame(spritesheet, 0, 50));
	sprite->addFrameToSequence("walk right", sprite->makeFrame(spritesheet, 25, 50));
	sprite->addFrameToSequence("walk right", sprite->makeFrame(spritesheet, 50, 50));
	sprite->addFrameToSequence("walk right", sprite->makeFrame(spritesheet, 75, 50));
	sprite->addFrameToSequence("walk right", sprite->makeFrame(spritesheet, 100, 50));
	sprite->addFrameToSequence("walk right", sprite->makeFrame(spritesheet, 125, 50));
	sprite->addFrameToSequence("walk right", sprite->makeFrame(spritesheet, 150, 50));
	sprite->addFrameToSequence("walk right", sprite->makeFrame(spritesheet, 175, 50));

	sprite->addFrameToSequence("walk left", sprite->makeFrame(spritesheet, 0, 25));
	sprite->addFrameToSequence("walk left", sprite->makeFrame(spritesheet, 25, 25));
	sprite->addFrameToSequence("walk left", sprite->makeFrame(spritesheet, 50, 25));
	sprite->addFrameToSequence("walk left", sprite->makeFrame(spritesheet, 75, 25));
	sprite->addFrameToSequence("walk left", sprite->makeFrame(spritesheet, 100, 25));
	sprite->addFrameToSequence("walk left", sprite->makeFrame(spritesheet, 125, 25));
	sprite->addFrameToSequence("walk left", sprite->makeFrame(spritesheet, 150, 25));
	sprite->addFrameToSequence("walk left", sprite->makeFrame(spritesheet, 175, 25));

	sprite->addFrameToSequence("float up", sprite->makeFrame(spritesheet, 0, 0));
	sprite->addFrameToSequence("float up", sprite->makeFrame(spritesheet, 25, 0));
	sprite->addFrameToSequence("float up", sprite->makeFrame(spritesheet, 50, 0));
	sprite->addFrameToSequence("float up", sprite->makeFrame(spritesheet, 75, 0));
	sprite->addFrameToSequence("float down", sprite->makeFrame(spritesheet, 100, 0));
	sprite->addFrameToSequence("float down", sprite->makeFrame(spritesheet, 125, 0));
	sprite->addFrameToSequence("float down", sprite->makeFrame(spritesheet, 150, 0));
	sprite->addFrameToSequence("float down", sprite->makeFrame(spritesheet, 175, 0));

	spritecollection.push_back(sprite);

	
	SDL_Texture *shrub = loadTexture(resPath + "shrub.png", renderer);
	if (shrub == nullptr){
		cleanup(shrub, renderer, window);
		IMG_Quit();
		SDL_Quit();
		return 1;
	}

	Sprite* obstacle1 = new Sprite(50, 50, renderer); //random objects
	obstacle1->setID("SHRUB");
	obstacle1->setPos(200, 200);
	int obstacleframe = obstacle1->makeFrame(shrub, 0, 0);
	spritecollection.push_back(obstacle1);

	int x = SCREEN_WIDTH / 2;
	int y = SCREEN_HEIGHT / 2;
	sprite->setPos(x, y);

	Physics* physic = new Physics();

	SDL_Event e;
	bool quit = false;
	std::string spriteDirection = "float up";
	while (!quit){
		while (SDL_PollEvent(&e)){
			if (e.type == SDL_QUIT){
				quit = true;
			}
			std::vector<Sprite*>::iterator it; //collding not working
			if (physic->boundarycheck(sprite, 100, 100, 440, 280) == 0) //sprite is inside boundary, not touching the "walls/corners"
			{
				for (it = spritecollection.begin(); it != spritecollection.end(); ++it) //going through each sprite to test for collision
				{
					if (physic->collisiondetection(sprite, *it) == 11) //it is touching sprite's left
					{
						if (e.type == SDL_KEYDOWN){
							if (e.key.keysym.sym == SDLK_RIGHT)
							{
								sprite->movex(5);
								spriteDirection = "walk right";
							}
							else if (e.key.keysym.sym == SDLK_UP)
							{
								sprite->movey(-5);
								spriteDirection = "float up";
							}
							else if (e.key.keysym.sym == SDLK_DOWN)
							{
								sprite->movey(5);
								spriteDirection = "float down";
							}
						}
					}
					else if (physic->collisiondetection(sprite, *it) == 22) //object is touching sprite's right
					{
						if (e.type == SDL_KEYDOWN){
							if (e.key.keysym.sym == SDLK_LEFT)
							{
								sprite->movex(-5);
								spriteDirection = "walk left";
							}
							else if (e.key.keysym.sym == SDLK_UP)
							{
								sprite->movey(-5);
								spriteDirection = "float up";
							}
							else if (e.key.keysym.sym == SDLK_DOWN)
							{
								sprite->movey(5);
								spriteDirection = "float down";
							}
						}
					}
					else if (physic->collisiondetection(sprite, *it) == 33) //object is touching sprite's top
					{
						if (e.type == SDL_KEYDOWN){
							if (e.key.keysym.sym == SDLK_RIGHT)
							{
								sprite->movex(5);
								spriteDirection = "walk right";
							}
							else if (e.key.keysym.sym == SDLK_LEFT)
							{
								sprite->movex(-5);
								spriteDirection = "walk left";
							}
							else if (e.key.keysym.sym == SDLK_DOWN)
							{
								sprite->movey(5);
								spriteDirection = "float down";
							}
						}
					}
					else if (physic->collisiondetection(sprite, *it) == 44) //object is touching sprite's bottom
					{
						if (e.type == SDL_KEYDOWN){
							if (e.key.keysym.sym == SDLK_RIGHT)
							{
								sprite->movex(5);
								spriteDirection = "walk right";
							}
							else if (e.key.keysym.sym == SDLK_LEFT)
							{
								sprite->movex(-5);
								spriteDirection = "walk left";
							}
							else if (e.key.keysym.sym == SDLK_UP)
							{
								sprite->movey(-5);
								spriteDirection = "float up";
							}
						}
					}
					else
					{
						if (e.type == SDL_KEYDOWN){
							if (e.key.keysym.sym == SDLK_RIGHT)
							{
								sprite->movex(5);
								spriteDirection = "walk right";
							}
							else if (e.key.keysym.sym == SDLK_LEFT)
							{
								sprite->movex(-5);
								spriteDirection = "walk left";
							}
							else if (e.key.keysym.sym == SDLK_UP)
							{
								sprite->movey(-5);
								spriteDirection = "float up";
							}
							else if (e.key.keysym.sym == SDLK_DOWN)
							{
								sprite->movey(5);
								spriteDirection = "float down";
							}
						}
					}
				}
			}
			else if (physic->boundarycheck(sprite, 100, 100, 440, 280) == 1)
			{
				if (e.type == SDL_KEYDOWN){
					if (e.key.keysym.sym == SDLK_RIGHT)
					{
						sprite->movex(5);
						spriteDirection = "walk right";
					}
					else if (e.key.keysym.sym == SDLK_DOWN)
					{
						sprite->movey(5);
						spriteDirection = "float down";
					}
				}
			}
			else if (physic->boundarycheck(sprite, 100, 100, 440, 280) == 2)
			{
				if (e.type == SDL_KEYDOWN){
					if (e.key.keysym.sym == SDLK_LEFT)
					{
						sprite->movex(-5);
						spriteDirection = "walk left";
					}
					else if (e.key.keysym.sym == SDLK_DOWN)
					{
						sprite->movey(5);
						spriteDirection = "float down";
					}
				}
			}
			else if (physic->boundarycheck(sprite, 100, 100, 440, 280) == 3)
			{
				if (e.type == SDL_KEYDOWN){
					if (e.key.keysym.sym == SDLK_RIGHT)
					{
						sprite->movex(5);
						spriteDirection = "walk right";
					}
					else if (e.key.keysym.sym == SDLK_UP)
					{
						sprite->movey(-5);
						spriteDirection = "float up";
					}
				}
			}
			else if (physic->boundarycheck(sprite, 100, 100, 440, 280) == 4)
			{
				if (e.type == SDL_KEYDOWN){
					if (e.key.keysym.sym == SDLK_LEFT)
					{
						sprite->movex(-5);
						spriteDirection = "walk left";
					}
					else if (e.key.keysym.sym == SDLK_UP)
					{
						sprite->movey(-5);
						spriteDirection = "float up";
					}
				}
			}
			else if (physic->boundarycheck(sprite, 100, 100, 440, 280) == 5)
			{
				if (e.type == SDL_KEYDOWN){
					if (e.key.keysym.sym == SDLK_RIGHT)
					{
						sprite->movex(5);
						spriteDirection = "walk right";
					}
					else if (e.key.keysym.sym == SDLK_UP)
					{
						sprite->movey(-5);
						spriteDirection = "float up";
					}
					else if (e.key.keysym.sym == SDLK_DOWN)
					{
						sprite->movey(5);
						spriteDirection = "float down";
					}
				}
			}
			else if (physic->boundarycheck(sprite, 100, 100, 440, 280) == 6)
			{
				if (e.type == SDL_KEYDOWN){
					if (e.key.keysym.sym == SDLK_LEFT)
					{
						sprite->movex(-5);
						spriteDirection = "walk left";
					}
					else if (e.key.keysym.sym == SDLK_UP)
					{
						sprite->movey(-5);
						spriteDirection = "float up";
					}
					else if (e.key.keysym.sym == SDLK_DOWN)
					{
						sprite->movey(5);
						spriteDirection = "float down";
					}
				}
			}
			else if (physic->boundarycheck(sprite, 100, 100, 440, 280) == 7)
			{
				if (e.type == SDL_KEYDOWN){
					if (e.key.keysym.sym == SDLK_RIGHT)
					{
						sprite->movex(5);
						spriteDirection = "walk right";
					}
					else if (e.key.keysym.sym == SDLK_LEFT)
					{
						sprite->movex(-5);
						spriteDirection = "walk left";
					}
					else if (e.key.keysym.sym == SDLK_DOWN)
					{
						sprite->movey(5);
						spriteDirection = "float down";
					}
				}
			}
			else if (physic->boundarycheck(sprite, 100, 100, 440, 280) == 8)
			{
				if (e.type == SDL_KEYDOWN){
					if (e.key.keysym.sym == SDLK_RIGHT)
					{
						sprite->movex(5);
						spriteDirection = "walk right";
					}
					else if (e.key.keysym.sym == SDLK_LEFT)
					{
						sprite->movex(-5);
						spriteDirection = "walk left";
					}
					else if (e.key.keysym.sym == SDLK_UP)
					{
						sprite->movey(-5);
						spriteDirection = "float up";
					}
				}
			}
		}
		//Render the scene
		SDL_RenderClear(renderer);
		spriteBG->show(bgFrame);
		obstacle1->show(obstacleframe);
		sprite->show(spriteDirection.c_str());
		SDL_RenderPresent(renderer);
	}

	cleanup(background, spritesheet, renderer, window);
	IMG_Quit();
	SDL_Quit();

	SDL_Quit();

	return 0;
}
