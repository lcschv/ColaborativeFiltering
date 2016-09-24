#ifndef ITEMBASED_H
#define ITEMBASED_H
#include "input.h"

struct tuplaItemSimilarity{
	int item;
	float simi;
};
struct cmp {
	bool operator()( const tuplaItemSimilarity & e1, const tuplaItemSimilarity & e2) {
		return (e1.simi > e2.simi);
	}
};


class ItemBasedRecommender{
private:
	LoadInput* loadinput;
	vector<tuplaItemScore> ItemsLikedbyTargetUser;
	vector<tuplaUserScore> targetvectorlist;
	vector<tuplaItemSimilarity> KNN;
public:
	ItemBasedRecommender(LoadInput* loadinput);
	float Similarity(int targetItem, tuplaItemScore item, const vector<tuplaUserScore> &targetvectorlist);
	void Recommender();
	void MyHeapPush(tuplaItemSimilarity truplas);
	float WeightedAverage(int Targetuser);
	float UserAverage(const vector<tuplaItemScore> &itemslist);
};


#endif