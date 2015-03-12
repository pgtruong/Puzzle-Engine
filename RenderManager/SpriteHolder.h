#pragma once
#include "renderObject.h"
#include "DumbSprite.h"

#include "renderManager.h"

class SpriteHolder : renderObject
{
public:
	SpriteHolder(Sprite* sprit, int layer = 2);
	~SpriteHolder();

	void setIndex(int index);
	void setSequence(std::string sequence);

	virtual void render(SDL_Renderer* ren)
	{
		if (useInt)
		{
			sprite->show(seqInt, ren);
		}
		else
		{
			sprite->show(seqName, ren);
		}
	}

	virtual int getLayer()
	{
		return zLayer;
	}
private:
	DumbSprite* sprite;
	int zLayer;

	bool useInt; 

	std::string seqName;
	int seqInt;

};