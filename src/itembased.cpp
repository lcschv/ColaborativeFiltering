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
		// cout << "Error nesse pia aqui:" << nextTarget.user<<" item:"<<nextTarget.item<<endl;
		if (loadinput->UsersMap.find(nextTarget.user) != loadinput->UsersMap.end()){	
			
			ItemsLikedbyTargetUser = loadinput->getListofItensLikedbyUser(nextTarget.user);
			targetvectorlist = loadinput->getListofUsersthatRatedItem(nextTarget.item);
			if (targetvectorlist.empty()){
				// cout << "Dei erro aqui quando target vector ta vazio.."<<endl;
				r = UserAverage(ItemsLikedbyTargetUser);
			}else{
				// cout << "Dei erro aqui quando target vector nao esta vazio"<<endl;
				for (auto item:ItemsLikedbyTargetUser){
					float similaridade = Similarity(nextTarget.item , item, targetvectorlist);
					tempTupla.item = item.item;
					tempTupla.simi = similaridade;
					// cout << "calculei simi normalmente.."<<similaridade<<endl;
					MyHeapPush(tempTupla);
					// cout << "Dei o push normalmente.."<<endl;
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
		cout <<"u"<<loadinput->MapCorrectUserId[nextTarget.user]<<":i"<<loadinput->MapCorrectItemId[nextTarget.item]<<","<<r<<endl;
		nextTarget = loadinput->getNextTarget();
		ItemsLikedbyTargetUser.clear();
		targetvectorlist.clear();
		KNN.clear();
	}
};


float ItemBasedRecommender::Similarity(int targetItem, tuplaItemScore item, const vector<tuplaUserScore> &targetvectorlist){
	float denom_a, denom_b, dot;
	denom_a = 0;
	denom_b = 0;
	dot = 0;
	for (auto i:targetvectorlist){
		if (i.rating != 0){
			denom_a += pow(i.rating,2);
		}

		if (loadinput->ItemsMap[item.item].find(i.user) != loadinput->ItemsMap[item.item].end()){
			dot += loadinput->ItemsMap[item.item][i.user] * i.rating;
		}
	}
	for (auto it:loadinput->ItemsMap[item.item]){
		if (it.second != 0){
			denom_b += pow(it.second,2); 
		}
	}
	if (denom_a != 0 && denom_b != 0){
		return dot / (sqrt(denom_a) * sqrt(denom_b));
	}else{
		return 0;
	}
};



void ItemBasedRecommender::MyHeapPush(tuplaItemSimilarity truplas) {
	// cout << "Entrei no push.."<<endl;
	if (KNN.size() < 5 && truplas.simi != 0){
		// cout << "entrei aqui.."<<endl;
		KNN.push_back(truplas);
    	push_heap(KNN.begin(), KNN.end(), cmp());
	} else if (!KNN.empty() && KNN.front().simi < truplas.simi){
		// cout << "entrei no segundo caso"<<endl;
		KNN.erase(KNN.begin());
		KNN.push_back(truplas);
    	push_heap(KNN.begin(), KNN.end(), cmp());
	} 
	// cout << "Entrei nao sei o que deu ero.."<<endl;
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
	if (denominator == 0){
		return 5;
	}else{
		predict = numerator/denominator;
		return predict;
	}
};

float ItemBasedRecommender::UserAverage(const vector<tuplaItemScore> &itemslist){
	float numerator, predict;
	numerator = 0;
	predict = 0;
	for (auto it:itemslist){
		numerator += it.rating;
	}
	if (itemslist.size() == 0){
		return 5;
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
			return 5;
		}else{
			predict = numerator / targetvectorlist.size();
			return predict;
		}
};
	