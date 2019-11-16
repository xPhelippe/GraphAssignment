#include <string>
using namespace std;

#ifndef Airport_H
#define Airport_H

struct Airport {
	int id; //unique, represents placement in matrix
	string airportName;

	//three efficency factors 
	int minutes; 
	double cost; 
	double distance;

	Airport() {
		id = -1; 
		airportName = "UNK";
	}

	Airport(int i, string k) {
		id = i;
		airportName = k;
	}

	bool operator == (Airport const & a) {
		bool result = false;

		if (id == a.id && airportName == a.airportName) {
			result = true;
		}

		return result;
	}
};
#endif 
