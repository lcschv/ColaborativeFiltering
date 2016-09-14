#include "../lib/input.h"





/*Method that reads the ratings.csv and load it into an buffer in the format of the quadruple [user,item,rating,timestamp]*/
void LoadInput::readInputFiletoBuffer(){
	ifstream inputfile;
	string line;
	vector<string> words (4);
    inputfile.open("files/ratings.csv");
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
			bufferedFile.push_back(tempQuadruple);
		};
    };
};