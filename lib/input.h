#ifndef INPUT_H
#define INPUT_H

#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <unordered_map>
#include <boost/algorithm/string.hpp>
#include <boost/tokenizer.hpp>
using namespace std;




struct quadruple{
	int user;
	int item;
	int rating;
	int timestamp;
};
struct tupla{
	int user;
	int item;
};
struct tuplaUserScore{
	int user;
	int rating;
};
struct tuplaItemScore{
	int item;
	int rating;
};
class LoadInput{
	private:
		std::vector<quadruple> bufferedFile;
		
		vector<tupla> targetBuffer;

	public:
		unordered_map<int,unordered_map<int,double>> UsersMap;
		unordered_map<int,unordered_map<int,int>> ItemsMap;
		unordered_map<int,string> MapCorrectUserId;
		unordered_map<int,string> MapCorrectItemId;
		LoadInput(string &ratingsfile, string &targetsfile);//{
			// std::cout << "Loading inputs..\n";
			// readInputFiletoBuffer();
			// readTargetFile();
			// loadUsers();
			// loadItems();
			// printTargetMap();
			// printItemsMap();
			// printUsersMap();
		//}
		//Method that read the input file to a buffer.
		void readInputFiletoBuffer(string &ratingsfile);
		void readTargetFile(string &targetsfile);
		void loadItens();
		void loadUsers();
		void loadItems();
		void printTargetMap();
		void printUsersMap();
		void printItemsMap();
		void printBufferedFile();
		vector<tuplaItemScore> getListofItensLikedbyUser(int user);
		vector<tuplaUserScore> getListofUsersthatRatedItem(int item);
		tupla getNextTarget();
};

#endif