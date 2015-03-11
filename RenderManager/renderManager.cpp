#include "renderManager.h"

RenderManager::RenderManager(std::string name, int x, int y, int w, int h)
{
	window = SDL_CreateWindow(name.c_str(), x, y, w, h, SDL_WINDOW_SHOWN);
	ren = SDL_CreateRenderer(window, -1,
		SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
}

RenderManager::~RenderManager()
{
	std::for_each(RenderList.begin(), RenderList.end(), [](std::pair<const int, Bucket*> bucketPair){delete[] bucketPair.second;});

	SDL_DestroyRenderer(ren);
	SDL_DestroyWindow(window);
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

void RenderManager::update()
{
	std::for_each(RenderList.begin(), RenderList.end(), [&](const std::pair<const int, Bucket*>& renPair){
		const Bucket* bucket = renPair.second;
		std::for_each(bucket->begin(), bucket->end(), [&](renderObject* robj){
			robj->render(ren);
		});
	});
}