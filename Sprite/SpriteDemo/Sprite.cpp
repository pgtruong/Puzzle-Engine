#include <iostream>
#include <sstream>
#include <Windows.h>
#include <SDL.h>
#include "SDL_image.h"
#include "Sprite.h"

Sprite::Sprite(int width, int height, SDL_Renderer* ren)
{
	this->width = width;
	this->height = height;
	this->renderer = ren;
	this->sequenceIndex = 0;
}

Sprite::~Sprite(void)
{
}

void Sprite::setPos(int x, int y)
{
	this->currX = x;
	this->currY = y;
}
void Sprite::setID(std::string id)
{
	this->ID = id;
}

void Sprite::movex(int delta)
{
	this->currX+= delta;
}

void Sprite::movey(int delta)
{
	this->currY+= delta;
}

int Sprite::getX()
{
	return currX;
}

int Sprite::getY()
{
	return currY;
}

int Sprite::getWidth()
{
	return width;
}

int Sprite::getHeight()
{
	return height;
}

std::string Sprite::getID()
{
	return ID;
}

int Sprite::makeFrame(SDL_Texture* texture, int x, int y)
{
	frame f;
	f.texture = texture;
	f.x = x;
	f.y = y;
	frames.push_back(f);
	return frames.size()-1;
}

int Sprite::addFrameToSequence(std::string seqName, int frameIndex)
{
	sequenceList[seqName].push_back(frameIndex);
	return sequenceList.size() - 1;
}

void Sprite::show(int frameIndex)
{
	frame f = frames[frameIndex];
	SDL_Rect source, dest;

	source.x = f.x;
	source.y = f.y;
	source.w = width;
	source.h = height;

	dest.x = currX;
	dest.y = currY;
	dest.w = width;
	dest.h = height;

	SDL_RenderCopy(renderer,f.texture, &source, &dest);
}

void Sprite::show(std::string sequence)
{
	if (sequenceIndex >= sequenceList[sequence].size())
	{
		sequenceIndex = 0;
	}
	else
	{
		if (sequenceList[sequence].size() == 1)
		{
			show(sequenceList.at(sequence)[0]);
		}
		else
		{
			show(sequenceList.at(sequence)[sequenceIndex]);
			sequenceIndex++;
		}
	}
}
