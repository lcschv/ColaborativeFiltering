#ifndef ITEMBASED_H
#define ITEMBASED_H
#include "input.h"

class ItemBasedRecommender{
private:
	LoadInput* loadinput;
	vector<tuplaItemScore> ItemsLikedbyTargetUser;
	vector<tuplaUserScore> targetvectorlist;
public:
	ItemBasedRecommender(LoadInput* loadinput);
	float Similarity(int targetItem, tuplaItemScore item, const vector<tuplaUserScore> &targetvectorlist);
	void Recommender();

};


#endif