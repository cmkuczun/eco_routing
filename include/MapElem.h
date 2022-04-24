#ifndef MAPELEM_H
#define MAPELEM_H

/* map element struct for storing our node data */ 
struct MapElem {
    unsigned int origin;
    unsigned int destination;
    double speed_limit;
    MapElem(unsigned int o, unsigned int d, double sl)
    {
        origin = o;
        destination = d;
        speed_limit = sl;
    }
};

#endif
