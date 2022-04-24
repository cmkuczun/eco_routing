#include "./Graph.h"
#include <string.h>
#include <fstream>
#include "MapElem.h"


// Read in a csv file and fill a vector with values
void parse_input(std::string path, VECTOR< MapElem >& MapElems);

// Create a graph of the map to be traversed
void create_map(VECTOR <MapElem>& MapElems, Graph<int>& map);

// Powertrain Efficiency function
double npt(double velocity);

// Total energy consumption function
double Energy(double velocity);
