#include "Sprite.h"
#include <iostream>
#include <sstream>
#include <SDL.h>
#include "SDL_image.h"

namespace
{
	void renderTexture(SDL_Texture *tex, SDL_Renderer *ren, SDL_Rect dst,
		SDL_Rect *clip = nullptr)
	{
		SDL_RenderCopy(ren, tex, clip, &dst);
	}

	void renderTexture(SDL_Texture *tex, SDL_Renderer *ren, int x, int y,
		SDL_Rect *clip = nullptr)
	{
		SDL_Rect dst;
		dst.x = x;
		dst.y = y;
		if (clip != nullptr){
			dst.w = clip->w;
			dst.h = clip->h;
		}
		else {
			SDL_QueryTexture(tex, NULL, NULL, &dst.w, &dst.h);
		}
		renderTexture(tex, ren, dst, clip);
	}
}


Sprite::Sprite(int width, int height, SDL_Renderer* ren)
{
	this->width = width;
	this->height = height;
	renderer = ren;
}

Sprite::~Sprite(void)
{
}

void Sprite::setPos(int x, int y)
{
	currX = x;
	currY = y;
}

void Sprite::movex(int delta)
{
	currX += delta;
}

void Sprite::movey(int delta)
{
	currY += delta;
}

int Sprite::getX()
{
	return currX;
}

int Sprite::getY()
{
	return currY;
}

int Sprite::makeFrame(SDL_Texture* texture, int x, int y)
{
	frame temp;
	temp.texture = texture;
	temp.clip.x = x;
	temp.clip.y = y;
	temp.clip.w = width;
	temp.clip.h = height;
	frames.push_back(temp);
	return frames.size() - 1;
}

int Sprite::addFrameToSequence(std::string seqName, int frameIndex)
{
	sequenceList[seqName].push_back(frameIndex);
	sequenceIndexList[seqName] = 0;
	return sequenceList.size();
}

void Sprite::show(int frameIndex)
{
	frame temp = frames[frameIndex];
	renderTexture(temp.texture, renderer, currX, currY, &temp.clip);
}

void Sprite::show(std::string sequence)
{
	show(sequenceList[sequence][sequenceIndexList[sequence]]);
	if (SDL_GetTicks() - time >= 128)
	{
		++sequenceIndexList[sequence];
		if (sequenceIndexList[sequence] >= sequenceList[sequence].size())
			sequenceIndexList[sequence] = 0;
		time = SDL_GetTicks();
	}
}