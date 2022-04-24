#include "../include/Graph.h"
#include "../include/Edge.h"
#include "../include/Vertex.h"
#include "../include/MapElem.h"
#include<string.h>
#include <fstream>

/* reads in a csv file and fills a vector with values */
void parse_input(std::string path, VECTOR< MapElem >& MapElems) {
    std::ifstream infile( path );

    std::string origin = ("");
    std::string destination = ("");
    std::string sp_lim = ("");

    while(infile >> origin >> destination >> sp_lim) {
        MapElems.push_back( MapElem((unsigned) stoi(origin), (unsigned) stoi(destination), (double) stoi(sp_lim)) );
        
        
        //COUT << "Line: " << origin << ", "<< destination << ", "<< sp_lim << ENDL;

    }
}

/* creates a graph of the map to be traversed */
void create_map(VECTOR <MapElem>& MapElems, Graph<int>& map) {

    unsigned int i, origin, destination, s_lim, o_index, d_index;

    int weight = 0;

    /* iterate through all elements */
    for (i = 0; i < MapElems.size(); i++) {  
        origin = MapElems[i].origin;
        destination = MapElems[i].destination;
        s_lim = MapElems[i].speed_limit;

        if (map.check_val(map, origin)) {
            map.add_vertex(origin);
        }

        if (map.check_val(map, destination)) {
            map.add_vertex(destination);
        }

        o_index = map.get_index(origin);
        d_index = map.get_index(destination);

        if(!map.get_edge_value(o_index, d_index, weight) && o_index != d_index) {
            map.add_edge(o_index, d_index, s_lim); 
            map.add_edge(d_index, o_index, s_lim);
        }
    }
    return;
}
