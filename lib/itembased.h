#ifndef ITEMBASED_H
#define ITEMBASED_H
#include "input.h"

struct tuplaItemSimilarity{
	int item;
	double simi;
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
	double Similarity(int targetItem, tuplaItemScore item, const vector<tuplaUserScore> &targetvectorlist);
	void Recommender();
	void MyHeapPush(tuplaItemSimilarity truplas);
	double WeightedAverage(int Targetuser);
	double UserAverage(const vector<tuplaItemScore> &itemslist);
	double ItemAverage(const vector<tuplaUserScore> &targetvectorlist);
};


#endif