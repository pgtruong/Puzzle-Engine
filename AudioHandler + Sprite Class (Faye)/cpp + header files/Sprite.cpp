#include "Sprite.h"

Sprite::Sprite(int width, int height, SDL_Renderer* ren, AudioHandler* ah)
{
	Sprite::audiohandler = ah;
	Sprite::renderer = ren;
	Sprite::width = width;
	Sprite::height = height;
}

Sprite::~Sprite(void)
{

}

void Sprite::setPos(int x, int y)
{
	Sprite::currX = x;
	Sprite::currY = y;
}

void Sprite::movex(int delta)
{
	Sprite::currX += delta;
}

void Sprite::movey(int delta)
{
	Sprite::currY += delta;
}

int Sprite::getX()
{
	return Sprite::currX;
}

int Sprite::getY()
{
	return Sprite::currY;
}

// Returns whether or not the Sprite is muted
bool Sprite::muted()
{
	return Sprite::mute;
}

// Sets the muting value for the Sprite
void Sprite::setMuting(bool value)
{
	Sprite::mute = value;
}

// returns unique index of the created graphic frame
int Sprite::createGraFrame(SDL_Texture* texture, int x, int y)
{
	Sprite::graFrameList.push_back(Sprite::graFrame{ texture, x, y });
	return Sprite::graFrameList.size() - 1;
}

// returns unique index of the created sequence frame
int Sprite::createSeqFrame(int graIndex, int audioTrackNo, int maxDur)
{
	Sprite::seqFrame newSeqFrame = Sprite::seqFrame{};
	newSeqFrame.graIndex = graIndex;
	newSeqFrame.audioTrackNo = audioTrackNo;
	newSeqFrame.maxDur = maxDur;
	newSeqFrame.currDur = maxDur;
	Sprite::seqFrameList.push_back(newSeqFrame);
	return Sprite::seqFrameList.size() - 1;
}

// adds a sequence frame to the sequence, specified by the seqName
void Sprite::addFrameToSequence(std::string seqName, int frameIndex)
{
	Sprite::sequenceList[seqName].frameList.push_back(frameIndex);
}

// show(int) renders the frame with the specified frameIndex
void Sprite::show(int graIndex)
{
	SDL_Rect clip;
	clip.x = Sprite::graFrameList[graIndex].x;
	clip.y = Sprite::graFrameList[graIndex].y;
	clip.w = Sprite::width;
	clip.h = Sprite::height;

	SDL_Rect dst;
	dst.x = Sprite::currX;
	dst.y = Sprite::currY;
	dst.w = Sprite::width;
	dst.h = Sprite::height;
	SDL_RenderCopy(Sprite::renderer, Sprite::graFrameList[graIndex].texture, &clip, &dst);
}

// show(string) cycles through all frames in the specified sequence, one per call
void Sprite::show(std::string seqName)
{
	Sprite::sequence *thisSequence = &Sprite::sequenceList[seqName];
	if (thisSequence->currentFrame >= thisSequence->frameList.size())
	{
		thisSequence->currentFrame = 0;
	}
	int thisSeqFrameIndex = Sprite::sequenceList[seqName].frameList[thisSequence->currentFrame];
	Sprite::seqFrame *thisSeqFrame = &Sprite::seqFrameList[thisSeqFrameIndex];
	if (thisSeqFrame->currDur == 0)
	{
		thisSeqFrame->currDur = thisSeqFrame->maxDur + 1;
		thisSequence->currentFrame++;
	}
	if (thisSeqFrame->currDur == thisSeqFrame->maxDur)
	{
		if ((thisSeqFrame->audioTrackNo != -1) && (!Sprite::muted()))
		{
			audiohandler->play(thisSeqFrame->audioTrackNo, 1);
		}
	}
	Sprite::show(thisSeqFrame->graIndex);
	thisSeqFrame->currDur--;
	//Sprite::seqFrameList[thisSeqFrameIndex] = thisSeqFrame;
	//Sprite::sequenceList[seqName] = thisSequence;
}
