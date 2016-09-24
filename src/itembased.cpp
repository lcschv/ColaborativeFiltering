#include "../lib/itembased.h"
# include <math.h> 

//Calculate the similarity between two itens.



ItemBasedRecommender::ItemBasedRecommender(LoadInput* loadinput){
    this->loadinput = loadinput;
    Recommender();
    
};



void ItemBasedRecommender::Recommender(){
	tupla nextTarget;
	tuplaItemSimilarity tempTupla;
	float r = 0;
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
			tempTupla.item = item.item;
			tempTupla.simi = similaridade;
			MyHeapPush(tempTupla);
			cout << "similaridades sao: "<< similaridade<<endl;
		}
		if (!KNN.empty()){
			r = WeightedAverage(nextTarget.user);
		}else{
			r = UserAverage(ItemsLikedbyTargetUser);
		}
		nextTarget = loadinput->getNextTarget();
		ItemsLikedbyTargetUser.clear();
		targetvectorlist.clear();
		KNN.clear();
	}
};


float ItemBasedRecommender::Similarity(int targetItem, tuplaItemScore item, const vector<tuplaUserScore> &targetvectorlist){
	vector<int> tempListofusers;
	float denom_a, denom_b, dot;
	denom_a = 0;
	denom_b = 0;
	dot = 0;
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



void ItemBasedRecommender::MyHeapPush(tuplaItemSimilarity truplas) {
	if (KNN.capacity() < 2 && truplas.simi != 0){
		KNN.push_back(truplas);
    	push_heap(KNN.begin(), KNN.end(), cmp());
	} else if (truplas.simi != 0 && KNN.front().simi < truplas.simi){
		KNN.erase(KNN.begin());
		KNN.push_back(truplas);
    	push_heap(KNN.begin(), KNN.end(), cmp());
	} 
};


float ItemBasedRecommender::WeightedAverage(int Targetuser){
	float predict, numerator ,denominator;
	predict = 0;
	numerator = 0;
	denominator = 0;
	for (auto it:KNN){
		cout <<"item: "<< it.item <<"Simi: " << it.simi << "rating: "<< loadinput->ItemsMap[it.item][Targetuser]<<endl;
		numerator += it.simi * loadinput->ItemsMap[it.item][Targetuser];
		denominator += it.simi;
	}
	predict = numerator/denominator;
	return predict;
};

float ItemBasedRecommender::UserAverage(const vector<tuplaItemScore> &itemslist){
	float numerator, predict;
	numerator = 0;
	predict = 0;
	for (auto it:itemslist){
		numerator += it.rating;
	}
	predict = numerator / itemslist.size();
	return predict;
};