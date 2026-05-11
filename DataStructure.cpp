#include <iostream>
#include <string>
#include <limits>
#include "Graph.h" 

using namespace std;

// Array to map integer IDs (1-6) to actual city names.
// Index 0 is left blank to match the 1-based indexing of your graph.
const string cityNames[7] = {
	"",              // 0 (Unused)
	"Seattle",       // 1
	"San Francisco", // 2
	"Los Angeles",   // 3
	"Denver",        // 4
	"Chicago",       // 5
	"New York"       // 6
};

// Helper function to display the list of cities
void DisplayCityOptions() {
	cout << "\n--- Available Cities ---\n";
	for (int i = 1; i <= 6; i++) {
		cout << "[" << i << "] " << cityNames[i] << "\n";
	}
	cout << "------------------------\n";
}

int main() {
	try {
		// 1. Initialize the Graph (6 cities, undirected roads)
		int numberOfCities = 6;
		Graph cityMap(numberOfCities, false);

		// 2. Add roads between cities (City A ID, City B ID, Distance in hours)
		// Shifted from 0-based to 1-based indexing
		cityMap.AddEdge(1, 2, 4);  // Seattle (1) to San Francisco (2)
		cityMap.AddEdge(1, 3, 4);  // Seattle (1) to Los Angeles (3)
		cityMap.AddEdge(2, 3, 2);  // San Francisco (2) to Los Angeles (3)
		cityMap.AddEdge(2, 4, 5);  // San Francisco (2) to Denver (4)
		cityMap.AddEdge(3, 4, 8);  // Los Angeles (3) to Denver (4)
		cityMap.AddEdge(3, 5, 2);  // Los Angeles (3) to Chicago (5)
		cityMap.AddEdge(4, 5, 3);  // Denver (4) to Chicago (5)
		cityMap.AddEdge(4, 6, 6);  // Denver (4) to New York (6)
		cityMap.AddEdge(5, 6, 5);  // Chicago (5) to New York (6)

		int choice = 0;
		int startCity = 0;

		cout << "Welcome to the Interactive City Routing System!\n";

		// 3. Main Application Loop
		while (choice != 5) {
			cout << "\n=============================================\n";
			cout << "                 MAIN MENU                   \n";
			cout << "=============================================\n";
			cout << "1. View all current routes (Full Map)\n";
			cout << "2. Find shortest paths from a specific city (GPS/Dijkstra)\n";
			cout << "3. Calculate cheapest network to connect all cities (Kruskal)\n";
			cout << "4. Explore neighboring cities step-by-step (BFS)\n";
			cout << "5. Exit System\n";
			cout << "=============================================\n";
			cout << "Enter your choice (1-5): ";

			cin >> choice;

			// Handle invalid input (e.g., typing letters instead of numbers)
			if (cin.fail()) {
				cin.clear();
				cin.ignore(numeric_limits<streamsize>::max(), '\n');
				cout << "Invalid input. Please enter a number.\n";
				continue;
			}

			switch (choice) {
			case 1:
				cout << "\n[Displaying All Available Routes]\n";
				cityMap.PrintGraph();
				break;

			case 2:
				DisplayCityOptions();
				cout << "Enter the ID of your starting city (1-6): ";
				cin >> startCity;
				if (startCity >= 1 && startCity <= 6) {
					cout << "\n[Calculating Shortest Paths from " << cityNames[startCity] << "]\n";
					Graph shortestPaths = cityMap.DijkstraSPT(startCity);
					shortestPaths.PrintGraph();
				}
				else {
					cout << "Invalid city ID! Must be between 1 and 6.\n";
				}
				break;

			case 3:
				cout << "\n[Calculating Minimum Cost to Connect All Cities]\n";
				cout << "Building Fiber Optic Network...\n";
				{
					Graph networkCables = cityMap.KruskalMST();
					networkCables.PrintGraph();
				}
				break;

			case 4:
				DisplayCityOptions();
				cout << "Enter the ID of your starting city (1-6): ";
				cin >> startCity;
				if (startCity >= 1 && startCity <= 6) {
					cout << "\n[Exploring outward from " << cityNames[startCity] << "]\n";
					cout << "City IDs visited in order: ";
					cityMap.BFS(startCity);
				}
				else {
					cout << "Invalid city ID! Must be between 1 and 6.\n";
				}
				break;

			case 5:
				cout << "Exiting system. Have a safe trip!\n";
				break;

			default:
				cout << "Invalid choice! Please select a number between 1 and 5.\n";
				break;
			}
		}
	}
	// Catch the exceptions thrown by your Graph implementation!
	catch (const std::exception& e) {
		cerr << "\n[ERROR] " << e.what() << "\n";
	}

	return 0;
}