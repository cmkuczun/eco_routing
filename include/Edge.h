/* Edge.h
 * This is the Edge struct that will be utilized in our program.
 * Date created: April 11, 2022
 * Creators: Claudia Kuczun, Dani Nah, Sam Webster
 *
 * Originally provided to us by:
 *    Author: Matthew Morrison
 *    Email: matt.morrison@nd.edu
 */

#ifndef EDGE_H
#define EDGE_H

struct Edge{
	
	unsigned int destin;	// Location of Edge Destination
	int weight;				// Edge Weight. Can be negative.

	// Default Constructor
	Edge() : destin(), weight( ) {}

	// Overloaded Constructor
	Edge( unsigned int dest, int weightIn ) : destin(dest), weight(weightIn) {}
	
	// Overloaded == operator
	bool operator==( const Edge& rhs ) const{
		
		return destin == rhs.destin && weight == rhs.weight;
		
	}
};

#endif
