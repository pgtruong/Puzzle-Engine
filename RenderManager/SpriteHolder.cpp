#include "SpriteHolder.h"

SpriteHolder::SpriteHolder(DumbSprite* sprit, int layer)
{
	this->sprite = sprit;
	this->zLayer = layer;

	int seqInt = 0;
	bool useInt = true;

	RenderManager::getInstance()->subscribe(this);
}

SpriteHolder::~SpriteHolder()
{
	RenderManager::getInstance()->unsubscribe(this);
}

void SpriteHolder::setIndex(int index)
{
	useInt = true;
	seqInt = index;
}

void SpriteHolder::setSequence(std::string sequence)
{
	useInt = false;
	seqName = sequence;
}
