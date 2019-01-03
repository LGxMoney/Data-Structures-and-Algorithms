#ifndef MONEY_PQ
#define MONEY_PQ

#include <cassert>
#include <cstdint>
#include <climits>
#include <vector>

/**
 * Provide a Heap datastructure to represent a priority queue using a vector.
 * This implementation also provides a field for counting basic operations.
 * @author Garrett Money
 * @version March 6 2018
 */
class PQ
{
 public:
  /**
   * Construct an empty priority queue
   */
 PQ() : op_count{ 0 }{}

  /**
   * Insert a priority into the PQ and sort it into a 
   * using bubble_up
   * @param priority the priority of the inserted job
   */
  void insert( uint priority )
  {
    array.push_back( priority );

    //calculate size and send to index to find its place
    uint current_index = array.size() - 1;
    bubble_up( current_index );
  }

  /**
   * Takes the top node off of the heap by swaping the
   * lowest child in the tree and popping off of the queue.
   * @return the priority of the removed job
   */
  uint remove()
  {
    //variables to keep track of indexes
    uint first_index = 0;
    uint highest_priority = array.at( first_index );
    uint youngest_child = array.size() - 1;

    //check for last node and proceed to swap, pop, and bubble down
    if( first_index != youngest_child )
    {
      swap ( first_index, youngest_child );
      array.pop_back();
      bubble_down( first_index );
      return highest_priority;
    }
    //if last node, just pop and return
    array.pop_back();
    return highest_priority;
  }

  /**
   * Report if the queue is empty
   * @return true if empty, false otherwise
   */
  bool is_empty() const
  {
    return array.empty();
  }

  /**
   * Return the number of basic operations counted so far
   * @return the count of basic operations
   */
  size_t get_op_count() const
  {
    return op_count;
  }
 
      
 private:
  std::vector< uint > array;
  size_t op_count;

  /**
   * Method used to swap data priority data based off of index
   * @param pos1_index is used to track index of first element to swap
   * @param pos2_index is used to track idnex of second element to swap
   */
  void swap ( uint pos1_index, uint pos2_index )
  {
    //check if swapping is redundant
    if( pos1_index == pos2_index)
      return;

    uint temp = array.at( pos1_index );
    array.at( pos1_index ) = array.at( pos2_index );
    array.at( pos2_index ) = temp;
    return;
  }

  /**
   * Takes an index and checks to see if it has a parent. If it does
   * proceed to calculate and return, if not, return -1.
   * @return the integer representation of the parent index
   */
  int find_parent ( uint index )
  {
    int parent = 0;
    if( index == 0 )
    {
      parent = -1;
      return parent;
    }
    else
    {
      parent = ( index - 1 )/2;
      return parent;
    }
  }

  /**
   * Calculates where the left child is
   * @param index looks for the left child of the indicated index
   * @return returns the int representation of the left child index
   */
  int find_left_child( uint index )
  {
    int child_index = 2 * index + 1;
    
    if( child_index > array.size() - 1)
      return -1;
    else
      return child_index;
  }

  /**
   * Calculates where the right child is
   * @param index looks for the right child of the indicated index
   * @return returns the int representation of the right child index
   */
  int find_right_child( uint index )
  {
    int child_index = 2 * index + 2;
    
    if(child_index > array.size() - 1)
      return -1;
    else
      return child_index;
  }

  /**
   * Recursive algorithm to percolate up a node that has just been inserted
   * Checks if parent is in correct position and if not, adjusts 
   * accordingly with swap
   * @param index is the index that will be percolating up through the heap
   */
  void bubble_up ( uint index )
  {
    op_count++;
    int parent = find_parent( index );
    
    if( parent < 0 )
    {
      return;
    }
    if( array.at( index ) >= array.at( parent ))
    {
      return;
    }
    while( array.at( index ) < array.at( parent ))
    {
      swap( index, parent );
      bubble_up ( parent );
    }
  }

  /**
   * Recursive algorithm to adjust the heap after moving the bottom-most 
   * child to the first index of the array. Looks at children and finds
   * the most optimal child to swap with.
   * @param index is the index that will be percolating down through the heap
   */
  void bubble_down( uint index )
  {
    op_count++;
    int left_child = find_left_child( index );
    int right_child = find_right_child( index );
    int optimal_swapping_child = 0;

    if( left_child == -1 && right_child == -1 )
      return;
    
    if( right_child == -1 && array.at( index ) < array.at( left_child ) )
      return;
    
    if( right_child != -1 && left_child != -1 )
    {
       if( array.at( index ) < array.at( right_child ) && array.at( index )
          < array.at( left_child ) )
         return;
       if( std::min( array.at( left_child ), array.at( right_child ) ) ==
	   array.at( left_child ) )
          optimal_swapping_child = left_child;
       else
          optimal_swapping_child = right_child;
       while( array.at( index ) > array.at( optimal_swapping_child ) )
       {
         swap ( index, optimal_swapping_child );
         bubble_down ( optimal_swapping_child );
       }
     }
  }
};
#endif


