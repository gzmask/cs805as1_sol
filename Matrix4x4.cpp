
// Billy Hamilton, student id 200288539
// Thursday, September 27th, 2012.
// CS405/805, Dr. XD Yang
// Assignment 1, question 3

// Matrix4x4.cpp -- implementation of the Matrix4x4 class,
//  used for transformation matrices.

#include "Matrix4x4.h"
#include "Vector3D.h"
#include <iostream>
#include <iomanip>
#include <cassert>

using namespace std; // for ostreams

///////////////////////////////////////////////////////////////////////
// canonical functions

// Default constructor
Matrix4x4::Matrix4x4 ()
{
	// fill all elements with zeroes
	for (unsigned int i = 0; i < 4; i++)
		for (unsigned int j = 0; j < 4; j++)
			element[i][j] = 0;
}

// Initializing constructor -- takes in sixteen values
//  and assigns them to the elements of the array in order.
Matrix4x4::Matrix4x4 ( double a1, double a2, double a3, double a4,
					   double b1, double b2, double b3, double b4,
					   double c1, double c2, double c3, double c4,
					   double d1, double d2, double d3, double d4 )
{
	// First row
	element[0][0] = a1;
	element[0][1] = a2;
	element[0][2] = a3;
	element[0][3] = a4;

	// Second row
	element[1][0] = b1;
	element[1][1] = b2;
	element[1][2] = b3;
	element[1][3] = b4;

	// First row
	element[2][0] = c1;
	element[2][1] = c2;
	element[2][2] = c3;
	element[2][3] = c4;

	// First row
	element[3][0] = d1;
	element[3][1] = d2;
	element[3][2] = d3;
	element[3][3] = d4;
}

// copy constructor
Matrix4x4::Matrix4x4 ( const Matrix4x4& original )
{
	copy(original);
}

// assignment operator
const Matrix4x4& Matrix4x4::operator= ( const Matrix4x4& original )
{
	if(this != &original)
	{
		copy(original);
	}
	return *this;
}

// Nothing to dealloc in destructor -- all var's are automatic.
Matrix4x4::~Matrix4x4 ()
{ }

// helper functions for copy constructor and assignment operator
void Matrix4x4::copy ( const Matrix4x4& original )
{
	// fill all elements with values from original
	for (unsigned int i = 0; i < 4; i++)
		for (unsigned int j = 0; j < 4; j++)
			element[i][j] = original.element[i][j];
}

////////////////////////////////////////////////////////////////////
// Class functions

// multiplication (or "concatenation") operation
Matrix4x4 Matrix4x4::operator* ( const Matrix4x4& rhs ) const
{
	Matrix4x4 temp;

	// calculate each element of the resulting matrix
	for (unsigned int i = 0; i < 4; i++)
	{
		for (unsigned int j = 0; j < 4; j++)
		{
			// The element at [i][j] is formed by the sum of the
			//  products of the elements of the ith row of the lhs
			//  matrix with the corresponding elements of the jth
			//  column of the rhs matrix.
			temp.element[i][j] =   ( element[i][0] * rhs.element[0][j] )
								 + ( element[i][1] * rhs.element[1][j] )
								 + ( element[i][2] * rhs.element[2][j] )
								 + ( element[i][3] * rhs.element[3][j] );
		}
	}

	return temp;
}

// multiplication with a vector -- used to transform points
Vector3D Matrix4x4::operator* ( const Vector3D& rhs ) const
{
	// The vector class is three-dimensional, but we add a fourth
	// (w) component where w = 1.  This allows us to perform
	// matrix multiplication.  We then convert the result back
	// into a regular three-dimensional vector by dividing each
	// component by the new value of w.
	double new_x =  element[0][0] * rhs.x
				  + element[0][1] * rhs.y
				  + element[0][2] * rhs.z
				  + element[0][3];
	double new_y =  element[1][0] * rhs.x
				  + element[1][1] * rhs.y
				  + element[1][2] * rhs.z
				  + element[1][3];
	double new_z =  element[2][0] * rhs.x
				  + element[2][1] * rhs.y
				  + element[2][2] * rhs.z
				  + element[2][3];
	double new_w =  element[3][0] * rhs.x
				  + element[3][1] * rhs.y
				  + element[3][2] * rhs.z
				  + element[3][3];

	// Normallize by dividing by found value of w
	new_x = new_x / new_w;
	new_y = new_y / new_w;
	new_z = new_z / new_w;

	// Return as an ordinary 3D vector.
	return Vector3D (new_x, new_y, new_z);
}

// Return a copy of the matrix with rows and colums switched.
Matrix4x4 Matrix4x4::transpose () const
{
	return Matrix4x4 ( element[0][0], element[1][0], element[2][0], element[3][0],
					   element[0][1], element[1][1], element[2][1], element[3][1],
					   element[0][2], element[1][2], element[2][2], element[3][2],
					   element[0][3], element[1][3], element[2][3], element[3][3]  );
}

///////////////////////////////////////////////////////////////////////////
// Static functions

// generate a matrix to translate by the given x, y, and z
Matrix4x4 Matrix4x4::translation ( double x, double y, double z )
{
	return Matrix4x4 ( 1.0, 0.0, 0.0, x,
					   0.0, 1.0, 0.0, y,
					   0.0, 0.0, 1.0, z,
					   0.0, 0.0, 0.0, 1.0  );
}

// friend function -- overloaded insertion (output) operator
ostream& operator<< (ostream& out, const Matrix4x4& m)
{
	out << fixed << setprecision(3);
	for (unsigned int i = 0; i < 4; i++)
	{
		for (unsigned int j = 0; j < 4; j++)
		{
			out << setw(8) << m.element[i][j];
		}
		out << endl;
	}
	return out;
}

