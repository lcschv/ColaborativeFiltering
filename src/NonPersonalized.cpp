#include "../lib/NonPersonalized.h"


NonPersonalizedRecommender::NonPersonalizedRecommender(LoadInput* loadinput){
    this->loadinput = loadinput;
    cout << "UserId:ItemId,Prediction"<<endl;
    CalcItensAverageRating();
    CalcUsersAverageRating();
    Recommender();
};


void NonPersonalizedRecommender::Recommender(){
	tupla nextTarget;
	double r = 0;
	nextTarget = loadinput->getNextTarget();
	while (nextTarget.item != -1){
		// cout << "Error nesse pia aqui:" << nextTarget.user<<" item:"<<nextTarget.item<<endl;
		if (ItemsAverageRating.find(nextTarget.item) != ItemsAverageRating.end()){
			r = ItemsAverageRating[nextTarget.item];
		}else if (UserAverageRating.find(nextTarget.user) != UserAverageRating.end()) {
			r = UserAverageRating[nextTarget.user];	
		}else{
			r = RatingAverage;
		}
		cout <<"u"<<loadinput->MapCorrectUserId[nextTarget.user]<<":i"<<loadinput->MapCorrectItemId[nextTarget.item]<<","<<r<<endl;
		nextTarget = loadinput->getNextTarget();
	}
};


// unordered_map<int, double> ItemsAverageRating;

void NonPersonalizedRecommender::CalcItensAverageRating(){
	double sum = 0;
	double sum2 = 0;
	double itemaverage = 0;
	int denom = 0;
	int denomb = 0;

	for (auto it:loadinput->ItemsMap){
		// cout <<"Item: "<< it.first<<"	->";
		for (auto it2:loadinput->ItemsMap[it.first]){
			// cout <<"usuario>"<<it2.first<<"rating>"<< it2.second<<endl;
			denom += 1;
			sum += it2.second;
		}
		itemaverage = sum / denom;
		ItemsAverageRating[it.first] = itemaverage;
		sum2 += itemaverage;
		denom = 0;
		itemaverage = 0;
		sum = 0;
		denomb += 1;
	}
	RatingAverage = sum2/denomb;
	// cout << RatingAverage;
};

void NonPersonalizedRecommender::CalcUsersAverageRating(){
	double sum = 0;
	double sum2 = 0;
	double useraverage = 0;
	int denom = 0;
	int denomb = 0;

	for (auto it:loadinput->UsersMap){
		// cout <<"Usuario: "<< it.first<<"	->";
		for (auto it2:loadinput->UsersMap[it.first]){
			// cout <<"Item>"<<it2.first<<"rating>"<< it2.second<<endl;
			denom += 1;
			sum += it2.second;
		}
		useraverage = sum / denom;
		// cout << useraverage<<endl;
		UserAverageRating[it.first] = useraverage;
		denom = 0;
		useraverage = 0;
		sum = 0;
	}
};