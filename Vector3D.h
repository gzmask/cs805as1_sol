
// Billy Hamilton, student id 200288539
// Thursday, September 27th, 2012.
// CS405/805, Dr. XD Yang
// Assignment 1, question 2

// Vector3D.h -- contains the definition for the Vector3D class.
//  This class is used to represent a point or vector.

#ifndef VECTOR_3D_H
#define VECTOR_3D_H

#include <iostream>

// Defines a class to represent a 3D vector or point in 3D space

class Vector3D
{
public:
	// Default constructor (makes all components zero)
	Vector3D () :
		x (0),
		y (0),
		z (0)
	{ }

	// Initializing constructor
	Vector3D (	double new_x,
				double new_y,
				double new_z) :
		x (new_x),
		y (new_y),
		z (new_z)
	{ }

	// Copy constructor, assignment operator, destructor
	Vector3D ( const Vector3D& original );
	const Vector3D& operator= ( const Vector3D& original );
	~Vector3D ();

private:
	// Helper function for copy constructor and assignment operator
	void copy ( const Vector3D& original );

public:
	// Data members: a component in each dimension.
	// Made public so math is easier to read.
	double x, y, z;

public:
	////////////////////////////////////////////////////////////
	// member functions

	// magnitude -- find the magnitude (length) of the vector
	double magnitude ();

	// normalize -- returns a vector parallel to the given vector
	//  but of a unit length.
	Vector3D normalize ();

	////////////////////////////////////////////////////////////
	// static member functions

	// dot_product -- returns the dot product of u and v (a scaler)
	static double dot_product (Vector3D u, Vector3D v);

	// cross_product -- returns the cross product of u and v
	//  (a new vector which is perpendicular to both)
	static Vector3D cross_product (Vector3D u, Vector3D v);

	////////////////////////////////////////////////////////////
	// friend function

	// overloaded insertion operator for printing the vector easily
	friend std::ostream& operator << (std::ostream&, const Vector3D&);
};

#endif


