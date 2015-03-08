#include <iostream>
#include <sstream>
#include <Windows.h>
#include <SDL.h>
#include "res_path.h"
#include "cleanup.h"
#include "SDL_image.h"
#include "Sprite.h"
#include <SDL_mixer.h>
#include "AudioHandler.h"

//============================
// Extracted from Homework 6
//============================

const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

void logSDLError(std::ostream &os, const std::string &msg)
{
	os << msg << " error: " << SDL_GetError() << std::endl;
	std::ostringstream errMsg;
	errMsg << " error: " << SDL_GetError() << std::endl;
	OutputDebugString(errMsg.str().c_str());
}

SDL_Texture* loadTexture(const std::string &file, SDL_Renderer *ren){
	SDL_Texture *texture = IMG_LoadTexture(ren, file.c_str());
	if (texture == nullptr){
		logSDLError(std::cout, "LoadTexture");
	}
	return texture;
}

int main(int argc, char **argv)
{
	const std::string resPath = getResourcePath("Final_Project");

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

	// background is from "http://www.snesmaps.com/maps/SuperMarioWorld/SuperMarioWorldMap10BG.html"
	SDL_Texture *background = loadTexture(resPath + "Background.png", renderer);
	//Make sure all is well
	if (background == nullptr){
		cleanup(background, renderer, window);
		IMG_Quit();
		SDL_Quit();
		return 1;
	}

	SDL_Texture *spritesheet = loadTexture(resPath + "boo.png", renderer);
	// spritesheet is from "http://www.spriters-resource.com/custom_edited/mario/sheet/17842/"
	if (spritesheet == nullptr){
		cleanup(spritesheet, renderer, window);
		IMG_Quit();
		SDL_Quit();
		return 1;
	}

	AudioHandler audiohandler = AudioHandler();
	audiohandler.setMusic((resPath + "m_house.mp3"), true);
	audiohandler.play(0, 0);

	//Check if SDL_mixer is initialized
	if (!audiohandler.initialized())
	{
		logSDLError(std::cout, "Mix_OpenAudio");
		SDL_Quit();
		return 1;
	}

	Sprite* spriteBG = new Sprite(SCREEN_WIDTH, SCREEN_HEIGHT, renderer, &audiohandler);
	spriteBG->setPos(0, 0);
	int bgFrame = spriteBG->createGraFrame(background, 0, 0);

	//Return SFX index
	int booSoundIndex = audiohandler.addSFX(-1, (resPath + "c_boo.wav"));
	int notUsed = audiohandler.addSFX(-1, (resPath + "c_high.wav"));

	if (((audiohandler.checkAudio(booSoundIndex)) && (!audiohandler.checkAudio(0))))
	{
		cleanup(spritesheet, renderer, window);
		IMG_Quit();
		SDL_Quit();
		return 1;
	}

	// Creating Boo sprite
	Sprite* boo = new Sprite(28, 26, renderer, &audiohandler);

	// Just some vectors to simplify initialization of frames and sequences
	std::vector<int> x_coords = std::vector<int>{1, 31, 61, 31};
	std::vector<std::string> directions = std::vector<std::string>{"down", "left", "up", "right"};
	std::vector<int> y_coords = std::vector<int>{1, 29, 57, 85};
	std::vector<int> audios = std::vector<int>{-1, booSoundIndex, -1, -1};
	std::vector<int> intervals = std::vector<int>{50, 20, 17, 20};
	std::map<std::string, std::vector<int>> graFrameMap;

	// createGraFrames()
	for (int y = 0; y < y_coords.size(); y++)
	{
		for (int x = 0; x < x_coords.size(); x++)
		{
			int graIndex = boo->createGraFrame(spritesheet, x_coords[x], y_coords[y]);
			graFrameMap[directions[y]].push_back(graIndex);
		}
	}
	// createSeqFrames
	for (int d = 0; d < directions.size(); d++)
	{
		for (int i = 0; i < intervals.size(); i++)
		{
			int frameIndex = boo->createSeqFrame(graFrameMap[directions[d]][i], audios[i], intervals[i]);
			boo->addFrameToSequence(directions[d], frameIndex);
		}
	}

	boo->setPos(114, 26);

	SDL_Event e;
	bool quit = false;
	std::string spriteDirection = "down";
	while (!quit)
	{
		while (SDL_PollEvent(&e))
		{
			if (e.type == SDL_QUIT)
			{
				quit = true;
			}
			if (e.type == SDL_KEYDOWN)
			{
				switch (e.key.keysym.sym)
				{
				case SDLK_1:
					audiohandler.setMusic((resPath + "m_chase.mp3"), true);
					audiohandler.play(0, 0);
					break;

				case SDLK_2:
					audiohandler.setMusic((resPath + "m_merry.mp3"), true);
					audiohandler.play(0, 0);
					break;

				case SDLK_3:
					audiohandler.setMusic((resPath + "m_fat.mp3"), true);
					audiohandler.play(0, 0);
					break;

				case SDLK_4:
					audiohandler.setMusic((resPath + "m_house.mp3"), true);
					audiohandler.play(0, 0);
					break;

				case SDLK_5:
					audiohandler.setMusic((resPath + "m_beat.wav"), true);
					audiohandler.play(0, 0);
					break;

				case SDLK_m:
					audiohandler.setMuting(!audiohandler.muted());
					break;

				case SDLK_b:
					boo->setMuting(!boo->muted());
					break;

				case SDLK_p:
					if (!audiohandler.playing())
					{
						audiohandler.play(0, 0);
					}
					break;

				case SDLK_s:
					audiohandler.stop();
					break;

				case SDLK_r:
					audiohandler.switch_pause_resume();
					break;

				case SDLK_RIGHT:
					boo->movex(5);
					spriteDirection = "right";
					break;

				case SDLK_LEFT:
					boo->movex(-5);
					spriteDirection = "left";
					break;

				case SDLK_UP:
					boo->movey(-5);
					spriteDirection = "up";
					break;

				case SDLK_DOWN:
					boo->movey(5);
					spriteDirection = "down";
					break;
				}
			}
		}
		//Render the scene
		SDL_RenderClear(renderer);
		spriteBG->show(bgFrame);
		boo->show(spriteDirection.c_str());
		SDL_RenderPresent(renderer);
	}

	cleanup(background, spritesheet, renderer, window);
	IMG_Quit();
	SDL_Quit();


	delete boo;
	delete spriteBG;

	//getchar();
	return 0;
}