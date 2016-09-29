#include "../lib/itembased.h"




// Instantiate the loadinput from the class LoadInput. Passed as reference // 
ItemBasedRecommender::ItemBasedRecommender(LoadInput* loadinput){
    this->loadinput = loadinput;
    cout << "UserId:ItemId,Prediction"<<endl;
    Recommender();
};

/*Main method of the class, it call all the other functions and calculate the predicion
for each of the target users. The value 6.87 is the average of the itens of the whole dataset.
It handles coldstart using the user average ratings or overall iten average.*/
void ItemBasedRecommender::Recommender(){
	tupla nextTarget;
	tuplaItemSimilarity tempTupla;
	double r = 0;
	nextTarget = loadinput->getNextTarget();

	//Calculates the prediction for each Target.
	while (nextTarget.user != -1){
		//Checks if theres no information about the target user in the dataset. Coldstart User.
		if (loadinput->UsersMap.find(nextTarget.user) != loadinput->UsersMap.end()){	
			
			ItemsLikedbyTargetUser = loadinput->getListofItensLikedbyUser(nextTarget.user);
			targetvectorlist = loadinput->getListofUsersthatRatedItem(nextTarget.item);
			//If theres infomation about the user, but no information about the item in the dataset. Coldstart Item.
			if (targetvectorlist.empty()){
				r = UserAverage(ItemsLikedbyTargetUser);
			}else{
				for (auto item:ItemsLikedbyTargetUser){
					double similaridade = Similarity(nextTarget.item , item, targetvectorlist);
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
			//If theres no information about the user, but have information about the item in the dataset. Coldstart User handler.
			targetvectorlist = loadinput->getListofUsersthatRatedItem(nextTarget.item);
			if (targetvectorlist.size() != 0){
				r = ItemAverage(targetvectorlist);
			}else{
				// No information of item and user. COLDSTART
				r = 6.87;
			}			
		}
		cout <<"u"<<loadinput->MapCorrectUserId[nextTarget.user]<<":i"<<loadinput->MapCorrectItemId[nextTarget.item]<<","<<r<<endl;
		nextTarget = loadinput->getNextTarget();
		ItemsLikedbyTargetUser.clear();
		targetvectorlist.clear();
		KNN.clear();
	}
};

//Calculate the cosine similarity between two itens.
double ItemBasedRecommender::Similarity(int targetItem, tuplaItemScore item, const vector<tuplaUserScore> &targetvectorlist){
	double denom_a, denom_b, dot;
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

/* This method just makes the push if the lowest similarity in the KNN vector is lower than the similarity to be pushed.
Controls the size of the neighboorhood.*/
void ItemBasedRecommender::MyHeapPush(tuplaItemSimilarity truplas) {
	// Change the value of the neighboorhood here.
	if (KNN.size() < 100 && truplas.simi != 0){
	KNN.push_back(truplas);
    	push_heap(KNN.begin(), KNN.end(), cmp());
	} else if (!KNN.empty() && KNN.front().simi < truplas.simi){
		KNN.erase(KNN.begin());
		KNN.push_back(truplas);
    	push_heap(KNN.begin(), KNN.end(), cmp());
	} 
};

// Calculates the weighted average by multiplying    (Rating * simi(i,j)) / Sum (sim(i,j))
double ItemBasedRecommender::WeightedAverage(int Targetuser){
	double predict, numerator ,denominator;
	predict = 0;
	numerator = 0;
	denominator = 0;
	for (auto it:KNN){
		//cout <<"item: "<< it.item <<"Simi: " << it.simi << "rating: "<< loadinput->ItemsMap[it.item][Targetuser]<<endl;
		numerator += it.simi * loadinput->ItemsMap[it.item][Targetuser];
		denominator += it.simi;
	}
	if (denominator == 0){
		return 6.87;
	}else{
		predict = numerator/denominator;
		return predict;
	}
};

// Calculate the Average of the ratings of an specific user.
double ItemBasedRecommender::UserAverage(const vector<tuplaItemScore> &itemslist){
	double numerator, predict;
	numerator = 0;
	predict = 0;
	for (auto it:itemslist){
		numerator += it.rating;
	}
	if (itemslist.size() == 0){
		return 6.87;
	}else{
		predict = numerator / itemslist.size();
		return predict;	
	}
};

// Calculate the Average of the ratings of an specific Item.
double ItemBasedRecommender::ItemAverage(const vector<tuplaUserScore> &targetvectorlist){
	double numerator, predict;
		numerator = 0;
		predict = 0;
		for (auto it:targetvectorlist){
			numerator += it.rating;
		}
		if (targetvectorlist.size() == 0){
			return 6.87;
		}else{
			predict = numerator / targetvectorlist.size();
			return predict;
		}
};
	
