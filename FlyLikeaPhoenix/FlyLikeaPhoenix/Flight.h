

#ifndef Flight_H
#define Flight_H
#include "Airport.h"
struct Flight {
	//airports connected at this arc
	Airport * src;
	Airport * dest;

	//cost of traveling this arc
	int minutes;
	double cost;
	double distance;

	Flight() {
		src = 0;
		dest = 0;
		minutes = 0;
		cost = 0;
		distance = 0;
	}

	Flight(Airport *s, Airport *d, int m, double c, double dist) {
		src = s;
		dest = d;
		minutes = m;
		cost = c;
		distance = dist;
	}
};



#endif // !Flight

#pragma once
