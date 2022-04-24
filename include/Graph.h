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
#include "MapElem.h"
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
		void add_edge(unsigned int origin, unsigned int destin, double weight ){
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
		bool get_edge_value( const unsigned int origin, const unsigned int destin, double& weight){

			if( origin < vertices.size() && destin < vertices.size() ){

				return vertices[origin].get_edge_value( destin, weight );
			}

			return false;
		}

		// Set the value at a given origin and destination
		// bool for if the origin and destination requested were valid
		bool set_edge_value( const unsigned int origin, const unsigned int destin, double weight){

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
		bool check_val(T val){

		  bool check = true;

		  for (size_t i = 0; i < vertices.size(); i++) {
		    if (vertices.at(i).get_vertex_value() == val) {
		      check = false;
		    }
		  }
		  return check;
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


		void create_map(VECTOR <MapElem>& MapElems) {

		    unsigned int i, origin, destination, o_index, d_index;
				double s_lim;

		    double weight = 0;

		    /* iterate through all elements */
		    for (i = 0; i < MapElems.size(); i++) {
		        origin = MapElems[i].origin;
		        destination = MapElems[i].destination;
		        s_lim = MapElems[i].speed_limit;

		        if (check_val(origin)) {
		            add_vertex(origin);
		        }

		        if (check_val(destination)) {
		            add_vertex(destination);
		        }

		        o_index = get_index(origin);
		        d_index = get_index(destination);

		        if(!get_edge_value(o_index, d_index, weight) && o_index != d_index) {
		            add_edge(o_index, d_index, s_lim);
		            add_edge(d_index, o_index, s_lim);
		        }
		    }
		    return;
		}

		// EFFICIENCY & POWER FUNCTIONS (DANI)

		double efficiency(double velocity){

		    double npt = 0.9 - pow(1.3, (-velocity + (log(0.9)/log(1.3))));

		    return npt;
		}

		double Energy(double velocity){

		    double total_energy;
		    double dist = 2*1609; // 2 miles converted to meters

		    // vehicle parameters
		    double g = 9.806; // gravity
		    double Aden = 1.225; // air density at sea level in kg/m^3

		    double Ppara = 1300; // parasitic power (Watts)
		    double mass = 3700 * 0.453592; // Mass of car in kilograms

		    double A = 2.22; // frontal area in m^2
		    double Cd = 0.23; // drag coefficient

		    double npt = efficiency(velocity);

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
    parents[origin] = (unsigned int) -1;

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

      while((int) parents[sentinel] != -1 ){

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
