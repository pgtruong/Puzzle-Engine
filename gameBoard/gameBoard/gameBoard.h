#pragma once

#include "SDL.h"
#include <vector>


class gameBoard
{
public:
	//Initializes the gameboard with the amount of columns and rows wanted.
	//Also includes the images width and height to adjust for tiling.
	//And finally adds the renderer.
	gameBoard(int c, int r, int w, int h, SDL_Renderer* renderer);

	//Destructor
	~gameBoard();

	//Sets the image to be the puzzle within the class
	void setPuzzle(SDL_Texture* p);
	
	//Creates the pieces based on the class variables.
	void createPieces();
	
	//Returns the amount of pieces.
	int getLength();

	//Renders to screen
	void show();

private:
	//Variables of the width and height required for tiling the image.
	const int SCREEN_WIDTH = 640;
	const int SCREEN_HEIGHT = 480;

	//These variables are required in creating the pieces.
	int column, row;
	int width, height;

	//Renderer, length, and main puzzle.
	SDL_Renderer* ren;
	int length;
	SDL_Texture* mainPuzzle;

	//Individual puzzle pieces that has a clip of the main texture and the puzzle piece number it is.
	struct frame{
		int x, y, w, h;
		int pieceNumber;
	};

	//The matrix holding the puzzle pieces.
	std::vector<std::vector<frame>> puzzlePiece;
};