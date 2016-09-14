#ifndef INPUT_H
#define INPUT_H

#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <unordered_map>
using namespace std;

struct quadruple{
	int user;
	int item;
	int rating;
	int timestamp;
};


class LoadInput{
	private:

	public:
		LoadInput ( ){
			std::cout << "Loading inputs..\n";
		}
		//Method that read the input file to a buffer.
		vector<quadruple> readInputFile(string filein);
};

#endif