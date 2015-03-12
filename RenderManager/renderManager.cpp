#include "renderManager.h"

RenderManager* RenderManager::thisInstance = nullptr;
RenderManager::RenderManager()
{
}

void RenderManager::Initialize(std::string name, int x, int y, int w, int h)
{
	IMG_Init(IMG_INIT_PNG);

	window = SDL_CreateWindow(name.c_str(), x, y, w, h, SDL_WINDOW_SHOWN);
	ren = SDL_CreateRenderer(window, -1,
		SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
}

RenderManager::~RenderManager()
{
	std::for_each(RenderList.begin(), RenderList.end(), [](std::pair<const int, Bucket*> bucketPair){delete[] bucketPair.second;});

	SDL_DestroyRenderer(ren);
	SDL_DestroyWindow(window);

	delete thisInstance;
}

RenderManager* RenderManager::getInstance()
{
	if (thisInstance == nullptr)
	{
		thisInstance = new RenderManager();
	}
	return thisInstance;
}

void RenderManager::subscribe(renderObject* robj)
{
	int layer = robj->getLayer();
	if(RenderList[layer] == nullptr)
	{
		RenderList[layer] = new Bucket;
	}
	RenderList[layer]->push_back(robj);
}

void RenderManager::unsubscribe(renderObject* robj)
{
	RenderList[robj->getLayer()]->remove(robj);
}

SDL_Texture* RenderManager::loadTexture(const std::string &file){
	SDL_Texture *texture = IMG_LoadTexture(ren, file.c_str());
	//if (texture == nullptr){
	//	logSDLError(std::cout, "LoadTexture");
	//}
	return texture;
}

void RenderManager::update()
{
	SDL_RenderClear(ren);
	std::for_each(RenderList.begin(), RenderList.end(), [&](const std::pair<const int, Bucket*>& renPair){
		const Bucket* bucket = renPair.second;
		std::for_each(bucket->begin(), bucket->end(), [&](renderObject* robj){
			robj->render(ren);
		});
	});
	SDL_RenderPresent(ren);
}