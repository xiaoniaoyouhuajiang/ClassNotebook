// To compile on linux with gcc: g++ Vector.cc main.cc
// When compiling you must specify all your .cc files

#include "Vector.h"

#include <cmath>
#include <sstream>
#include <cassert>

double const pi { std::acos(-1.0) };

using namespace std;
int main()
{
  Vector zero { };
  Vector e1 { 1.0, 0.0 };
  Vector e2 { 0.0, 1.0 };
  Vector v1 { 3.0, 4.0 };
  
  // check comparison
  assert( e1 == e1 );
  assert( e1 != e2 );

  // check default constructor
  assert( (Vector { 0.0, 0.0 } == zero) );
  
  // check addition
  assert( (e1 + e2 == Vector { 1.0, 1.0 }) );
  
  // check multiplication and addition
  assert( 3.0 * e1 + e2 * 4.0 == v1 );

  // check division, subtraction and negation
  assert( (-e1 - e2 / 2.0 == Vector { -1.0, -0.5 }) );
  
  // check length function
  assert( v1.length() == 5.0 );

  // check output stream operator
  {
    ostringstream oss { };
    assert( oss << e1 );
    assert( oss.str() == "(1, 0)");
  }
  {
    ostringstream oss { };
    assert( oss << 0.5 * e1 + 1.5 * e2 );
    assert( oss.str() == "(0.5, 1.5)" );
  }

  // check input stream operator
  {
    istringstream iss { "(0.25, 0.125)" };
    Vector v { };
    assert( iss >> v );
    assert( (v == Vector { 0.25, 0.125 }) );
  }
  { // check that we can read multiple values with arbitrary
    // whitespaces between each component
    istringstream iss { "( 1, 0)      (    2,     0 )       (   3.00000,   0.000 ) " };
    Vector v { };
    for (int i{0}; i < 3; ++i)
    {
      assert( iss >> v );
      assert( (v == Vector { i + 1.0, 0 }) ); 
    }
  }
  { // check that the stream operator checks for the parenthesis
    istringstream iss { "(1, 0" };
    Vector v { };
    assert( !(iss >> v) );
    assert( v == Vector { } );
  }
  { // check for error
    istringstream iss { "1 0" };
    Vector v { };
    assert( !(iss >> v) );
    assert( v == Vector { } );
  }
}
