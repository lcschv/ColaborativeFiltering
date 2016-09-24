#include "../lib/input.h"



LoadInput::LoadInput(string &ratingsfile, string &targetsfile){
	readInputFiletoBuffer(ratingsfile);
	readTargetFile(targetsfile);
	loadUsers();
	loadItems();
}


/*Method that reads the ratings.csv and load it into an buffer in the format of the quadruple [user,item,rating,timestamp]*/
void LoadInput::readInputFiletoBuffer(string &ratingsfile){
	ifstream inputfile;
	// cout <<ratingsfile<<endl;
	string line;
	vector<string> words (4);
    inputfile.open(ratingsfile);
    // Removing header of the file ..
    getline(inputfile,line);
    quadruple tempQuadruple;
    //Treating fields of the file ..
    while (!inputfile.eof()){
        getline(inputfile,line);
        if (line != ""){
			boost::split(words, line, boost::is_any_of(",:"));
			//removing character U from users.
			words[0].erase(0,1);
			//removing character i from itens.
			words[1].erase(0,1);
			tempQuadruple.user = stoi(words[0]);
			tempQuadruple.item = stoi(words[1]);
			tempQuadruple.rating = stoi(words[2]);
			tempQuadruple.timestamp = stoi(words[3]);
			MapCorrectUserId[stoi(words[0])] = words[0];
			MapCorrectItemId[stoi(words[1])] = words[1];
			bufferedFile.push_back(tempQuadruple);
		};
    };
};

void LoadInput::readTargetFile(string &targetsfile){
	ifstream targetFile;
	string line;
	vector<string> words (4);
    targetFile.open(targetsfile);
    // Removing header of the file ..
    getline(targetFile,line);
    tupla tempTuple;
    //Treating fields of the file ..
    while (!targetFile.eof()){

        getline(targetFile,line);
        if (line != ""){
			boost::split(words, line, boost::is_any_of(":"));
			//removing character U from users.
			words[0].erase(0,1);
			//removing character i from itens.
			words[1].erase(0,1);
			tempTuple.user = stoi(words[0]);
			tempTuple.item = stoi(words[1]);
			MapCorrectUserId[stoi(words[0])] = words[0];
			MapCorrectItemId[stoi(words[1])] = words[1];
			targetBuffer.push_back(tempTuple);
		};
    };
};

void LoadInput::loadUsers(){
	for (auto i:bufferedFile){
		UsersMap[i.user][i.item] = i.rating; 
	}
};

void LoadInput::loadItems(){
	for (auto i:bufferedFile){
		ItemsMap[i.item][i.user] = i.rating; 
	}
};

void LoadInput::printTargetMap(){
	for (auto i:targetBuffer){
		cout <<"usuario:"<<i.user <<"	item:"<<i.item <<endl;
	};
};




void LoadInput::printUsersMap(){
	for (auto i:UsersMap){
		for (auto j:i.second){
			cout <<"usuario:"<<i.first <<"	item:"<<j.first<<"	rating:"<<j.second<<endl;
		}		
	}	
}
void LoadInput::printItemsMap(){
	for (auto i:ItemsMap){
		for (auto j:i.second){
			cout <<"item:"<<i.first <<"	usuario:"<<j.first<<"	rating:"<<j.second<<endl;
		}		
	}	
}


void LoadInput::printBufferedFile(){

}

vector<tuplaItemScore> LoadInput::getListofItensLikedbyUser(int user){
	vector<tuplaItemScore> listOfItensLikedbyUser;
	tuplaItemScore tempTupla;
	for (auto i:UsersMap[user]){
		tempTupla.item = i.first;
		tempTupla.rating = i.second;
		// cout << "items curtidos pelo usuario:"<<user<<"--->"<<i.first<<endl;
		listOfItensLikedbyUser.push_back(tempTupla);
	}
	return listOfItensLikedbyUser;
}

vector<tuplaUserScore> LoadInput::getListofUsersthatRatedItem(int item){
	vector<tuplaUserScore> listofUsersthatRatedItem;
	tuplaUserScore tempTuple;
	for (auto i:ItemsMap[item]){
		tempTuple.user = i.first;
		tempTuple.rating = i.second;
		// cout << "usuarios que deram rating ao item:" <<item<<"--->"<<i.first<<endl;
		listofUsersthatRatedItem.push_back(tempTuple);
	}
	return listofUsersthatRatedItem;
}


tupla LoadInput::getNextTarget(){
	tupla tempTuple;
	if (!targetBuffer.empty()){
		tempTuple = targetBuffer.back();
		targetBuffer.pop_back();
		return tempTuple;
	} else {
		tempTuple.user = -1;
		tempTuple.item = -1;
		return tempTuple;
	}
}