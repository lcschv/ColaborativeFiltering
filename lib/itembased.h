#ifndef ITEMBASED_H
#define ITEMBASED_H
#include "input.h"

class ItemBasedRecommender{
private:
	LoadInput* loadinput;
public:
	ItemBasedRecommender(LoadInput* loadinput);
	void Similarity(int targetItem, int item);
};


#endif