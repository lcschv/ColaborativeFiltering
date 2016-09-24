#ifndef NONPERSONALIZED_H
#define NONPERSONALIZED_H
#include "input.h"


class NonPersonalizedRecommender{
	private:
		LoadInput* loadinput;
		vector<tuplaItemScore> ItemsLikedbyTargetUser;
		double RatingAverage;
		vector<tuplaUserScore> targetvectorlist;
		unordered_map<int, double> ItemsAverageRating;
		unordered_map<int, double> UserAverageRating;

	public:
		NonPersonalizedRecommender(LoadInput* loadinput);
		void Recommender();
		void CalcItensAverageRating();
		void CalcUsersAverageRating();
};


#endif