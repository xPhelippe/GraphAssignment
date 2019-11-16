#include "pch.h"
#include "Route.h"
#include "CompareTime.h"
#include <iostream>
#include <queue>
#include <string>

using namespace std;

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

void Route::determineFastestFlight(Airport * src, Airport * dest)
{
	//here we do dijkstras algorithm hehehe
	//fastest flight is based off of time so I will be using the time of each flight to determine the 
	//most efficient path

	int inf = std::numeric_limits<int>::max();

	//first I need to set the time of all airports to infinity
	for (int i = 0; i < airports.size(); i++) {
		airports.at(i).minutes = inf;
	}

	//now I nee to set the time of the source flight to 0

	airports.at(findorAddAirportIndex(src)).minutes = 0;

	//this priority queue contains a pair of int and string. The int will carry the value
	//of the cost and the string will carry the path yielding that cost.
	// the gretaer comparator turns the max pqueue into a min pqueue

	priority_queue<std::pair<Airport, string>, vector<std::pair<Airport, string>>, CompareTime> pq;

	
	//std::pair<Airport, string>, vector<Airport, string>, CompareTime

	//to help me visualize the algorithm
	std::cout << "CurrentAir ";

	for (int i = 0; i < airports.size(); i++) {
		std::cout << "       " << airports.at(i).airportName << " ";
	}

	std::cout << endl;


	//add source airport to the front of the priority queue
	pq.push(std::make_pair(airports.at(findorAddAirportIndex(src)), airports.at(findorAddAirportIndex(src)).airportName));

	while (!pq.empty())
	{
		//grab the item at the beginning of the queue
		std::pair<Airport, string> currentPair = pq.top();

		Airport currentAir = currentPair.first;
		pq.pop();

		//see if the item is the destination. If so then we are done
		if (currentAir == *dest) {
			std::cout << endl;
			std::cout << "Path: " << currentPair.second << endl;
			std::cout << "Cost: "<< currentAir.minutes << endl;
			break;
		}

		//to help me visualize the algorithm
		std::cout << "       " << currentAir.airportName << " ";

		//find the index of the current airport
		int index = findorAddAirportIndex(&currentAir);

		//find all its neighbors. test to see if their new cost is less than their current cost.
		for (int i = 0; i < airports.size(); i++) {
			
			if (flights[index][i].cost) {//see if a flight exists
				
				//now compare the new cost (vertex cost + edge cost) with the current cost to that airport
				if (airports.at(i).minutes > airports.at(index).minutes + flights[index][i].minutes) {
					//set the new cost
					airports.at(i).minutes = airports.at(index).minutes + flights[index][i].minutes;

					pq.push(std::make_pair(airports.at(i), currentPair.second + " -> " + airports.at(i).airportName));
				}

			}
			
		}

		//to help me visualize the algorithm
		for (int i = 0; i < airports.size(); i++) {
			std::printf("%10d ", airports.at(i).minutes);
		}
		
		std::cout << endl;


	}


	//loop through queue
		//grab the item at the beginning of the queue
		//find all its neighbors. test to see if their new cost is less than their current cost.
		//if so, add them to the pqueue
		// when adding to the pqueue, append the airport's name to the current airport
	//end loop

	//output front of pqueue

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
