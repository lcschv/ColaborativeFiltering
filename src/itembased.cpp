#include "../lib/itembased.h"

//Calculate the similarity between two itens.



ItemBasedRecommender::ItemBasedRecommender(LoadInput* loadinput){
    this->loadinput = loadinput;
    Similarity(1,2);
};

void ItemBasedRecommender::Similarity(int targetItem, int item){
	loadinput->printUsersMap();
};

