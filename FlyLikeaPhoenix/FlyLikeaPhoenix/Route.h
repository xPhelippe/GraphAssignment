#include "Flight.h"
#include "Airport.h"
#include <vector>
#ifndef Route_H
#define Route_H


class Route {
public:
	Route(int totalAirports);
	void addFlight(Flight* flight);
	void DFS(Airport* src);
	void determineShortestPath(Airport* src, Airport* dest);
	void determineFastestFlight(Airport* src, Airport* dest);
	void determineLowestCostFlight(Airport* src, Airport* dest);
	void determineShortestDistanceFlight(Airport* src, Airport* dest);
	void printNetwork();

private:
	//I am using a Adjacency Matrix to implement my graph
	//in order to do so, I need to keep track of which index corresponds to which airport
	// that is what the Airports array is for
	Flight** flights;

	vector<Airport> airports; //to keep track of the airports added to the networkif(
	//the index of the airport will ocrrespond to an index on the flight array

	int totalAirports;

	int findorAddAirportIndex(Airport* airport);
	void depthFirstSearch(Airport *airport, bool visited[]);


	
};

#endif // !Route_H
