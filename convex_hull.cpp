/**
 * brute-force convex hull algorithm from Levitin chapter 3
 *
 * input: space-separated pairs of integer coordinates on the x-y plane,
 * one pair per line
 *
 * output: a line on cout consisting of the pairs that form the convex
 * hull of the input, with x and y coordinates separated by a comma
 * and pairs separated by space
 *
 * @author Jon Beck
 * @author Garrett Money
 * @version 1/22/2018
 */

#include <cassert>
#include <cstdint>
#include <iostream>
#include <vector>

using namespace std;

/**
 * Takes a vector of x coordinates and a vector of y coordinates. The
 * function proceeds to test every combination of two points, forming a 
 * line segment to see if there are any points outside of the line. If
 * there are none, it will store those points in the convex hull point
 * vector
 * @param xcoords stores the x values in a vector
 * @param ycoords stores the y values in a vector
 * @param chpoints stores the points that are in the convex hull
 */
uint find_convex_hull( const vector< int > & xcoords,
                       const vector< int > & ycoords,
                       vector< bool > & chpoints );

int main()
{
  vector< int > xcoords; // the x-coordinates
  vector< int > ycoords; // the y-coordinates

  uint basicOps = 0;

  uint n = 0;
  while( ! cin.eof() )
  {
    int value;
    if( cin >> value && ! cin.eof() )
    {
      xcoords.push_back( value );
      cin >> value;
      ycoords.push_back( value );
      n++;
    }
  }

  // a boolean array that states whether the point is in the convex
  // hull or not. start with all points not in the hull
  vector< bool > chpoints( xcoords.size(), false );

  // determine the convex hull
  basicOps = find_convex_hull( xcoords, ycoords, chpoints );

  // print the points that make up the convex hull
  for( uint i = 0; i < chpoints.size(); i++ )
  {
    if( chpoints.at( i ))
      cout << xcoords.at( i ) << ',' << ycoords.at( i ) << ' ';
  }
  cout << endl << n << "\t" << basicOps << endl;
  return 0;
}

uint find_convex_hull( const vector< int > & xcoords,
                       const vector< int > & ycoords,
                       vector< bool > & chpoints )
{
  uint basicOpCount = 0;
  assert( xcoords.size() > 0 );

  if( xcoords.size() == 1 )
  {
    chpoints.at( 0 ) = true;
  }
  else if( xcoords.size() == 2 )
  {
    chpoints.at( 0 ) = chpoints.at( 1 ) = true;
  }
  else
  {
    // generate all pairwise points. only need each pair once
    for( uint point1 = 0; point1 < xcoords.size() - 1; point1++ )
    {
      for( uint point2 = point1 + 1; point2 < xcoords.size(); point2++ )
      {
        int a_coeff = ycoords.at( point2 ) - ycoords.at( point1 );
        int b_coeff = xcoords.at( point1 ) - xcoords.at( point2 );
        int c_coeff = xcoords.at( point1 ) * ycoords.at( point2 ) -
          xcoords.at( point2 ) * ycoords.at( point1 );
        
        uint positives = 0; // count the number of points with positive sign
        uint negatives = 0; // and with negative sign
        for( uint point3 = 0; point3 < xcoords.size(); point3++ )
        {
	  basicOpCount++;
          if( point3 != point1 && point3 != point2 )
          {
            int signvalue = a_coeff * xcoords.at( point3 ) + 
              b_coeff * ycoords.at( point3 ) - c_coeff;
            if( signvalue < 0 )
            {
              negatives++;
            }
            else if( signvalue > 0 )
            {
              positives++;
            }
          }
        }
        
        if( positives == 0 || negatives == 0 )
        {
          chpoints.at( point1 ) = chpoints.at( point2 ) = true;
        }
      } // for point2
    }
  }
  return basicOpCount;
}
