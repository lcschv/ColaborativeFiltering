#include "../lib/itembased.h"
# include <math.h> 

//Calculate the similarity between two itens.



ItemBasedRecommender::ItemBasedRecommender(LoadInput* loadinput){
    this->loadinput = loadinput;
    Recommender();
};



void ItemBasedRecommender::Recommender(){
	tupla nextTarget;
	// vector<int> ItemsLikedbyTargetUser;
	// vector<int> UsersthatLikedTarget;
	nextTarget = loadinput->getNextTarget();
	while (nextTarget.user != -1){
		//List of itens liked by the user target, this will be used to calculate the similarity.
		ItemsLikedbyTargetUser = loadinput->getListofItensLikedbyUser(nextTarget.user);
		targetvectorlist = loadinput->getListofUsersthatRatedItem(nextTarget.item);
		// cout << "usuariotarget: "<<nextTarget.user<<"->itemtarget:"<<nextTarget.item<<endl;
		for (auto item:ItemsLikedbyTargetUser){
			// cout << "Similaridade do target para o item "<<item<<endl;
			float similaridade = Similarity(nextTarget.item , item, targetvectorlist);
			cout << "similaridades sao: "<< similaridade<<endl;
		}
		
		nextTarget = loadinput->getNextTarget();
		ItemsLikedbyTargetUser.clear();
		targetvectorlist.clear();
	}
};


float ItemBasedRecommender::Similarity(int targetItem, tuplaItemScore item, const vector<tuplaUserScore> &targetvectorlist){
	vector<int> tempListofusers;
	float denom_a, denom_b, dot;
	for (auto i:targetvectorlist){
		denom_a += pow(i.rating,2);
		if (loadinput->ItemsMap[item.item].find(i.user) != loadinput->ItemsMap[item.item].end()){
			dot += loadinput->ItemsMap[item.item][i.user] * i.rating;
		}
	}
	for (auto it:loadinput->ItemsMap[item.item]){
		denom_b += pow(it.second,2); 
	}
	return dot / (sqrt(denom_a) * sqrt(denom_b));
};

