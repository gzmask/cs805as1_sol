
// Billy Hamilton, student id 200288539
// Thursday, September 27th, 2012.
// CS405/805, Dr. XD Yang
// Assignment 1, question 3

// Matrix4x4.h -- contains the definition for the Matrix4x4 class,
//  suitable for representing transformation matrices.

#ifndef MATRIX_4X4_H
#define MATRIX_4X4_H

#include <iostream>

class Vector3D;

class Matrix4x4
{
public:
	// Default constructor (makes all components zero)
	Matrix4x4 ();

	// Initializing constructor -- takes in sixteen values
	//  and assigns them to the elements of the array in order.
	Matrix4x4 (	double a1, double a2, double a3, double a4,
				double b1, double b2, double b3, double b4,
				double c1, double c2, double c3, double c4,
				double d1, double d2, double d3, double d4 );

	// Copy constructor, assignment operator, destructor
	Matrix4x4 ( const Matrix4x4& original );
	const Matrix4x4& operator= ( const Matrix4x4& original );
	~Matrix4x4 ();

private:
	// Data members: a 2D array to store the matrix elements.
	// element[row][column]
	double element [4][4];

	// Helper function for copy constructor and assignment operator
	void copy ( const Matrix4x4& original );
	
public:
	////////////////////////////////////////////////////////////
	// member functions
	
	// multiplication (or "concatenation") operation
	Matrix4x4 operator* ( const Matrix4x4& rhs ) const;

	// multiplication by a vector (for transforming points)
	Vector3D operator* ( const Vector3D& rhs ) const;

	// overloaded insertion operator for printing the matrix easily
	friend std::ostream& operator << (std::ostream&, const Matrix4x4&);

	// operation to find the transpose
	Matrix4x4 transpose () const;

	////////////////////////////////////////////////////////////
	// static member functions

	// generate a matrix to translate by the given x, y, and z
	static Matrix4x4 translation ( double x, double y, double z );
};

#endif


