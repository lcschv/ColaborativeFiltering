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
	

	/*Check if the parameters are ok.*/
	if (argc != 3){
		cout << "Wrong parameters, please use ./recommender ratings.csv targets.csv > submission.csv" <<endl;
	return 0;
	}
		string ratingsfile(argv[1]);
		string targetsfile(argv[2]);

	LoadInput loadinput(ratingsfile,targetsfile);


	ItemBasedRecommender itembased(&loadinput);	
	// NonPersonalizedRecommender MeanBased(&loadinput);

	return 0;
}
