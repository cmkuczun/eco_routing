#include "../include/Eco_Functions.h"

void parse_input(std::string path, std::vector< MapElem >& MapElems) {
    std::ifstream infile( path );

    std::string origin = ("");
    std::string destination = ("");
    std::string sp_lim = ("");

    while(infile >> origin >> destination >> sp_lim) {
        MapElems.push_back( MapElem((unsigned) stoi(origin), (unsigned) stoi(destination), (double) stoi(sp_lim)) );


        //COUT << "Line: " << origin << ", "<< destination << ", "<< sp_lim << ENDL;

    }
}
