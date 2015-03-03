#include "gameBoard.h"
#include <iostream>

//Sets all the variables.
gameBoard::gameBoard(int c, int r, int w, int h, SDL_Renderer* renderer){
	column = c;
	row = r;
	ren = renderer;
	length = c*r;
	width = w;
	height = h;
}

//Destructor
gameBoard::~gameBoard(){}

//Sets the puzzle texture inside the class as a pointer.
void gameBoard::setPuzzle(SDL_Texture* p){
	mainPuzzle = p;
}

//Creates the pieces. This function saves the clip of the original image and
//indicates which puzzle piece number it is within the struct frame.
void gameBoard::createPieces(){
	int count = 1;
	for (int a = 0; a < row; a++){
		std::vector<frame> addit;
		for (int b = 0; b < column; b++){
			frame f;
			SDL_Rect clip = { a*width / row, b*height / column, width / row, height / row };
			f.x = a*width / row;
			f.y = b*height / column;
			f.w = width / row;
			f.h = height / row;
			f.pieceNumber = count;
			count++;
			addit.push_back(f);
		}
		puzzlePiece.push_back(addit);
	}
}

//Returns the length, used for checks?
int gameBoard::getLength(){ return length; }

//Rendering the board
void gameBoard::show(){
	for (int a = 0; a < row; a++){
		for (int b = 0; b < column; b++){
			SDL_Rect clip = { puzzlePiece[a][b].x, puzzlePiece[a][b].y, puzzlePiece[a][b].w, puzzlePiece[a][b].h };
			SDL_Rect dst = { SCREEN_WIDTH*a/row + a, SCREEN_HEIGHT*b/column + b, SCREEN_WIDTH/row, SCREEN_HEIGHT/column };
			SDL_RenderCopy(ren, mainPuzzle, &clip, &dst);
		}
	}
}