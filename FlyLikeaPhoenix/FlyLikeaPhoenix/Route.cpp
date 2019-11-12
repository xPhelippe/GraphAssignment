#include "pch.h"
#include "Route.h"
#include <iostream>

Route::Route(int totalAirports)
{
	//creating a 2d array dynamically by creating an array of pointers
	flights = new Flight*[totalAirports];

	for (int i = 0; i < totalAirports; i++) {
		flights[i] = new Flight[totalAirports];
	}

	airports.reserve(totalAirports);

	//keep the size of the arrays handy for when I need it
	this->totalAirports = totalAirports;
}

void Route::addFlight(Flight * flight)
{
	//find the x and y coordinate that intersects the 
	//source and destination airports
	int from = findorAddAirportIndex(flight->src);
	int to = findorAddAirportIndex(flight->dest);

	flights[from][to] = *flight;

}

void Route::DFS(Airport * src)
{
	//create bool array to keep track of visited nodes
	//thanks GeeksforGeeks for the idea!
	bool* visited = new bool[airports.size()];

	for (int i = 0; i < airports.size(); i++) {
		visited[i] = false;
	}
	
	//do a depth first search on that source.
	depthFirstSearch(src, visited);

	int indexofunvisited = -1;
	do {
		//see if there are any other nodes that need to be visited
		for (int i = 0; i < totalAirports; i++) {
			if (visited[i] == false) {
				indexofunvisited = i;
				break;
			}
			else {
				indexofunvisited = -1;
			}
		}

		//visit those nodes
		if (indexofunvisited >= 0) {
			Airport* a = &airports.at(indexofunvisited);
			depthFirstSearch(a, visited);
		}

	} while (indexofunvisited >= 0);
	
}

void Route::depthFirstSearch(Airport * airport, bool visited[])
{
	//view current node
	std::cout << airport->airportName << " ";

	//mark as visited
	int srcIndex = findorAddAirportIndex(airport);

	visited[srcIndex] = true;

	//see if another node that is connected has been visited already or not
	//find connected airport
	//if not then visit that node
	for (int i = 0; i < totalAirports; i++) {
		if (flights[srcIndex][i].cost != NULL && visited[i] == false) {
			depthFirstSearch(flights[srcIndex][i].dest, visited);
		}
	}

}

void Route::printNetwork()
{
	std::cout << "     ";

	//print top row of airports
	for (int i = 0; i < totalAirports; i++) {
		std::cout << airports.at(i).airportName << " ";
	}

	std::cout << endl;

	//print out a 1 if a flight exists at that point
	//existence is tested by seeing if there is a flight cost at that
	// point
	for (int i = 0; i < totalAirports; i++) {
		std::cout << airports.at(i).airportName << " |";

		for (int j = 0; j < totalAirports; j++) {
			if (!flights[i][j].cost) {
				std::cout << " 0  ";
			}
			else {
				std::cout << " 1  ";
			}

		}

		std::cout << "|"<< endl;
	}
}

int Route::findorAddAirportIndex(Airport * airport)
{
	//index out of bounds to start
	int index = -1;

	//looks for index in the current list
	for (int i = 0; i < airports.size(); i++) {
		if (airports.at(i) == *airport) {
			index = i;
			break;
		}
	}

	//if index is not in current list,
	//add item to end of list
	if (index == -1) {
		airports.push_back(*airport);
		index = airports.size() - 1;
	}
	return index;
}
