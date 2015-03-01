//Randomization Demo: Evangeline Smith, 80193366
/*Generates a 2D board of Xs with a single O in the upper left hand corner, then moves the O around randomly.*/

#include "randomization.h"
#include <iostream>

int main(){
	std::vector<std::string> inputs;
	inputs.push_back("X");

	std::vector<std::vector<std::string>> newList = randomGen(inputs, 8, 8);
	newList[0][0]="O";
	for(int i=0;i<8;i++){
		for(int j=0;j<8;j++){
			std::cout << newList[i][j].c_str()<<", ";
		}
		std::cout << std::endl;
	}
	std::cout<<std::endl;

	newList = randomSwap(newList, 0,0,64);
	for(int i=0;i<8;i++){
		for(int j=0;j<8;j++){
			std::cout << newList[i][j].c_str()<<", ";
		}
		std::cout << std::endl;
	}
	system("pause");
	return 0;
}