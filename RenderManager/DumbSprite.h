#ifndef DUMBSPRITE_H
#define DUMBSPRITE_H

#include "SDL.h"
#include "../AudioHandler + Sprite Class (Faye)/cpp + header files/AudioHandler.h"
#include "renderObject.h"
#include <vector>
#include <map>

//Sprite class from AudioHandler, but modified to not store the renderer as a class variable
class DumbSprite
{
public:
	DumbSprite(int width, int height, AudioHandler* ah);
	~DumbSprite(void);

	void setPos(int x, int y);
	void movex(int delta);
	void movey(int delta);
	int getX();
	int getY();

	// Physics class
	int getWidth();
	int getHeight();
	std::string getID();
	int boundarycheck(int topleftx, int toplefty, int width, int height);
	void setID(std::string id);
	// END

	// Returns whether or not the Sprite is muted
	bool muted();
	// Sets the muting value for the Sprite
	void setMuting(bool value);

	// returns unique index of the created graphic frame
	int createGraFrame(SDL_Texture* texture, int x, int y);
	// returns unique index of the created sequence frame, -1 if Audio is invalid
	int createSeqFrame(int graIndex, int audioTrackNo, int maxDur = 1);
	// adds a sequence frame to the sequence, specified by the seqName
	void addFrameToSequence(std::string seqName, int frameIndex);

	// show(int) renders the frame with the specified graIndex
	void show(int graIndex, SDL_Renderer* ren);
	// show(string) cycles through all frames in the specified sequence, one per call
	void show(std::string seqName, SDL_Renderer* ren);

private:
	// Physics class
	std::string ID;
	// END
	AudioHandler *audiohandler;
	bool mute = false;
	int width, height;
	int currX, currY;		// the coordinates of the sprite's upper left hand corner relative to the window

	struct graFrame
	{
		SDL_Texture* texture;
		int x;
		int y;
	};
	std::vector<graFrame> graFrameList;

	struct seqFrame
	{
		int graIndex = -1;
		int audioTrackNo = -1;
		int maxDur = 1;
		int currDur = 1;
	};
	std::vector<seqFrame> seqFrameList;

	struct sequence
	{
		int currentFrame = 0;
		std::vector<int> frameList;
	};
	std::map<std::string, Sprite::sequence> sequenceList;

};

#endif //DUMBSPRITE_H