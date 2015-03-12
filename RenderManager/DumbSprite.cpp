#include "DumbSprite.h"

DumbSprite::DumbSprite(int width, int height, AudioHandler* ah)
{
	DumbSprite::audiohandler = ah;
	DumbSprite::width = width;
	DumbSprite::height = height;
}

DumbSprite::~DumbSprite(void)
{

}

void DumbSprite::setPos(int x, int y)
{
	DumbSprite::currX = x;
	DumbSprite::currY = y;
}

// Physics class
void DumbSprite::setID(std::string id)
{
	this->ID = id;
}
int DumbSprite::getWidth()
{
	return width;
}

int DumbSprite::getHeight()
{
	return height;
}

std::string DumbSprite::getID()
{
	return ID;
}
//
void DumbSprite::movex(int delta)
{
	DumbSprite::currX += delta;
}

void DumbSprite::movey(int delta)
{
	DumbSprite::currY += delta;
}

int DumbSprite::getX()
{
	return DumbSprite::currX;
}

int DumbSprite::getY()
{
	return DumbSprite::currY;
}

// Returns whether or not the DumbSprite is muted
bool DumbSprite::muted()
{
	return DumbSprite::mute;
}

// Sets the muting value for the DumbSprite
void DumbSprite::setMuting(bool value)
{
	DumbSprite::mute = value;
}

// returns unique index of the created graphic frame
int DumbSprite::createGraFrame(SDL_Texture* texture, int x, int y)
{
	DumbSprite::graFrameList.push_back(DumbSprite::graFrame{ texture, x, y });
	return DumbSprite::graFrameList.size() - 1;
}

// returns unique index of the created sequence frame
int DumbSprite::createSeqFrame(int graIndex, int audioTrackNo, int maxDur)
{
	DumbSprite::seqFrame newSeqFrame = DumbSprite::seqFrame{};
	newSeqFrame.graIndex = graIndex;
	newSeqFrame.audioTrackNo = audioTrackNo;
	newSeqFrame.maxDur = maxDur;
	newSeqFrame.currDur = maxDur;
	DumbSprite::seqFrameList.push_back(newSeqFrame);
	return DumbSprite::seqFrameList.size() - 1;
}

// adds a sequence frame to the sequence, specified by the seqName
void DumbSprite::addFrameToSequence(std::string seqName, int frameIndex)
{
	DumbSprite::sequenceList[seqName].frameList.push_back(frameIndex);
}

// show(int) renders the frame with the specified frameIndex
void DumbSprite::show(int graIndex, SDL_Renderer* ren)
{
	SDL_Rect clip;
	clip.x = DumbSprite::graFrameList[graIndex].x;
	clip.y = DumbSprite::graFrameList[graIndex].y;
	clip.w = DumbSprite::width;
	clip.h = DumbSprite::height;

	SDL_Rect dst;
	dst.x = DumbSprite::currX;
	dst.y = DumbSprite::currY;
	dst.w = DumbSprite::width;
	dst.h = DumbSprite::height;
	SDL_RenderCopy(ren, DumbSprite::graFrameList[graIndex].texture, &clip, &dst);
}

// show(string) cycles through all frames in the specified sequence, one per call
void DumbSprite::show(std::string seqName, SDL_Renderer* ren)
{
	DumbSprite::sequence *thisSequence = &DumbSprite::sequenceList[seqName];
	if (thisSequence->currentFrame >= thisSequence->frameList.size())
	{
		thisSequence->currentFrame = 0;
	}
	int thisSeqFrameIndex = DumbSprite::sequenceList[seqName].frameList[thisSequence->currentFrame];
	DumbSprite::seqFrame *thisSeqFrame = &DumbSprite::seqFrameList[thisSeqFrameIndex];
	if (thisSeqFrame->currDur == 0)
	{
		thisSeqFrame->currDur = thisSeqFrame->maxDur + 1;
		thisSequence->currentFrame++;
	}
	if (thisSeqFrame->currDur == thisSeqFrame->maxDur)
	{
		if ((thisSeqFrame->audioTrackNo != -1) && (!DumbSprite::muted()))
		{
			audiohandler->play(thisSeqFrame->audioTrackNo, 1);
		}
	}
	DumbSprite::show(thisSeqFrame->graIndex, ren);
	thisSeqFrame->currDur--;
	//DumbSprite::seqFrameList[thisSeqFrameIndex] = thisSeqFrame;
	//DumbSprite::sequenceList[seqName] = thisSequence;
}
