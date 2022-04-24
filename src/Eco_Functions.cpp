#include "../include/Eco_Functions.h"

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


// EFFICIENCY & POWER FUNCTIONS (DANI)
  
double npt(double& velocity){

    double npt = 0.95 - pow(1.2, (-velocity + (log(0.95)/log(1.2))));

    return npt;
}

double Energy(double& velocity){

    double total_energy;
    double dist = 2*1609; // 2 miles converted to meters

    // vehicle parameters
    double g = 9.806; // gravity
    double Aden = 1.225; // air density at sea level in kg/m^3

    double Ppara = 1300; // parasitic power (Watts)
    double mass = 3700 * 0.453592; // Mass of car in kilograms

    double A = 2.22; // frontal area in m^2
    double Cd = 0.23; // drag coefficient

    double npt = npt(velocity);

    // Drag-Area Product
    double CdA = Cd*A;


    // Air drag force equation
    double ADrag = ((1/(2*npt))*(CdA*Aden));

    // Convert mph to m/s
    double Vel = velocity*0.44704;

    // Rolling Resistance equation
    double roll = 0.0075 + (3.078*pow(10,-6)*pow(Vel,2));

    // Air drag portion
    double a = ADrag*pow(Vel,2)*dist;

    // Rolling Resistance portion
    double b = (mass*g)*(roll/npt)*dist;

    // Power portion
    double c = (Ppara/Vel)*dist;

    // Total energy consumption (in watt-seconds)
    total_energy = a + b + c;

    return total_energy/3600000;
}
