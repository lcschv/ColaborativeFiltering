#include <fstream>
#include <limits>
#include <iostream>
#include <string>
#include <istream>
#include <sstream>
#include <iostream>
#include <fstream>
#include <algorithm>
#include <unordered_map>
#include "lib/input.h"
#include "lib/itembased.h"
#include "lib/NonPersonalized.h"
using namespace std;



int main(int argc,char *argv[]){
	
	if (argc != 3){
		cout << "Wrong parameters, please use ./recommender ratings.csv targets.csv > submission.csv" <<endl;
	return 0;
	}
		string ratingsfile(argv[1]);
		string targetsfile(argv[2]);
	// cout <<"Antes de chamar.." <<ratingsfile<<endl;
	LoadInput loadinput(ratingsfile,targetsfile);


	ItemBasedRecommender itembased(&loadinput);
	NonPersonalizedRecommender MeanBased(&loadinput);
	for (auto it:loadinput.AnswerMap){
		for (auto it2:loadinput.AnswerMap[it.first])
		cout <<"u"<<loadinput.MapCorrectUserId[it.first]<<":i"<<loadinput.MapCorrectItemId[it2.first]<<","<<it2.second<<endl;

	}

	return 0;
}
