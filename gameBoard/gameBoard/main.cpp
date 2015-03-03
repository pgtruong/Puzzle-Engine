#include <iostream>
#include <sstream>
#include <Windows.h>
#include <SDL.h>
#include "SDL_image.h"
#include "res_path.h"
#include "cleanup.h"
#include "gameBoard.h"

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

	//SDL init everything
	if (SDL_Init(SDL_INIT_EVERYTHING) != 0){
		std::ostringstream debugMsg;
		debugMsg << "SDL_Init Error: " << SDL_GetError() << std::endl;
		OutputDebugString(debugMsg.str().c_str());
		std::cout << "SDL_Init Error: " << SDL_GetError() << std::endl;
		return 1;
	}

	//Initiates PNG images
	if ((IMG_Init(IMG_INIT_PNG) & IMG_INIT_PNG) != IMG_INIT_PNG){
		logSDLError(std::cout, "IMG_Init");
		SDL_Quit();
		return 1;
	}

	//Creates window
	SDL_Window *window = SDL_CreateWindow("Game Board Demo", 800, 100, SCREEN_WIDTH,
		SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
	if (window == nullptr){
		logSDLError(std::cout, "CreateWindow");
		SDL_Quit();
		return 1	;
	}

	//Creates renderer
	SDL_Renderer *renderer = SDL_CreateRenderer(window, -1,
		SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	if (renderer == nullptr){
		logSDLError(std::cout, "CreateRenderer");
		cleanup(window);
		SDL_Quit();
		return 1;
	}

	//Check for the puzzle image and loads it into a texture
	const std::string resPath = getResourcePath("gameBoard");
	SDL_Texture *puzzle = loadTexture(resPath + "puzzle1.png", renderer);
	if (puzzle == nullptr){
		cleanup(puzzle, renderer, window);
		IMG_Quit();
		SDL_Quit();
		return 1;
	}
	int w, h;
	SDL_QueryTexture(puzzle, NULL, NULL, &w, &h);
	gameBoard* gamePuzzle = new gameBoard(10, 10, w, h, renderer);
	gamePuzzle->setPuzzle(puzzle);
	gamePuzzle->createPieces();

	//Game Loop Begins Here
	SDL_Event e;
	bool quit = false;
	while (!quit){
		while (SDL_PollEvent(&e)){
			if (e.type == SDL_QUIT){
				quit = true;
			}
		}
		//Render the scene
		SDL_RenderClear(renderer);
		gamePuzzle->show();
		SDL_RenderPresent(renderer);
	}

		cleanup(puzzle, renderer, window);

		IMG_Quit();
		SDL_Quit();

		return 0;
}