#ifndef compare_time
#define compare_time
#include"Airport.h"


//these comparator objects are used to compare items in the priority queue

struct CompareTime {

	bool operator()(std::pair<Airport, string> &a1, std::pair<Airport, string> &a2) {
		return a1.first.minutes > a2.first.minutes;
	}
};

struct CompareDistance {

	bool operator()(std::pair<Airport, string> &a1, std::pair<Airport, string> &a2) {
		return a1.first.distance > a2.first.distance;
	}
};

struct CompareCost {

	bool operator()(std::pair<Airport, string> &a1, std::pair<Airport, string> &a2) {
		return a1.first.cost > a2.first.cost;
	}
};

#endif // !compare_time
