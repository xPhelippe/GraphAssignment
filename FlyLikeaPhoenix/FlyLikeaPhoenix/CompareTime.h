#ifndef compare_time
#define compare_time
#include"Airport.h"

struct CompareTime {

	bool operator()(std::pair<Airport, string> &a1, std::pair<Airport, string> &a2) {
		return a1.first.minutes > a2.first.minutes;
	}
};

#endif // !compare_time
