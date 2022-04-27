/* Eco_Routing.cpp
 * This is the main driver for the code that we have created.
 * We will demonstrate our application of Dijkstra's algorithm,
 * and how we modified edge weights to account for fuel efficiency.
 * The program prints out the final most 'fuel-efficient' path.
 *
 * Creators: Claudia Kuczun, Dani Nah, Sam Webster
 * Date created: April 22, 2022
 */


#include "../include/Eco_Functions.h"

int main(int argc, char* argv[]) {

	printf("<<< Eco Routing Simulation >>> \n");
	std::cout << std::endl;

	if (argc != 2) {
        COUT << "Usage: ./exe/PC07 [filename]" << ENDL;
        return 1;
    }

	// Initialize variables
  VECTOR< MapElem > MapElems;
	Graph<int> map;
	unsigned int origin, destin;

	// Parse input txt file
	parse_input(argv[1], MapElems);

	// Create our map
  map.create_map(MapElems);

	// Print Adjacency List
	// map.print_graph();

	// Get user input
	printf("Please enter your starting location: ");
	scanf("%u", &origin);
	std::cout << std::endl;
	printf("Please enter your destination location: ");
	scanf("%u", &destin);
	std::cout << std::endl;
	std::cout << "----------------------------------------------------------------------" << std::endl;
	std::cout << std::endl;

	// Output result
	std::cout << "The most energy efficient route to from location " << origin << " to location " << destin << " is: \n";

	std::cout << std::endl;

	// Find Most Energy Efficieny Route
	map.Dijkstra(origin, destin);

	return 0;

}
