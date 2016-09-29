#include "../lib/NonPersonalized.h"

// Instantiate the loadinput from the class LoadInput. Passed as reference // 
NonPersonalizedRecommender::NonPersonalizedRecommender(LoadInput* loadinput){
    this->loadinput = loadinput;
    cout << "UserId:ItemId,Prediction"<<endl;
    CalcItensAverageRating();
    CalcUsersAverageRating();
    Recommender();
};

/*Main method of the class, for each target user, it checks if theres information about the item,
if there is information it returns the item average rating. If theres no information about the item,
uses the average of the user target, if theres no information about the user, use the item average of the dataset.*/
void NonPersonalizedRecommender::Recommender(){
	tupla nextTarget;
	double r = 0;
	nextTarget = loadinput->getNextTarget();
	while (nextTarget.item != -1){

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


/* Calculates the item average for each of the itens in the dataset and store it in a map called ItemsAverage.
 This method also calculates the overall dataset average of the itens.*/
void NonPersonalizedRecommender::CalcItensAverageRating(){
	double sum = 0;
	double sum2 = 0;
	double itemaverage = 0;
	int denom = 0;
	int denomb = 0;

	for (auto it:loadinput->ItemsMap){
		for (auto it2:loadinput->ItemsMap[it.first]){
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
	// DATASET ITEM AVERAGE
	RatingAverage = sum2/denomb;
};

// Calculate the Average of the ratings of an specific user and store it in a map called UsersAverage.
void NonPersonalizedRecommender::CalcUsersAverageRating(){
	double sum = 0;
	double sum2 = 0;
	double useraverage = 0;
	int denom = 0;
	int denomb = 0;

	for (auto it:loadinput->UsersMap){
		for (auto it2:loadinput->UsersMap[it.first]){
			denom += 1;
			sum += it2.second;
		}
		useraverage = sum / denom;
		UserAverageRating[it.first] = useraverage;
		denom = 0;
		useraverage = 0;
		sum = 0;
	}
};