//Randomization module: Evangeline Smith, 80193366
/*NOTE: I know this looks sort of messed up with both the declarations and the definitions in the same file, but
after doing some research, it seemed like this was the only way to have the templates work. Whenever I split them up
I kept getting linker errors because it couldn't match the types correctly. So yeah it's all one file.

SLIDE PUZZLE DESIGNERS: use the 2d randomSwap below to randomize slide puzzle. */

#ifndef RANDOMIZING
#define RANDOMIZING

#include <vector>

//ONE-DIMENSIONAL RANDOMIZATION
//shuffle: takes ordered data structure, rearranges order
template<typename Type>
std::vector<Type> shuffle1D(std::vector<Type> input);

//randomGen: takes data structure of potential options, generates random set of some number of elements
template <typename Type>
std::vector<Type> randomGen(std::vector<Type> inputs, int finalLength);

//TWO-DIMENSIONAL RANDOMIZATION
//shuffle: same
template<typename Type>
std::vector<std::vector<Type>> shuffle2D(std::vector<Type> input);

//randomGen: same
template<typename Type>
std::vector<std::vector<Type>> randomGen(std::vector<Type> inputs, int rows, int columns);

//randomwalk: same: keep track of last move, prevent from undoing it
template<typename Type>
std::vector<std::vector<Type>> randomSwap(std::vector<std::vector<Type>> input, int rowInit, int colInit, int swaps);



//randomization.cpp
#include <random>
#include <algorithm>
#include <mutex>
#include <time.h>

std::once_flag flag;

void seedRandom(){
	std::call_once(flag, [](){srand(time(0));});
}

//ONE DIMENSION
template <typename Type>
std::vector<Type> shuffle1D(std::vector<Type> input){
	/*Randomly shuffle a vector of elements*/
	std::random_shuffle(input.begin(), input.end());
	return input;
}

template <typename Type>
std::vector<Type> randomGen(std::vector<Type> inputs, int finalLength){
	seedRandom();
	std::vector<Type> newVector(finalLength);
	for(int i=0; i<finalLength; i++){
		newVector[i] = inputs[rand()%inputs.size()];
	}
	return newVector;
}

//TWO DIMENSIONS
template<typename Type>
std::vector<std::vector<Type>> shuffle2D(std::vector<std::vector<Type>> input){
	/*Randomly shuffle a 2d vector of elements*/
	seedRandom();
	int rows = input.size();
	int columns = input[0].size();

	std::vector<Type> totalVector;
	for(int i=0;i<rows;i++){
		for(int j=0;j<columns;j++){
			totalVector.push_back(input[i][j]);
		}
	}
	std::random_shuffle(totalVector);

	std::vector<std::vector<Type>> returnVector(rows,std::vector<Type>(columns));
	for(int i=0;i<rows;i++){
		for(int j=0;j<columns;j++){
			returnVector[i][j] = totalVector[i*rows+j];
		}
	}
	return returnVector;
}

template<typename Type>
std::vector<std::vector<Type>> randomGen(std::vector<Type> inputs, int rows, int columns){
	/*2d Random Generation:
	Input a vector of potential elements, desired number of rows, and desired number of columns.
	Returns a 2d vector (vector w/in a vector) filled randomly with elements from input vector*/
	seedRandom();
	std::vector<std::vector<Type>> newVector(rows,std::vector<Type>(columns));
	
	for(int i=0;i<rows;i++){
		for(int j=0;j<columns;j++){
			newVector[i][j] = inputs[rand()%inputs.size()];
		}
	}
	return newVector;
}

template<typename Type>
std::vector<std::vector<Type>> randomSwap(std::vector<std::vector<Type>> input, int markRinit, int markCinit, int swaps){
	/*Randomly move a marked piece around a 2d board by swapping it with adjacent elements.
	SLIDE PUZZLE DESIGNERS!!! USE THIS!!!*/
	seedRandom();
	int markR = markRinit; int markC = markCinit; //row/column coords of 'marked' piece (i.e. empty space in slide puzzle
	int toSwapR = markR; int toSwapC = markC; //row/column coords of piece we're about to swap with
	Type temp; //temp var for swapping
	int dir; //direction of piece we are about to swap with
	int prevMove = 4; //direction of piece we just swapped with, initialized as something irrelevant

	for(int i = 0; i<swaps; i++){ //for however many swaps the designer wants...
		dir = rand()%4; //randomly pick a direction
		while(dir==prevMove||edge(dir, input.size(),input[0].size(), markR, markC)){ //if direction doesn't work...
			dir = rand()%4; //keep swapping until we get one that does work
		}

		if (dir==0){ //swap with above piece
			toSwapR--; //find toSwap piece

			temp = input[toSwapR][toSwapC]; //store toSwap in temp
			input[toSwapR][toSwapC] = input[markR][markC]; //put marked piece into toSwap space
			input[markR][markC] = temp; //put toSwap where marked piece was
			markR = toSwapR; markC = toSwapC; //locate marked piece again
			prevMove=2;
		}
		else if (dir==1){ //swap with right piece
			toSwapC++; //find toSwap piece

			temp = input[toSwapR][toSwapC]; //store toSwap in temp
			input[toSwapR][toSwapC] = input[markR][markC]; //put marked piece into toSwap space
			input[markR][markC] = temp; //put toSwap where marked piece was
			markR = toSwapR; markC = toSwapC; //locate marked piece again
			prevMove=3;
		}
		else if (dir==2){ //swap with bottom piece
			toSwapR++; //find toSwap piece

			temp = input[toSwapR][toSwapC]; //store toSwap in temp
			input[toSwapR][toSwapC] = input[markR][markC]; //put marked piece into toSwap space
			input[markR][markC] = temp; //put toSwap where marked piece was
			markR = toSwapR; markC = toSwapC; //locate marked piece again
			prevMove=0;
		}
		else if (dir==3){ //swap with left piece
			toSwapC--; //find toSwap piece

			temp = input[toSwapR][toSwapC]; //store toSwap in temp
			input[toSwapR][toSwapC] = input[markR][markC]; //put marked piece into toSwap space
			input[markR][markC] = temp; //put toSwap where marked piece was
			markR = toSwapR; markC = toSwapC; //locate marked piece again
			prevMove=2;
		}
	}

	return input;
}

bool edge(int dir, int rows, int cols, int markR, int markC){
	/*Helper function for randomSwap. Maybe don't use. Tells if marked piece is about to switch with thin air*/
	if( (markR==0&&dir==0)||(markR==rows-1&&dir==2)||
		(markC==0&&dir==3)||(markC==cols-1&&dir==1)){
			return true;
	}
	return false;
}

#endif //RANDOMIZING