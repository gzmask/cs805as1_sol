
// Billy Hamilton, student id 200288539
// Thursday, September 27th, 2012.
// CS405/805, Dr. XD Yang
// Assignment 1, question 3

// Implementation of the Vector3D class, used to represent
// a three dimensional point or vector.

#include "Vector3D.h"
#include <cmath>
#include <iostream>
#include <iomanip>

using namespace std;

///////////////////////////////////////////////////////////////////////
// canonical functions

// copy constructor
Vector3D::Vector3D ( const Vector3D& original )
{
	copy(original);
}

// assignment operator
const Vector3D& Vector3D::operator= ( const Vector3D& original )
{
	if(this != &original)
	{
		copy(original);
	}
	return *this;
}

// Nothing to dealloc in destructor -- all var's are automatic.
Vector3D::~Vector3D ()
{ }

// helper functions for copy constructor and assignment operator
void Vector3D::copy ( const Vector3D& original )
{
	x = original.x;
	y = original.y;
	z = original.z;
}

//////////////////////////////////////////////////////////////////////
// other class functions

double Vector3D::magnitude ()
{
	// The magnitude (length) of a vector v is found as the
	// square root of the sum of the squares of its components.
	return sqrt(  (x*x)	+ (y*y)	+ (z*z) );
}

Vector3D Vector3D::normalize ()
{
	// Vector is normallized by dividing each component by the
	// magnitude of the original vector.
	double m = magnitude();
	return Vector3D( x/m, y/m, z/m );
}

//////////////////////////////////////////////////////////////////////
// static functions

double Vector3D::dot_product (Vector3D u, Vector3D v)
{
	// the dot product of u and v is found as the sum of the
	// products of the corresponding components.
	return (  (u.x * v.x)
		    + (u.y * v.y)
			+ (u.z * v.z) );
}

Vector3D Vector3D::cross_product (Vector3D u, Vector3D v)
{
	// We know the crossproduct can be found as the following determinant:
	//
	//          | i  j  k  |
	//  u x v = | ux uy uz |
	//          | vx vy vz |
	//
	// (where i, j, and k are unit vectors in the x, y, and z directions)
	//
	// A cofactor expansion along the first row gives us our formula. 

	return Vector3D( (u.y * v.z) - (v.y * u.z),
					 (u.z * v.x) - (v.z * u.x),
					 (u.x * v.y) - (v.x * u.y)  );
}

///////////////////////////////////////////////////////////////
// Friend function

// Output the vector in on a single line.
// Fixed precision is used to make results easier to read.
ostream& operator<< (ostream& out, const Vector3D& u)
{
	out << fixed << setprecision(3);
	out << "(" << setw(8) << u.x << ", "
			   << setw(8) << u.y << ", "
			   << setw(8) << u.z << ")";

	return out;
}



