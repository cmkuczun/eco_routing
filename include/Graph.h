/* Graph.h
 * This is the Graph struct that will be utilized in our program.
 * Creators: Claudia Kuczun, Dani Nah, Sam Webster
 * Date created: April 11, 2022
 *
 * Originally provided to us by:
 *    Author: Matthew Morrison
 *    Email: matt.morrison@nd.edu
 */


#ifndef GRAPH_H
#define GRAPH_H

#include "Vertex.h"
#include "Eco_Functions.h"
#include <stack>
#include <iostream>
#include <vector>
#include <queue>
#include <unordered_map>
#include <limits> 
#include <cmath>

#define VECTOR std::vector
#define STACK std::stack
#define QUEUE std::queue
#define PRIORITY_QUEUE std::priority_queue
#define UNOR_MAP std::unordered_map

template< typename T>
struct Graph{
	
	private:
	
		VECTOR< Vertex< T > > vertices;	// Adjacency List
	
	public:
		// Constructor
		Graph( ) : vertices() {}
		
		// Destructor
		~Graph( ) { }
		
		// Add a vertex prior to any edges
		void add_vertex( const T& vertexData ){
			
			Vertex<T> theVertex( vertexData );
			vertices.push_back( theVertex );
		}
		
		// Add Edge from Origin to Destination, with weight
		void add_edge(unsigned int origin, unsigned int destin, T weight ){
			if( origin < vertices.size() && destin < vertices.size() ){
			
				vertices[origin].add_edge( destin, weight );
		
			}
		}
		
		// Return the value with a Call by Reference
		// bool for if the vertex requested was valid
		bool get_vertex_value( const unsigned int vertex, T& value ){
			
			if( vertex < vertices.size() ){
				
				value = vertices.at(vertex).get_vertex_value();
				return true;
			}
			
			return false;
			
		}
		
		// Set the value at a given vertex 
		// bool for if the vertex requested was valid
		bool set_vertex_value( const unsigned int vertex, T& value ){
						
			if( vertex < vertices.size() ){
				
				value = vertices[vertex].set_vertex_value( value );
				return true;
			}			
			return false;
		}
		
		// Return the value with a Call by Reference
		// bool for if the origin and destination requested were valid
		bool get_edge_value( const unsigned int origin, const unsigned int destin, T& weight){
				
			if( origin < vertices.size() && destin < vertices.size() ){
				
				return vertices[origin].get_edge_value( destin, weight );
			}
			
			return false;
		}
		
		// Set the value at a given origin and destination 
		// bool for if the origin and destination requested were valid
		bool set_edge_value( const unsigned int origin, const unsigned int destin, T weight){
				
			if( origin < vertices.size() && destin < vertices.size() ){
				
				return vertices[origin].set_edge_value( destin, weight );
			}
			
			return false;
		}
		
		// Remove an edge
		bool remove_edge( unsigned int origin, unsigned int destin){
				
			// If the origin and destination are valid
			if( origin < vertices.size() && destin < vertices.size() ){
				
				// From the Origin vertex, remove the destination vertex
				return vertices[origin].remove_edge( destin );
			}
			
			return false;
		}
		
		
		void remove_vertex( unsigned int vertVal ){
			
			// First, perform Lazy Deletion on the vertex 
			vertices[ vertVal ].lazy_delete();
			
			// Next, go through each vertex and remove all edges with the destination to the vertex 
			for( unsigned int iter = 0; iter < vertices.size(); iter++ ){
				
				int jter = 0;
				
				// While the increment is less than the number of edges
				while( jter < vertices[iter].num_edges() ){
					
					// If the destination of the edge is the vertex we are removing
					if( vertices[iter].get_edge( jter ).destin == vertVal ){
						
						// Remove that edge
						vertices[iter].remove_edge( vertVal );
					}
					else{
						// Only increment jter is there is not any deletion
						jter++;
					}
				}
			}
		}

		// Check if the value given is already in the graph (so we don't add duplicate vertices)
		bool check_val(Graph<T>& theGraph, T val){

		  bool check = true;

		  for (size_t i = 0; i < theGraph.vertices.size(); i++) {
		    if (theGraph.vertices.at(i).get_vertex_value() == val) {
		      check = false;
		    }
		  }
		  return check;
		}

		// A function to create our graph given an vector of inputs
		void create_graph( VECTOR< VECTOR<T> >& routes, Graph<T>& theGraph){

		  // Add all of the vertices (making sure we check that there are no duplicate vertices)
		  for (int i = 0; i < routes.size(); i++) {
		    for (int j = 0; j < routes[i].size(); j++) {
		      if (theGraph.check_val(theGraph, routes[i][j]) == true) {
		        theGraph.add_vertex( routes[i][j] );
		      }
		    }
		  }

		  // Add edges
		  for (int k = 0; k < routes.size(); k++) {
		    for (int m = 0; m < routes[k].size()-1; m++) {

					// Get the index of the value
		      unsigned int destin = get_index(routes[k][m+1]);
		      unsigned int origin = get_index(routes[k][m]);

					// Check if it is already in adjacency list
					for (unsigned int i = 0; i < theGraph.vertices.size(); i++) {
						if (theGraph.vertices[origin].check_edge_destin(destin) == false) {
							theGraph.add_edge(origin, destin, 1);
						}
					}


		    }
		   }

		}

		// Get vertex index from vertex data
		unsigned int get_index(T val) const{

			unsigned int index = 0;

			for (unsigned int i = 0; i < vertices.size(); i++) {
				if ( vertices.at(i).get_vertex_value() == val ) {
					index = i;
				}
			}
			return index;
		}



	// EFFICIENCY & POWER FUNCTIONS (DANI)
		
    // Powertrain Efficiency function
  double npt(T& velocity){

    double npt = 0.95 - pow(1.2, (-velocity + (log(0.95)/log(1.2))));

    return npt;
  }

    // Total energy consumption function
  double Energy(T& velocity){

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

    // Dijkstra's Algorithm
  void Dijkstra( unsigned int origin, unsigned int destin ){


    if( origin >= vertices.size() || destin >= vertices.size() || vertices.size() == 0 ){

      std::cout << "Invalid Inputs" << std::endl;
      return;

    }

    // Infinity
    double inf = std::numeric_limits<double>::infinity();

    /* Initialize the Elements */
    PRIORITY_QUEUE< unsigned int > the_PQ;
    VECTOR< unsigned int > parents( vertices.size(), -1 );
    VECTOR< double > distance( vertices.size(), inf );
    STACK< unsigned int > finalPath;

    bool found = false;

    /* Initialize the origin */
    the_PQ.push( origin );
    distance[origin] = 0;
    parents[origin] = -1;

    if( destin == origin ){
      found = true;
    }

    if( !found ){

      /* Run the shortest path algorithm */
      while( !the_PQ.empty() ){

        // Get the top element of the stack and pop
        unsigned int index = the_PQ.top();
        the_PQ.pop();

        // Evaluate the edges from the vertex
        for(unsigned int iter = 0; iter < vertices[ index ].num_edges(); iter++ ){

          // Obtain the edge
          Edge tempEdge = vertices[ index ].get_edge( iter );

          // If the weight of the edge plus distance of the  distance is less than the destin weight
          if( distance[ index ] + Energy(tempEdge.weight) < distance[ tempEdge.destin ] ) {

            // Update the distance
            distance[ tempEdge.destin ] = distance[ index ] + Energy(tempEdge.weight);

            // Update the parent of the destin
            parents[ tempEdge.destin ] = index;

            // Check if destin is the result;
            if( tempEdge.destin == destin && !found ){

              found = true;
            }

            the_PQ.push( tempEdge.destin );
          }
        }
      }
    }

    // Otherwise, go through the parents until we find the origin
    if( found ){

      unsigned int sentinel = destin;
      finalPath.push( sentinel );		// Push the desination onto the stack

      while( parents[sentinel] != -1 ){

        finalPath.push( parents[sentinel] );	// Push the parent onto the stack
        sentinel = parents[sentinel];			// Update the sentinel

      }

      // Stack contains the correct order
      std::cout << "The valid Dijkstra path from 0 to " << destin << " is: ";
      while( !finalPath.empty() ){

        std::cout << finalPath.top() << " ";
        finalPath.pop();
      }
      std::cout << ", and the distance is " << distance[destin] << std::endl;
      std::cout << std::endl;
    }

  }

};

#endif
