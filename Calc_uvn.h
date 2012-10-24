
// Billy Hamilton, student id 200288539
// Thursday, September 27th, 2012.
// CS405/805, Dr. XD Yang
// Assignment 1, question 2

// Calc_uvn.h -- contains the prototype for the function to calculate u, v, and n.

#ifndef CALC_UVN_H
#define CALC_UVN_H

#include "Vector3D.h"

// This function finds three orthogonal unit vectors to form the basis of
// a coordinate system based on a given view plane normal (V1) and an "up"
// vector (V2).
void calculate_uvn ( Vector3D  V1,	// in
					 Vector3D  V2,	// in
					 Vector3D& u,	// out
					 Vector3D& v,	// out
					 Vector3D& n  );// out

#endif