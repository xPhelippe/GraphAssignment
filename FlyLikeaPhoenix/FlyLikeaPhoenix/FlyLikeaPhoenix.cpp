// FlyLikeaPhoenix.cpp : This file contains the 'main' function. Program execution begins and ends there.
//


#include "pch.h"
#include <iostream>
#include "Route.h"
#include "Airport.h"

int main()
{

	Route* flightRoutes = new Route(10);

	Airport* airports[10];


	airports[0] = new Airport(0, "MCO");
	airports[1] = new Airport(1, "ATL");
	airports[2] = new Airport(2, "LAX");
	airports[3] = new Airport(3, "ORD");
	airports[4] = new Airport(4, "DFW");
	airports[5] = new Airport(5, "DEN");
	airports[6] = new Airport(6, "JFK");
	airports[7] = new Airport(7, "SEA");
	airports[8] = new Airport(8, "LAS");
	airports[9] = new Airport(9, "EWR");

	flightRoutes->addFlight(new Flight(airports[0], airports[1], 100, 170, 441));
	flightRoutes->addFlight(new Flight(airports[0], airports[2], 330, 227, 2218));
	flightRoutes->addFlight(new Flight(airports[2], airports[3], 242, 113, 1742));
	flightRoutes->addFlight(new Flight(airports[1], airports[4], 147, 149, 731));
	flightRoutes->addFlight(new Flight(airports[4], airports[5], 126, 65, 641));
	flightRoutes->addFlight(new Flight(airports[5], airports[8], 116, 120, 628));
	flightRoutes->addFlight(new Flight(airports[8], airports[9], 297, 125, 2227));
	flightRoutes->addFlight(new Flight(airports[7], airports[9], 311, 269, 2396));
	flightRoutes->addFlight(new Flight(airports[0], airports[7], 347, 362, 3075));
	flightRoutes->addFlight(new Flight(airports[0], airports[5], 260, 157, 1546));
	flightRoutes->addFlight(new Flight(airports[6], airports[7], 327, 237, 2415));
	flightRoutes->addFlight(new Flight(airports[3], airports[7], 278, 173, 1716));

	flightRoutes->printNetwork();
	std::cout << endl;
	flightRoutes->DFS(airports[5]);
	std::cout << endl;

}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
