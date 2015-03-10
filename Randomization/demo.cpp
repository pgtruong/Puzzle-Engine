//Randomization Demo: Evangeline Smith, 80193366
/*Generates a 2D board of Xs with a single O in the upper left hand corner, then moves the O around randomly.*/

#include "randomization.h"
#include <iostream>
#include <sstream>

int main(){
	//std::vector<std::string> inputs;
	//inputs.push_back("X");

	//std::vector<std::vector<std::string>> newList = randomGen(inputs, 8, 8);
	//newList[0][0]="O";
	std::vector<std::vector<std::string>> newList(10,std::vector<std::string>(10));
	for(int i=0;i<newList.size();i++){
		for(int j=0;j<newList[0].size();j++){
			newList[i][j] = std::to_string(i)+std::to_string(j);
			std::cout << newList[i][j].c_str() <<" ";
		}
		std::cout << std::endl;
	}
	std::cout<<std::endl;

	newList[9][9] = "__";
	newList = randomSwap(newList, 9,9,1000);
	for(int i=0;i<newList.size();i++){
		for(int j=0;j<newList[0].size();j++){
			std::cout << newList[i][j].c_str() <<" ";
		}
		std::cout << std::endl;
	}
	system("pause");
	return 0;
}
