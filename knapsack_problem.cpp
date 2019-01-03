/**
 * a framework for exhaustive-search discrete knapsack 
 * @author originally written by Jon Beck
 * @author modified by Garrett Money
 * @version date February 28, 2018
 */

#include <cstdint>
#include <climits>
#include <iomanip>
#include <iostream>
#include <vector>
using namespace std;


/**
 * raise an unsigned integer to an unsigned power
 * C++ has pow, but it accepts and returns floating point values
 * @param base the base to be raised to a power
 * @param exp the exponent to which to reaise the base
 * @return base ^ exp
 */
uint ipow( uint base, ulong exp );

/*
 * standard input must be of the form
 * capacity
 * weight value
 * weight value
 * ...
 */
int main()
{
  uint capacity;
  cin >> capacity;
  uint basic_operation = 0;

  vector< uint > weights;
  vector< uint > values;

  while( !cin.eof() )
  {
    uint weight;
    uint value;
    cin >> weight >> value;
    if( !cin.eof() )
    {
      weights.push_back( weight );
      values.push_back( value );
    }
  }

  ulong size = weights.size();
  uint permutations = ipow(2,size);

  //generate the amount of permutations based off of input with 2^n
  for(uint perm_count = 0; perm_count < permutations; perm_count++)
  {
    uint total_weight = 0, total_value = 0, current_item = 0;
    cout << "{ ";

    /* decide which items are in the permuation indicated by a bit = 1
     * and then calculate accordingly
     */
    for ( uint item_count = perm_count; item_count > 0; item_count >>= 1 )
    {
      uint bit = item_count % 2;
      if( bit == 1 )
      {
        total_weight = total_weight + weights.at( current_item );
	total_value = total_value + values.at( current_item );
        cout << current_item << " ";
      }
      basic_operation++;
      current_item++;
    }

    //formatting for columns
    cout << "}";
    if( perm_count == 0 )
    {
      cout.width( 14 );
    }
    else
    {
      cout.width( 12 );
    }
    cout << "\t" << total_weight;
    cout.width( 4 );
    cout << "\t";

    //check if weight is under capacity 
    if( total_weight <= capacity )
    { 
      cout << right << total_value << endl;
    }
    else
    {
      cout<< right << "NF" << endl;
    }
  }
  //print the size of inputs followed by a count of the basic operation
  cerr << values.size() << "\t" << basic_operation << endl;   
}

uint ipow( uint base, ulong exp )
{
  if( base == 0 )
    return 1;
  uint result = 1;
  while( exp > 0 )
  {
    if( (exp & 1) == 1 )
      result *= base;
    exp >>= 1;
    base *= base;
  }
  return result;
}
