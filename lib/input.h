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


class LoadInput{
	private:
		std::vector<quadruple> bufferedFile;
		unordered_map<int,unordered_map<int,float>> UsersMap;
		unordered_map<int,unordered_map<int,float>> ItemsMap;
		unordered_map<int,vector<int>> targetMap;
		vector<int> listofItens;
		vector<int> listofUsers;

	public:
		LoadInput(){
			std::cout << "Loading inputs..\n";
			readInputFiletoBuffer();
			readTargetFile();
			loadUsers();
			loadItems();
			// printTargetMap();
			// printUsersMap();
			listofItens = getListofItensLikedbyUser(1);
			listofUsers = getListofUsersthatRatedItem(listofItens[2]);
		}
		//Method that read the input file to a buffer.
		void readInputFiletoBuffer();
		void readTargetFile();
		void loadItens();
		void loadUsers();
		void loadItems();
		void printTargetMap();
		void printUsersMap();
		void printItemsMap();
		void printBufferedFile();
		vector<int> getListofItensLikedbyUser(int user);
		vector<int> getListofUsersthatRatedItem(int item);
};

#endif