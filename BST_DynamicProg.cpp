  /**
   *Finds the optimum Binary Search tree
   *for a given set of probabilites using dynamic programming
   *@author Garrett Money
   *@version April 9, 2018
  */

  #include <cstdint>
  #include <climits>
  #include <cfloat>
  #include <iomanip>
  #include <iostream>
  #include <stdio.h>
  #include "matrix.h"

  using namespace std;

  /**
   *Opt is the main recursive function that fills the root and memo
   *tables
   *@param row is the current row of the table we are on
   *@param col is the current column of the table we are on
   *@param prob is the vector of input probabilities
   *@param memo is the table used to track which subproblems are solved
   *@param root is the table used to show the solution of the optimum
   *@returns the most optimum tree cost as a double
   */
  double opt( size_t row, size_t col, const vector < double > & prob,
	      Matrix < double > & memo, Matrix < uint > & root );
  /**
   *Ouput is the function to print our final answer and two tables
   *@param n is the amount of input we have recieved
   *@param memo is the memo table that we are filling
   *@param root is the root table that we are filling
   */
  void output( uint n, Matrix< double > & memo, Matrix< uint > & root ); 

  /**
   *Main sets up the tables and calls opt to populate
   *the memo table. It then prints the results of that table.
   *@returns 0
   */
  int main()
  {
    uint n = 0;
    double probability;
    vector < double > prob;
    
    //extract our input and fill up a probability vector
    while( cin >> probability )
    {
      n++;
      prob.push_back( probability );
    }

    //declare two matrices to store our dynamic programming results
    Matrix< double > memo ( n, n );
    Matrix< uint > root ( n, n );

    //fill the tables with const MAX values and the base case diagonals
    for( uint row = 0; row < n; row++ )
    {
      for ( uint col = 0; col < n; col ++ )
      {
	if ( row == col )
	{
	  memo.at( row, col ) = prob.at( row );
          root.at( row, col ) = row ;
	}
	else
	{
	  memo.at( row, col ) = DBL_MAX;       
	  root.at( row, col ) = UINT_MAX;
        }
      }
    }
    
    //call the function opt and store the result in lowest_cost
    double lowest_cost = opt( 0, n - 1, prob, memo, root );

    //print output and return 0
    cout << "\nThe lowest-cost tree has a value of " << lowest_cost << "\n\n";
    output( n, memo, root );
    return 0;
  }

  //opt is the function that calls itself recursively and solves
  //subproblems within a memo table (see prototype for more info)
  double opt( size_t row, size_t col, const vector < double > & prob,
	      Matrix< double > & memo, Matrix< uint > & root )
  {
    //check if our cell is not solved
    if( memo.at( row, col ) == DBL_MAX )
    {
      //if 
      if( row >= col )
      {
	return 0;
      }
     
      //calculate the sum of the probabities
      double sum = 0;
      for(size_t input_prob = row; input_prob <= col; input_prob++)
      {
         sum = sum + prob.at( input_prob );
      }
      
      //Collectively calculate the cost of a certain row and cell by
      //recursing through the memo table until a base case is reached
      double memo_minimum = DBL_MAX;
      size_t root_minimum = UINT_MAX;
      size_t n = prob.size(); 

      for(size_t i = row; i <= col; i++)
      {
	double cost = 0.0;
 
        //if i is within the bounds, recurse on the adjacent row
        if( i + 1 < n )
        {
	  cost = cost + opt( i + 1, col, prob, memo, root );
        }
        //if i is within the bounds, recurse on the adjacent col
	if( i > 0 )
        {
	  cost = cost + opt( row, i - 1, prob, memo, root );
        }
        
        //cost so far plus the sum calculated earlier from the probablities
	cost = cost + sum;

        //if the cost is smaller than the current minimum, we have a new minimum
	if( cost < memo_minimum )
	{
	  memo_minimum = cost;
	  root_minimum = i;
        }
      }
      //update our tables with the new minimums
      root.at( row, col ) = static_cast< uint >( root_minimum );
      memo.at( row, col ) = memo_minimum;
    }
    return memo.at( row, col ); 
  }
   
  //output is used to display the tables comuted in opt (see prototype for
  //more info)
  void output( uint n, Matrix< double > & memo, Matrix< uint > & root )
  {
     //display memo header
     cout << "The Completed Memo (main) Table:\n";
     for( uint i = 0; i < n; i++ )
     {
       cout << "\t  " << i;
     }
     cout << endl;
     
     //display cells of memo table
     for(uint i = 0; i < n; i++ )
     {
        cout << i << "\t";
        for(uint j = 0; j < n; j++ )
        {
           //if cell was updated, print the updated number
           if( memo.at( i, j ) != DBL_MAX )
              cout << fixed << setprecision( 2 ) << memo.at( i, j ) << "\t";
           //otherwise, print a dash
           else
              cout << "  -\t";
        }
        cout << endl;
     }
     
     //display root header
     cout << "\n\n\nThe Root Table:\n";
     for( uint i = 0; i < n; i++ )
     {
       cout << "\t" << i;
     }
     cout << endl;
     
     //display root cells
     for(size_t i = 0; i < n; i++ )
     {
        cout << i << "\t";
        for(size_t j = 0; j < n; j++ )
        {
           //if cell was updated, print the updated number
           if( root.at( i, j ) != UINT_MAX )
              cout << root.at( i, j ) << "\t";
           //otherwise, print a dash
           else
              cout << "-\t";
        }
        cout << endl;
     }

  }

