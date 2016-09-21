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
using namespace std;


int main(int argc, char *argv[]){
	if (argc != 3){
		cout << "Wrong parameters, please use ./recommender ratings.csv targets.csv > submission.csv" <<endl;
	return 0;
	}
	LoadInput loadinput;
	ItemBasedRecommender itembased(&loadinput);
return 0;
}
