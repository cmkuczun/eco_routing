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

	if (argc != 2) {
        COUT << "Usage: ./exe/PC07 [filename]" << ENDL;
        return 1;
    }

  VECTOR< MapElem > MapElems;
	Graph<int> map;

	// Create our map
	parse_input(argv[1], MapElems);

  map.create_map(MapElems);

	map.print_graph();

	// Get user input

	// Test
	unsigned int origin = 1;
	unsigned int destin = 4;

	// Output result
	std::cout << "The most energy efficient route to from the location " << origin << " to your destination, location " << destin << ", is: \n";

	map.Dijkstra(1, 4);

	return 0;
}
