#ifndef ECO_FUNCTIONS_H
#define ECO_FUNCTIONS_H

#include <string>
#include <fstream>
#include <vector>
#include "Graph.h"


// Read in a csv file and fill a vector with values
void parse_input(std::string path, std::vector< MapElem >& MapElems);

#endif
