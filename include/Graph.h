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
#include "MSTElem.h"
#include <stack>
#include <iostream>
#include <vector>
#include <queue>
#include <unordered_map>

#define VECTOR std::vector
#define STACK std::stack
#define QUEUE std::queue
#define PRIORITY_QUEUE std::priority_queue
#define UNOR_MAP std::unordered_map

template< typename T >
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
		void add_edge(unsigned int origin, unsigned int destin, int weight ){
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
		bool get_edge_value( const unsigned int origin, const unsigned int destin, int& weight){
				
			if( origin < vertices.size() && destin < vertices.size() ){
				
				return vertices[origin].get_edge_value( destin, weight );
			}
			
			return false;
		}
		
		// Set the value at a given origin and destination 
		// bool for if the origin and destination requested were valid
		bool set_edge_value( const unsigned int origin, const unsigned int destin, int weight){
				
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
