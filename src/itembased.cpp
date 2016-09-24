#include "../lib/itembased.h"
# include <math.h> 

//Calculate the similarity between two itens.



ItemBasedRecommender::ItemBasedRecommender(LoadInput* loadinput){
    this->loadinput = loadinput;
    cout << "UserId:ItemId,Prediction"<<endl;
    Recommender();
    
};



void ItemBasedRecommender::Recommender(){
	tupla nextTarget;
	tuplaItemSimilarity tempTupla;
	float r = 0;
	nextTarget = loadinput->getNextTarget();
	while (nextTarget.user != -1){
		if (loadinput->UsersMap.find(nextTarget.user) != loadinput->UsersMap.end()){	
			
			ItemsLikedbyTargetUser = loadinput->getListofItensLikedbyUser(nextTarget.user);
			targetvectorlist = loadinput->getListofUsersthatRatedItem(nextTarget.item);
			if (targetvectorlist.empty()){
				r = UserAverage(ItemsLikedbyTargetUser);
			}else{
				for (auto item:ItemsLikedbyTargetUser){
					float similaridade = Similarity(nextTarget.item , item, targetvectorlist);
					tempTupla.item = item.item;
					tempTupla.simi = similaridade;
					MyHeapPush(tempTupla);
				}
				if (!KNN.empty()){
					r = WeightedAverage(nextTarget.user);
				}else{
					r = UserAverage(ItemsLikedbyTargetUser);
				}
			}
		}else {
			targetvectorlist = loadinput->getListofUsersthatRatedItem(nextTarget.item);
			if (targetvectorlist.size() != 0){
				r = ItemAverage(targetvectorlist);
			}else{
				r = 6;
			}			
		}
		cout <<nextTarget.user<<":"<<nextTarget.item<<","<<r<<endl;
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
	// cout << "Entrei no push.."<<endl;
	if (KNN.size() < 5 && truplas.simi != 0){
		KNN.push_back(truplas);
    	push_heap(KNN.begin(), KNN.end(), cmp());
	} else if (KNN.front().simi < truplas.simi){
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
		//cout <<"item: "<< it.item <<"Simi: " << it.simi << "rating: "<< loadinput->ItemsMap[it.item][Targetuser]<<endl;
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
	if (itemslist.size() == 0){
		return 0;
	}else{
		predict = numerator / itemslist.size();
		return predict;	
	}
};


float ItemBasedRecommender::ItemAverage(const vector<tuplaUserScore> &targetvectorlist){
	float numerator, predict;
		numerator = 0;
		predict = 0;
		for (auto it:targetvectorlist){
			numerator += it.rating;
		}
		if (targetvectorlist.size() == 0){
			return 0;
		}else{
			predict = numerator / targetvectorlist.size();
			return predict;	
		}
};
	