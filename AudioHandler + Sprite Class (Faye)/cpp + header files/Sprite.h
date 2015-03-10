#ifndef SPRITE_H
#define SPRITE_H

#include "SDL.h"
#include "AudioHandler.h"
#include <vector>
#include <map>

class Sprite
{
public:
	Sprite(int width, int height, SDL_Renderer* ren, AudioHandler* ah);
	~Sprite(void);

	void setPos(int x, int y);
	void movex(int delta);
	void movey(int delta);
	int getX();
	int getY();
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
	void show(int graIndex);
	// show(string) cycles through all frames in the specified sequence, one per call
	void show(std::string seqName);

private:
	AudioHandler *audiohandler;
	bool mute = false;
	int width, height;
	int currX, currY;		// the coordinates of the sprite's upper left hand corner relative to the window
	SDL_Renderer* renderer;

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

#endif //SPRITE_H