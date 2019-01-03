  /**
   *Finds the MST @author Jon Beck
   *Computes the twice around algorithm to find
   *a hamiltonian circuit using MST
   *@author Garrett Money
   *@version May 8, 2018
  */

#include <climits>
#include <cstdint>
#include <iostream>
#include <list>
#include <vector>
#include "graph_helpers.h"

using namespace std;

/**
 *This function takes multiple parameters and runs through the edges
 *of a given vertex. If we haven't seen it, we add it to our hamiltonian
 *vector and mark it as read
 *
 *@param source_graph the current graph being passed
 *@param edge the edge we are iterating on
 *@param hamiltonian the vector we are storing our progress in
 *@param length the combined weights of our progress
 *@param read which vertices we have read
 *@param found informs of a hit
 *@param vertex the current vertex we are on
 */
void insertHamil( vector< list< Edge >> &source_graph,
	     list< Edge >::iterator &it, size_t &edge,
	     vector < uint > &hamiltonian, uint &length,
	     vector <bool> &read, bool &found, size_t &vertex );

/**
 *This prints out our calculated path and total weight of path
 *
 *@param hamil is the hamiltonian circuit we have calculated
 *@param length is the total weight of the hamiltonian path
 */
void print( vector <uint> hamil, uint length);

int main ()
{

  vector< list < Edge >> graph;
  vector< Edge > all_edges;

  read_adjacency_lists( graph, all_edges);
  print_graph( graph );

  // implement prim's algorithm for mst, hard-coded to start at vertex 0
  vector< list< Edge >> mst;
  vector< bool > known;

  for( size_t i = 0; i < graph.size(); i++ )
  {
    list< Edge > empty_list;
    mst.push_back( empty_list );
    known.push_back( false );
  }

  known.at( 0 ) = true;

  Edge max_weight_edge;
  max_weight_edge.start_vertex = UINT_MAX;
  max_weight_edge.end_vertex = UINT_MAX;
  max_weight_edge.weight = UINT_MAX;

  // do this once for each vertex after 0
  // i is irrelevant
  for( size_t i = 1; i < graph.size(); i++ )
  {
    // get shortest-distance edge from known to unknown vertices
    Edge shortest_edge = max_weight_edge;
    for( auto edge : all_edges )
    {
      if( known.at( edge.start_vertex )
          && !known.at( edge.end_vertex)
          && edge < shortest_edge )
      {
        shortest_edge = edge;
      }
    }

    // add this edge and its reverse to mst
    Edge other_direction;
    other_direction.start_vertex = shortest_edge.end_vertex;
    other_direction.end_vertex = shortest_edge.start_vertex;
    other_direction.weight = shortest_edge.weight;

    mst.at( shortest_edge.start_vertex ).push_back( shortest_edge );
    mst.at( shortest_edge.end_vertex ).push_back( other_direction );
    known.at( shortest_edge.end_vertex ) = true;

    // go through and remove all edges from a known to a known vertex
    // this is not essential but results in fewer basic operations
    vector< Edge > edges_to_keep;
    for( auto edge : all_edges )
    {
      if( !known.at( edge.start_vertex ) || !known.at( edge.end_vertex ))
      {
        edges_to_keep.push_back( edge );
      }
    }
    all_edges = edges_to_keep;
  }
  
  //---------------STEPS TWO AND THREE OF TWICE AROUND----------------
  
  //used to track iterations we have read
  vector <bool> read;

  //used to store final hamiltonian circuit
  vector < uint > hamiltonian;
  uint length = 0;

  //initialize
  hamiltonian.push_back( mst.at( 0 ).begin()->start_vertex );

  //initialize what we have read to nothing/false
  for( size_t vert = 0; vert < mst.size(); vert++)
  {
    //we know the first one
    if( vert == 0 )
      read.push_back( true );
    else
      read.push_back( false );
  }

  //run through mst and create the circuit
  for( size_t vert = 0; vert < mst.size(); vert++ )
  {
    //list of edge iterators for mst and graph
    list< Edge >::iterator graph_iterator = graph.at( vert ).begin();
    list< Edge >::iterator mst_iterator = mst.at( vert ).begin();

    //keeps track of edge and hit
    bool hit = false;
    size_t edge = 0;

    //run through edges
    insertHamil( mst, mst_iterator, edge, hamiltonian, length, read,
		 hit, vert );
    if( hit == false )
    {
      insertHamil( graph, graph_iterator, edge, hamiltonian, length, read,
		   hit, vert );
    }
  }

  //add the edge 
  list< Edge >::iterator it = graph.at( graph.size() - 1 ).begin();
  while( it->end_vertex != hamiltonian.at( 0 ) )
  {
    it++;
  }
  length = length + it->weight;
  hamiltonian.push_back( it->end_vertex );

  //print the results
  print( hamiltonian, length );
  return 0;
}

void insertHamil( vector< list< Edge >> &source_graph,
	     list< Edge >::iterator &it, size_t &edge,
	     vector < uint > &hamil, uint &length,
	     vector <bool> &read, bool &found, size_t &vertex )
{
   for(; edge < source_graph.at( vertex ).size(); edge++)
   {
      //if it's new, add it and mark it as read, then add the weight
      if( read.at( it->end_vertex ) == false )
      {
         hamil.push_back( it->end_vertex );
	 found = true;
         read.at( it->end_vertex ) = true;
	 length = length + it->weight;
         break;
      }
      it++;
   }
}

void print( vector <uint> hamil, uint length)
{
   cout << "Hamiltonian circuit: ";
   for( size_t i = 0; i < hamil.size(); i++)
   {
     if( i == hamil.size() - 1 )
       cout << " " << hamil.at( i );
     else
       cout << " " << hamil.at( i ) << ",";
   }
   cout << "\ncircuit length: " << length << endl;
}
